#include <stdio.h>
#include <string.h>

int main()
{
    char str[100] = "this subject is awful";
    int length = sizeof(str);
   
    char encrypted[length];
    for(int i = 0; i < length; i++)
        encrypted[i] = str[i] + 5; //the key for encryption is 3 that is added to ASCII value

    printf("\nEncrypted string: %s\n", encrypted);

    char decrypted[length];
    for(int j = 0; j < length; j++)
        decrypted[j] = encrypted[j] - 5; //the key for encryption is 3 that is subtracted to ASCII value

    printf("\nDecrypted string: %s\n", decrypted);

   return 0;
}
