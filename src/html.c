//placeholder
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_LINE 1024
#define MAX_CHAR 1024

void html()
{

}

char* read_html(const char* path){
    FILE * fileptr = fopen("file.txt","r");
    if (fileptr == NULL){
        printf("Error opening file// check permissions or path");
        return NULL;
    }
    char ** lines; //pointer to a pointer to a char
    lines = malloc(sizeof(char*) * MAX_LINE);
    size_t total_lines = 0;
    size_t total_char = 0;

    char letter;
    //read each char until eof

    do{
        letter = fgetc(fileptr);
        
        if (ferror(fileptr)){
            printf("Error reading from file");
            return NULL;
        }
        if(feof(fileptr)){
            if(total_char != 0){
                lines[total_lines] = realloc(lines[total_lines], total_char+1); //rellocate mem
                lines[total_lines][total_char] = '\0';

                total_lines++;
            }
            break;

        }
        if (total_char ==0) lines[total_lines] = malloc(MAX_CHAR);

        lines[total_lines][total_char] = letter;
        total_char++;
        if(letter == '\n'){
            lines[total_lines] = realloc(lines[total_lines], total_char+1);
            lines[total_lines][total_char] = '\0';

            total_lines++;

            total_char = 0; //reset to another line
        }
        else if (total_char % MAX_CHAR == 0){
            size_t updated = total_char + MAX_CHAR;
            lines[total_lines] = realloc(lines[total_lines], updated);
        }
    }
    while (true){
        
    }
    
}