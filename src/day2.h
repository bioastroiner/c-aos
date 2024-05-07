typedef unsigned int uint;
typedef struct Round {
    uint red;
    uint green;
    uint blue;
} Round;
typedef struct game {
    Round *rounds;
    uint num_of_rounds;
    uint id;
} Game;

/* 
    it processes and tokenizes each line and gets an Game obj
    from it;
    @param _gdesc: 
        a single line of game descriptors:
              "Game 13:
               1 green, 3 red, 3 blue;
               1 blue, 10 green;
               2 green, 3 blue"
    @return it returns a real type and not a ptr
        usualy grouped together in getgame_l()
*/              
Game *getgame_line(const char* _gdesc);
/* 
    @param _fdesc: 
            a file countaining Game objs (your entry
            this the file you get from AOC day2)
    @return Game
            a ptr to all Games created
            last game has ID of -1 
            for use with while lps
*/
Game        *getgame_lines(const char* _fdesc);
int ispsbl(Game *_game,Round _cmp);

/*
    processes games using the getgame_l()
        @param _gptr ptr to first game
                usualy the one with id of 1 (games start from 1
                ,0 is an invalid and -1 is a terminator).
                start from later_ptrs ommits the rest
                it loops all the way till it hits
                the game with id of -1

*/
void proc_games(Game* _gptr);

/*
    @param _nmbR number of Rounds
    @param _id, you cant provide negetive value
                use game_t() to create a default
                terminator.
    this func will allocate memory
    to rounds stored in this object
    care must be taken into acount
    by freeing its rounds field's memory,
    or use the native destructor. 
    @see game_d
    @see game_ds
*/
static Game *game_c(uint _id,uint _nmbR);
static Game *game_t();
/*
    Deletes a given game
*/
static void game_d(Game *_target);
/*
    Deletes all games
*/
static void game_ds(Game *_target);
static Round *add_new_round(Game *_target);
static Round *get_last_round(Game *_target);

int pt1_gpssble(Game *_target,uint _minR,uint _minG,uint _minB);