#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <curses.h>
#include <Windows.h>
#include <string>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;

int getMaxX()
{
    return 20;
}


int getMaxY()
{
    return 20;
}


class Point {
private:
    int _x;
    int _y;    
public:
    //Конструктор класса
    Point(int x, int y) 
    {
        setX(x);
        setY(y);
    }

    int getX()
    {
        return _x;
    }

    void setX(int x)
    {//TODO Проверка на ввод
        _x = x;
    }

    int getY()
    {
        return _y;
    }

    void setY(int y)
    {//TODO Проверка на ввод
        _y = y;
    }

    void print() 
    {    
        cout << "x = " << getX()<< " y = "<< getY()<<endl;
    }

    static float getDistance(Point first, Point second)
    {
        int x1 = first.getX();
        int y1 = first.getY();
        int x2 = second.getX();
        int y2 = second.getY();

        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }
};

class Snake 
{
private:
    int size;
    char tail;
    char head;
    vector <Point> body;

public:

    Snake()
    {
        head = 'O';
        tail = 'X';

        body.push_back(Point(1, 1));
        body.push_back(Point(1, 2));
        body.push_back(Point(2, 2));
        body.push_back(Point(2, 3));
        body.push_back(Point(3, 3));
    }



    void print()
    {
        initscr();



        for (auto it : body)
        {
            mvaddch(it.getY(), it.getX(), tail);
        }
        refresh();

        getch();

        endwin();
    }
};


int main()

{
    auto point1 = Point(8,18);
    auto point2 = Point(4, 84);
    point1.print();
    point2.print();
    cout<< Point::getDistance(point1, point2)<<endl;

    auto snake = Snake();

    snake.print();
    
    
        
}
