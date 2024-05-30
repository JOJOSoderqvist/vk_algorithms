#include "../include/ListGraph.hpp"

ListGraph::ListGraph(const int number_of_vertices) : adjacency_lists(number_of_vertices) {
}

ListGraph::ListGraph(const IGraph& graph) : adjacency_lists(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        adjacency_lists[i] = graph.GetNextVertices(i);
    }
}

int ListGraph::VerticesCount() const {
    return static_cast<int>(adjacency_lists.size());
}

void ListGraph::AddEdge(const int from, const int to) {
    assert(0 <= from && from < adjacency_lists.size() && 0 <= to && to <= adjacency_lists.size());
    adjacency_lists[from].push_back(to);
}

std::vector<int> ListGraph::GetNextVertices(const int vertex) const {
    assert(0 <= vertex && vertex <= adjacency_lists.size());
    return adjacency_lists[vertex];
}


std::vector<int> ListGraph::GetPrevVertices(const int vertex) const {
    assert(0 <= vertex && vertex <= adjacency_lists.size());
    std::vector<int> prev_vertices;
    for (int from = 0; from < adjacency_lists.size(); ++from) {
        for (const int to: adjacency_lists[from]) {
            if (to == vertex) {
                prev_vertices.push_back(from);
            }
        }
    }

    return prev_vertices;
}
