#pragma once

//#include "vertex.hh"
#include <string>
#include <fstream> 
#include <iostream>

template<typename Type>
class Node{

  private:

    Type Elem;

    Node<Type> *Next;

    Node<Type> *Prev;
  
  public:

    Node();

    Node(Type new_elem);

    //int GetKey() const{return Elem.Key;};

    //std::string GetMessage() const{return Elem.Message;};

    Node<Type> * const GetNext() const{return Next;};

    Node<Type> * const GetPrev() const{return Prev;};

    Type GetElem() const{return Elem;};

    void SetNext(Node<Type> *new_next){Next = new_next;};

    void SetPrev(Node<Type> *new_prev){Prev = new_prev;};


   // friend class Dequeue;
};


template <typename Type>
Node<Type>::Node(){
  Elem = Type();
  Next = NULL;
  Prev = NULL;
}

template <typename Type>
Node<Type>::Node(Type new_elem){
  Elem = new_elem;
  Next = NULL;
  Prev = NULL;
}




