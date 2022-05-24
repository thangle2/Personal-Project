//
//  LinkedList.h
//  Linked_List
//
//  Copyright Â© Tali Moreshet. All rights reserved.
//
//  This is an implementation of an ordered Linked List class, which is made up of Nodes.
//  All classes are templated, such that their types may be provided at creation.
//  Nodes contain data (which doubles as key), and pointers to all directions.

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <cstdlib>
#include <time.h>

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
};

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
        cout<< "ERROR: 'Location' data is bigger than 'data'"<<endl;
        return NULL;
    }
    else if (location->data == data) //Checking if location points to desired data
    {
        return location;
    }
    

    while (temp->data <= data) 
    {
        if (temp->data == data) //Check if data already exists in linkedlist
        {
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
        cout<< "ERROR: Wrong position!"<<endl;
        return NULL;
    }

    Node<T> *newNode = new Node<T>(data);
    //update pointers
    newNode->prev = location;
    newNode->next = location->next;

    location->next = newNode; 

    newNode->next->prev = newNode;

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

    cout<<temp->data<<endl; // print last node
    
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


#endif /* LinkedList_h */
