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
    return getmaxx(stdscr)-1;
}


int getMaxY()
{
    return getmaxy(stdscr)-1;
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




/*class Game
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
*/




class Snake
{
private:

    vector<Point> body;

public:

    Snake()
    {
        body.push_back(Point(2, 2));
        body.push_back(Point(3, 2));
        body.push_back(Point(4, 2));
        body.push_back(Point(4, 3));
        body.push_back(Point(5, 3));
        body.push_back(Point(5, 4));
        body.push_back(Point(5, 5));
        body.push_back(Point(6, 5));
        body.push_back(Point(7, 5));
    }


    vector<Point> getBody()
    {
        return body;
    }



    bool isValidPoint(Point point)
    {
        bool inAreaX = point.getX() >= 0 && point.getX() <= getMaxX();
        bool inAreaY = point.getY() >= 0 && point.getY() <= getMaxY();
        bool isEmpty = true;

        for (auto it : body)
        {
            if (point.getX() == it.getX() && point.getY() == it.getY())
            {
                isEmpty = false;
            }
        }

        if (inAreaX && inAreaY && isEmpty)
        {
            return true;
        }
        else
        {
            return false;
        }

    }




    void moveUp()
    {
        Point newHead = body[0];
        newHead.setY(newHead.getY()-1);
        if (isValidPoint(newHead))
        {
            body.erase(body.end() - 1);
            body.insert(body.begin(), newHead);
        }
    }



    void moveDown()
    {
        Point newHead = body[0];
        newHead.setY(newHead.getY() + 1);

        if (isValidPoint(newHead))
        {
            body.erase(body.end() - 1);
            body.insert(body.begin(), newHead);
        }
    }


    void moveLeft()
    {
        Point newHead = body[0];
        newHead.setX(newHead.getX() - 1);

        if (isValidPoint(newHead))
        {
            body.erase(body.end() - 1);
            body.insert(body.begin(), newHead);
        }
    }

    void moveRight()
    {
        Point newHead = body[0];
        newHead.setX(newHead.getX() + 1);
        if (isValidPoint(newHead))
        {
            body.erase(body.end() - 1);
            body.insert(body.begin(), newHead);
        }
    }



};



int main()

{
    /*
    auto point1 = Point(8,18);
    auto point2 = Point(4, 84);
    point1.print();
    point2.print();
    cout<< Point::getDistance(point1, point2)<<endl;
    */

    Snake snake = Snake();



    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);


    int ch = - 1;




    while (ch != 'q')
    {
        erase();
        for (auto it : snake.getBody())
        {
            mvaddch(it.getY(), it.getX(), 'X');
        }
        refresh();
        ch = getch();

        
        switch (ch)
        {
        case KEY_UP:
        {
            snake.moveUp();
            break;
        }

        case KEY_DOWN:
        {
            snake.moveDown();
            break;
        }

        case KEY_LEFT:
        {
            snake.moveLeft();
            break;
        }

        case KEY_RIGHT:
        {
            snake.moveRight();
            break;
        }


        default:
            break;
        }
    }






    endwin();
    
    
    
        
}
