#pragma once

#include "node.h"

template<typename T>
class Dequeue{

  private:
  
    Node<T> *Head;

    Node<T> *Tail;

  public:

    Dequeue();

    void InsertFront(T new_pack);

    void InsertEnd(T new_pack);

    T RemoveFirst();

    T RemoveLast();

    T Remove(int n);

    int Size() const;

    void Delete();

    bool IsEmpty() const {return !Head;};

    Node<T> * const GetHead() const{return Head;};

    Node<T> * const GetTail() const{return Tail;};

    void SetHead(Node<T> *new_head){Head = new_head;};

    void SetTail(Node<T> *new_tail){Tail = new_tail;};

    void PrintEnd();
};


