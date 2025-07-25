/*
 * File: fractals.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains fractal problems for CS106B.
 */


#include "fractals.h"
#include <cmath>
#include"complex.h"

using namespace std;

const int LEAF_COLOR = 0x2e8b57;   /* Color of all leaves of recursive tree (level 1) */
const int BRANCH_COLOR = 0x8b7765; /* Color of all branches of recursive tree (level >=2) */

/**
 * Draws a Sierpinski triangle of the specified size and order, placing its
 * top-left corner at position (x, y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the Sierpinski triangle.
 * @param x - The x coordinate of the top-left corner of the triangle.
 * @param y - The y coordinate of the top-left corner of the triangle.
 * @param size - The length of one side of the triangle.
 * @param order - The order of the fractal.
 */

void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order) {
    // TODO: write this function
    if(x < 0 || y < 0 || size < 0 || order < 0) throw("Invalid");
    if(order == 0) return;
    double h = size*sin(60 * 3.14159265347578/180);//没有抗锯齿

    drawSierpinskiTriangle(gw,x,y,size/2,order-1);
    drawSierpinskiTriangle(gw,x+size/2,y,size/2,order-1);
    drawSierpinskiTriangle(gw,x+size/4,y+h/2,size/2,order-1);

    if(order == 1)
    {
        gw.drawLine(x,y,x+size,y);
        gw.drawLine(x,y,x+size/2,y+h);
        gw.drawLine(x+size,y,x+size/2,y+h);
    }
}

/*Extra
int colours = 0;
void drawSierpinskiTriangleExtra(GWindow& gw, double x, double y, double size, int order) {
    // TODO: write this function
    if(x < 0 || y < 0 || size < 0 || order < 0) throw("Invalid");
    if(order == 0) return;
    double h = size*sin(60 * 3.14159265347578/180);//没有抗锯齿

    string colorset[2] = {"red","blue"};
    colours ++;
    gw.setColor(colorset[colours%2]);
    drawSierpinskiTriangle(gw,x,y,size/2,order-1);
    drawSierpinskiTriangle(gw,x+size/2,y,size/2,order-1);
    colours ++;
    gw.setColor(colorset[colours%2]);
    drawSierpinskiTriangle(gw,x+size/4,y+h/2,size/2,order-1);


    if(order == 1)
    {
        gw.drawLine(x,y,x+size,y);
        gw.drawLine(x,y,x+size/2,y+h);
        gw.drawLine(x+size,y,x+size/2,y+h);
    }
}
*/



/**
 * Draws a recursive tree fractal image of the specified size and order,
 * placing the bounding box's top-left corner at position (x,y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the recursive tree.
 * @param x - The x coordinate of the top-left corner of the bounding box.
 * @param y - The y coordinate of the top-left corner of the bounding box.
 * @param size - The length of one side of the bounding box.
 * @param order - The order of the fractal.
 */

void drawTreeHelper(GWindow& gw, double x, double y, double size, int order,int r){
    if(x < 0 || y < 0 || size < 0 || order < 0) throw("Invalid");

    if(order == 0) return ;//边界问题

    //调色
    if(order == 1) gw.setColor("#2e8b57");
    else gw.setColor("#8b7765");

    //drawPolarLine返回Gpoint的值 : p1 = drawPolarLine(p0,size,r)
    GPoint p = gw.drawPolarLine(x,y,size,r);

    for(int i = -3 ; i <= 3 ; i ++)
    {
        drawTreeHelper(gw,p.getX(),p.getY(),size/2,order - 1,r + 15*i);
    }
}

void drawTree(GWindow& gw, double x, double y, double size, int order) {
    // TODO: write this function
    drawTreeHelper(gw,x+size/2,y+size,size/2,order,90);
}


/**
 * Draws a Mandelbrot Set in the graphical window give, with maxIterations
 * (size in GUI) and in a given color (zero for palette)
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the Mandelbrot set.
 * @param minX - left-most column of grid
 * @param incX - increment value of columns of grid
 * @param minY - top-most row of grid
 * @param incY - increment value of rows of grid
 * @param maxIterations - The maximum number of iterations to run recursive step
 * @param color - The color of the fractal; zero if palette is to be used
 */
