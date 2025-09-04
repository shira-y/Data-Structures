#pragma once
#ifndef EDGE_H
#define EDGE_H

class Vertex;

class Edge {
private:
    Vertex* destination;

public:
    Edge(Vertex* dest);
    Vertex* getDestination() const;
};

#endif