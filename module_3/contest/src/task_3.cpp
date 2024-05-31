#include <cstdint>
#include <iostream>
#include <set>

#include "../include/ListGraphDijkstra.hpp"

int dijkstra(ListGraphDijkstra list_graph, int vertex_from, int vertex_to) {
    std::set<std::pair<int, int>> set;
    std::vector<int> distance(list_graph.VerticesCount(), INT32_MAX);
    set.insert({0, vertex_from});
    distance[vertex_from] = 0;

    while (!set.empty()) {
        const auto tmp = set.begin();
        set.erase(set.begin());

        const int current_vertex = tmp->second;

        for (const auto [vertex, weight] : list_graph.GetNextVertices(current_vertex)) {
            if (distance[vertex] > distance[current_vertex] + weight) {
                if (distance[vertex] != INT32_MAX) {
                    set.erase(set.find({distance[vertex], vertex}));
                }
                distance[vertex] = distance[current_vertex] + weight;
                set.insert({distance[vertex], vertex});
            }
        }
    }
    return distance[vertex_to];
}

namespace task_3 {
    void IO(std::istream& input_stream, std::ostream& output_stream) {
        int number_of_vertices, number_of_edges, edge_from, edge_to, weight, vertex_from, vertex_to;
        input_stream >> number_of_vertices >> number_of_edges;
        ListGraphDijkstra list_graph(number_of_vertices);
        for (int i = 0; i < number_of_edges; ++i) {
            input_stream >> edge_from >> edge_to >> weight;
            list_graph.AddEdge(edge_from, edge_to, weight);
            list_graph.AddEdge(edge_to, edge_from, weight);
        }
        input_stream >> vertex_from >> vertex_to;
        output_stream << dijkstra(list_graph, vertex_from, vertex_to);
    }
}
