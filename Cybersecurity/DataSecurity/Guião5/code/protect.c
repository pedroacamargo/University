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

int hash_file(const char *path, unsigned char output[SHA256_DIGEST_LENGTH]) {
    FILE *file = fopen(path, "rb");
    if (!file) return 0;

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

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

    FILE *tmpfile = fopen("file_shadow.tmp", "w");
    if (tmpfile == NULL)
    {
        perror("Error opening temporary file");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Read and process the file content
    char buffer[2000];
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
            printf("%s\n", buffer);

            // Check if file is already protected]
            char *token = strtok(strdup(buffer), ":");
            char *name = token;
            while (token != NULL) {
                if (argv[1] != NULL && strcmp(token, argv[1]) == 0) {
                    printf("File is already protected: %s\n", argv[1]);
                    fclose(file);
                    fclose(tmpfile);
                    remove("file_shadow.tmp");
                    return EXIT_SUCCESS;
                }
                token = strtok(NULL, ":");
            }


            // Found the matching user — append our text
            if (hash_file(argv[1], hash)) {
                to_hex_string(hash, hash_str, SHA256_DIGEST_LENGTH);
                fprintf(tmpfile, "%s:%s:%s\n", buffer, argv[1], hash_str);
                printf("Added: %s:%s:%s\n", buffer, argv[1], hash_str);
            } else {
                fprintf(stderr, "Error hashing file: %s\n", argv[1]);
                fclose(file);
                fclose(tmpfile);
                return EXIT_FAILURE;
            }

            printf("Modified line for user: %s\n", target);
            found = 1;
        } else {
            // Just copy unchanged
            fprintf(tmpfile, "%s\n", buffer);
        }
    }
    
    // If not found, append a new line
    if (!found) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        char hash_str[SHA256_DIGEST_LENGTH * 2 + 1];
        if (hash_file(argv[1], hash)) {
            to_hex_string(hash, hash_str, SHA256_DIGEST_LENGTH);
            fprintf(tmpfile, "%s:%s:%s\n", target, argv[1], hash_str);
            printf("Appended new line for user: %s\n", target);
        }
    }


    fclose(file);
    fclose(tmpfile);

    remove("file_shadow");
    rename("file_shadow.tmp", "file_shadow");

    return EXIT_SUCCESS;
}