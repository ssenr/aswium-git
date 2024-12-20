#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void html()
{

}

char* read_html(const char* path){
    FILE *file = fopen(path, "r");

    if (file == NULL){
        printf("Error opening file\n");
        return "";
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* file_data = malloc(file_size+1); //reads the whole file immediately
    size_t len = fread(file_data, 1, file_size, file);
    fclose(file);
    char* i;
    
    //removes all \n and takes care of the ""?      should work in theory?
    for (i = file_data; i* != '\0'; i++){
        if (i* == '\n'){
            i* = '';
        }
        else if(i* == '"')
            i* = '\"';
    }

    file_data = i;

    file_data[len] = '\0';
    return file_data;
}