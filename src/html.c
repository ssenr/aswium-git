#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void html()
{
// read only html so seperate everything else
    char* path = "alksdhlkajsfdh.html";
    char* file_name = getfile_name(path); //change later maybe
    if (get_file_ext(file_name) == "html"){
        char* html_content = read_html(path);
    }
}

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

char* get_file_name(const char* fn)
{
    char *cpy = strdup(fn);
    if (!cpy)
        return "";

    char *ext = strrchr(cpy, '/');
    if (ext == NULL)
    {
        free(cpy);
        return "";
    }
    memmove(ext, ext + 1, strlen(ext));
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
    char* i;
    
    //removes all \n and takes care of the ""?      should work in theory?
    for (i = file_data; i* != '\0'; i++){
        if (i* == '\n'){
            i* = '';
        }
        else if(i* == '"')
            i* = append('\"', i*);
    }

    file_data = i;

    file_data[len] = '\0';
    return file_data;
}

//theoretically will work
char* append(const char* value, const char* origin){
    size_t new = strlen(origin);
    char* appended = (char*)malloc(new+1);
    appended[0] = '\"';
    appended[1] = origin;
    
    return appended;

}

