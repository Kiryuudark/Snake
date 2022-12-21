#include <iostream>
#include <curses.h> // manipulação de tela, 
#include <cstdlib> // para a função rand();
#include <utility> // para usar a função pair que armazena a localização de cada parte da cobra
#include <list> // list permite uma rapida movimentação no primeiro e último termo


// verificar colisão com o próprio corpo. 
// apagar o anterior do corpo ao invés de apagar todo o mapa
// condição para vencer

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
    int bodyCollision=0;

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
        if (mv == 4) { if (dir != 3) {dir = 4; }} // LEFT
        else if (mv == 5) {if (dir != 4) {dir = 3;}} // RIGHT
        else if (mv == 2) {if (dir != 2) {dir = 1;};} // DOWN
        else if (mv == 3) {if (dir != 1) {dir = 2;}} // UP

        // move e apaga o anterior 
        clear();
        if (isPressed && dir == 1) { 
            hAltura++;
            while(itSnakePosi!=snakePosi.end()){
            mvprintw(itSnakePosi->first, itSnakePosi->second, "%c", 'O'); 
            itSnakePosi++;
            }
        }
        else if (isPressed && dir == 2) { 
            hAltura --;  
            while(itSnakePosi!=snakePosi.end()){
            mvprintw(itSnakePosi->first, itSnakePosi->second, "%c", 'O'); 
            itSnakePosi++;
            }

        }
        else if (isPressed && dir == 3) { 
            hComprimento ++;  
            while(itSnakePosi!=snakePosi.end()){
            mvprintw(itSnakePosi->first, itSnakePosi->second, "%c", 'O'); 
            itSnakePosi++;
            }

        }
        else if (isPressed && dir == 4) { 
            hComprimento --;  
            while(itSnakePosi!=snakePosi.end()){
            mvprintw(itSnakePosi->first, itSnakePosi->second, "%c", 'O'); 
            itSnakePosi++;
            }
        }
        
        itSnakePosi->first=hAltura; itSnakePosi->second=hComprimento;
        itSnakePosi = snakePosi.begin();

        //define o local onde o jogador tem que ir para ganhar pontos
        if (cont == 0){ premioX = rand()%altura; premioY = rand()%comprimento; cont ++;}
        else if (itSnakePosi->first==premioX && itSnakePosi->second==premioY) { 
            score ++; 
            do{
            bodyCollision=0;
            premioX = rand()%altura; premioY = rand()%comprimento;
            while(itSnakePosi!=snakePosi.end()){
                if(itSnakePosi->first==premioX && itSnakePosi->second==premioY){
                    bodyCollision++;
                }
                itSnakePosi++;
            }   
            }while(bodyCollision>0);
            snakePosi.push_back(make_pair(hAltura+1,hComprimento+1)); 
        }

        mvprintw(premioX, premioY, "O");
        napms(150);
        mvprintw(0, 0, "%d", score); // mostra o score
        
        mvprintw(0, (comprimento/2), "%d - %d", itSnakePosi->first, itSnakePosi->second); //mostra a posição da cabeça
        
        snakePosi.push_front(make_pair(hAltura, hComprimento));
        itSnakePosi = snakePosi.begin();

        snakePosi.pop_back();

    }
    getch();
    endwin();
    return 0;
}