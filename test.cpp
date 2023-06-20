//
// Created by Ferdinand on 2022. 05. 08..
//

#include "memtrace.h"

#include <iostream>
#include "io.h"
#include "game.h"
#include "exception.h"
#include "LinkedList.h"

///A teszteselésnél azért az std::cin-t és az std::cout-ot használom,
/// mert a tesztelések lefutása előtt a saját IO interfészemet(Reader, Writer) hibásnak tekintem,
/// az std::cout/cin-ről meg feltételezem hogy jól működik.

#ifdef CPORTA

void test0_IO() {
    //Megvizsgaljuk, hogy a kivetel dobas mukodik-e
    Reader* fr = new FileReader("nonexistent.txt");
    std::string exc;
    try {
        exc = fr->read();
        std::cerr <<"Valalmiert nem dobott kivetelt, pedig ezt vartuk";
        abort();
    }catch(FileNotFound& f) {
        std::cout << "Kivetel elkapva: " <<f.what() <<std::endl;
    }
    delete fr;
    //Először is kiírjuk ezt a stringet a fájlba("test0.txt");
    std::string toBeWritten = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    Writer* FileOut = new FileWriter("test0.txt");
    try {
        FileOut->write(toBeWritten);
    }catch(FileNotFound& d) {
        //Ha van hiba, elkapjuk, jelezzük
        std::cerr << d.what() <<std::endl;
        return;
    }
    //Ezután visszaolvassuk
    std::string readFromFile;
    Reader* FileIn = new FileReader("test0.txt");
    readFromFile = FileIn->read();
    //És egyenlőséget vizsgálunk
    if(toBeWritten != readFromFile) {
        std::cerr << "Fajl kezeles hiabs, vart: "<< toBeWritten<< ", kapott::" <<readFromFile <<std::endl;

    }else {
        //Ha a két string egyenlő, akkor sikeres a teszt
        std::cout << "Fajl kezeles sikeres, vart: "<< toBeWritten<< ", kapott::" <<readFromFile <<std::endl;
        std::cout << "0. teszt sikeres_(io.h)\n";
    }
    //FileNotFound kivetel tesztelese

    delete FileOut; delete FileIn;
}


void test1_Node() {
    //Létrehozunk 2db integer Node-ot 9 és 56 értékekkel
    auto* testNode1 = new Node<int>(9,1);
    auto*testNode2 = new Node<int>(56,2);
    ///Getter teszeK:
    //GetData
    if(9 != testNode1->getData()) {
        std::cerr <<"Hibas Node interfesz Node<int>::getData vart: 9, kapott: "<<testNode1->getData()<< std::endl;
        return;
    }
    if(56 != testNode2->getData()) {
        std::cerr <<"Hibas Node interfesz Node<int>::getData vart: 56, kapott: "<<testNode2->getData()<< std::endl;
        return;
    }
    //GetIndex
    if(1 != testNode1->getIndex()) {
        std::cerr <<"Hibas Node interfesz Node<int>::getIndex vart: 1, kapott: "<<testNode1->getIndex()<< std::endl;
        return;
    }
    if(2 != testNode2->getIndex()) {
        std::cerr <<"Hibas Node interfesz Node<int>::getIndex vart: 2, kapott: "<<testNode2->getIndex()<< std::endl;
        return;
    }
    //getYes
    if(nullptr != testNode1->getYes()) {
        std::cerr <<"Hibas Node interfesz Node<int>::getYes vart: nullptr, kapott: "<<testNode1->getYes()<< std::endl;
        return;
    }
    if(nullptr != testNode2->getYes()) {
        std::cerr <<"Hibas Node interfesz Node<int>::getYes vart: nullptr, kapott: "<<testNode2->getYes()<< std::endl;
        return;
    }
    //getNO
    if(nullptr != testNode1->getNo()) {
        std::cerr <<"Hibas Node interfesz Node<int>::getNo vart: nullptr, kapott: "<<testNode1->getNo()<< std::endl;
        return;
    }
    if(nullptr != testNode2->getNo()) {
        std::cerr <<"Hibas Node interfesz Node<int>::getNo vart: nullptr, kapott: "<<testNode2->getNo()<< std::endl;
        return;
    }
    ///Setter tesztek:
    //Beállítjuk, hogy testNode1 yes pointere testNode2-re, no pointere önmagára mutasson
    testNode1->setYes(testNode2);testNode1->setNo(testNode1);
    //Beállítjuk, hogy testNode2 no pointere testNode2-re, yes pointere önmagára mutasson
    testNode2->setNo(testNode1);testNode2->setYes(testNode2);
    //Beállítjuk ezeket az értékeket
    int newdata1 = 12152, newdata2 = 8731645;
    testNode1->setData(newdata1);testNode2->setData(newdata2);
    //getData
    if(12152 != testNode1->getData()) {
        std::cerr << "Hibas Node interfest Node<int>::getData vart:" << 12152 <<", kapott:" << testNode1->getData();
        return;
    }
    if(8731645 != testNode2->getData()) {
        std::cerr << "Hibas Node interfest Node<int>::getData vart:" << 8731645 <<", kapott:" << testNode2->getData();
        return;
    }
    //getYes
    if(testNode2 != testNode1->getYes()) {
        std::cerr <<"Hibas Node interfesz Node<int>::getYes vart:"<< testNode2 <<"kapott: "<<testNode1->getYes()<< std::endl;
        return;
    }
    if(testNode2 != testNode2->getYes()) {
        std::cerr <<"Hibas Node interfesz Node<int>::getYes vart:"<< testNode2 <<"kapott: "<<testNode2->getYes()<< std::endl;
        return;
    }
    //getNO
    if(testNode1 != testNode1->getNo()) {
        std::cerr <<"Hibas Node interfesz Node<int>::getYes vart:"<< testNode1 <<"kapott: "<<testNode1->getNo()<< std::endl;
        return;
    }
    if(testNode1 != testNode2->getNo()) {
        std::cerr <<"Hibas Node interfesz Node<int>::getYes vart:"<< testNode1 <<"kapott: "<<testNode2->getNo()<< std::endl;
        return;
    }
    delete testNode1;
    delete testNode2;
    std::cout << "1. teszt sikeres(Node<int>)\n";

}


