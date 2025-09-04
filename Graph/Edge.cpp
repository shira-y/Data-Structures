#include "Edge.h"
#include "Vertex.h"

Edge::Edge(Vertex* dest) : destination(dest) {}

Vertex* Edge::getDestination() const {
    return destination;
}