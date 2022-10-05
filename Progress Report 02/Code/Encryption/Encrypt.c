#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{

    double time_spent = 0.0;
    clock_t begin = clock();


    char str[4000] = "0 0 0 0 0 -0,01 0 0 -0,02 0 0,01 0 0 0 0 0 0,01 0 0 0 0 0 0,02 0 0 0 -0,01 0 -0,01 0,01 0,01 0 -0,01 0 0 0 0,01 0 0 0 0 0 0 0 -0,01 0 0 0 0 0 0 0 -0,01 -0,01 0 0 0 -0,01 0 0 0 0 0 -0,02 -0,01 -0,01 0";
    int length = sizeof(str);
   
    char encrypted[length];
    for(int i = 0; i < length; i++)
        encrypted[i] = str[i] + 5; //the key for encryption is 3 that is added to ASCII value

    printf("\nEncrypted string: %s\n", encrypted);

    char decrypted[length];
    for(int j = 0; j < length; j++)
        decrypted[j] = encrypted[j] - 5; //the key for encryption is 3 that is subtracted to ASCII value

    printf("\nDecrypted string: %s\n", decrypted);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);

   return 0;
}
