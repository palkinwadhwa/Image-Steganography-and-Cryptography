//reading size of image file
#include<string.h>
#define MAXSIZE 100
int size_of_image(FILE *filePointer1)
{
    int width, height;

    fseek(filePointer1, 0x12, SEEK_SET);    //Seek to the Width position
    fread(&width, sizeof(int), 1, filePointer1);    //Reading Width
    fread(&height, sizeof(int), 1, filePointer1);    //Read height
    printf("Dimensions of the Image is %d x %d \n", width, height);
    fseek(filePointer1, 0L, SEEK_SET);    //Seek to the start position

    return ((width * height * 3) / 8); //multiplied by 3 (RGB) and divided by 8 (bit to byte)
}


//Entering Secret Message to file
void secret_text(FILE *filePointer2)
{
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
   
    fputs(y,filePointer2);
    printf("1. Your original message is :%s",plain);
    printf("\n2. Message after encryption using Affine Cipher Algorithm is:%s",y);
   
}

//Size Of The Secret Message
int secret_text_size(FILE *filePointer2)
{
    int size_txt;
    fseek(filePointer2, 0L, SEEK_END);
    size_txt = ftell(filePointer2);
    fseek(filePointer2, 0L, SEEK_SET);
    return size_txt;
}
//bits of text file
int get_bit(char byte, int bit)
{
    return ((byte >> 8 - bit) & 1);
}

//encryption of message
void stega_encrypt(FILE *filePointer1, FILE *filePointer2, FILE *filePointer3)
{
    char file_buff = 0, msg_buff = 0, ch;    //temp var for one byte from file and msg
    int i;
    int bit_msg;
    while((msg_buff = fgetc(filePointer2)) != EOF)
    {
        for(i = 1; i <= 8; i++)
        {
            file_buff = fgetc(filePointer1);

            int file_byte_lsb = (file_buff & 1);

            bit_msg = get_bit(msg_buff, i);

            if(file_byte_lsb == bit_msg)
            {
                fputc(file_buff, filePointer3);
            }
            else
            {
                if(file_byte_lsb == 0)
                    file_buff = (file_buff | 1);
                else
                    file_buff = (file_buff ^ 1);

                fputc(file_buff, filePointer3);
            }
        }
    }

    /*copying rest of data */
    while(!feof(filePointer1))
    {
        char tmp_cpy = fgetc(filePointer1);
        fputc(tmp_cpy,filePointer3);

    }

    if(msg_buff == EOF)
        printf("\n3. Secret encrypted message embedded/encoded in the image successfully.\n");
    else
        printf("\n Failed Encrypting \n");
}
//Encryption For Strings
void string_encrypt(char *str,FILE *filePointer1, FILE *filePointer3)
{

    char file_buff, msg_buff;    //temp var for one byte from file and msg
    int i, j = 0;
    int bit_msg;
    while((msg_buff = str[j]) != '\0')
    {
        for(i = 1; i <= 8; i++)
        {
            file_buff = fgetc(filePointer1);

            int file_byte_lsb = (file_buff & 1);

            bit_msg = get_bit(msg_buff, i);

            if(file_byte_lsb == bit_msg)
            {
                fputc(file_buff, filePointer3);
            }
            else
            {
                if(file_byte_lsb == 0)
                    file_buff = (file_buff | 1);
                else
                    file_buff = (file_buff ^ 1);

                fputc(file_buff, filePointer3);
            }
        }
        j++;
    }
}
//Encryption For Numbers
void size_encrypt(int num,FILE *filePointer1, FILE *filePointer3)
{

    char file_buff;   
    int i, j = 0;
    int bit_msg;

    for(i = 1; i <= 8; i++)
    {
        file_buff = fgetc(filePointer1);

        int file_byte_lsb = (file_buff & 1);

        bit_msg = get_bit(num, i);

        if(file_byte_lsb == bit_msg)
        {
            fputc(file_buff, filePointer3);
        }
        else
        {
            if(file_byte_lsb == 0)
                file_buff = (file_buff | 1);
            else
                file_buff = (file_buff ^ 1);

            fputc(file_buff, filePointer3);
        }
    }

}

int Encoding(char *argv_2,char *argv_3,char *argv_4)
{
    FILE *filePointer1, *filePointer2, *filePointer3;

    //opening Image File
    if((filePointer1 = fopen(argv_2, "r+")) == NULL)
    {
        printf("Could not open file %s.\nAborted\n", argv_2);
        return 1;
    }

    int size_image = size_of_image(filePointer1);
    printf("Total %d Characters can be stored in %s.\n", size_image, argv_2);

    //opening secret text file
    filePointer2 = fopen(argv_3, "w+");

    //Entering secret text to file
    secret_text(filePointer2);
   

    int size_txt = secret_text_size(filePointer2);
    printf("\nSize of The Secret Message is : %d\n", size_txt);

    //Comparing Image Size With Text
    if(size_image < size_txt)
    {
        printf("\n The Size Of Message Exceeds the Size of image \n");
        return 1;
    }

    //opening destination file
    filePointer3 = fopen(argv_4, "w+");
    if (filePointer3== NULL)
    {
        fprintf(stderr, "Cannot create output file %s\n",argv_4);
        exit(1);
    }

    //copying 54 header file
    int i, c = 0;
    char tmp_cpy;
    rewind(filePointer1);    //Goes back to the beginning of the file
    for(i = 0;i < 54; i++)
    {
        tmp_cpy = fgetc(filePointer1);
        fputc(tmp_cpy,filePointer3);
        c++;
    }

    //checking 54 bytes copyed or not
    if(i == c)
        printf("\n Sucessfully copied 54 header bytes \n");
    else
    {
        printf("\n Failed to copy 54 header bytes \n");
        return 0;
    }

    //For Magic String
    char magic_str[10];
    char magic;
    int size;

    printf("\nEnter The User-ID '#' or '$' Only : \t");

    for(i = 0; (magic = getchar()) != '\n'; i++)
    {
        if(magic == '#')
        {
            magic_str[i] = magic;
        }
        else if(magic == '$')
        {
            magic_str[i] = magic;
        }
        else
        {
            printf(" You Entered Wrong Characters \n");
            exit(2);
        }
    }

    magic_str[i] = '\0';
    size = strlen(magic_str);
    printf("Size Of the User-ID is : %d\n", size);
    size_encrypt(size,filePointer1,filePointer3);
    string_encrypt(magic_str,filePointer1,filePointer3);
    printf(" User-ID Encrypted \n");

    //FOR PASSWORD
    char str[20];
    printf("\nEnter the Password : \t");

    for (i=0;((str[i] = getchar()) != '\n');i++);
    str[i]= '\0';

    int size1;   
    size1 = strlen(str);
    printf("Size Of The Password is : %d\n", size1);
    size_encrypt(size1,filePointer1,filePointer3);
    string_encrypt(str,filePointer1,filePointer3);
    printf(" Password Encrypted \n");

    //Encryption for Message
    size_encrypt(size_txt,filePointer1,filePointer3);
    stega_encrypt(filePointer1,filePointer2,filePointer3);

    /*Clean up before exit */
    fclose(filePointer1);   
    fclose(filePointer2);
    fclose(filePointer3);

    return 0;

}


