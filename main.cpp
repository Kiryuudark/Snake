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
    int a=0;

    //using keypad is possible get direcional keys
    keypad(stdscr, TRUE);
    while(mv!='q'){
        mv = getch();
        //timelapse to move snake
        //move_snake(altura, comprimento, mv);
        // 4 - LEFT ; 5 - RIGHT ; 2 - DOWN ; 3 - UP
        if ((mv == 4 || mv == 5 || mv == 2 || mv == 3) && !isPressed){
            isPressed=true;
            mvprintw(hAltura, hComprimento, " true ");
        }
        else {
            mvprintw(hAltura+a-1, hComprimento, "     ");
            mvprintw(hAltura+a, hComprimento, "false");
            if (isPressed){
                a++;
            }
        }
        refresh();


        napms(500);
    }
    

    getch();
    endwin();
    return 0;
}