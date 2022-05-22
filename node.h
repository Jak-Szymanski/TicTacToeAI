#pragma once

//#include "vertex.hh"
#include <string>
#include <fstream> 
#include <iostream>

template<typename T>
class Node{

  private:

    T Elem;

    Node *Next;

    Node *Prev;
  
  public:

    Node();

    Node(T new_elem);

    //int GetKey() const{return Elem.Key;};

    //std::string GetMessage() const{return Elem.Message;};

    Node * const GetNext() const{return Next;};

    Node * const GetPrev() const{return Prev;};

    T GetElem() const{return Elem;};

    void SetNext(Node *new_next){Next = new_next;};

    void SetPrev(Node *new_prev){Prev = new_prev;};


    friend class Queue;
};


template <typename T>
Node<T>::Node(){
  Elem = T();
  Next = NULL;
  Prev = NULL;
}

template <typename T>
Node<T>::Node(T new_elem){
  Elem = new_elem;
  Next = NULL;
  Prev = NULL;
}




