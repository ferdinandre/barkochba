//
// Created by Ferdinand on 2022. 05. 07..
//
#include "memtrace.h"
#include "exception.h"
#include "game.h"
void Game::start() const {
    ///Jatek kezdete
    CW->write("Kezdodjon a jatek!\nGondolj valamire, es mindjart kitalalom'\nElso kerdes:");
    std::string another_game;
    do {
        //A root-tol indulunk
        Node<std::string>* temp = root->getRoot();
        //Es addig lepkedunk lefele amig leaf node-ba nem utkozunk
        while(!Tree::leafNode(temp)) {
            //Feltesszuk akerdest a usernek
            CW->write(temp->getData());
            //Beolvassuk a ra adott valaszt
            std::string answer = CR->read();
            //Es a valasz fuggvenyeben
            if(answer == "I") {
                //Vagy balra,
                temp = temp->getYes();
            }else if(answer == "N") {
                //vagy jobbra lepunk le.
                temp = temp->getNo();
            }
        }
        //Rakerdezunk
        CW->write("Rakerdezhetek?");
        CW->write(temp->getData());
        //Es valaszt varunk(I/N)
        std::string answer;
        answer = CR->read();
        //Ha a valasz nemléges
        if(answer == "N") {
            //Megkerjuk a user-t, hogy adjon meg egy uj kerdest
            CW->write("Adjon meg egy uj kerdest");
            std::string newQuestion = CR->read();
            //Megkerjuk, hogy adjon meg egy erre adott kovetkezo kerdeset igen valasz eseten
            CW->write("Ha igen lenne a valsz mi lenne a kovetkezo kerdes?");
            std::string newYes = CR->read();
            //Megkerjuk, hogy adjon meg egy erre adott kovetkezo kerdeset nem valasz eseten
            CW->write("Ha nem lenne a valasz mi lenne a kovetkezo kerdes?");
            std::string newNo = CR->read();
            //termeszetesen ezeket mind beolvassuk
            //Es letrehozunk egy uj Node-ot a binaris faban, a lancolt listaban, es kiirjuk az uj fat fileba.
            root->InsertNewNode(newQuestion, newYes, newNo, temp, FW);


            CW->write("Jatsszunk meg egyet?");
            another_game = CR->read();
        }else
            if(answer == "I") {
                CW->write("Kitalatam!");
                CW->write("Jatsszunk meg egyet?");
                another_game = CR->read();
            }else {
                CW->write("Nem ertelemezett bemenet: ");
                CW->write(answer);
            }
    }while(another_game == "I");

}
