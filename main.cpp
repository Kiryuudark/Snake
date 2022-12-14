#include <iostream>
#include <curses.h> // manipulação de tela, 
#include <cstdlib> // para a função rand();
#include <utility> // para usar a função pair que armazena a localização de cada parte da cobra
#include <list> // list permite uma rapida movimentação no primeiro e último termo

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
    int snakelen=5;
    int i;

    list <pair<int, int>> snakePosi;
    snakePosi.push_back(make_pair(hAltura,hComprimento));
    list<pair<int, int>>::iterator itSnakePosi = snakePosi.end(), itSnakeAux = snakePosi.end();
    int aux;

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

        // itSnakePosi--;
        // itSnakeAux--;

        // move e apaga o anterior 
        clear();
        if (isPressed && dir == 1) { 
            hAltura++;
            while(itSnakePosi!=snakePosi.end()){
            mvprintw(itSnakePosi->first, itSnakePosi->second, "%c", 219); 
            itSnakePosi++;
            }
        }
        else if (isPressed && dir == 2) { 
            hAltura --;  
            while(itSnakePosi!=snakePosi.end()){
            mvprintw(itSnakePosi->first, itSnakePosi->second, "%c", 219); 
            itSnakePosi++;
            }

        }
        else if (isPressed && dir == 3) { 
            hComprimento ++;  
            while(itSnakePosi!=snakePosi.end()){
            mvprintw(itSnakePosi->first, itSnakePosi->second, "%c", 219); 
            itSnakePosi++;
            }

        }
        else if (isPressed && dir == 4) { 
            hComprimento --;  
            while(itSnakePosi!=snakePosi.end()){
            mvprintw(itSnakePosi->first, itSnakePosi->second, "%c", 219); 
            itSnakePosi++;
            }
        }
        
        itSnakePosi = snakePosi.begin();
        itSnakePosi->first=hAltura; itSnakePosi->second=hComprimento;


        //define o local onde o jogador tem qeu ir para ganhar pontos
        if (score == 0 && cont == 0){ premioX = rand()%altura; premioY = rand()%comprimento; cont ++;}
        else if (hAltura==premioX && hComprimento==premioY) { score ++; premioX = rand()%altura; premioY = rand()%comprimento; snakePosi.push_back(make_pair(altura,comprimento)); }
        mvprintw(premioX, premioY, "p");
        napms(150);
        mvprintw(0, 0, "%d", score); // mostra o score
        
        mvprintw(0, (comprimento/2), "%d - %d", itSnakePosi->first, itSnakePosi->second);
        
        snakePosi.push_front(make_pair(hAltura, hComprimento));
        itSnakePosi = snakePosi.begin();
        i=0;
        //mvprintw(itSnakePosi->first, itSnakePosi->second, " ");

        snakePosi.pop_back();

    }
    getch();
    endwin();
    return 0;
}