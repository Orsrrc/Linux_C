#include "generatePassword.h"


void* generatePassword(char* plainText)
{

    for(int i = 0;;i++)
    {
        if(plainText[i] == '\0')
        {   
            return plainText;
        }
    plainText[i] = (char)( (int)plainText[i] + ( rand() % 10) );
    //printf("%c\n", plainText[i]);
    }
}
