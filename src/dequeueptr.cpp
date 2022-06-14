#include "../inc/dequeueptr.h"

template <typename Type>
std::ostream &operator << (std::ostream &out, Dequeue<std::shared_ptr<Vertex<Type>>> const &dequeue){

   if(dequeue.IsEmpty()){
    out << "Kolejka jest pusta" << std::endl;
    return out;
  }

  Node<std::shared_ptr<Vertex<Type>>> *ptr = dequeue.GetHead();
  while(ptr->GetNext() != NULL){
    out << *ptr->GetElem() << std::endl;
    ptr = ptr->GetNext();
  }
  out << *ptr->GetElem(); 
  return out;
}


template <typename Type>
std::ostream &operator << (std::ostream &out, Dequeue<std::shared_ptr<Edge<Type>>> const &dequeue){

   if(dequeue.IsEmpty()){
    out << "Kolejka jest pusta" << std::endl;
    return out;
  }

  Node<std::shared_ptr<Edge<Type>>> *ptr = dequeue.GetHead();
  while(ptr->GetNext() != NULL){
    out << *ptr->GetElem() << std::endl;
    ptr = ptr->GetNext();
  }
  out << *ptr->GetElem(); 
  return out;
}