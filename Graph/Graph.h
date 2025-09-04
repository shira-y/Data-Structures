#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <string>
#include <list>
#include "Vertex.h"

class Graph {
private:
    std::map<std::string, Vertex*> vertices;

public:
    Graph();
    ~Graph();

    bool addv(const std::string& key);
    bool adde(const std::string& from, const std::string& to);
    void printAll() const;
    void topologicalSort();

private:
    void dfsVisit(Vertex* v, std::map<Vertex*, bool>& visited, std::list<Vertex*>& sortedList);
};

#endif