#include <ncurses.h>
#pragma once
#include "Map.h"
#include "Snake.h"
#include <chrono>
using namespace std::chrono;

class SnakeGame{
    Map map;
    Snake snake;
public:
    SnakeGame(int height, int width) : map(height, width), snake() {
        map = Map(height, width);
        initialize(0);  // 초기시작 0단계
    }

    void initialize(int stagenum){
        map.initialize(stagenum);
        snake.initialize();
        map.addChar(1, 4, '%');
        map.addChar(1, 3, '#');
        map.addChar(1, 2, '#');
        map.addChar(1, 1, '#');
    }

    void UserInput(int ch){
        //char input = map.getInput();

        switch (ch)
        {
        case 'w':
            snake.setDirection(up);
            break;
        case 's':
            snake.setDirection(down);
            break;
        case 'd':
            snake.setDirection(right);
            break;
        case 'a':
            snake.setDirection(left);
            break;
        }
    }

    void runGame(steady_clock::time_point& last_move){
        auto now = steady_clock::now();
        if (duration_cast<milliseconds>(now - last_move).count() >= 1000){
            last_move = now;
            SnakePiece next = snake.nextHead();
            controlNext(next);
        }
    }

    void controlNext(SnakePiece next){
        int nextRow = next.getY();
        int nextCol = next.getX();

        if (map.getChar(nextRow, nextCol) == ' '){
            // snake의 꼬리 위치에 있는 icon을 ' '로 설정
            map.addChar(snake.tail().getY(), snake.tail().getX(), ' ');
            // snake의 꼬리 부분을 없앤다
            snake.removePiece();

            // snake의 머리 부분의 icon을 '#'로 설정
            snake.head().setIcon('#');
            // 게임 창에도 똑같이 반영
            map.addChar(snake.head().getY(), snake.head().getX(), '#');

            // snake의 머리 부분을 next로 설정
            snake.addPiece(next);
            // snake의 머리 부분의 icon을 '%'로 설정
            snake.head().setIcon('%');
            // 게임 창에도 똑같이 반영
            map.addChar(snake.head().getY(), snake.head().getX(), '%');
        }
    }

    // 스테이지에 따라 맵 설정
    void setStage(int stageNum){
        map.initialize(stageNum);
    }

    // 스테이지 반환
    int getStage(){
        return map.getStageNum();
    }

    // 게임 새로고침
    void redraw(){   
        map.updateScore(snake.getSize());
        map.refresh();
    }
};