void mandelbrotSet(GWindow& gw, double minX, double incX,
                   double minY, double incY, int maxIterations, int color) {

    // Creates palette of colors
    // To use palette:
    // pixels[r][c] = palette[numIterations % palette.size()];
    Vector<int> palette = setPalette();

    int width = gw.getCanvasWidth();
    int height = gw.getCanvasHeight();
    GBufferedImage image(width,height,0xffffff);
    gw.add(&image);
    Grid<int> pixels = image.toGrid(); // Convert image to grid

    // TODO: Put your Mandelbrot Set code here

    for(int r = 0 ; r < pixels.numRows() ; r ++)
        for(int c = 0 ; c < pixels.numCols() ; c ++)
        {
            int numIterations = mandelbrotSetIterations(Complex(minX + c * incX,minY + r * incY),maxIterations);
            if(color){
                if(numIterations == maxIterations) pixels[r][c] = color;
            }
            else{
                if(numIterations) pixels[r][c] = palette[numIterations % palette.size()];
            }
        }

    image.fromGrid(pixels); // Converts and puts the grid back into the image
}

/**
 * Runs the Mandelbrot Set recursive formula on complex number c a maximum
 * of maxIterations times.
 *
 * This will be called by you. Think about how this fits with the other two functions.
 *
 * @param c - Complex number to use for recursive formula.
 * @param maxIterations - The maximum number of iterations to run recursive step
 * @return number of iterations needed to determine if c is unbounded
 */
int mandelbrotSetIterationsHelper(Complex z, Complex c, int remainingIterations,int &maxIterations); //提前声明 Helper
int mandelbrotSetIterations(Complex c, int maxIterations) {
    // TODO: Write this function
    return mandelbrotSetIterationsHelper(Complex(0,0),c,maxIterations,maxIterations); // Only here to make this compile
}
/**
 * An iteration of the Mandelbrot Set recursive formula with given values z and c, to
 * run for a maximum of maxIterations.
 *
 * This will be called by you. Think about how this fits with the other two functions.
 *
 * @param z - Complex number for a given number of iterations
 * @param c - Complex number to use for recursive formula.
 * @param remainingIterations - The remaining number of iterations to run recursive step
 * @return number of iterations needed to determine if c is unbounded
 */

//此Extra似乎这里缺少color map?
int mandelbrotSetIterationsHelper(Complex z, Complex c, int remainingIterations,int &maxIterations) {
    // TODO: write this function
    Complex cpx = z * z + c;
    if(cpx.abs() > 4 || remainingIterations == 0) return maxIterations - remainingIterations;
    else return mandelbrotSetIterationsHelper(cpx,c,remainingIterations - 1,maxIterations);
    // Only here to make this compile
}

// Helper function to set the palette
Vector<int> setPalette() {
    Vector<int> colors;

    // Feel free to replace with any palette.
    // You can find palettes at:
    // http://www.colourlovers.com/palettes

    // Example palettes:
    // http://www.colourlovers.com/palette/4480793/in_the_middle
    // string colorSt = "#A0B965,#908F84,#BF3C43,#9D8E70,#C9BE91,#A0B965,#908F84,#BF3C43";

    // http://www.colourlovers.com/palette/4480786/Classy_Glass
    // string colorSt = "#9AB0E9,#C47624,#25269A,#B72202,#00002E,#9AB0E9,#C47624,#25269A";

    // The following is the "Hope" palette:
    // http://www.colourlovers.com/palette/524048/Hope
    string colorSt =  "#04182B,#5A8C8C,#F2D99D,#738585,#AB1111,#04182B,#5A8C8C,#F2D99D";
    Vector<string>colorsStrVec = stringSplit(colorSt,",");
    for (string color : colorsStrVec) {
        colors.add(convertColorToRGB(trim(color)));
    }
    return colors;
}

/*
Possible Extra Features
Here are some ideas for extra features that you could add to your program for a very small amount of extra credit:
Sierpinski colors: Make your Sierpinski triangle draw different levels in different colors.(half finish)
Mandelbrot Set Gradient: The Wikipedia page on the Mandelbrot Set discusses ways to make a smooth gradient for the images, as opposed to using a palette. Implement a smooth gradient in your code.
Mandelbrot Set iterations: The number of iterations needed to get a clear picture depends on the zoom. In the GUI, you can manually set this value, but you might want to use the minX, incX, and minY, incY parameters to determine the number of iterations, rather than the maxIterations passed into the function.
(Advanced) Mandelbrot Parallelism: Every point in the Mandelbrot set is independent of every other point, and thus this part of the assignment can be parallelized. You might do this using PThreads.
Add another fractal: Add another fractal function representing a fractal image you like. You'll have to do some reconstructive surgery on the GUI to achieve this, and/or swap it in place of one of the existing fractal functions (make sure to turn in your non-extra-feature version first, so as not to lose your solution code).
Other: If you have your own creative idea for an extra feature, ask your SL and/or the instructor about it.
*/