void test2_LinkedListElement() {
    auto* first = new LinkedListElement<int>(34);
    auto* second = new LinkedListElement<int>(7445);
    ///Interfesz teszt. leteszteljuk elobb a gettereket, majd a setterket
    //getData
    if(34 != first->getData()) {
        std::cerr <<"Hibas LinkedListElement interfesz LinkedListElement<int>::getData vart: 34, kapott: "<<first->getData()<< std::endl;
        return;
    }
    if(7445 != second->getData()) {
        std::cerr <<"Hibas LinkedListElement interfesz LinkedListElement<int>::getData vart: 7445, kapott: "<<second->getData()<< std::endl;
        return;
    }
    //getNext
    if(nullptr != first->getNext()) {
        std::cerr <<"Hibas LinkedListElement interfesz LinkedListElement<int>::getNext vart: nullptr, kapott: "<<first->getNext()<< std::endl;
        return;
    }
    if(nullptr != first->getPrev()) {
        std::cerr <<"Hibas LinkedListElement interfesz LinkedListElement<int>::getPrev vart: nullptr, kapott: "<<first->getPrev()<< std::endl;
        return;
    }
    //getPrev
    if(nullptr != second->getNext()) {
        std::cerr <<"Hibas LinkedListElement interfesz LinkedListElement<int>::getNext vart: nullptr, kapott: "<<second->getNext()<< std::endl;
        return;
    }
    if(nullptr != second->getPrev()) {
        std::cerr <<"Hibas LinkedListElement interfesz LinkedListElement<int>::getPrev vart: nullptr, kapott: "<<second->getPrev()<< std::endl;
        return;
    }
    //Most beállítjük first mindkét pinterét secondre
    first->setNext(second);first->setPrev(second);
    //Most beállítjük second mindkét pinterét firstre
    second->setPrev(first);second->setNext(first);
    int newdata1 = 67, newdata2 = 253;
    first->setData(newdata1); second->setData(newdata2);
    if(67 != first->getData()) {
        std::cerr <<"Hibas LinkedListElement interfesz LinkedListElement<int>::getData vart: 67, kapott: "<<first->getData()<< std::endl;
        return;
    }
    if(253 != second->getData()) {
        std::cerr <<"Hibas LinkedListElement interfesz LinkedListElement<int>::getData vart: 253, kapott: "<<second->getData()<< std::endl;
        return;
    }
    if(second != first->getNext()){
        std::cerr <<"Hibas LinkedListElement interfesz LinkedListElement<int>::getNext vart:"<< second <<"kapott: "<<first->getNext()<< std::endl;
        return;
    }
    if(second != first->getPrev()) {
        std::cerr <<"Hibas LinkedListElement interfesz LinkedListElement<int>::getNext vart:"<< second <<"kapott: "<<first->getPrev()<< std::endl;
        return;
    }
    if(first != second->getNext()) {
        std::cerr <<"Hibas LinkedListElement interfesz LinkedListElement<int>::getNext vart:"<< first <<"kapott: "<<second->getNext()<< std::endl;
        return;
    }
    if(first != second->getPrev()) {
        std::cerr <<"Hibas LinkedListElement interfesz LinkedListElement<int>::getNext vart:"<< first <<"kapott: "<<second->getPrev()<< std::endl;
        return;
    }
    delete first;
    delete second;
    std::cout << "3. teszt sikeres(LinkedListElement<int>)\n";

}


