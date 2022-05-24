/
//  SkipList.h
//  Skip_List
//
//  Copyright © Tali Moreshet. All rights reserved.
//
//
//  This is an implementation of a Skip List class, consisting of Linked Lists, which are made up of Nodes.
//  All classes are templated, such that their types may be provided at creation.
//  Nodes contain data (which doubles as key), and pointers to all directions.

#ifndef SkipList_h
#define SkipList_h

#include <iostream>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

template<class T>
class Node {
public:
    Node(const T& data);                            // constructor
    T data;                                         // node data, doubles as key
    Node<T> *next;                                  // node next pointer
    Node<T> *prev;                                  // node previous pointer
    Node<T> *up;                                    // node above pointer
    Node<T> *down;                                  // node below pointer
    void printData();                               // prints data value
    void print();                                   // prints entire node object content
};

template <class T>
class LinkedList {
public:
    LinkedList(T minVal, T maxVal);                 // constructor: accepts -infinity, +infinity values,
                                                    //  creates linked list with two corresponding nodes
    ~LinkedList();                                  // destructor
    Node<T>* search(Node<T>* location, T data);     // search for data starting at location, return node <= data
    Node<T>* insert(Node<T>* location, T data);     // insert node with data at new node to be placed directly 
                                                    //  after node with povided location, return new node
    void printData();                               // prints linked list data
    void print();                                   // prints linked list with all nodes pointers
    Node<T>* head;                                  // head of list
    int n = 0;                                      // number of nodes in list
    int level;                                      //level in skipList
    LinkedList<T>* up;
    LinkedList<T>* down;
};

template <class T>
class SkipList {
public:
    SkipList(T minVal, T maxVal);                   // constructor: accepts -infinity, +infinity values,
                                                    //  creates skip list with top-level only
    ~SkipList();                                    // destructor
    Node<T>* search(T data);                        // search for data, return node <= data (existing node, or location
                                                    //  where new node should be inserted in the bottom-most list)
    Node<T>* insert(T data);                        // insert node with data, return pointer if inserted, NULL if error
    LinkedList<T>* addList(LinkedList<T>* current);          //Add new list to SkipList
    void printData();                               // prints skip list data
    void print();                                   // prints skip list with all nodes pointers
    LinkedList<T> *topList;                         // pointer to the top-most list
    LinkedList<T> *bottomList;
    int randSeed = 330;                             // to be used as seed for the getRand() function
    int h = 0;                                      // height
};

//returns 0 or 1 with a 50% chance 
//When it returns 1, insert the node to next level of the skiplist
int getRand(){
    return rand()%2;
}

/********************** From here down is the content of the LinkedList.cpp file: ***********************/

/****** Implementation of Node ******/

// Constructor
template<class T>
Node<T>::Node(const T& data)
{
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
    this->up = nullptr;
    this->down = nullptr;
}

// Print node's data value
template <class T>
void Node<T>::printData()
{
    cout << data << " ";
}

// Print entire node object content (data value, object's address, and all pointers)
template <class T>
void Node<T>::print()
{
    cout << " * " << data << ": [addr: " << this << " next: " << this->next << " prev: " << this->prev << " up: " << this->up << " down: " << this->down << "]  ";
}


/****** Implementation of linked list ******/

// Copyright Tiffany Lukmantara 2021 tiffaluk@bu.edu
// Copyright Thang Le 2021 thangle2@bu.edu

//Constructor
template <class T>
LinkedList<T>::LinkedList(T minVal, T maxVal){
    this->head = new Node<T>(minVal);       
    this->head->next = new Node<T>(maxVal);
    this->head->prev = this->head->next;
    this->head->next->next = this->head;    //Doubly linked list needs next and prev of max node to point to min
    this->head->next->prev = this->head;
    this->head->down = NULL;
    this->head->up = NULL;
    this->head->next->down = NULL;
    this->head->next->up = NULL;
    this->down = NULL;
    this->up = NULL;
}

//Destructor
template <class T>
LinkedList<T>::~LinkedList(){

}

template <class T>
Node<T>* LinkedList<T>::search(Node<T>* location, T data){
    Node<T> *temp = location;

    if (location->data > data)                          //Error checking if location in sorted list pointd to a bigger value than provided data, impossible to search
    {
        cerr << "ERROR: 'Location' data is bigger than 'data'"<<endl;
        return NULL;
    }
    
    if (location->data == data)                         //Checking if location points to desired data
    {
        // cerr <<"WARNING: Data already in List"<<endl;
        return location;
    }
    

    while (temp->data <= data) 
    {
        if (temp->data == data)                         //Check if data already exists in linkedlist
        {
            // cerr<<"WARNING: Data already in List"<<endl;
            return temp;
        } 
        temp = temp->next;
    }
    
    return temp->prev;

}


