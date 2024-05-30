#pragma once

#include "IGraph.hpp"

struct MatrixGraph final : IGraph {
private:
    std::vector<std::vector<bool>> adjacency_matrix;

public:
    explicit MatrixGraph(int number_of_vertices);

    explicit MatrixGraph(const IGraph& graph);

    ~MatrixGraph() override = default;

    void AddEdge(int from, int to) override;

    [[nodiscard]] int VerticesCount() const override;

    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;

    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;
};
