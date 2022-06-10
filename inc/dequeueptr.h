#pragma once

#include "edge.h"

std::ostream &operator << (std::ostream &out, Dequeue<std::shared_ptr<Vertex>> const &dequeue);
std::ostream &operator << (std::ostream &out, Dequeue<std::shared_ptr<Edge>> const &dequeue);