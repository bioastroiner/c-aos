#include <stdlib.h>
#define LNK "https://adventofcode.com/2023/day/2"
#define NULL ((void *)0)

#include "day2.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

/*
    swaps all char @param _toswap with @param _swapc
    mutates the string
*/
static char* swapc(char* _str,int _toswap,int _swapc){
    char* _w;
    _w=strchr(_str,_toswap);while(_w!=NULL){*_w=' ';_w++;_w=strchr(_w,_toswap);}
    return _w;
}
/*
    gives you how many time a @param _char 
    has repeated in @param _str
*/
static int strci(char* _str,int _char){
    int _c;
    char* _w;
    _w=strchr(_str,';');while(_w!=NULL){_c++;_w++;_w=strchr(_w,';');}
    return _c;
}

// allocate & copy
static char *strcpy_alloc(char * _Dest,const char * _Source){
    _Dest = calloc(strlen(_Source)+1,sizeof(char));
    if(_Dest==NULL) {
        //printf(stderr,"Error allocating memory: %s\n",_Source);
        return _Dest;
    }
    strcpy(_Dest,_Source);
    return _Dest;
}

/*
    converts a string into a stream of tokens
    @return int numbers of output buffer
    @param _dest writes this ptr to the first token
*/
static int tokens(const char* _target,const char* _by,char** _dest){
    char* _buf = strcpy_alloc(_buf,_target);
    uint _siz = 0;
    char* _wptr = strtok(_buf,_by);while(_wptr!=NULL){
        _siz++;
        _dest[_siz-1]=_wptr;
        _wptr = strtok(NULL," ");
    }
    //realloc it
    return _siz;
}
/*
    process tokens using a pair parsing func
    parser works by breaking down tokens into pairs
    and loop over the sets for example:
        {"a" "b" "c" "d" "e"}
    becomes:
        a,b
        c,d
        e,NULL
*/
static Game *process_tokens(char** _tokens,uint _size_token,void (*_pair_parsing_func)(char* _token_1,char* _token_2,uint index,uint size,Game* _current_game)){
    int _i = 0;
    Game *_g = game_c(0,0);
    while(_i < _size_token){
        char* _val;
        if(_i==_size_token-1) _val=NULL;
        else _val = _tokens[_i+1];
        (_pair_parsing_func)(_tokens[_i],_val,_i,_size_token,_g);
        _i+=2;
    }
    return _g;
}

/*
{Game,18}
    {9,blue}
    {4,green}
    {2,red;}

    {1,green}
    {9,red}
    {10,blue;}

    {14,red}
    {10,green}
    {17,blue;}

    {12,red}
    {1,green}
    {15,blue;}

    {3,blue}
    {8,red}
    {2,green;}

    {3,green}
    {11,red}
    {13,blue}
*/
static void pair_parser(char* _key,char* _val,uint _ix,uint _size,Game* _game){
    //printf("{%s,%s}\n",_key,_val);
    if(_game->id==0){
        // _key must be "game" but we check anyways
        if(_key[0] == 'G') {
            _game->id = strtol(_val, NULL, 10);
            add_new_round(_game);
        }
        return;
    }
    if(_val[0]=='r') get_last_round(_game)               ->red=strtol(_key,NULL,10);
    if(_val[0]=='g') get_last_round(_game)               ->green=strtol(_key,NULL,10);
    if(_val[0]=='b') get_last_round(_game)               ->blue=strtol(_key,NULL,10);
    if(_val[strlen(_val)-1]==';') {
        //printf("{%s,%s}\n",_key,_val);
        add_new_round(_game);}
}

Game *getgame_lines(const char* _fdesc){
    
    return getgame_line(_fdesc);
}

Game *getgame_line(const char* _gdesc){
    char* _cw = strcpy_alloc(_cw,_gdesc);
    char** _tks = calloc(50,sizeof(char*));
    swapc(_cw,':',' ');
    swapc(_cw,',',' ');
    //printf("%s\n",_cw);
    uint _c = tokens(_cw," ",_tks);
    // for (uint i = 0; i < _c; i++)
    // {
    //     printf("%d/%d %s\n",i,_c-1,_tks[i]);
    // }
    return process_tokens(_tks,_c,pair_parser);
}

