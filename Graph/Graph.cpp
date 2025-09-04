#include "Graph.h"
#include "Edge.h"
#include <iostream>
#include <algorithm>

Graph::Graph() {}

Graph::~Graph() {
    for (auto& pair : vertices) {
        delete pair.second;
    }
}

bool Graph::addv(const std::string& key) {
    if (vertices.find(key) != vertices.end()) {
        return false; // Vertex already exists
    }
    vertices[key] = new Vertex(key);
    return true;
}

bool Graph::adde(const std::string& from, const std::string& to) {
    auto it_from = vertices.find(from);
    auto it_to = vertices.find(to);

    if (it_from == vertices.end() || it_to == vertices.end()) {
        return false; // One or both vertices don't exist
    }

    Vertex* v_from = it_from->second;
    Vertex* v_to = it_to->second;

    // Check if edge already exists
    for (Edge* e : v_from->getEdges()) {
        if (e->getDestination() == v_to) {
            return false; // Edge already exists
        }
    }

    v_from->addEdge(new Edge(v_to));
    return true;
}

void Graph::printAll() const {
    for (const auto& pair : vertices) {
        std::cout << pair.first << ": ";
        for (const Edge* e : pair.second->getEdges()) {
            std::cout << e->getDestination()->getKey() << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::topologicalSort() {
    std::map<Vertex*, bool> visited;
    std::list<Vertex*> sortedList;

    // Initialize all vertices as not visited
    for (const auto& pair : vertices) {
        visited[pair.second] = false;
    }

    // Process vertices in lexicographic order
    for (const auto& pair : vertices) {
        if (!visited[pair.second]) {
            dfsVisit(pair.second, visited, sortedList);
        }
    }

    // Print the result - the list is already in correct order (descending finish time)
    std::cout << "order: ";
    for (Vertex* v : sortedList) {
        std::cout << v->getKey() << " ";
    }
    std::cout << std::endl;
}

void Graph::dfsVisit(Vertex* v, std::map<Vertex*, bool>& visited, std::list<Vertex*>& sortedList) {
    visited[v] = true;

    // Visit neighbors in the order they were added (insertion order)
    for (const auto& edge : v->getEdges()) {
        Vertex* neighbor = edge->getDestination();
        if (!visited[neighbor]) {
            dfsVisit(neighbor, visited, sortedList);
        }
    }

    // Insert at front to get descending finish time order
    sortedList.push_front(v);
}