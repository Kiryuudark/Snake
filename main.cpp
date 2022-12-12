#include <iostream>
#include <curses.h>

using namespace std;

int main() {

    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    char mv;
    int altura, comprimento;
    getmaxyx(stdscr, altura, comprimento);
    int hAltura = altura/2, hComprimento = comprimento/2;
    bool isPressed = false;
    int dir;

    //using keypad is possible get direcional keys
    keypad(stdscr, TRUE);
    while(mv!='q'){
        mv = getch();
        //timelapse to move snake
        //move_snake(altura, comprimento, mv);
        // 4 - LEFT ; 5 - RIGHT ; 2 - DOWN ; 3 - UP
        if ((mv == 4 || mv == 5 || mv == 2 || mv == 3) && !isPressed){
            isPressed=true;
            
        }
            if (mv == 4) {dir = 4;} // LEFT
            else if (mv == 5) {dir = 3;} // RIGHT
            else if (mv == 2) {dir = 1;}
            else if (mv == 3) {dir = 2;}
            
            if (isPressed && dir == 1) { hAltura ++; mvprintw(hAltura-1, hComprimento, "         "); mvprintw(hAltura, hComprimento, "false"); }
            else if (isPressed && dir == 2) { hAltura --; mvprintw(hAltura+1, hComprimento, "         "); mvprintw(hAltura, hComprimento, "false");}
            else if (isPressed && dir == 3) { hComprimento ++; mvprintw(hAltura, hComprimento-1, "         "); mvprintw(hAltura, hComprimento, "false");}
            else if (isPressed && dir == 4) { hComprimento --; mvprintw(hAltura, hComprimento+1, "         "); mvprintw(hAltura, hComprimento, "false");}
        refresh();


        napms(800);
    }
    

    getch();
    endwin();
    return 0;
}