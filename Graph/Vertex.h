#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <list>

class Edge;

class Vertex {
private:
    std::string key;
    std::list<Edge*> edges;

public:
    Vertex(const std::string& k);
    ~Vertex();

    void addEdge(Edge* e);
    const std::string& getKey() const;
    const std::list<Edge*>& getEdges() const;
};

#endif