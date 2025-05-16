#include <ncurses.h>
#include "Map.h"

#define height 21
#define width 42

int main(void){
    initscr();
    refresh();

    Map Map(height, width);
    Map.initalize();

    getch();
    endwin();

    return 0;
}