#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(const std::string& k) : key(k) {}

Vertex::~Vertex() {
    for (Edge* e : edges) {
        delete e;
    }
}

void Vertex::addEdge(Edge* e) {
    edges.push_back(e);
}

const std::string& Vertex::getKey() const {
    return key;
}

const std::list<Edge*>& Vertex::getEdges() const {
    return edges;
}