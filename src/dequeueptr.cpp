#include "../inc/dequeueptr.h"


/*Wyświetlenie kolejki wskaźników na wierzchołki (tak by nie wyświetlała ich adresów, tylko wartości)*/
template <typename Type>
std::ostream &operator << (std::ostream &out, Dequeue<Vertex<Type>*> const &dequeue){

   if(dequeue.IsEmpty()){
    out << "Kolejka jest pusta" << std::endl;
    return out;
  }

  Node<Vertex<Type>*> *ptr = dequeue.GetHead();
  while(ptr != NULL){
    out << *ptr->GetElem() << std::endl;
    ptr = ptr->GetNext();
  } 
  return out;
}

//Wyświetlenie kolejki wskaźników na krawędzie (tak by nie wyświetlała ich adresów, tylko wartości)
template <typename Type>
std::ostream &operator << (std::ostream &out, Dequeue<Edge<Type>*> const &dequeue){

   if(dequeue.IsEmpty()){
    out << "Kolejka jest pusta" << std::endl;
    return out;
  }

  Node<Edge<Type>*> *ptr = dequeue.GetHead();
  while(ptr != NULL){
    out << *ptr->GetElem() << std::endl;
    ptr = ptr->GetNext();
  }
  return out;
}

/* template<>
void Dequeue<Edge<int>*>::Delete(){

  Node<Edge<int>*> *ptr = Head;
  Node<Edge<int>*> *next;
  Head = NULL;

  while(ptr != NULL){
    next = ptr->Next;
    ptr->Elem->Delete();
    ptr = next;
  }
} */