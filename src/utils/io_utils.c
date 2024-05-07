#include<stdio.h>
#include"io_utils.h"
#include<malloc.h>

#include <sys/stat.h>

void parseln(const char *_Filename,const int _nLn,void (*func_)(char* elm_[],size_t)){
    struct stat fileInfo;
    if (stat(_Filename, &fileInfo) == -1) {
        printf("Error getting file: %s AT %d\n",_Filename,__LINE__);
        //return NULL;
    }
    size_t fileSize = fileInfo.st_size;

    if(fileSize > _FILESIZE_LIMIT){
        printf("Exceded the file size limit of{%d}} AT %d\n",_FILESIZE_LIMIT,__LINE__);
    }
    FILE* file = fopen(_Filename, "r");
    char* fileData = (char*)malloc(fileSize); 
    char* str_ptr_arr[_nLn];

    size_t bytesRead = fread(fileData, 1, fileSize, file);
    fclose(file);
    
    for (int i = 0; i < _nLn; i++)
    {
        char* str_ptr;
        if(i==0){
            str_ptr_arr[0] = fileData;
            continue;
        }
        // old met gives seg fault here (smts)
        else if((str_ptr = strchr(str_ptr_arr[i-1],'\n'))!=NULL){
            str_ptr++; // skip the \n at the first
            str_ptr_arr[i]=str_ptr;
        }
    }
    for (size_t i = 0; i < _nLn; i++)
    {
        strtok(str_ptr_arr[i],"\n");
    }
    (*func_)(str_ptr_arr,_nLn);
    //free(fileData);
}

void parseFile(const char* _Filename,const int _line_size,void (*_processor)(char* buf)){
    struct stat fileInfo;
    if (stat(_Filename, &fileInfo) == -1) {
        printf("Error getting file: %s AT %d\n",_Filename,__LINE__);
        return;
    }
    size_t fileSize = fileInfo.st_size;
    if(fileSize > _FILESIZE_LIMIT){
        printf("Exceded the file size limit of{%d}} AT %d\n",_FILESIZE_LIMIT,__LINE__);
        return;
    }
    FILE* file = fopen(_Filename, "r");
    char buf[_line_size];
    while(fgets(buf, _line_size, file) != NULL){
        _processor(buf);
    }
}