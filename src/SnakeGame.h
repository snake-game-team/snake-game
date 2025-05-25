#include <ncurses.h>
#pragma once
#include "Map.h"
#include "Snake.h"
#include "ItemManager.h"
#include "Item.h"
#include <chrono>
using namespace std::chrono;

class SnakeGame{
    Map map;
    Snake snake;
    ItemManager itemManager;
    bool game_over = false;
    steady_clock::time_point last_move;
    int moveDelay = 300;
public:
    SnakeGame(int height, int width) : map(height, width), snake() {
        map.initialize(0);  // 초기시작 0단계
        snake.initialize();
        map.addChar(1, 4, '%');  // snack 초기 위치 설정
        map.addChar(1, 3, '#');
        map.addChar(1, 2, '#');
        map.addChar(1, 1, '#');
        last_move = steady_clock::now();  // 초기화 당시 시간 측정
    }

    // 메인 게임 루프
    void run() {
        redraw();
        while (!checkOver()) {
            userInput();
            if (isTimeToMove()) {
                last_move = steady_clock::now();

                // 다음 위치로 이동 및 처리
                moveSnakeToNext(snake.nextHead());                         

                itemManager.update(map, snake);
                redraw();
            }    
        }
    }
        
    // 게임 새로고침
    void redraw(){   
        map.updateScore(snake.getSize());
        map.refresh();
    }

    // 게임오버 체크
    bool checkOver()
    {
        return game_over;
    }

    // 사용자 입력에 따라 진행방향 설정
    void userInput() { 
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

    // 일정 시간 경과 확인
    bool isTimeToMove() { 
        auto now = steady_clock::now();
        return duration_cast<milliseconds>(now - last_move).count() >= moveDelay;
    }

    void moveSnakeToNext(SnakePiece next){
        int nextRow = next.getY();
        int nextCol = next.getX();

        auto item = itemManager.checkCollision(next);
        if (item) {  // 아이템 충돌
            handleItemCollision(next, *item);
        } else { // 평범한 이동

            // 벽 또는 몸통 충돌 체크
            if (map.getChar(nextRow, nextCol) != ' ') { 
                game_over = true;
                return;
            }

            // 꼬리 제거
            map.addChar(snake.tail().getY(), snake.tail().getX(), ' ');
            snake.removePiece();
            
            // 머리 추가
            snake.head().setIcon('#');
            map.addChar(snake.head().getY(), snake.head().getX(), '#');
            snake.addPiece(next);
            snake.head().setIcon('%');
            map.addChar(snake.head().getY(), snake.head().getX(), '%');
        }
    }

    
    // 아이템 효과 처리
    void handleItemCollision(const SnakePiece& next, ItemType itemType) {
        
        // 머리 추가(공통)
        snake.head().setIcon('#');
        map.addChar(snake.head().getY(), snake.head().getX(), '#');
        snake.addPiece(next);
        snake.head().setIcon('%');
        map.addChar(snake.head().getY(), snake.head().getX(), '%');
        

        switch(itemType){
            case ItemType::GROWTH: // 아무 것도 안 함(꼬리 유지)
                break;

            case ItemType::POISON: // 꼬리 두 번 삭제
                for (int i = 0; i < 2; i++) {
                    map.addChar(snake.tail().getY(), snake.tail().getX(), ' ');
                    snake.removePiece();

                    if(snake.getSize() < 3){
                        game_over = true;
                        break;
                    }    
                }
                break;
        }
    }
};