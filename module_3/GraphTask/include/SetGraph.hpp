#pragma once

#include <unordered_set>

#include "IGraph.hpp"

struct SetGraph final : IGraph {
private:
    std::vector<std::unordered_set<int>> adjacency_sets;

public:
    explicit SetGraph(int number_of_vertices);

    explicit SetGraph(const IGraph& graph);

    ~SetGraph() override = default;

    void AddEdge(int from, int to) override;

    [[nodiscard]] int VerticesCount() const override;

    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;

    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;
};
