/*
    Specefic Code from each day lives here
*/
#include "main.h"
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include"day1.h"
#include"utils/lnklist.h"
#include <stdio.h>

int calibrate_pt1(char* _Str,const char _Sprt){
    char* p = _Str;
    char* target_char;
    int num[2] = {0};
    int numsfound = 0;
    for (size_t i = 0; i < strlen(_Str); i++)
    {
        target_char = p + (sizeof(char)*i);
        
        if(isdigit(*target_char)){
            numsfound++;
            if(numsfound==1) num[0]=*target_char-'0';
            if(numsfound>1) num[1]=*target_char-'0';
        }
    }
    if(numsfound==1) num[1]=num[0];
    if(numsfound==0) return 0; // should never happen

    // while(*p!=_Sprt){
    //     if(*p=='\r') return (num[0]*10+num[1]);
    //     if(isdigit(*p)){
    //         if(num[0]==NULL) num[0] = *p - '0';
    //         else num[1] = *p - '0';
    //     }
    //     else if(num[1]==NULL) num[1]=num[0];
    //     p++;
    // }
    return (num[0]*10+num[1]);
    free(num);
    free(p);
}

typedef struct {
    int left;
    int right;
} Pair;
Pair* putToPair(int _elm,Pair* _pair){
    if(_pair->left==0)
        _pair->left=_elm;
    else _pair->right=_elm;
    return _pair;
}
Pair* createPair(){
    Pair* _pair = malloc(sizeof(Pair));
    _pair->left=0;
    _pair->right=0;
    return _pair;
}

int calibrate_pt2(char* _Str,const char _Sprt){
    //LinkedStr_t* char_lst = makeLnList_c(_Str,0);
    //print_list(char_lst);

    char* head = _Str;
    Pair* _pair = createPair();
    while(*head!=0) {
        for (size_t i = strlen(head); i > 0; i--)
        {
            char* tail = head+i;
            char* str_p = malloc(sizeof(char)*(i+1));
            strncpy(str_p,head,i);
            str_p[i]=0;
            int dig = checkdigits(str_p);
            if(dig > -1) {
                // we have a number from the left to right
                // we can add this number to an stack
                // an struct that only its under and top value is important
                // and rest get popped out
                putToPair(dig,_pair);
            }
            free(str_p); 
        }
        head++;
    }
    if(_pair->right==0)_pair->right=_pair->left;
    return (_pair->left*10)+_pair->right;
}

int checkdigits(char* _Str){
    //if(strcmp(_Str,"zero")==0) return 0;
    if(strlen(_Str)==1&&isdigit(*_Str)) return *_Str - '0';
    if(strcmp(_Str,"one")==0) return 1;
    if(strcmp(_Str,"two")==0) return 2;
    if(strcmp(_Str,"three")==0) return 3;
    if(strcmp(_Str,"four")==0) return 4;
    if(strcmp(_Str,"five")==0) return 5;
    if(strcmp(_Str,"six")==0) return 6;
    if(strcmp(_Str,"seven")==0) return 7;
    if(strcmp(_Str,"eight")==0) return 8;
    if(strcmp(_Str,"nine")==0) return 9;
    return -1;
}




