/*
Written by Trevor Madge
12 July 2022
*/

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Grid {
    protected:
        int width, height;
        vector< vector<bool>> data{}; //information storage
        void setWidth(int _w){
            width = _w;
        }
        void setHeight(int _h){
            height = _h;
        }

    public:
        Grid(){
            width = 1;
            height = 1;
        };
        void init(int _w, int _h){
            setWidth(_w);
            setHeight(_h);
            data.resize(_w, vector<bool>(_h));
        }
        int getWidth(){
            return width;
        };
        int getHeight(){
            return height;
        };
        bool getCell(int x, int y){
            return data[x][y];
        };
        void toggleCell(int x, int y){
            data[x][y] = !getCell(x,y);
        };
        

    void render(){
        for (int y = 0; y<height; y++){
            for (int x = 0; x<width; x++){
                if (getCell(x,y))
                    cout << ",";
                else
                    cout << ".";
            }
            cout << endl;
        }
    }
};

class Ant {
    //Creature that moves around grid toggling cells and changing directions based on cell value
    public:
    Ant(){
        x = 0;
        y = 0;
        direction = 0;
    };
    void randomLocation(Grid &g){
        x = rand() % g.getWidth()-1;
        y = rand() % g.getHeight()-1;
        direction = rand() % 4;
    };

    int x, y, direction;

    void move(Grid &g){
        int new_x, new_y;
        new_x = x;
        new_y = y;
        switch (direction)
        {
        case 0:
            new_x = x+1;
            break;
        case 1:
            new_y = y-1;
            break;
        case 2:
            new_x = x-1;
            break;
        case 3:
            new_y = y+1;
            break;
        default:

            break;
        }

        //Loop around edges
        if (new_x>=g.getWidth()) new_x = 0;
        if (new_x<0) new_x = g.getWidth()-1;
        if (new_y>=g.getHeight()) new_y = 0;
        if (new_y<0) new_y = g.getHeight()-1;

        //update pos
        x = new_x;
        y = new_y;

        g.toggleCell(x,y);

        if (g.getCell(x,y)) 
            direction++;
        else
            direction--;

        if (direction > 3)
            direction = 0;

        if (direction<0)
            direction = 3; 
    };
};

void Clear() // Clear cmd window.
{
    #if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

int main() {
    Grid grid;
    Ant ants[3];
    grid.init(20,10);
    int nAnts = sizeof(ants)/sizeof(ants[0]);


    for (int i = 0; i < nAnts; i++)
        ants[i].randomLocation(grid); //Randomize starting locations

    while(true) //Main Loop
    {
        for (int i = 0; i < nAnts; i++)
            ants[i].move(grid);

        Clear();
        grid.render(); //Update screen
    }
    return 0;
};