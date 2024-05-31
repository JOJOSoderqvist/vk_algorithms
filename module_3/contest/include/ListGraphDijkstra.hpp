#pragma once
#include <cassert>
#include <vector>

struct ListGraphDijkstra {
private:
    std::vector<std::vector<std::pair<int, int>>> adjacency_lists;
public:
    explicit ListGraphDijkstra(const int number_of_vertices) : adjacency_lists(number_of_vertices){}

    ~ListGraphDijkstra() = default;
    void AddEdge(const int from, const int to, const int weight) {
        assert(0 <= from && from < adjacency_lists.size() && 0 <= to && to <= adjacency_lists.size());
        adjacency_lists[from].push_back({to, weight});
    }

    [[nodiscard]] int VerticesCount() const {
        return static_cast<int>(adjacency_lists.size());
    }

    [[nodiscard]] std::vector<std::pair<int, int>> GetNextVertices(const int vertex) const {
        assert(0 <= vertex && vertex <= adjacency_lists.size());
        return adjacency_lists[vertex];
    }
    [[nodiscard]] std::vector<int> GetPrevVertices(const int vertex) const {
        assert(0 <= vertex && vertex <= adjacency_lists.size());
        std::vector<int> prev_vertices;
        for (int from = 0; from < adjacency_lists.size(); ++from) {
            for (const auto [to, _]: adjacency_lists[from]) {
                if (to == vertex) {
                    prev_vertices.push_back(from);
                }
            }
        }
        return prev_vertices;
    }
};
