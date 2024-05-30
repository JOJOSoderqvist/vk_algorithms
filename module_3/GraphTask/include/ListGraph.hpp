#pragma once
#include "IGraph.hpp"

struct ListGraph final : IGraph {
private:
    std::vector<std::vector<int>> adjacency_lists;
public:
    explicit ListGraph(int number_of_vertices);
    explicit ListGraph(const IGraph& graph);

    ~ListGraph() override = default;
    void AddEdge(int from, int to) override;
    [[nodiscard]] int VerticesCount() const override;
    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;
    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;
};
