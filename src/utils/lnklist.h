typedef struct linkedList {
    char* str_ptr;
    struct linkedList* prev;
    struct linkedList* next;
} LinkedStr_t;
/*
    creates a LinkedList of String and returns a pntr to the first element
    @param char* base[] the building array
*/
LinkedStr_t* makeLnList_c(char*,int size);
LinkedStr_t* makeLnList_s(char*[]);
void print_list(LinkedStr_t*);