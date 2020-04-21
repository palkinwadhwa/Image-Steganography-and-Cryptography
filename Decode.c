/* decryption of sizes */
void size_decryption(FILE *pointerFile1, int *size_txt)
{
    int file_buff = 0, i;
    int ch, bit_msg;
    for (i = 0; i < 8; i++)
    {
        ch = fgetc(pointerFile1);
        bit_msg = (ch & 1);
        if (bit_msg)
        {
            file_buff = (file_buff << 1) | 1;
        }
        else
        {
            file_buff = file_buff << 1;
        }
    }
    *size_txt = file_buff;
}

/* decryption of strings*/
void string_decryption(FILE *pointerFile1,char *strng,int size)
{
    int file_buff=0, i, j=0, k=0;
    int ch, bit_msg;
    for (i = 0; i < (size * 8); i++)
    {
        j++;
        ch = fgetc(pointerFile1);
        bit_msg = (ch & 1);
        if (bit_msg)
        {
            file_buff = (file_buff << 1) | 1;
        }
        else
        {
            file_buff = file_buff << 1;
        }

        if ( j == 8)
        {
            strng[k] =(char)file_buff;
            j=0;
            k++;
            file_buff = 0;
        }
    }
    strng[k] = '\0';
}
/* decryption of secret message*/
void secret_decryption(int size_txt, FILE *pointerFile1, FILE *pointerFile2)
{
    int file_buff=0, a, j = 0, k = 0;
    int ch,bit_msg;
    char output[250] = {0};
    for (a = 0; a < (size_txt * 8); a++)
    {
        j++;
        ch = fgetc(pointerFile1);
        bit_msg = (ch & 1);
        if (bit_msg)
        {
            file_buff = (file_buff << 1) | 1;
        }
        else
        {
            file_buff = file_buff << 1;
        }

        if ( j == 8)
        {
            putc(file_buff, pointerFile2);
            output[k++] = file_buff;
            j=0;
            file_buff = 0;
        }
    }

   

    const int A = 7;
    const int B = 6;

    char plain[] = "THIS IS OUR MINOR PROJECT BASED ON IMAGE STEGANOGRAPHY AND CRYPTOGRAPHY USING LSB AND AFFINE CIPHER ALGORITHM";
 
     static char y[MAXSIZE];
    int i;
      for (i = 0; i < strlen(plain); i++)
        {
                if (plain[i] != ' ')
         // added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
                  y[i] = y[i] + (char) ((((A * (plain[i]-'A') ) + B) % 26) + 'A');
              else
                  y[i] +=plain[i];
            }
   
// decrypt
static char d[MAXSIZE];
 int a_inverse = 0;
   int flag = 0;
   i = 0;
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
   for (i = 0;i<strlen(output);i++)
   {
       if(output[i]!=' ')
           d[i] = d[i] + (char) (((a_inverse * ((output[i]+'A' - B)) % 26)) + 'A');
        else
         //else append space character
         d[i] += output[i];
   }
printf("4. Message after encyption using Affine was:%s",output);
printf("\n5. Message after decryption from the image is: %s\n\n",d);

}


int Decode(char *argv_2, char *argv_4)
{
    FILE *pointerFile1, *pointerFile2;
   
    int size, size1, size_txt;

    //opening Image File
    if((pointerFile1 = fopen(argv_2, "r")) == NULL)
    {
        printf("Could not open file %s.\nAborting\n", argv_2);
        return 1;
    }

    fseek(pointerFile1,54 ,SEEK_SET);
   
    if((pointerFile2 = fopen(argv_4, "w+")) == NULL)
    {
        printf("Could not open file %s.\nAborting\n", argv_4);
        return 1;
    }

    //magic str
    char magic_strn[20], magic_strn1[20], strng[20];
    int j;

    size_decryption(pointerFile1,&size);
    string_decryption(pointerFile1,magic_strn,size);

    printf("\nEnter the User-ID : \t");
    for(j = 0;(magic_strn1[j] = getchar()) != '\n'; j++);
    magic_strn1[j]= '\0';

    int temp;
    temp = strcmp(magic_strn1, magic_strn);

    if(temp)
    {
        printf("\n\t Entered User-ID String \n");
        return 0;
    }
    else
        printf("\n\t!!! User-ID Accepted !!!\n\n");

    //password
    char passwd[20], passwd_str[20];

    size_decryption(pointerFile1,&size1);
    string_decryption(pointerFile1,passwd_str,size1);

    printf("Enter The Password : \t");
    scanf("%s", passwd);

    temp = strcmp(passwd,passwd_str);

    if(temp)
    {
        printf("\n\t Entered Wrong Password \n");
        return 0;
    }
    else
        printf("\n\t Password Accepted \n");

    /*Secret Text */
    size_decryption(pointerFile1, &size_txt);
    secret_decryption(size_txt, pointerFile1, pointerFile2);

    printf(" The Secret Text Is Copied To : %s\n\n", argv_4);

    /* closeing files */
    fclose(pointerFile1);

}
