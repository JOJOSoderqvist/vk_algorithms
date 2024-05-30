#pragma once
#include <vector>
#include <cassert>

struct IGraph {
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    [[nodiscard]] virtual int VerticesCount() const = 0;

    [[nodiscard]] virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    [[nodiscard]] virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};
