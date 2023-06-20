//
// Created by Ferdinand on 2022. 05. 06..
//

#ifndef NHF4_TREE_H
#define NHF4_TREE_H
#include "node.h"
#include "io.h"
#include "LinkedList.h"





class Tree {
    //Beolvasott fájl tartalama, ebből épül a bináris fa
    std::string seed;
    //A tárolt bináris fa gyökerére mutató pointer
    Node<std::string>* root;
    //A tárolt lánvolt listára mutató pointer
    LinkedList<std::string>* list;
public:
    //konstruktor
    explicit Tree(Reader* FR);
    void freeBinTree(Node<std::string>* node) {
        if(node == nullptr) return;
        Node<std::string>* left = node->getYes();
        Node<std::string>* right = node->getNo();
        freeBinTree(left);
        delete node;
        freeBinTree(right);
    }
    ~Tree() {
        freeBinTree(root);
        delete list;
    }
    //Egy adott Node szülőjének megkeresése a bináris fában
    Node<std::string>* FindParent(size_t index) const ;
    //root getter
    Node<std::string>* getRoot ()const  {return root;}
    //Kiírja a kért Node-t a paramétereket egymás alá(data, index, yes, no)
    void printNode(Node<std::string>* pNode)const ;
    //Kiírja a binársi fát
    void printTree(Node<std::string>* currentNode)const ;
    //Beszúr egy új kérdést(és az erre adott válaszokat) a bináris fába, a láncolt listába, és kimenti azt fájlba
    void InsertNewNode(std::string& newQ, std::string& newY, std::string& newN, Node<std::string>* where, Writer* FW);
    //Eldönti egy Node-ról hogy leaf Node-e.
    static bool leafNode(Node<std::string> *pNode) ;
    //list getter
    LinkedList<std::string>* getList() const {return list;}
    //memória felszabadítás

};
#endif //NHF4_TREE_H
