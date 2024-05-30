#include "../include/MatrixGraph.hpp"

MatrixGraph::MatrixGraph(const int number_of_vertices) : adjacency_matrix(
    number_of_vertices, std::vector<bool>(number_of_vertices, false)) {
}

MatrixGraph::MatrixGraph(const IGraph& graph) : adjacency_matrix(graph.VerticesCount(),
                                                                 std::vector<bool>(graph.VerticesCount(), false)) {
    for (int from = 0; from < graph.VerticesCount(); ++from) {
        for (const int to: graph.GetNextVertices(from)) {
            adjacency_matrix[from][to] = true;
        }
    }
}

int MatrixGraph::VerticesCount() const {
    return static_cast<int>(adjacency_matrix.size());
}


void MatrixGraph::AddEdge(const int from, const int to) {
    assert(0 <= from && from < adjacency_matrix.size() && 0 <= to && to <= adjacency_matrix.size());
    adjacency_matrix[from][to] = true;
}

std::vector<int> MatrixGraph::GetNextVertices(const int vertex) const {
    assert(0 <= vertex && vertex <= adjacency_matrix.size());
    std::vector<int> next_vertices;
    for (int to = 0; to < adjacency_matrix.size(); ++to) {
        if (adjacency_matrix[vertex][to])
            next_vertices.push_back(to);
    }
    return next_vertices;
}


std::vector<int> MatrixGraph::GetPrevVertices(const int vertex) const {
    assert(0 <= vertex && vertex <= adjacency_matrix.size());
    std::vector<int> prev_vertices;
    for (int from = 0; from < adjacency_matrix.size(); ++from) {
        if (adjacency_matrix[from][vertex])
            prev_vertices.push_back(from);
    }
    return prev_vertices;
}