static Game *game_c(uint _id,uint _nmbR){
    if(_id<0) {
        //sprintf(stderr,"%d game_c can't create with non positive IDs",_id);
        return NULL;
    }
    if(_nmbR<0) {
        //sprintf(stderr,"%d game_c can't create with non positive or non-zero Rounds nmbrs",_nmbR);
        return NULL;
    }
    Round *ptr = NULL;
    if(_nmbR>0) ptr = calloc(_nmbR,sizeof(Round));
    Game *_g = calloc(1,sizeof(Game));
    *_g = (Game) {
        ptr,_nmbR,_id
    };
    return _g;
}

static Round *get_last_round(Game *_target){
    if(_target->num_of_rounds<1) return NULL;
    return &_target->rounds[_target->num_of_rounds-1];
}

static Round *add_new_round(Game *_target)
{
    if(_target->num_of_rounds<1){
        // create a new one
        _target->rounds=calloc(1,sizeof(Round));
    } else {
        // expand the current one
        Round *_new_round = _recalloc(_target->rounds,_target->num_of_rounds+1,sizeof(Round));
        _target->rounds=_new_round;
    }
    _target->num_of_rounds++;
    // _target->rounds[_target->num_of_rounds-1]=(Round){
    //     0,0,0
    // };
    return get_last_round(_target);
}

int ispsbl(Game *_game,Round _cmp){
    Round *_r;
    for (uint i = 0; i < _game->num_of_rounds; i++)
    {
        _r = (_game->rounds)+i;
        if(_r->red>_cmp.red) return 0;
        if(_r->green>_cmp.green) return 0;
        if(_r->blue>_cmp.blue) return 0;
    }
    return 1;
}

int pt1_gpssble(Game *_target,uint _minR,uint _minG,uint _minB){
    return ispsbl(_target,(Round){_minR,_minG,_minB});
}







////////////////////////////////////// OLD


// //pt2: fewest number of cubes of each color
// #define EXAMPLE "Game 18: 9 blue, 4 green, 2 red; 1 green, 9 red, 10 blue; 14 red, 10 green, 17 blue; 12 red, 1 green, 15 blue; 3 blue, 8 red, 2 green; 3 green, 11 red, 13 blue"
// void _DAY2_Lagacy_pt1(char* elm){
//     // 2727 was right answe! first try (pt1 anyways)
//     static int sum;
//     char* _w;
//     uint _count = 1;
//     _w=strchr(elm,':');while(_w!=NULL){*_w=' ';_w++;_w=strchr(_w,':');}
//     _w=strchr(elm,',');while(_w!=NULL){*_w=' ';_w++;_w=strchr(_w,',');}
//     _w=strchr(elm,';');while(_w!=NULL){_count++;_w++;_w=strchr(_w,';');}
//     Game _g = {
//         malloc(sizeof(Round)*_count),
//         _count,
//         0
//     };
// #define _R _g.rounds[_i].red
// #define _G _g.rounds[_i].green
// #define _B _g.rounds[_i].blue
//     for (uint _i = 0; _i < _count; _i++){_R=0;_G=0;_B=0;}
//     uint _c;
//     uint _i=0;
//     _w=strtok(elm," ");while(_w!=NULL){
//         if(*_w=='G') _w=strtok(NULL," ");
//         if(_g.id==0) _g.id=strtol(_w,NULL,10);
//         if(*_w=='r') {_R=_c;_c=0;}
//         if(*_w=='g') {_G=_c;_c=0;}
//         if(*_w=='b') {_B=_c;_c=0;}
//         if(_w[strlen(_w)-1]==';')_i++;
//         _c=strtol(_w,NULL,10);
//         _w=strtok(NULL," ");
//     }
//     // parsing is done
//     int bol = (ispsbl(&_g, (Round){12, 13, 14}));
//     if(bol) sum+=_g.id;
//     printf("-Game (id=%d): %s",_g.id,(bol ? "True, Possible" : "False, Impossible"));
//     printf("\n-num_of_rounds:%d\n\t-",_g.num_of_rounds);
//     for (uint _i = 0; _i < _count; _i++){
//         printf("\n--Round (%d): \n---Red:%d\n---Green:%d\n---Blue:%d\n------",_i+1,_R,_G,_B);
//     }
//     printf("sum:%d\n",sum);
//     free(_g.rounds);
// #undef _R
// #undef _G
// #undef _B
// }