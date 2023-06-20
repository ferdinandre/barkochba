//
// Created by Ferdinand on 2022. 05. 06..
//
#include "memtrace.h"
#include "LinkedList.h"
#include "exception.h"
#include <cmath>
#include "tree.h"

Tree::Tree(Reader *FR)  {
    seed = FR->read();
    Writer* temp = new ConsoleWriter();
    size_t idx = 0;
    bool firstNode = true;
    for(size_t i = 0; i < seed.size(); ++i) {
        size_t j;
        std::string line;
        for(j = i; j < seed.size() && seed[j] != '|'; ++j) {
            line += seed[j];
        }
        if (line.empty()){
            line = "GhostNode";
        }
        auto* newNode = new Node<std::string>(line, ++idx);

        LinkedListElement<std::string>* newElement;
        newElement = new LinkedListElement<std::string>(newNode->getData());

        if(firstNode) {
            root = newNode;
            list = new LinkedList<std::string>(newElement);
            firstNode = false;
        }else {
            Node<std::string>* parentNode;
            try {
                parentNode = FindParent(newNode->getIndex());
            }catch(Index_OutOFRange& i) {
                temp->write("Kivetel: ");
                temp->write(i.what());
                delete temp;
                abort();
            }

            if(parentNode != nullptr) {
                if(newNode->getIndex() % 2 == 0) {
                    parentNode->setYes(newNode);
                }else {
                    parentNode->setNo(newNode);
                }
            }
            list->add(newElement);
        }
        i = j;
    }
    delete temp;


}


void Tree::printTree(Node<std::string> *currentNode)const  {
    if(currentNode->getNo() != nullptr) {
        printTree(currentNode->getNo());
    }
    printNode(currentNode);
    if(currentNode->getYes() != nullptr) {
        printTree(currentNode->getYes());
    }
}

void Tree::InsertNewNode(std::string &newQ, std::string &newY, std::string &newN, Node<std::string> *where, Writer* FW) {
    where->setData(newQ);
    LinkedListElement<std::string>* wh;
    try {
        wh = (*list)[where->getIndex()];
    }catch(Index_OutOFRange& i) {
        wh = (*list)[list->Count()];
    }

    wh->setData(newQ);
    if(where->getYes() != nullptr) {
        where->getYes()->setData(newY);
    }else {
        //Csinalunk egy uj Node-ot
        auto* newYes = new Node<std::string>(newY, where->getIndex() * 2);

        where->setYes(newYes);
    }
    if(where->getNo() != nullptr) {
        where->getNo()->setData(newN);
    }else {
        auto* newNo = new Node<std::string>(newN, where->getIndex()* 2 + 1);

        where->setNo(newNo);
    }
    if(where->getIndex()* 2 >= list->Count()) {
        for(size_t i = list->Count(); i < 2* where->getIndex() - 1; ++i) {
            auto* empty = new LinkedListElement<std::string>("GhostNode");
            list->add(empty);
        }
        auto* newYesElement = new LinkedListElement<std::string>(newY);
        list->add(newYesElement);
        auto* newNoElement = new LinkedListElement<std::string>(newN) ;
        list->add(newNoElement);
    }else {
        LinkedListElement<std::string> *toBeModified = (*list)[where->getIndex() * 2];
        toBeModified->setData(newY);
        LinkedListElement<std::string> *toBeModified2 = (*list)[where->getIndex() * 2 + 1];
        toBeModified2->setData(newN);
    }
    std::string newSeed = list->elementsInOrder();
    try {
        FW->write(newSeed);
    }catch(FileNotFound& f) {
        std::cerr <<f.what() << std::endl;
        return;
    }

}

bool Tree::leafNode(Node<std::string> *pNode) {
    if(pNode->getYes() == nullptr || pNode->getNo() == nullptr) {
        return true;
    }
    if(pNode->getYes()->getData() == "GhostNode" || pNode->getNo()->getData() == "GhostNode" ) {
        return true;
    }
    return false;
}

void Tree::printNode(Node<std::string> *pNode)const  {
    if(pNode->getData() != "GhostNode") {
        std::string tabs;
        int numoftabs = (int)log2(pNode->getIndex());
        for(int i = 0; i < numoftabs; ++i) {
            tabs += '\t'; tabs += '\t';
        }
        std::string yes = pNode->getYes() == nullptr ? "NULL" : pNode->getYes()->getData();
        std::string no = pNode->getNo() == nullptr ? "NULL" : pNode->getNo()->getData();
        std::cout << tabs <<"kerdes: "<< pNode->getData() << std::endl << tabs <<"Index: " <<pNode->getIndex() << std::endl <<tabs <<"Yes: " << yes<< std::endl << tabs << "No: " << no << std::endl;
    }

}

Node<std::string> *Tree::FindParent(size_t index)const  {
    if(index == 0) {
        throw Index_OutOFRange("Alulindexeles!");
    }
    size_t maxindex = this->getList()->Count() + 1;
    if(index > maxindex) {
        throw Index_OutOFRange("Tulindexeles");
    }
    if(index == 1) {
        return nullptr;
    }
    if(index == 2 || index == 3) {
        return root;
    }else {
        if(index % 4 == 0 || index % 4 == 1) {
            return FindParent(index / 2)->getYes();
        }else {
            return FindParent(index  / 2)->getNo();
        }

    }


}













