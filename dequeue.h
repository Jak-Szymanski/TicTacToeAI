#pragma once

#include "node.h"

template<typename Type>
class Dequeue{

  private:
  
    Node<Type> *Head;

    Node<Type> *Tail;

  public:

    Dequeue();

    void InsertFront(Type new_pack);

    void InsertEnd(Type new_pack);

    Type RemoveFirst();

    Type RemoveLast();

    Type Remove(int n);

    int Size() const;

    void Delete();

    bool IsEmpty() const {return !Head;};

    Node<Type> * const GetHead() const{return Head;};

    Node<Type> * const GetTail() const{return Tail;};

    void SetHead(Node<Type> *new_head){Head = new_head;};

    void SetTail(Node<Type> *new_tail){Tail = new_tail;};

    void PrintEnd();
};


 template<typename Type>
std::ostream &operator << (std::ostream &out, Dequeue<Type> const &dequeue){

   if(dequeue.IsEmpty()){
    out << "Kolejka jest pusta" << std::endl;
    return out;
  }

  Node<Type> *ptr = dequeue.GetHead();
  while(ptr->GetNext() != NULL){
    out << ptr->GetElem() << std::endl;
    ptr = ptr->GetNext();
  }
  out << ptr->GetElem(); 
  return out;
}



template<typename Type>
Dequeue<Type>::Dequeue(){
  Head = NULL;  
  Tail = NULL;
}

// Wstaw nowy element na początek kolejki
template<typename Type>
void Dequeue<Type>::InsertFront(Type new_pack){

  Node<Type> *tmp = new Node<Type>(new_pack);
  
  tmp->Next = Head;
  if (IsEmpty()){ 
    Tail = tmp;
  } else {
    tmp->Next->Prev = tmp;
  }
  Head = tmp;
}

// Wstaw nowy element na koniec kolejki
template<typename Type>
void Dequeue<Type>::InsertEnd(Type new_pack){

  Node<Type> *tmp = new Node<Type>(new_pack);

  tmp->Prev = Tail;
  if (IsEmpty()){
    Head = tmp;
  } else {
    tmp->Prev->Next = tmp;
  }
  Tail = tmp;
}

// Zwróć rozmiar kolejki
template<typename Type>
int Dequeue<Type>::Size() const{

  if(IsEmpty()) return 0;

  int size = 1;
  Node<Type> *tmp = Head;
  
  while(tmp->Next != NULL){
    tmp = tmp->Next;
    size++;
  }

  return size;
}


// Usuń i zwróć pierwszy element
template<typename Type>
Type Dequeue<Type>::RemoveFirst(){

  if(IsEmpty()){
    throw "Proba usuniecia elementu z pustej kolejki!";
  }

  Node<Type> *ptr = Head;
  Type first = ptr->Elem;
  Head = Head->Next;
  if(Head){
    Head->Prev = NULL;
  } else {
    Tail = NULL;
  }
  return first;
}

// Usuń i zwróć ostatni element
template<typename Type>
Type Dequeue<Type>::RemoveLast(){

  if(IsEmpty()){
    throw "Proba usuniecia elementu z pustej kolejki!";
  }

  Node<Type> *ptr = Tail;
  Type last = ptr->Elem;
  Tail = Tail->Prev;
  if(Tail){
    Tail->Next = NULL;
  } else {
    Head = NULL;
  }
  return last;
}

// Usuń i zwróć n-ty element 
template<typename Type>
Type Dequeue<Type>::Remove(int n){
  if(IsEmpty()){
    throw "Próba usunięcia elementu z pustej kolejki!";
  }
  if(n < 0){
    throw "Próba usunięcia nieistniejącego elementu!";
  }
  if (n==0){
    return RemoveFirst();
  }

  Node<Type> *ptr = Head;
  for(int i=0; i<n-1; i++){
    if(ptr->Next == NULL){
      throw "Próba usunięcia nieistniejącego elementu!";
    }
    ptr = ptr->Next;
  }
  Type pack = ptr->Next->Elem;
  if(ptr->Next->Next == NULL){
    Tail = ptr;
    ptr->Next = NULL;
  } else {
  ptr->Next->Next->Prev = ptr->Next;
  ptr->Next = ptr->Next->Next;
  }
  return pack;
}  

// Wyczyść całą kolejkę
/* template<typename T>
void Dequeue<T>::Delete(){

  Node<T> *ptr = Head;
  Node<T> *next;
  Head = NULL;

  while(ptr != NULL){
    next = ptr->Next;
    free(ptr);
    ptr = next;
  }
} */

/* Wyświetl całą kolejkę idąc od końca
(funkcja była używana jedynie do testów poprawności działania kolejki w obu kierunkach) */
/* template<typename T>
void Dequeue<T>::PrintEnd(){

  if(IsEmpty()){
    std::cout << "Kolejka jest pusta" << std::endl;
    return;
  }

  Node<T> *tmp = GetTail();
  while(tmp->GetPrev() != NULL){
    std::cout << tmp->GetElem();
    tmp = tmp->GetPrev();
  }
  std::cout << tmp->GetElem(); 
} */

/* Operator kopiowania */
/* template<typename T>
Dequeue<T> &Dequeue<T>::operator = (const Dequeue<T> &other){

  if (this == &other) return *this;

  Delete();

  Node<T> *tmp = other.GetHead();
 while(tmp->Next != NULL) {
    InsertEnd(tmp->Elem);
    tmp = tmp->Next;
  } 
  InsertEnd(tmp->Elem);
  return *this;
}
 */



