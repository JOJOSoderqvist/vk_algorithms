#pragma once
#include "IGraph.hpp"

struct ArcGraph final : IGraph {
private:
    std::vector<std::pair<int, int>> arcs;
    int _number_of_vertices{};
public:
    explicit ArcGraph(int number_of_vertices);

    explicit ArcGraph(const IGraph& graph);

    ~ArcGraph() override = default;

    void AddEdge(int from, int to) override;

    [[nodiscard]] int VerticesCount() const override;

    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;

    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;
};