#include <stdio.h>
#include <string.h>

int main() {
    char string1[] = "Bro";
    char string2[] = "Code";

    strlwr(string1); // converts a string to lowercase
    strupr(string2); // converts a string to uppercase
    strcat(string1, string2); // appends string2 to end of string1
    strncat(string1, string2, 1); // appends n characters from strin2 to string1
    strcpy(string1, string2); // copy string2 to string1
    strncpy(string1, string2, 4); // copy n characters from string2 to string1


    strset(string1, '?'); // sets all characters of a string to a given character
    strnset(string1, 'x', 1); // sets first n characters of a string to a given character
    strrev(string1); // reverses a string

    int result = strlen(string1); // return string length as int
    int result2 = strcmp(string1,string2); //string compare all characters // if str1 == str2 then 0, else 1
    int result3 = strncmp(string1, string2, 1); // string compare n characters
    int result4 = strcmpi(string1, string2); // string compare all (ignore case)
    int result5 = strnicmp(string1, string2, 1); // string compare n characters (ignore case)


    printf("%d",result);

    printf("%s", string1);
}