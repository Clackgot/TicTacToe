#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <curses.h>
#include <Windows.h>
#include <string>
#include <ctime>
#include <vector>

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

};





//0 - Пусто
//1 - Крестик
//2 - Нолик



class Game
{
private:
    bool isRun = false;
public:
    Game()
    {
        initscr();
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        noecho();
        curs_set(0);

    }
    ~Game()
    {
        endwin();
    }
    void run()
    {
        isRun = true;
        while (isRun)
        {
            erase();
            for (int y = 0; y < getmaxy(stdscr); y++)
            {
                for (int x = 0; x < getmaxx(stdscr); x++)
                {
                    attron(COLOR_PAIR(rand() % 4 + 1));
                    
                    mvaddch(y,x,'O');


                    refresh();
                    Sleep(1);
                }

            }
            refresh();
            Sleep(3000);
        }


        printw("Stop\n");
        getch();
    }

    
};



int main()

{
    auto point1 = Point(8,18);
    
    
    
    
    srand(time(0));
    
    int x = 0;
    int y = 0;

    initscr();



    printw("x=%d,y=%d | %d", x, y, getmouse());

    refresh();
    
    getch();


    endwin();
    
    
    
}
