// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include<iostream>
#include<cctype>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"

#include<random>//为了更好的随机数
using namespace std;



int neighbor(int r,int c,Grid<char> & grid,bool wrap);
void newLife(int i,int j,int nums,Grid<char> & grid,Grid<char> & Newgrid,LifeGUI & gui);

//欢迎信息
void WelcomeM()
{
    cout<<"Welcome to the CS 106B Game of Life,"<<'\n'
        <<"a simulation of the lifecycle of a bacteria colony."<<'\n'
        <<"Cells (X) live and die by the following rules:"<<'\n'
        <<"- A cell with 1 or fewer neighbors dies."<<'\n'
        <<"- Locations with 2 neighbors remain stable."<<'\n'
        <<"- Locations with 3 neighbors will create life."<<'\n'
        <<"- A cell with 4 or more neighbors dies."<<endl;
}

//随机生成grid
Grid<char> CreateRandom()
{
    int rwidth = 0, cwidth = 0;
    do{
        rwidth = getInteger("scope of rows : ");
    }while(rwidth <= 1);

    do{
        cwidth = getInteger("scope of columns : ");
    }while(cwidth <= 1);

    std::random_device rowRd;
    std::mt19937 mtr(rowRd());
    std::uniform_real_distribution<> row(1, rwidth+1);

    std::random_device colRd;
    std::mt19937 mtc(colRd());
    std::uniform_real_distribution<> col(1, cwidth);

    int r = (int)row(mtr);
    int c = (int)col(mtc);
    Grid<char> gridRd(r,c);

    int rate;
    do{
        rate = getInteger("'X' generating rate (The higher the number the less 'X'): ");
    }while(rate <= 1);

    std::random_device Rd;
    std::mt19937 mt(Rd());
    std::uniform_real_distribution<> Rate(1, rate);

    for(int i = 0;i < r;i++)
        for(int j = 0;j < c;j++)
        {
            if((int)Rate(mt) == 1) gridRd[i][j] = 'X';
            else gridRd[i][j] = '-';
        }


    return gridRd;
}

//打开文件
void getFile(ifstream& input,string& name)
{
    do
    {
        //name = promptUserForFile("Grid input file name?");
        name = getLine("Grid input file name?");
        if(equalsIgnoreCase("Random",name)) return;
        input.open(name);//openFile(input,name);
        if(input.fail()) cout<<"Unable to open that file.  Try again."<<endl;
    }while(!isFile(name));
}


//展示出grid
void showgrid(Grid<char> & grid)
{
    for(int i = 0; i < grid.numRows(); i++)
    {
        for(int j = 0; j < grid.numCols(); j++)
            cout<<grid[i][j];
        cout<<endl;
    }
}

//更新grid
void newgrid(Grid<char> & grid,bool wrap,LifeGUI & gui)
{
    Grid<char> Newgrid(grid.numRows(),grid.numCols());
    for(int i = 0;i < Newgrid.numRows();i++)
        for(int j = 0;j < Newgrid.numCols();j++)
        {
            int nums = neighbor(i,j,grid,wrap);
            newLife(i,j,nums,grid,Newgrid,gui);
        }
    grid = Newgrid;
    clearConsole();
    showgrid(Newgrid);
}

//命令 a,t,q
void command(Grid<char> & grid,bool wrap,LifeGUI & gui)
{
    string option;
    option = getLine("a)nimate, t)ick, q)uit?");

    if(equalsIgnoreCase("a",option))
    {
        do{
            int frames = 0;
            frames = getInteger("How many frames?");

            while(frames)
            {
                newgrid(grid,wrap,gui);
                frames--;
                pause(100);
            }

            option = getLine("a)nimate, t)ick, q)uit?");

        }while(equalsIgnoreCase("a",option));
    }

    if(equalsIgnoreCase("t",option))
    {
        do{
            int frames = 1;

            while(frames)
            {
                newgrid(grid,wrap,gui);
                frames--;

            }

            option = getLine("a)nimate, t)ick, q)uit?");
        }while(equalsIgnoreCase("t",option));
    }

    if(equalsIgnoreCase("q",option))
    {
        return;
    }

    command(grid,wrap,gui);
}


//数邻居
int neighbor(int r,int c,Grid<char> & grid,bool wrap)
{
    int nums = 0;
    for (int i = -1; i <= 1; i++)
        for(int j = -1;j <=1;j++)
        {
            if(i == 0 && j == 0) continue;
            if(grid.inBounds(r+i,c+j) && grid[r+i][c+j] == 'X') nums++;
            if(wrap && !grid.inBounds(r+i,c+j))
            {
                if(grid[(r+i+grid.numRows())%grid.numRows()][(c+j+grid.numCols())%grid.numCols()] == 'X') nums++;
            }
        }

    return nums;
}


/*
 < Cells (X) live and die by the following rules:
           < - A cell with 1 or fewer neighbors dies.
           < - Locations with 2 neighbors remain stable.
           < - Locations with 3 neighbors will create life.
           < - A cell with 4 or more neighbors dies.
*/
void newLife(int i,int j,int nums,Grid<char> & grid,Grid<char> & Newgrid,LifeGUI & gui)
{

    switch (nums) {
    case 0:
        Newgrid[i][j] = '-';
        gui.drawCell(i,j,false);
        break;
    case 1:
        Newgrid[i][j] = '-';
        gui.drawCell(i,j,false);
        break;
    case 2:
        Newgrid[i][j] = grid[i][j];
        if(grid[i][j] == 'X') gui.drawCell(i,j,true);
        if(grid[i][j] == '-') gui.drawCell(i,j,false);
        break;
    case 3:
        Newgrid[i][j] = 'X';
        gui.drawCell(i,j,true);
        break;
    default:
        Newgrid[i][j] = '-';
        gui.drawCell(i,j,false);
        break;
    }
}



int main()
{
    WelcomeM();

    ifstream input;
    string name;

    //获取文件
    getFile(input,name);

    //提前声明网格
    Grid<char> grid;

    //随机情况
    if(equalsIgnoreCase("Random",name))
    {
        grid = CreateRandom();

    }

    //读取文件情况
    else{
    //读取文件
    string rows,columns;
    getline(input,rows);
    int r = stringToInteger(rows);

    getline(input,columns);
    int c = stringToInteger(columns);

    string word;
    Grid<char> gridReadFile(r,c);

    grid = gridReadFile;

    for(int i = 0;i < r;i++)
    {
        getline(input,word);
        for(int j = 0;j < c;j++)
            grid[i][j] = word[j];
    }

    input.close();

    }


    //yes or no
    bool wrap = getYesOrNo("Should the simulation wrap around the grid (y/n)?","y","n");


    showgrid(grid);
    //gui展示
    LifeGUI gui;
    gui.resize(grid.numRows(),grid.numCols());


    //选择command模式
    command(grid,wrap,gui);

    cout << "Have a nice Life!" << endl;
    return 0;
}



