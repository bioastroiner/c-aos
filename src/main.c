#include "utils/io_utils.h"
#include "day1.h"
#include "main.h"

void _DAY1_Lagacy(char* [],size_t);
void _DAY2_Lagacy_pt1(char*);
void _DAY2_pt1(char* elm);
void _DAY2_pt2(char* elm);

/*
    ENTRY
*/
#undef TODAY
#define TODAY 2
int main(){
    printf("Today is Day %d\n",TODAY);
    switch (TODAY){
    case 1:
        parseln("inputs/day1.txt",1000,_DAY1_Lagacy);// parseFile("inputs/day2.txt",100,_DAY1);
        break;
    case 2:
        parseFile("inputs/day2.txt",180,_DAY2_pt2);
        //parseFile("inputs/day2.txt",160,_DAY2_Lagacy_pt1);// the biggest line (18) was 159 char long! so this is JUST close enough
        break;
    default:
        ERR("Unimplemented Day " + TODAY);// day 69 for example falls right here!
        return 1;
        break;
    }
    return 1;
}

/*
    DAYS IMPLEMENTATION
*/
#define day1_pt 2
// https://adventofcode.com/2023/day/1
void _DAY1_Lagacy(char* elm_[],size_t size_){
    // calibrate_pt2("ssfour7ninek",0);
    //prtElm(elm_,size_);
    int sum = 0;
    for (size_t i = 0; i < size_; i++){
#if day1_pt==2
        int clb = calibrate_pt2(elm_[i],0);
#else
        int clb = calibrate_pt1(elm_[i],0);
#endif
        printf("%s: %d\n",elm_[i],clb);
        sum += clb;
    }
    printf("The Final Answer is: %d",sum);
}

#include "day2.h"
#include <string.h>
void _DAY2_pt1(char* elm){
    Game *_game = getgame_line(elm);
    //printf("%d"pt1_gpssble(_game,12, 13, 14));
    // do the sum TODO
}
static int answer = 0;
void _DAY2_pt2(char* elm){
    Game *_game = getgame_line(elm);
    int r = 0;
    int g = 0;
    int b = 0;
    if(pt1_gpssble(_game,12,13,14)){
        for (uint i = 0; i < _game->num_of_rounds; i++)
        {
            if(_game->rounds[i].blue>b)b=_game->rounds[i].blue;
            if(_game->rounds[i].red>r)r=_game->rounds[i].red;
            if(_game->rounds[i].green>g)g=_game->rounds[i].green;
        }
        int power = r*g*b;
        answer+=power;
        printf("id: %d has %d power\n",_game->id,power);
        printf("answer: %d\n",answer);
    }

    
}

/*
    MISC. FUNCs
*/

void prtElm(char* elm_[],size_t size_){
    for (size_t i = 0; i < size_; i++)
    {
        printf("%s\n",elm_[i]);
    }
}

