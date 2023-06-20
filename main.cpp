#include "memtrace.h"
#include "io.h"
#include "game.h"

#ifndef CPORTA
int main() {
    Writer* FW = new FileWriter("seed.txt");
    Reader* FR = new FileReader( "seed.txt");
    Writer* CW = new ConsoleWriter();
    Reader* CR = new ConsoleReader();

    Game* newGame = new Game(FR, CR, FW, CW);
    newGame->start();
    delete newGame;
}

#endif
