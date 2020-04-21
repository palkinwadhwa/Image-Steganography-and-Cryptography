#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Encode.c"
#include "Decode.c"

//reading size of image file
int size_of_image(FILE *filePointer1);

//Entering Secret Message to file
void secret_text(FILE *filePointer2);

//Size Of The Secret Message
int secret_text_size(FILE *filePointer2);

//bits of text file
int get_bit(char byte, int bit);

//encription of message
void stega_encrypt(FILE *filePointer1, FILE *filePointer2, FILE *filePointer3);

//Encription For Strings
void string_encrypt(char *str,FILE *filePointer1, FILE *filePointer3);

//Encription For Numbers
void size_encrypt(int num,FILE *filePointer1, FILE *filePointer3);

/* decryption of sizes */
void size_decryption(FILE *pointerFile1, int *size_txt);

/* decryption of strings*/
void string_decryption(FILE *pointerFile1,char *strng,int size);

/* decryption of secret message*/
void secret_decryption(int size_txt,FILE *pointerFile1, FILE *pointerFile2);
