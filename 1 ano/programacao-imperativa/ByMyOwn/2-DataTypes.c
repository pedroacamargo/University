#include <stdio.h>
#include <stdbool.h> // type this to work with booleans

int main() {
    char a = 'C'; // single character %c
    char b[] = "Bro"; // array of charaters %s

    float c = 3.141592; // 4 bytes (32 bits of precision) 6 - 7 digits %f
    double d = 3.141583653689793; // 8 bytes (64 bits of precision) 15 - 16 digits %lf

    bool e = true; // 1 byte (true or false) %d 1 = True || 0 = False

    char f = 100; // 1 byte (-128 to +127) %d or %c
    unsigned char g = 255; // 1 byte (0 to +255) %d or %c

    short int h = 32767; // 2 bytes (-32,768 to +32,767) %d
    unsigned short int i = 65535; // 2 bytes (0 to +65,535) %d

    int j = 2047843700; // 4 bytes (-2,147,483,648 to + 2,147,483,647) %d
    unsigned int k = 4047843700; // 4 bytes (0 to +4,294,967,295) %u

    long long int l = 922293994748971207821; // 8 bytes (-9 quintillion to +9 quintillion) %lld
    unsigned long int l = 922293994748971207821U; // 8 bytes (0 to +18 quintillion) %lld

}