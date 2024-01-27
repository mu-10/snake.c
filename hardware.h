#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
//Windows Libraries
#include <conio.h>
#include <windows.h>
void clrscr(){
    // Clears the screen, disabling the cursor
    system("cls");
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
    return;
}
void gotoxy(int x, int y){
    // Sets the cursor at position (x,y)
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}


#else
//Linux-macOS Libraries
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

//http://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

//http://www.experts-exchange.com/Programming/Languages/C/Q_10119844.html - posted by jos
int getch() {
    int c;
    system("stty raw");
    c=getchar();
    printf("\r     "); // Typed character replaced, stty raw -echo doesn't fix it
    system("stty sane");
    return(c);
}

void clrscr() {
    // Clears the screen
    system("clear");
    return;
}
void gotoxy(int x,int y){
    // Sets the cursor at position (x,y)
    printf("%c[%d;%df",0x1B,y,x);
}
//End linux-macOS functions
#endif
