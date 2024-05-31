#pragma once
#include <cassert>
#include <vector>

struct ListGraph {
private:
    std::vector<std::vector<int>> adjacency_lists;
public:
    explicit ListGraph(const int number_of_vertices) : adjacency_lists(number_of_vertices){}

    ~ListGraph() = default;
    void AddEdge(const int from, const int to) {
        assert(0 <= from && from < adjacency_lists.size() && 0 <= to && to <= adjacency_lists.size());
        adjacency_lists[from].push_back(to);
    }

    [[nodiscard]] int VerticesCount() const {
        return static_cast<int>(adjacency_lists.size());
    }

    [[nodiscard]] std::vector<int> GetNextVertices(const int vertex) const {
        assert(0 <= vertex && vertex <= adjacency_lists.size());
        return adjacency_lists[vertex];
    }
    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const {
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
};
