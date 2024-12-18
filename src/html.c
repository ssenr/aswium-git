//placeholder
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_LINE 1024
#define MAX_CHAR 1024

void html()
{

}

char* read_html(const char* path){
    FILE * fileptr = fopen(path,"r");
    char* result = "";

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
    while (true);

    lines = realloc(lines,sizeof(char*) * total_lines);

    strcpy(result, lines[0]);
    for (size_t i =1; i< total_lines; i++){
        printf("%s",lines[i]);
        strcat(result, lines[i]);

    }
    free(result);

    for (size_t i =0; i< total_lines; i++)free(lines[i]);

    fclose(fileptr);

    
    return result;
}