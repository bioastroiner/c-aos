#include <stdlib.h>

typedef enum {
    D0,D1,D2,D3
} DAY;

#define TODAY D2
#define DEBUG 1

#if DEBUG
#define ERR(_MSSG) printf("\033[31mERROR %s: \nIN:  %s, \nLINE:%d\033[0m\n",_MSSG,__FILE__,__LINE__)
#else 
#define ERR(MSSG)
#endif

void prtElm(char* [],size_t);