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

    FILE *tmpfile = fopen("file_shadow.tmp", "w");
    if (tmpfile == NULL)
    {
        perror("Error opening temporary file");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Read and process the file content
    char buffer[256];
    int updated = 0;

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
            
            // Break user line into tokens
            char tempbuf[2048];
            strcpy(tempbuf, buffer);

            char *tokens[256];
            int count = 0;
            char *tok = strtok(tempbuf, ":");
            while (tok && count < 256) {
                tokens[count++] = tok;
                tok = strtok(NULL, ":");
            }

            fprintf(tmpfile, "%s", tokens[0]); // username

            for (int i = 1; i < count; i += 2) {
                if (i + 1 >= count) break; // malformed pair
                char *path = tokens[i];
                char *old_hash = tokens[i + 1];

                if (strcmp(path, argv[1]) == 0) {
                    unsigned char hash[SHA256_DIGEST_LENGTH];
                    char hash_str[SHA256_DIGEST_LENGTH * 2 + 1];
                    if (hash_file(argv[1], hash)) {
                        to_hex_string(hash, hash_str, SHA256_DIGEST_LENGTH);
                        fprintf(tmpfile, ":%s:%s", path, hash_str);
                        printf("Updated hash for %s for user %s\n", path, target);
                        updated = 1;
                    } else {
                        fprintf(stderr, "Failed to hash %s\n", path);
                        fprintf(tmpfile, ":%s:%s", path, old_hash);
                    }
                } else {
                    fprintf(tmpfile, ":%s:%s", path, old_hash);
                }
            }
            fprintf(tmpfile, "\n");
        } else {
            fprintf(tmpfile, "%s\n", buffer);
        }
    }
    
    if (updated)
        printf("✅ Hash updated successfully.\n");
    else
        printf("⚠️ File not found in file_shadow for update.\n");

    fclose(file);
    fclose(tmpfile);

    remove("file_shadow");
    rename("file_shadow.tmp", "file_shadow");

    return EXIT_SUCCESS;
}