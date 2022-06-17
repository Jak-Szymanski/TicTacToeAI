#pragma once

#include "node.h"

/* Kolejka dwukierunkowa zawierająca elementy typu Type */
template<typename Type>
class Dequeue{

  private:
  
    Node<Type> *Head;

    Node<Type> *Tail;

  public:

    Dequeue();

    /* Wstaw nowy element na początek kolejki*/
    void InsertFront(Type new_pack);

    /* Wstaw nowy element na koniec kolejki */ 
    void InsertEnd(Type new_pack);

    /* Usuń i zwróć pierwszy element */
    Type RemoveFirst();

    /* Usuń i zwróć ostatni element */
    Type RemoveLast();

    /* Usuń i zwróć n-ty element */
    Type Remove(int n);

    /*Zwróć rozmiar kolejki*/
    int Size() const;

    /* Wyczyść całą kolejkę */
    void Delete();

    /* Czy kolejka jest pusta */
    bool IsEmpty() const {return !Head;};

    Node<Type> * const GetHead() const{return Head;};

    Node<Type> * const GetTail() const{return Tail;};

    void SetHead(Node<Type> *new_head){Head = new_head;};

    void SetTail(Node<Type> *new_tail){Tail = new_tail;};

    void PrintEnd();
};

/*Wyświetlanie kolejki*/
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
  delete ptr;
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
  delete ptr;
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
  Node<Type> *del = ptr->Next;    //Zachowuje wskaznik na usuwany element, by moc pozniej zwolnic jego pamiec
  if(ptr->Next->Next == NULL){
    Tail = ptr;
    ptr->Next = NULL;
  } else {
  ptr->Next->Next->Prev = ptr->Next;
  ptr->Next = ptr->Next->Next;
  }
  delete del;
  return pack;
}  

// Wyczyść całą kolejkę
template<typename T>
void Dequeue<T>::Delete(){

  Node<T> *ptr = Head;
  Node<T> *next;
  free(Head);
  free(Tail);

  while(ptr != NULL){
    next = ptr->Next;
    delete ptr;
    ptr = next;
  }
}