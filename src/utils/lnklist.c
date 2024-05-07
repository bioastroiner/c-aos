#include "lnklist.h"
//#include "../main.h"
#include <stdio.h>
#include "string.h"
#include "malloc.h"

void print_list(LinkedStr_t* list_ptr){
    //if(list_ptr==NULL) ERR("Invalid argument");
    printf("[\n");
    while (list_ptr->next!=NULL)
    {
        printf("%s\n",*(char*)list_ptr);
    }
    printf("]\n");
}

LinkedStr_t* makeLnList_c(char* str_ptr,int size){
    if(size < 1) size = strlen(str_ptr);
    if(strlen(str_ptr)>size) size=strlen(str_ptr);
    LinkedStr_t* first = (LinkedStr_t*)malloc(sizeof(LinkedStr_t)*size);
    LinkedStr_t* curnt;
    for (size_t i = 0; i < size; i++)
    {
        curnt = first + i;
        if(i!=0) curnt->prev=(curnt-sizeof(LinkedStr_t));
        else curnt->prev=NULL;
        if(i!=size-1) curnt->next=(curnt+sizeof(LinkedStr_t));
        else curnt->next=NULL;
    }
    return first;
}