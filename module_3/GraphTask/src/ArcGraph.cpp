#include "../include/ArcGraph.hpp"

ArcGraph::ArcGraph(const int number_of_vertices) : _number_of_vertices(number_of_vertices) {
}

ArcGraph::ArcGraph(const IGraph& graph) : _number_of_vertices(graph.VerticesCount()){
    for (int from = 0; from < _number_of_vertices; ++from) {
        for (const int to : graph.GetNextVertices(from)) {
            arcs.push_back({from, to});
        }
    }
}

int ArcGraph::VerticesCount() const {
    return _number_of_vertices;
}


void ArcGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < _number_of_vertices && 0 <= to && to <= _number_of_vertices);
    arcs.push_back({from, to});
}


std::vector<int> ArcGraph::GetNextVertices(const int vertex) const {
    assert(0 <= vertex && vertex <= _number_of_vertices);
    std::vector<int> next_vertices;
    for (const auto [from, to] : arcs) {
        if (from == vertex) {
            next_vertices.push_back(to);
        }
    }
    return next_vertices;
}

std::vector<int> ArcGraph::GetPrevVertices(const int vertex) const {
    assert(0 <= vertex && vertex <= _number_of_vertices);
    std::vector<int> prev_vertices;
    for (const auto [from, to] : arcs) {
        if (to == vertex) {
            prev_vertices.push_back(from);
        }
    }
    return prev_vertices;
}