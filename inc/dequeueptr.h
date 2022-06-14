#pragma once

#include "edge.h"
template <typename Type>
std::ostream &operator << (std::ostream &out, Dequeue<std::shared_ptr<Vertex<Type>>> const &dequeue);

template <typename Type>
std::ostream &operator << (std::ostream &out, Dequeue<std::shared_ptr<Edge<Type>>> const &dequeue);

