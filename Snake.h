#include <ncurses.h>
#pragma once
#include <queue>

enum Direction{
    up, down, left, right
};

class SnakePiece {
private:
    int row, col;
    char icon;
public:
    SnakePiece(int y, int x, char ch) : row(y), col(x), icon(ch) {}

    int getX()
    {
        return col;
    }

    int getY()
    {
        return row;
    }

    void setIcon(char ch)
    {
        icon = ch;
    }
};

class Snake{
    // 길이 증가, 감소를 위해 큐 사용
    // 머리 쪽으로 삽입, 꼬리 쪽으로 삭제되어야 하므로
    // 큐의 전단이 꼬리, 후단이 머리로 설정함
    std::queue<SnakePiece> snake;
    Direction cur_direction;

public: 
    Snake(){
        cur_direction = right;
    }

    void initialize(){
        while (!snake.empty())
        {
            snake.pop();
        }

        snake.push(SnakePiece(1, 1, '#'));
        snake.push(SnakePiece(1, 2, '#'));
        snake.push(SnakePiece(1, 3, '#'));
        snake.push(SnakePiece(1, 4, '%'));

        cur_direction = right;
    }

    // piece 위치를 큐에 삽입
    void addPiece(SnakePiece piece){
        snake.push(piece);
    }

    void removePiece(){
        snake.pop();
    }

    SnakePiece tail(){
        return snake.front();
    }

    SnakePiece head(){
        return snake.back();
    }

    Direction getDirection(){
        return cur_direction;
    }

    void setDirection(Direction d){
        cur_direction = d;
    }

    int getSize(){
        return snake.size() - 1;
    }

    SnakePiece nextHead(){
        int row = head().getY();
        int col = head().getX();

        switch(cur_direction){
        case down:
            row++;
            break;
        case up:
            row--;
            break;
        case left:
            col--;
            break;
        case right:
            col++;
            break;
        }

        return SnakePiece(row, col, '%');
    }
};