template <class T>
Node<T>* LinkedList<T>::insert(Node<T>* location, T data){
    if (location->data >= data || location->next->data <= data) //Check if location is wrong
    {
        cerr << "ERROR: Wrong position or data already exists"<<endl;
        return NULL;
    }

    Node<T> *newNode = new Node<T>(data);
    //update pointers
    newNode->prev = location;
    newNode->next = location->next;

    location->next = newNode; 

    newNode->next->prev = newNode;
    this->n++;
    return newNode;
    
}


template <class T>
void LinkedList<T>::printData(){
    Node<T> *temp = this->head;

    while (temp->next != this->head) // print node data until last node
    {
        cout<<temp->data<<' ';
        temp = temp->next;
    }

    cout<<temp->data << ' ' <<endl; // print last node
    
}                              

template <class T>
void LinkedList<T>::print(){
    Node<T> *temp = this->head;

    while (temp->next != head) // prints entire node object content
    {
        temp->print();
        temp = temp->next;
    }
    
    temp->print();
    cout<<endl;
}



/****** Skip List Implementation ******/
// Copyright Tiffany Lukmantara 2021 tiffaluk@bu.edu
// Copyright Thang Le 2021 thangle2@bu.edu

template <class T>
SkipList<T>::SkipList(T minVal, T maxVal){
    this->topList = new LinkedList<T>(minVal, maxVal);
    this->topList->level = this->h++;
    this->bottomList = this->topList;
    srand(this->randSeed);
    // cout<<"SkipList successfully created"<<endl;
}

template <class T>
SkipList<T>::~SkipList(){

}

template <class T>
Node<T>* SkipList<T>::search(T data){

Node<T>* temp = this->topList->head;
LinkedList<T>* tempList = topList;

temp = topList->search(topList->head, data);
if (temp == NULL)
{
    cerr <<"Search returned NULL"<<endl;
    return NULL;
}


while (temp->down != NULL)
{
    temp = temp->down;
    tempList = tempList->down;
    temp = tempList->search(temp, data);
}

return temp;

}

template <class T>
LinkedList<T>* SkipList<T>::addList(LinkedList<T>* current){
    LinkedList<T>* newList = new LinkedList<T>(topList->head->data, topList->head->prev->data);
    newList->head->down = current->head;
    newList->head->next->down = current->head->next;
    current->head->up = newList->head;
    current->head->next->up = newList->head->next;
    newList->level = this->h++;
    newList->down = current;
    current->up = newList;
    topList = newList;

    // cout<<"Added new topList"<<endl;

    
    return newList;

}


template <class T>
Node<T>* SkipList<T>::insert(T data){

    Node<T>* temp = this->search(data);
    if (temp == NULL || temp->data == data)             //If already exists or invalid input
    {
        return NULL;
    }

    LinkedList<T>* tempList = bottomList;

    if (this->h == 1)                                   //If first time inserting, need to add new list to skiplist
    {
        topList = this->addList(topList);
        // cout<<"First time inserting successful"<<endl;
    }

    Node<T>* newNode = tempList->insert(temp, data);

    if (newNode == NULL)                                //If error inserting
    {
        return NULL;
    }
    Node<T>* temp2 = newNode;
    tempList = tempList->up;

    // cout<<"Inserted "<<data<<" into bottom list"<<endl;
    
    while (getRand() == 1)
    {
        temp = tempList->search(tempList->head, data);
        temp2->up = tempList->insert(temp, data);
        if (temp2->up == NULL)                            //If error inserting
        {
            cerr<<"ERROR: Insert in list "<<tempList->level<<" failed"<<endl;
            return NULL;
        }
        temp2->up->down = temp2;
        temp2 = temp2->up;
        // cout<<"Inserted "<<data<<" in list "<<tempList->level<<endl;
        if (tempList == topList)
        {
            topList = this->addList(tempList);
        }
        tempList = tempList->up;
    }

    // cout<<"Done insert"<<endl;
    return newNode;

}

template <class T>
void SkipList<T>::printData(){
    LinkedList<T>* tempList = topList;

    while (tempList != NULL)
    {
        tempList->printData();
        tempList = tempList->down;
    }
    // cout<<endl;

}  

template <class T>
void SkipList<T>::print(){
    LinkedList<T>* tempList = topList;

    while (tempList != NULL)
    {
        tempList->print();
        tempList = tempList->down;
    }
    // cout<<endl;
}


#endif /* SkipList_h */
