#include<stdio.h>
#include<string.h>

//Key values of a and b 
const int A = 7; 
const int B = 6;
#define MAXSIZE 100
//Driver Program 
int main(void) 
{ 
	char pf2[] = "SIDDHI GUPTA"; 
 
 	static char y[MAXSIZE];
   {  
	int i;
    	for (i = 0; i < strlen(pf2); i++) 
	{
        	if (pf2[i] != ' ')
         		// added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
          		y[i] = y[i] + (char) ((((A * (pf2[i]-'A') ) + B) % 26) + 'A');
         	else
          		y[i] +=pf2[i];
   	}
    }

    
// decrypt
static char d[MAXSIZE];
 int a_inverse = 0;
   int flag = 0;
   int i = 0;
   /*Find a^-1 (the multiplicative inverse of a
   in the group of integers modulo m.)*/
   for (i = 0; i < 26; i++)
{
      flag = (A * i) % 26;
      /*Check if (a * i) % 26 == 1,
      then i will be the multiplicative inverse of a*/
      if (flag == 1) 
    {
         a_inverse = i;
    }
}
   for (i = 0;i<strlen(y);i++)
   {
   	if(y[i]!=' ')
   		d[i] = d[i] + (char) (((a_inverse * ((y[i]+'A' - B)) % 26)) + 'A');
        else
         //else append space character
         d[i] += y[i];
   }
 printf("Decrypted text is :%s\n",d);
	return 0; 
}
