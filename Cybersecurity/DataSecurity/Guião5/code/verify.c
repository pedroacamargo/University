#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

// Convert hash bytes to hex string
void to_hex_string(const unsigned char *hash, char *output, size_t length) {
    for (size_t i = 0; i < length; i++)
        sprintf(output + (i * 2), "%02x", hash[i]);
    output[length * 2] = '\0';
}

// Hash a file with a salt
int hash_file(const char *path, unsigned char output[SHA256_DIGEST_LENGTH]) {
    const unsigned char salt[] = "salt1234"; 
    size_t salt_len = strlen((const char *)salt);

    FILE *file = fopen(path, "rb");
    if (!file) return 0;

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    // Add the salt to the beginning of the hash
    SHA256_Update(&ctx, salt, salt_len);

    unsigned char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), file)) != 0) {
        SHA256_Update(&ctx, buffer, bytes);
    }

    SHA256_Final(output, &ctx);
    fclose(file);
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file;
    file = fopen("file_shadow", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and process the file content
    char buffer[256];
    int found = 0;

    const char *target = getenv("USER");
    if (target == NULL) {
        fprintf(stderr, "USER environment variable not set.\n");
        return 1;
    }


    // Process each line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        unsigned char hash[SHA256_DIGEST_LENGTH];
        char hash_str[SHA256_DIGEST_LENGTH * 2 + 1];

        // Check if this line corresponds to the target user
        if (strncmp(buffer, target, strlen(target)) == 0 && buffer[strlen(target)] == ':') {

            // Check if file is already protected
            char *token = strtok(buffer, ":");
            token = strtok(NULL, ":"); // skip username


            while (token != NULL) {
                char *path = token;
                token = strtok(NULL, ":");
                if (token == NULL) break; // malformed line
                char *stored_hash = token;

                if (strcmp(path, argv[1]) == 0) {
                    found = 1;
                    unsigned char current_hash[SHA256_DIGEST_LENGTH];
                    char current_hash_str[SHA256_DIGEST_LENGTH * 2 + 1];

                    if (!hash_file(argv[1], current_hash)) {
                        printf("Cannot read file: %s\n", argv[1]);
                        fclose(file);
                        return 0;
                    }

                    to_hex_string(current_hash, current_hash_str, SHA256_DIGEST_LENGTH);

                    if (strcmp(current_hash_str, stored_hash) == 0) {
                        printf("Integrity OK for %s\n", argv[1]);
                    } else {
                        printf("Integrity FAILED for %s\n", argv[1]);
                        printf("Stored:  %s\nCurrent: %s\n", stored_hash, current_hash_str);
                    }
                    fclose(file);
                    return 1;
                }
            }
        }
    }
    
    // If not found, append a new line
    if (!found) {
        printf("No entry found for file: %s\n", argv[1]);
        fclose(file);
        return 0;
    }

    fclose(file);

    return EXIT_SUCCESS;
}