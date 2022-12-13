#include <iostream>
#include <curses.h> // manipulação de tela, 
#include <cstdlib> // para a função rand();

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
    int premioX, premioY;
    int score=0, cont=0;

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
        else if (mv == 2) {dir = 1;} // DOWN
        else if (mv == 3) {dir = 2;} // UP
        
        if (isPressed && dir == 1) { hAltura ++; mvprintw(hAltura-1, hComprimento, "         "); mvprintw(hAltura, hComprimento, "%c", 219); }
        else if (isPressed && dir == 2) { hAltura --; mvprintw(hAltura+1, hComprimento, "         "); mvprintw(hAltura, hComprimento, "%c", 219);}
        else if (isPressed && dir == 3) { hComprimento ++; mvprintw(hAltura, hComprimento-1, "         "); mvprintw(hAltura, hComprimento, "%c", 219);}
        else if (isPressed && dir == 4) { hComprimento --; mvprintw(hAltura, hComprimento+1, "         "); mvprintw(hAltura, hComprimento, "%c",219);}
        refresh();

        if (score == 0 && cont == 0){ premioX = rand()%altura; premioY = rand()%comprimento; cont ++;}
        else if (hAltura==premioX && hComprimento==premioY) { score ++; premioX = rand()%altura; premioY = rand()%comprimento; }
        mvprintw(premioX, premioY, "p");
        napms(400);
        mvprintw(0, 0, "%d", score);
    }
    
    mvprintw(10, 10, "%d", score);
    getch();
    endwin();
    return 0;
}