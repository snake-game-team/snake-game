#include <ncurses.h>
#pragma once
#include "Map.h"
#include "Snake.h"
#include <chrono>
using namespace std::chrono;

class SnakeGame{
    Map map;
    Snake snake;
    bool game_over = false;
    steady_clock::time_point last_move;
public:
    SnakeGame(int height, int width) : map(height, width), snake() {
        map = Map(height, width);
        initialize(0);  // 초기시작 0단계
    }

    void initialize(int stagenum){
        map.initialize(stagenum);
        snake.initialize();
        map.addChar(1, 4, '%');  // snack 초기 위치 설정
        map.addChar(1, 3, '#');
        map.addChar(1, 2, '#');
        map.addChar(1, 1, '#');
        last_move = steady_clock::now();  // 초기화 당시 시간 측정
    }

    // 게임오버 체크 함수
    bool checkOver()
    {
        return game_over;
    }

    // 입력한 키를 input으로 받고 진행방향과 반대방향이 아니면 input을 진행 방향으로 갱신
    void UserInput(){
        int input = map.getInput();
        if (input == ERR) return;

        switch (input)
        {
        case 'w':
            if (snake.getDirection() == down){
                game_over = true;
            }
            snake.setDirection(up);
            break;
        case 's':
            if (snake.getDirection() == up){
                game_over = true;
            }
            snake.setDirection(down);
            break;
        case 'd':
            if (snake.getDirection() == left){
                game_over = true;
            }
            snake.setDirection(right);
            break;
        case 'a':
            if (snake.getDirection() == right){
                game_over = true;
            }
            snake.setDirection(left);
            break;
        }
    }

    // 현재 시각을 now로 체크 후 가장 마지막에 체크된 시간, 즉 가장 마지막으로 움직인 시각과의 차이가
    // 1초 이상이라면 last_move 갱신 후 뱀 이동
    void runGame(){
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