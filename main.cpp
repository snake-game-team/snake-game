#include <ncurses.h>
#include "SnakeGame.h"
#include <chrono>
using namespace std::chrono;

int main(void){
    initscr();
    refresh();
    noecho(); // 입력된 키 미표시
    curs_set(0);  // 커서 미표시
    nodelay(stdscr, TRUE);

    auto last_move = steady_clock::now();
    SnakeGame game(21, 39);
    game.redraw();
    while (1){
        int ch = getch();  // 2단계 테스트를 위함입니다. 게임오버 조건이 생기면 지워주세요.
        if (ch == 'q')
            break;

        game.UserInput(ch);  // 게임오버 조건이 생기면 UserInput 함수를 수정해주세요.
        game.runGame(last_move);
        game.redraw();
    }
    getch();
    endwin();

    return 0;
}