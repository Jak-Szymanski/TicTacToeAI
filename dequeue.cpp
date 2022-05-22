#include "dequeue.h"

template<typename T>
Dequeue<T>::Dequeue(){
  Head = NULL;  
  Tail = NULL;
}

/* Wstaw nowy element na początek kolejki*/
template<typename T>
void Dequeue<T>::InsertFront(T new_pack){

  Node<T> *tmp = new Node<T>(new_pack);
  
  tmp->Next = Head;
  if (IsEmpty()){ 
    Tail = tmp;
  } else {
    tmp->Next->Prev = tmp;
  }
  Head = tmp;
}

/* Wstaw nowy element na koniec kolejki */
template<typename T>
void Dequeue<T>::InsertEnd(T new_pack){

  Node *tmp = new Node(new_pack);

  tmp->Prev = Tail;
  if (IsEmpty()){
    Head = tmp;
  } else {
    tmp->Prev->Next = tmp;
  }
  Tail = tmp;
}

/* Zwróć rozmiar kolejki */
template<typename T>
int Dequeue<T>::Size() const{

  if(IsEmpty()) return 0;

  int size = 1;
  Node<T> *tmp = Head;
  
  while(tmp->Next != NULL){
    tmp = tmp->Next;
    size++;
  }

  return size;
}


/* Usuń i zwróć pierwszy element */
template<typename T>
T Dequeue<T>::RemoveFirst(){

  if(IsEmpty()){
    throw "Proba usuniecia elementu z pustej kolejki!";
  }

  Node<T> *ptr = Head;
  T first = ptr->Elem;
  Head = Head->Next;
  if(Head){
    Head->Prev = NULL;
  } else {
    Tail = NULL;
  }
  return first;
}

/* Usuń i zwróć ostatni element */
template<typename T>
T Dequeue<T>::RemoveLast(){

  if(IsEmpty()){
    throw "Proba usuniecia elementu z pustej kolejki!";
  }

  Node<T> *ptr = Tail;
  T last = ptr->Elem;
  Tail = Tail->Prev;
  if(Tail){
    Tail->Next = NULL;
  } else {
    Head = NULL;
  }
  return last;
}

/* Usuń i zwróć n-ty element */
template<typename T>
T Dequeue<T>::Remove(int n){
  if(IsEmpty()){
    throw "Próba usunięcia elementu z pustej kolejki!";
  }
  if(n < 0){
    throw "Próba usunięcia nieistniejącego elementu!";
  }
  if (n==0){
    return RemoveFirst();
  }

  Node<T> *ptr = Head;
  for(int i=0; i<n-1; i++){
    if(ptr->Next == NULL){
      throw "Próba usunięcia nieistniejącego elementu!";
    }
    ptr = ptr->Next;
  }
  T pack = ptr->Next->Elem;
  if(ptr->Next->Next == NULL){
    Tail = ptr;
    ptr->Next = NULL;
  } else {
  ptr->Next->Next->Prev = ptr->Next;
  ptr->Next = ptr->Next->Next;
  }
  return pack;
}

/* Wyczyść całą kolejkę */
template<typename T>
void Dequeue<T>::Delete(){

  Node<T> *ptr = Head;
  Node<T> *next;
  Head = NULL;

  while(ptr != NULL){
    next = ptr->Next;
    free(ptr);
    ptr = next;
  }
}

/* Wyświetl całą kolejkę idąc od końca
(funkcja była używana jedynie do testów poprawności działania kolejki w obu kierunkach) */
template<typename T>
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
}

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