void test3_LinkedList (){
    ///Csak string típusra teszteljük a LinkedListet
    //Létrehozunk két string lista elemet
    auto* first = new LinkedListElement<std::string>("34");
    auto* second = new LinkedListElement<std::string>("7445");
    //Az elsőt paraméterül kapja alistánk konstruktoraú
    auto* testList = new LinkedList<std::string>(first);
    if(1 != testList->Count()) {
        std::cerr <<"Hibas LinkedList<string> interfesz LinkedList::Count() vart: 1, kapott:" << testList->Count() <<std::endl;
    }
    if(first != testList->getFirst()) {
        std::cerr <<"Hibas LinkedList<string> interfesz LinkedList::getFirst() vart:"<<  first <<"kapott:" << testList->getFirst() <<std::endl;
    }
    if(first != testList->getLast()) {
        std::cerr <<"Hibas LinkedList<string> interfesz LinkedList::getFirst() vart:"<<  first <<"kapott:" << testList->getLast() <<std::endl;
    }
    LinkedListElement<std::string>* egyedik;
    try {
        egyedik = (*testList)[1];
    }catch(Index_OutOFRange& f) {
        std::cerr << f.what();
    }
    if(egyedik != first) {
        std::cerr <<"Hibas LinkedList<string> funkcio LinkedList::operator[]() vart:"<<  first <<"kapott:" << egyedik<<std::endl;
    }
    std::string supposed = "34|";
    if(supposed != testList->elementsInOrder()) {
        std::cerr <<"Hibas LinkedList<string> funkcio LinkedList::elemenstInOrder() vart:"<<  "34|" <<"kapott:" << testList->elementsInOrder();
    }
    LinkedListElement<std::string>* exc;
    try {
        exc = (*testList)[0];
    }catch(Index_OutOFRange& i) {
        std::cout <<"Kivetel elkapva: " << i.what() << std::endl;
    }
    try {
        exc = (*testList)[2];
        std::cout << "Nem dobott kivetelt valamiert:" << exc->getData();
    }catch(Index_OutOFRange& i) {
        std::cout <<"Kivetel elkapva: " << i.what() << std::endl;
    }
    testList->printList();
    ///Most adjuk hozza a masodik elemeet
    testList->add(second);
    if(2 != testList->Count()) {
        std::cerr <<"Hibas LinkedList<string> interfesz LinkedList::Count() vart: 1, kapott:" << testList->Count() <<std::endl;
    }
    if(first != testList->getFirst()) {
        std::cerr <<"Hibas LinkedList<string> interfesz LinkedList::getFirst() vart:"<<  first <<"kapott:" << testList->getFirst() <<std::endl;
    }
    if(second != testList->getLast()) {
        std::cerr <<"Hibas LinkedList<string> interfesz LinkedList::getFirst() vart:"<<  first <<"kapott:" << testList->getLast() <<std::endl;
    }

    try {
        egyedik = (*testList)[1];
    }catch(Index_OutOFRange& f) {
        std::cerr <<"Hibas LinkedList<string> funkcio LinkedList::operator[]() " << f.what() <<std::endl;
    }
    if(egyedik != first) {
        std::cerr <<"Hibas LinkedList<string> funkcio LinkedList::operator[]() vart:"<<  first <<"kapott:" << egyedik <<std::endl;
    }

    LinkedListElement<std::string>* kettedik;
    try {
        kettedik = (*testList)[2];
    }catch(Index_OutOFRange& f) {
        std::cerr <<"Hibas LinkedList<string> funkcio LinkedList::operator[]() " << f.what() <<std::endl;
    }
    if(kettedik != second) {
        std::cerr <<"Hibas LinkedList<string> funkcio LinkedList::operator[]() vart:"<<  second <<"kapott:" << kettedik <<std::endl;
    }
    supposed = "34|7445|";
    if(supposed != testList->elementsInOrder()) {
        std::cerr <<"Hibas LinkedList<string> funkcio LinkedList::elemenstInOrder() vart:"<<  "34|7445|" <<"kapott:" << testList->elementsInOrder();
    }
    try {
        exc = (*testList)[0];
    }catch(Index_OutOFRange& i) {
        std::cout <<"Kivetel elkapva: " << i.what() << std::endl;
    }
    try {
        exc = (*testList)[3];
    }catch(Index_OutOFRange& i) {
        std::cout <<"Kivetel elkapva: " << i.what() << std::endl;
    }
    delete testList;
    std::cout << "5. teszt sikeres: LinkedList<string>" <<std::endl;
};


