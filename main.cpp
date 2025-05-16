#include <ncurses.h>
#include <thread>
#include "SnakeGame.h"
#include <chrono>
using namespace std::chrono;

int main(void){
    initscr();
    refresh();
    noecho(); // 입력된 키 미표시
    curs_set(0);  // 커서 미표시
    nodelay(stdscr, TRUE);

    SnakeGame game(21, 39);  // 높이 21, 너비 39로 게임 화면 설정
    game.redraw();
    while (!game.checkOver()){
        game.UserInput();
        game.runGame();
        game.redraw();
    }
    getch();
    endwin();

    return 0;
}