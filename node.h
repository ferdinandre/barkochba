//
// Created by Ferdinand on 2022. 05. 06..
//

#ifndef NHF4_NODE_H
#define NHF4_NODE_H
#include <iostream>



template<class T>
class Node{
    //Index, masneven sorszam. Ez azert kell, hogy amikor a binaris fat epitjuk fel, hozza tudjuk kotni a szulojehez
    size_t index;
    //Tarolt adat
    T data;
    //Balra lefele mutato pointer
    Node* yes;
    //Jobbra lefele mutato pointer
    Node* no;
public:
    // Node konstruktor, ket parameterrel: data: ez lesz a data, index: ez lesz az idx, a pointerek alap esetben nullpointerek
    Node(T data, size_t idx):index(idx), data(data), yes(nullptr), no(nullptr) {}
    ~Node() = default;
    // A megadott ertekre allitja az adattagot
    void setData(T& newData) { data = newData; }
    // A megadott ertekre allitja a yes pointert
    void setYes(Node* newYes) { yes = newYes;}
    // A megadott ertekre allitja a no pointert
    void setNo(Node* newNo) {no = newNo;}

    size_t getIndex()const {return index;}
    T getData()const  {return data;}
    Node* getYes()const  {return yes;}
    Node* getNo() const {return no;}
};


#endif //NHF4_NODE_H
