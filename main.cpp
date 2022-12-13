#include <iostream>
#include <curses.h> // manipulação de tela, 
#include <cstdlib> // para a função rand();
#include <utility> // para usar a função pair que armazena a localização de cada parte da cobra
#include <list> // Vector permite uma rapida movimentação no primeiro e último termo

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
    int snakelen=1;

    list <pair<int, int>> snakePosi;
    snakePosi.push_back(make_pair(1,2));
    list<pair<int, int>>::iterator itSnakePosi = snakePosi.begin();

    //using keypad is possible get direcional keys
    keypad(stdscr, TRUE);
    while(mv!='q'){
        mv = getch();

        // movimentação
        // 4 - LEFT ; 5 - RIGHT ; 2 - DOWN ; 3 - UP
        if ((mv == 4 || mv == 5 || mv == 2 || mv == 3) && !isPressed){
            isPressed=true;
            
        }
        if (mv == 4) {dir = 4;} // LEFT
        else if (mv == 5) {dir = 3;} // RIGHT
        else if (mv == 2) {dir = 1;} // DOWN
        else if (mv == 3) {dir = 2;} // UP

        // move e apaga o anterior 
        for (int i=0; i<snakelen; i++){
        if (isPressed && dir == 1) { hAltura ++; mvprintw(hAltura-1, hComprimento, " "); mvprintw(hAltura, hComprimento, "%c", 219); }
        else if (isPressed && dir == 2) { hAltura --; mvprintw(hAltura+1, hComprimento, " "); mvprintw(hAltura, hComprimento, "%c", 219);}
        else if (isPressed && dir == 3) { hComprimento ++; mvprintw(hAltura, hComprimento-1, " "); mvprintw(hAltura, hComprimento, "%c", 219);}
        else if (isPressed && dir == 4) { hComprimento --; mvprintw(hAltura, hComprimento+1, " "); mvprintw(hAltura, hComprimento, "%c",219);}
        }

        //define o local onde o jogador tem qeu ir para ganhar pontos
        if (score == 0 && cont == 0){ premioX = rand()%altura; premioY = rand()%comprimento; cont ++;}
        else if (hAltura==premioX && hComprimento==premioY) { score ++; premioX = rand()%altura; premioY = rand()%comprimento; }
        mvprintw(premioX, premioY, "p");
        napms(100);
        mvprintw(0, 0, "%d", score); // mostra o score


        snakePosi.push_front(make_pair(hAltura, hComprimento));
        itSnakePosi = snakePosi.begin();
        mvprintw(0, (comprimento/2), "%d - %d", itSnakePosi->first, itSnakePosi->second);
        snakePosi.pop_back();

    }
    getch();
    endwin();
    return 0;
}