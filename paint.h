#ifndef __PAINT_H__
#define __PAINT_H__

// Use externally defined sizes
extern const int NCOLS;
extern const int NROWS;

// Define the symbols at hand for the painting
// World elements for the snake world
typedef enum {
    APPLE='@', GRASS='.', SNAKE_BODY='#', SNAKE_HEAD='O', WALL='+'
} symbols_t;

// 
// The functions
//

// For all functions below, adding an object, it is allowed that the object 
// extends outside of the image. The part outsiude of the image is ignored.

// Prints the image defined in I. 
// The 2D array shall contain printable ASCII numbers
void image_print(int I[NROWS][NCOLS]);

// Set all values if I to symbol
void image_init(int I[NROWS][NCOLS], symbols_t symbol);

// Sets I[row][col] to symbol. 
// If this matches a postion outside of the image, nothing is done.
void add_point(int I[NROWS][NCOLS], symbols_t symbol, int col, int row);

// Adds a horisontal line to I, using symbol as marker.
// The line starts at [row0,col0], and have length l.
void add_line_hori(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int length);

// Adds a vertical line to I, using symbol as marker.
// The line starts at [row0,col0], and have length l.
void add_line_vert(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int length);

// Adds a rectangle to I, using symbol as marker.
// One corner of the rectangle is at [row0,col0],
// and it extends towards higher row and column 
// index with size lrow and lcol, respectively.
void add_rectangle(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int lcol, int lrow);

// Adds a n symbols, with positions defined of the 1D arrays cols and rows.
void add_points(int I[NROWS][NCOLS], symbols_t symbol, int cols[], int rows[], int n);

// Adds a diagonal upsloping line to I, using symbol as marker.
// The line starts at [row0,col0], and have length l.
void add_line_up(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int length);

// Adds a diagonal downsloping line to I, using symbol as marker.
// The line starts at [row0,col0], and have length l.
void add_line_down(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, int length);

// Adds a filled circle to I, using symbol as marker.
// The centre of the circle is at [row0,col0], and the radius is r.
void add_circle(int I[NROWS][NCOLS], symbols_t symbol, int col0, int row0, double r);

#endif
