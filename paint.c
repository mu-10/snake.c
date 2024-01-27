#include "paint.h"

#include <math.h>
#include <stdio.h>


// TODO copy functions that you implemented in assignment 2a here

void image_print(int I[NROWS][NCOLS])
{
    for (int row = 0; row < NROWS; ++row)
    {
        for (int col = 0; col < NCOLS; ++col)
        {
            printf("%c", I[row][col]);
        }
        printf("\n");
    }
}

void image_init(int I[NROWS][NCOLS], symbols_t symbol)
{
    // Here you should set all values of I to symbol
    // A double for-loop will do the job
    for (int row = 0; row < NROWS; row++)
    {
        for (int col = 0; col < NCOLS; col++)
        {
            I[row][col] = symbol;
        }
    }
}

void add_point(int I[NROWS][NCOLS], symbols_t symbol, int col, int row)
{
    // Here you shall only set I[row][col], but only if col and row
    // have valid values for setting I.
    if (row >= 0 && row < NROWS && col >= 0 && col < NCOLS)
    {
        I[row][col] = symbol;
    }
}

void add_line_hori(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int length)
{
    // Add your code here
    // Starting with this function, you should use add_point to set I's values
    // This means that you in this function don't need to check if the line is
    // fully inside the image
    for (int l = 0; l < length; l++)
    {
        add_point(I, symbol, (col0 + l), row0);
    }
}

void add_line_vert(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int length)
{
    // Add your code here
    for (int l = 0; l < length; l++)
    {
        add_point(I, symbol, col0, (row0 + l));
    }
}

void add_rectangle(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int lcol, int lrow)
{
    // Add the top line of the rectangle
    add_line_hori(I, symbol, col0, row0, lcol);

    // Add the bottom line of the rectangle
    add_line_hori(I, symbol, col0, row0 + lrow - 1, lcol);

    // Add the left line of the rectangle
    add_line_vert(I, symbol, col0, row0, lrow);

    // Add the right line of the rectangle
    add_line_vert(I, symbol, col0 + lcol - 1, row0, lrow);
}

// Adds a n symbols, with positions defined of the 1D arrays cols and rows.
void add_points(int I[NROWS][NCOLS], symbols_t symbol, int cols[], int rows[], int n)
{
    for (int x = 0; x < n; x++)
    {
        add_point(I, symbol, cols[x], rows[x]);
    }
}

// Adds a diagonal upsloping line to I, using symbol as marker.
// The line starts at [row0,col0], and have length l.
void add_line_up(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int length)
{
    for (int x = row0; x > (row0 - length); x--)
    {
        add_point(I, symbol, col0, x);
        col0++;
    }
}

// Adds a diagonal downsloping line to I, using symbol as marker.
// The line starts at [row0,col0], and have length l.
void add_line_down(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int length)
{
    for (int x = row0; x < (row0 + length); x++)
    {
        add_point(I, symbol, col0, x);
        col0++;
    }
};

// The centre of the circle is at [row0,col0], and the radius is r.
void add_circle(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, double r)
{
    for (int y = row0 - r; y <= row0 + r; ++y)
    {
        for (int x = col0 - r; x <= col0 + r; ++x)
        {
            //(x-col0)^2+(y-row0)^2=r^2;
            if ((x - col0) * (x - col0) + (y - row0) * (y - row0) <= r * r)
            {
                add_point(I, symbol, x, y);
            }
        }
    }
}