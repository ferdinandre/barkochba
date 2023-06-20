//
// Created by Ferdinand on 2022. 05. 17..
//

#ifndef BKOBA4_LINKEDLIST_H
#define BKOBA4_LINKEDLIST_H
#include <iostream>
#include "exception.h"

template<typename T>
class LinkedListElement {
    //Tarolt adat
    T data;
    //kovetkezo pointer
    LinkedListElement<T>* next;
    //elozo pointer
    LinkedListElement<T>* prev;
public:
    //Konstruktor
    LinkedListElement(T data):data(data), next(nullptr), prev(nullptr) {}
    //data setter
    void setData(T& t) {data = t;}
    //next setter
    void setNext(LinkedListElement<T>* newNext) {next = newNext;}
    //prev setter
    void setPrev(LinkedListElement<T>* newPrev) {prev = newPrev;}
    //data getter
    T getData() const {return data;}
    //next getter
    LinkedListElement<T>* getNext() const {return next;}
    //prev getter
    LinkedListElement<T>* getPrev() const {return prev;}
};


template<typename T>
class LinkedList {
    typedef LinkedListElement<T>* iterator;
    //Első elemre mutató pointer
    iterator first;
    //Utolsó elemre mutató pointer
    iterator last;
    //Tárolt elemek mennyisége
    size_t count;
public:
    //Konstruktor
    explicit LinkedList(iterator first) :first(first), last(first), count(1) {}
    //index operátor 1-nél kisebb vagy count-nál nagyobb index esetén kivételt dob
    iterator operator[](size_t idx) const {
        if(idx <1 ||idx > count) {
            throw Index_OutOFRange("LinkedList<T>::operator[]");
        }else {
            iterator iter = first;
            for(size_t i = 1; i <idx; ++i) {
                iter = iter->getNext();
            }
            return iter;
        }
    }
    //first getter
    iterator getFirst() const {return first;}
    //lsat getter
    iterator getLast() const {return last;}
    //méret lekérdezés
    size_t Count() const {return count;}

    ~LinkedList() {
        //Lista elemek felszabadítása
        iterator f = getFirst();
        while(f != getLast()) {
            iterator next  = f->getNext();
            delete f;
            f = next;
        }
        delete last;
    }


    // egy elem hozzáfűzése a lista végére
    void add(LinkedList::iterator newElement) {
        last->setNext(newElement);
        newElement->setPrev(last);
        ++count;
        last = newElement;
    }
    // kiírás
    void printList() {
        for(size_t i = 1; i <= count; ++i) {
            std::cout << i << "-edik elem: " << (*this)[i]->getData() <<" ";
        }
        std::cout << std::endl;
    }
    // elemek összeadása/összefűzése
    std::string elementsInOrder() {
        std::string temp;
        for(size_t i = 1; i <= count; ++i) {
            temp += (*this)[i]->getData();
            temp += '|';
        }
        return temp;
    }
};




#endif //BKOBA4_LINKEDLIST_H
