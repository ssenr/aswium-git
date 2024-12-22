#include <stdio.h>
#include <stdlib.h>
#include <string.h>





char* get_file_ext(const char* fn)
{
    char* cpy = strdup(fn);
    if (!cpy) return "";

    char* ext = strrchr(cpy, '.');
    if (ext == NULL)
    {
        free(cpy);
        return "";
    }
    memmove(ext, ext+1, strlen(ext));
    return ext;
}


char* read_html(const char* path){
    FILE *file = fopen(path, "rb");

    
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
    
    //char* final;
    char* delim = "\n";
    char* token;
    char* final = (char*)malloc(len*sizeof(char));
    
   // printf("%s", file_data);
    token = strtok(file_data, delim); 
    //printf("%s", token);
 
    while (token != NULL){
        //printf("here");
        strcat(final, token);
        //printf("%s",token);
        token = strtok(NULL, delim);
    }//so delimiter then append for final

    free(file_data);
    free(token);

    final[len] = '\0';
    return final;
}



void html()
{
// read only html so seperate everything else
    char* path = "test.html";

    
    if (strcmp(get_file_ext(path) ,"html")==0){
        char* html_content = read_html(path);
        printf("\n%s", html_content);
    }
   
}