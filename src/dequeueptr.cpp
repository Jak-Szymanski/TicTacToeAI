#include "../inc/dequeueptr.h"

std::ostream &operator << (std::ostream &out, Dequeue<std::shared_ptr<Vertex>> const &dequeue){

   if(dequeue.IsEmpty()){
    out << "Kolejka jest pusta" << std::endl;
    return out;
  }

  Node<std::shared_ptr<Vertex>> *ptr = dequeue.GetHead();
  while(ptr->GetNext() != NULL){
    out << *ptr->GetElem() << std::endl;
    ptr = ptr->GetNext();
  }
  out << *ptr->GetElem(); 
  return out;
}

std::ostream &operator << (std::ostream &out, Dequeue<std::shared_ptr<Edge>> const &dequeue){

   if(dequeue.IsEmpty()){
    out << "Kolejka jest pusta" << std::endl;
    return out;
  }

  Node<std::shared_ptr<Edge>> *ptr = dequeue.GetHead();
  while(ptr->GetNext() != NULL){
    out << *ptr->GetElem() << std::endl;
    ptr = ptr->GetNext();
  }
  out << *ptr->GetElem(); 
  return out;
}