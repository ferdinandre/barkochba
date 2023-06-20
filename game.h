//
// Created by Ferdinand on 2022. 05. 06..
//

#ifndef NHF4_GAME_H
#define NHF4_GAME_H
#include "io.h"
#include "tree.h"

///Game osztaly
/*
 * a root nevu adattag egy Tree-re mutato pointer, itt van tarolva a binaris fa
 */
class Game {
    Tree* root; //Binaris fa gyokere
    Reader* FR; //File olvasó
    Reader* CR; //Konzol Olvasó
    Writer* FW; //File íro
    Writer* CW; //Konzol iro
public:
    ///Game konstruktora
    /*
     * Parameterek:
     * fr - Reader objektumra mutato pointer. Ezt a readert hasznalja a binarisfa beolvasahoz
     * cr - Reader objektumra mutato pointer. Ezzel fogad bemenetet a kulvilagtol(user).
     * fw - Writer objektumra mutato pointer. Ezzel a writerrel menti ki a binarisfat. Hogy hova azt nem tudja, nem is kell neki.
     * cw - Writer objektumra mutato pointer. Ezzel ad kimenetet a kulviagnak(user).
     *
     */
    Game(Reader* fr, Reader* cr, Writer* fw, Writer* cw) :FR(fr), CR(cr), FW(fw), CW(cw){
        try {
            root = new Tree(FR);
        }catch(FileNotFound& f) {
            cw->write("Kivetel tortent: ");
            cw->write(f.what());
            abort();
        }
    }
    //Vissztaer a root-ra mutato pointerrel
    Tree* getRoot() {return root;}

    ///Destruktor. Felszabaditja a readereket es a writereket, majd meghivjaa Tree del() fuggvenyet, ami tovabbi felszabaditasokat vegez(binaris fa, lancolt lista)
    ~Game() {
        delete FR;
        delete CR;
        delete FW;
        delete CW;
        delete root;
    }
    //Game objektumot es annak dinamikusan foglalt adattagjait felszabadito fuggveny

    ///Ez a fuggveny vezerli a jatekot.
    void start() const;
};
#endif //NHF4_GAME_H
