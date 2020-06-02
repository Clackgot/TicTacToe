#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <curses.h>
#include <Windows.h>
#include <string>
#include <ctime>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;



WINDOW* win;

WINDOW* win2;





int getMaxX()
{
    return getmaxx(win)-2;
}


int getMinX()
{
    return 1;
}


int getMaxY()
{
    return getmaxy(win)-2;
}

int getMinY()
{
    return 1;
}


chrono::microseconds getDelayByMs()
{
    return 50ms;
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
        bool inAreaX = point.getX() >= getMinX() && point.getX() <= getMaxX();
        bool inAreaY = point.getY() >= getMinY() && point.getY() <= getMaxY();
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



    bool isMoveUp()
    {
        Point newHead = body[0];
        newHead.setY(newHead.getY() - 1);
        return isValidPoint(newHead);
    }

    bool isMoveDown()
    {
        Point newHead = body[0];
        newHead.setY(newHead.getY() + 1);
        return isValidPoint(newHead);
    }


    bool isMoveLeft()
    {
        Point newHead = body[0];
        newHead.setX(newHead.getX() - 1);
        return isValidPoint(newHead);
    }


    bool isMoveRight()
    {
        Point newHead = body[0];
        newHead.setX(newHead.getX() + 1);
        return isValidPoint(newHead);
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


Snake snake;

void gameLoop(int& ch)
{
    
    win = newwin(30, 30, 0, 0);
    
    snake = Snake();



    
    keypad(win, TRUE);
    noecho();
    curs_set(0);
    
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLUE);
    init_pair(3, COLOR_GREEN, COLOR_GREEN);


    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(5, COLOR_RED, COLOR_RED);
    init_pair(6, COLOR_CYAN, COLOR_CYAN);

    
    wbkgdset(win, COLOR_PAIR(6));
    while (ch != 'q')
    {
        wclear(win);
        box(win, 0, 0);
        for (auto it : snake.getBody())
        {
            wmove(win, it.getY(), it.getX());
            
            
            wattron(win,COLOR_PAIR(2));
            waddch(win, ' ');
            wattron(win, COLOR_PAIR(1));
        }
        wrefresh(win);
        //ch = wgetch(win);


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
        //Sleep(getDelay());
        this_thread::sleep_for(getDelayByMs());
    }

    


    delwin(win);
    endwin();
}



void readKey(int& key)
{
    win2 = newwin(10, 10, 0, 30);
    box(win2, 0, 0);
    
    int tempKey;

    keypad(win2, TRUE);

    while (true)
    {
        tempKey = wgetch(win2);
        

        switch (tempKey)
        {
        case KEY_UP:
            if(snake.isMoveUp() && key != KEY_DOWN)key = tempKey;
            break;
        case KEY_DOWN:
            if (snake.isMoveDown() && key != KEY_UP)key = tempKey;
            break;
        case KEY_LEFT:
            if (snake.isMoveLeft() && key != KEY_RIGHT)key = tempKey;
            break;
        case KEY_RIGHT:
            if (snake.isMoveRight() && key != KEY_LEFT)key = tempKey;
            break;
        default:
            break;
        }

        
    }


    delwin(win2);
    endwin();
}



int main()

{
    initscr();

    int key = KEY_DOWN;
    thread thr1(gameLoop, ref(key));
    thread thr2(readKey, ref(key));
    
    thr2.join();
    thr1.join();
    //thr2.detach();
    //thr1.detach();

    
    
    
        
}
