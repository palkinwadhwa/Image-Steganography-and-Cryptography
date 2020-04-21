#include<stdio.h>
#include<string.h>

//Key values of a and b 
const int A = 7; 
const int B = 6;
#define MAXSIZE 100
//Driver Program 
int main(void) 
{ 
	char fp2[] = "SIDDHI GUPTA"; 
 
 	static char y[MAXSIZE];
 {  
	int i;
	    for (i = 0; i < strlen(fp2); i++) 
	{
	        if (fp2[i] != ' ')
         // added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
          y[i] = y[i] + (char) ((((A * (fp2[i]-'A') ) + B) % 26) + 'A');
          else
          y[i] +=fp2[i];
        }
 }
    printf("Encrypted text is : %s\n",y);
    
}


