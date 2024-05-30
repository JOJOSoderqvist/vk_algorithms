#include "../include/SetGraph.hpp"

SetGraph::SetGraph(const int number_of_vertices) : adjacency_sets(number_of_vertices) {
}

SetGraph::SetGraph(const IGraph& graph) : adjacency_sets(graph.VerticesCount()) {
    for (int from = 0; from < graph.VerticesCount(); ++from) {
        for (const int to: graph.GetNextVertices(from)) {
            adjacency_sets[from].insert(to);
        }
    }
}

int SetGraph::VerticesCount() const {
    return static_cast<int>(adjacency_sets.size());
}

void SetGraph::AddEdge(const int from, const int to) {
    assert(0 <= from && from < adjacency_sets.size() && 0 <= to && to <= adjacency_sets.size());
    adjacency_sets[from].insert(to);
}

std::vector<int> SetGraph::GetNextVertices(const int vertex) const {
    assert(0 <= vertex && vertex <= adjacency_sets.size());
    std::vector<int> next_vertices;
    for (const int to : adjacency_sets[vertex]) {
        next_vertices.push_back(to);
    }
    return next_vertices;
}

std::vector<int> SetGraph::GetPrevVertices(const int vertex) const {
    assert(0 <= vertex && vertex < adjacency_sets.size());
    std::vector<int> prev_vertices;
    for (int from = 0; from < adjacency_sets.size(); ++from) {
        if (adjacency_sets[from].find(vertex) != adjacency_sets[from].end()) {
            prev_vertices.push_back(from);
        }
    }
    return prev_vertices;
}