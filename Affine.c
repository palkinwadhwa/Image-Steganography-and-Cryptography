#include<stdio.h>
#include<string.h>

//Key values of a and b 

const int A = 17; 
const int B = 20;

#define MAXSIZE 100

//Driver Program 

int main(void) 
{ 
    char Plaintext[] = "We are using Encryption in Steganography using Least Bit Significant Algorithm."; 
    printf("The text which is being encrypted is: %s", Plaintext );
    static char Ciphered[MAXSIZE];
    int i;
    char y;
    char index;
    for (i = 0; i < strlen(Plaintext) - 1; i++) 
	{
        if (Plaintext[i] == ' ') 
	{
            Ciphered[i] = ' ';
        } else 
	{
            index = (int)Plaintext[i] - 'a';
            y = (A * index + B) % 26;
            Ciphered[i] = (char)y + 97;
        }
    }
    printf("\nThe encrypted text is : %s \n",Ciphered);

	return 0; 
}
