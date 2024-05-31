#include <queue>

#include <iostream>
#include "../include/ListGraph.hpp"

int BFSNumberOfPaths(ListGraph list_graph, const int vertex_from, const int vertex_to) {
    assert(
        0 <= vertex_from && vertex_from <= list_graph.VerticesCount() && 0 <= vertex_to && vertex_to <= list_graph.
        VerticesCount());
    std::queue<int> queue;
    std::vector<int> distance(list_graph.VerticesCount());
    std::vector<int> paths(list_graph.VerticesCount());
    std::vector<bool> visited(list_graph.VerticesCount(), false);

    queue.push(vertex_from);
    distance[vertex_from] = 0;
    paths[vertex_from] = 1;
    while (!queue.empty()) {
        const int current_vertex = queue.front();
        queue.pop();
        for (const int next_vertex : list_graph.GetNextVertices(current_vertex)) {
            if (!visited[next_vertex]) {
                visited[next_vertex] = true;
                queue.push(next_vertex);
            }
            if (distance[next_vertex] == 0 || distance[next_vertex] > distance[current_vertex] + 1) {
                distance[next_vertex] = distance[current_vertex] + 1;
                paths[next_vertex] = paths[current_vertex];
            } else if (distance[next_vertex] == distance[current_vertex] + 1) {
                paths[next_vertex] += paths[current_vertex];
            }
        }
    }
    return paths[vertex_to];
}


namespace task_2 {
    void IO(std::istream& input_stream, std::ostream& output_stream) {
        int number_of_vertices, number_of_edges, edge_from, edge_to, vertex_from, vertex_to;
        input_stream >> number_of_vertices >> number_of_edges;
        ListGraph list_graph(number_of_vertices);
        for (int i = 0; i < number_of_edges; ++i) {
            input_stream >> edge_from >> edge_to;
            list_graph.AddEdge(edge_from, edge_to);
            list_graph.AddEdge(edge_to, edge_from);
        }
        input_stream >> vertex_from >> vertex_to;
        output_stream << BFSNumberOfPaths(list_graph, vertex_from, vertex_to);
    }
}