void test4_Tree() {
    Reader* fr = new FileReader("test3.txt");
    Writer* fw = new FileWriter("test3.txt");
    std::string originalFileContent = fr->read(); //Ezt eltároljuk, hogy a teszt végé vissza tudjuk írni
    std::cout << "Teszt file eredeti tartalma: " << originalFileContent << "\n";
    Tree* testTree = new Tree(fr); //Ha ez sikeresen lefut akkor a konstruktor tesztet sikeresnek tekintjük

    /*
     * Ezt a fat olvastuk be a fajlbol:
     *                              A
     *                             / \
     *                           B     C
     *                         /  \   /  \
     *                       D    E  F    G
     *                      / \          / \
     *                     H   I        N   O
     */
    std::cout <<"Kerdesek hozzaadasa elott: \n";
    testTree->printTree(testTree->getRoot());
    ///Interfész tesztek, bar ha ezek hibasak az inkabb a konstruktor hibajanak tudhato be
    if(nullptr == testTree->getRoot()) {
        std::cerr <<"Hibas Tree interfesz Tree::getRoot nullpointerrel ter vissza\n";
    }
    if(nullptr == testTree->getList()) {
        std::cerr <<"Hibas Tree interfesz Tree::getList nullpointerrel ter vissza\n";
    }
    ///Funkcionális tesztek
    //bool leafNode
    Node<std::string>* H = testTree->getRoot()->getYes()->getYes()->getYes();
    Node<std::string>* E = testTree->getRoot()->getYes()->getNo();

    if(testTree->getRoot()->getYes() != testTree->FindParent(E->getIndex())) {
        std::cerr <<"Hibas Tree funkcionalitas Tree::FindParent ..........";
    }
    if(testTree->getRoot()->getYes()->getYes() != testTree->FindParent(H->getIndex())) {
        std::cerr <<"Hibas Tree funkcionalitas Tree::FindParent ..........";
    }
    if(!Tree::leafNode(H)) {
        std::string result = Tree::leafNode(H) ? "igaz" : "hamis";
        std::cerr <<"Hibas Tree funkcionalitas Tree::leafNode vart: igaz kapott: " << result <<  ", vizsgalt Node: H\n";
        testTree->printTree(testTree->getRoot());
    }
    if(!Tree::leafNode(E)) {
        std::string result = Tree::leafNode(E) ? "igaz" : "hamis";
        std::cerr <<"Hibas Tree funkcionalitas Tree::leafNode vart: igaz kapott: " << result <<  ", vizsgalt Node: E\n";
        testTree->printTree(testTree->getRoot());
    }

    //InsertNewNode: beszurunk egy uj kerdest E-be meghozza a kovetkezokepp:
    /*
     *             . . .
     *               /
     *               E
     *              / \
     *             W   Q
     */
    std::string e = "E";
    std::string w = "W";
    std::string q = "Q";
    testTree->InsertNewNode(e, w, q, E, fw);
    //Megvizsgéljuk E pointereit
    if(E->getYes()== nullptr) {
        std::cerr <<"Hibas Tree funkcionalitas Tree::InsertNewNode, nullpointer a valtoztatott node Yes pointere\n";
        testTree->printTree(testTree->getRoot());
    }
    if(E->getNo()== nullptr) {
        std::cerr <<"Hibas Tree funkcionalitas Tree::InsertNewNode, nullpointer a valtoztatott node No pointere\n";
        testTree->printTree(testTree->getRoot());
    }
    if(E->getYes()->getData() != "W") {
        std::cerr <<"Hibas Tree funkcionalitas Tree::InsertNewNode, az uj kerdes rosszul lett beallitva, vart: W, kapott: " << E->getYes()->getData()<<"\n";
        testTree->printTree(testTree->getRoot());
    }
    if(E->getNo()->getData() != "Q") {
        std::cerr <<"Hibas Tree funkcionalitas Tree::InsertNewNode, az uj kerdes rosszul lett beallitva, vart: Q, kapott: " << E->getNo()->getData()<<"\n";
        testTree->printTree(testTree->getRoot());
    }
    //Megnezzuk, hogy a lancolt lista jol modosult-e
    if((*testTree->getList())[E->getIndex()*2]->getData() != "W" ) {
        std::cerr <<"Hibas Tree funkcionalitas Tree::insertNewNode, a lancolt lista nem jol modosult az kovetkezo indexen: " << E->getIndex()*2<< std::endl <<
        "vart: " << "W" << "kapott: " << (*testTree->getList())[E->getIndex()*2]->getData() << std::endl;
        testTree->getList()->printList();
     }
    if((*testTree->getList())[(E->getIndex()*2) + 1]->getData() != "Q" ) {
        std::cerr <<"Hibas Tree funkcionalitas Tree::insertNewNode, a lancolt lista nem jol modosult az kovetkezo indexen: " << (E->getIndex()*2) + 1<< std::endl <<
                  "vart: " << "Q" << "kapott: " << (*testTree->getList())[E->getIndex()*2]->getData() << std::endl;
        testTree->getList()->printList();
    }
    //Most H-ba szurunk be egy uj kerdest:
    std::string h = "H";
    std::string x = "X";
    std::string y = "Y";
    testTree->InsertNewNode(h, x, y, H, fw);
    //Megvizsgaljuk H pointereit
    if(H->getYes()== nullptr) {
        std::cerr <<"Hibas Tree funkcionalitas Tree::InsertNewNode, nullpointer a valtoztatott node Yes pointere\n";
        testTree->printTree(testTree->getRoot());
    }
    if(H->getNo()== nullptr) {
        std::cerr <<"Hibas Tree funkcionalitas Tree::InsertNewNode, nullpointer a valtoztatott node No pointere\n";
        testTree->printTree(testTree->getRoot());
    }
    if(H->getYes()->getData() != "X") {
        std::cerr <<"Hibas Tree funkcionalitas Tree::InsertNewNode, az uj kerdes rosszul lett beallitva, vart: X, kapott: " << H->getYes()->getData()<<"\n";
        testTree->printTree(testTree->getRoot());
    }
    if(H->getNo()->getData() != "Y") {
        std::cerr <<"Hibas Tree funkcionalitas Tree::InsertNewNode, az uj kerdes rosszul lett beallitva, vart: Y, kapott: " << H->getNo()->getData()<<"\n";
        testTree->printTree(testTree->getRoot());
    }
    //Megnezzuk, hogy a lancolt lista jol modosult-e
    if((*testTree->getList())[H->getIndex()*2]->getData() != "X" ) {
        std::cerr <<"Hibas Tree funkcionalitas Tree::insertNewNode, a lancolt lista nem jol modosult az kovetkezo indexen: " << H->getIndex()*2<< std::endl <<
                  "vart: " << "X" << "kapott: " << (*testTree->getList())[E->getIndex()*2]->getData() << std::endl;
        testTree->getList()->printList();
    }
    if((*testTree->getList())[(H->getIndex()*2) + 1]->getData() != "Y" ) {
        std::cerr <<"Hibas Tree funkcionalitas Tree::insertNewNode, a lancolt lista nem jol modosult az kovetkezo indexen: " << (H->getIndex()*2) + 1<< std::endl <<
                  "vart: " << "Y" << "kapott: " << (*testTree->getList())[E->getIndex()*2]->getData() << std::endl;
        testTree->getList()->printList();
    }
    std::cout <<"Kerdesek hozzaadasa utan: \n";
    testTree->printTree(testTree->getRoot());
    delete testTree;
    fw->write(originalFileContent);
    delete fr; delete fw;
    std::cout <<"6. teszt sikeres (Tree)\n";

}


void test5_Game() {
    Writer* FW = new FileWriter("test5.txt");
    Reader* FR = new FileReader( "test5.txt");
    Writer* CW = new ConsoleWriter();
    Reader* CR = new ConsoleReader();

    Game* newGame = new Game(FR, CR, FW, CW);
    newGame->start();
    newGame->getRoot()->printTree(newGame->getRoot()->getRoot());
    delete newGame;
}


int main(){
    test0_IO();
    test1_Node();
    test2_LinkedListElement();
    test3_LinkedList();
    test4_Tree();
    test5_Game();
    return 0;
}

#endif