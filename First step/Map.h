#include <ncurses.h>

class Map {

public:
    Map(int height, int width){
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);

        map = newwin(height, width, (max_y / 2) - 11, (max_x / 2) - 20); // 맵
        score = newwin(3, width, (max_y / 2) + 10, (max_x / 2) - 20);  // 스코어보드
        initalize();
    }

    void initalize(){  // 초기화화
        clear();
        updateScore();
        refresh();
    }

    void updateScore(){  // 스코어보드 초기화화
        werase(score);
        mvwprintw(score, 0, 1, "Score : %d", point);
        wrefresh(score);
    }

    void addPoint(int p = 1){  // 점수 증가가
        point += p;
        updateScore();
    }

    void addBorder(){
        box(map, 0, 0);
    }

    void clear(){
        wclear(map);
        addBorder();
    }

    void refresh(){
        wrefresh(map);
        wrefresh(score);
    }
    
private:
    int height, width;
    int point = 0;
    WINDOW *map;
    WINDOW *score;
};