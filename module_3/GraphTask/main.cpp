#include <functional>
#include <iostream>
#include <queue>

#include "include/ArcGraph.hpp"
#include "include/IGraph.hpp"
#include "include/ListGraph.hpp"
#include "include/MatrixGraph.hpp"
#include "include/SetGraph.hpp"

void BFS(const IGraph& graph, const int vertex, std::vector<bool>& visited, const std::function<void(int)>& func) {
    std::queue<int> queue;
    queue.push(vertex);
    visited[vertex] = true;
    while (!queue.empty()) {
        const int current_vertex = queue.front();
        queue.pop();
        func(current_vertex);

        for (int next_vertex: graph.GetNextVertices(current_vertex)) {
            if (!visited[next_vertex]) {
                visited[next_vertex] = true;
                queue.push(next_vertex);
            }
        }
    }
}


void mainBFS(const IGraph& graph, const std::function<void(int)>& func) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            BFS(graph, i, visited, func);
        }
    }
}


int main() {
    ListGraph list_graph(7);
    list_graph.AddEdge(0, 1);
    list_graph.AddEdge(0, 5);
    list_graph.AddEdge(1, 2);
    list_graph.AddEdge(1, 3);
    list_graph.AddEdge(1, 5);
    list_graph.AddEdge(1, 6);
    list_graph.AddEdge(3, 2);
    list_graph.AddEdge(3, 4);
    list_graph.AddEdge(3, 6);
    list_graph.AddEdge(5, 4);
    list_graph.AddEdge(5, 6);
    list_graph.AddEdge(6, 4);
    //
    //     mainBFS(list_graph, [](const int vertex){ std::cout << vertex << " "; });
    //     std::cout << '\n';
    //     ListGraph list_graph2(list_graph);
    //     mainBFS(list_graph, [](const int vertex){ std::cout << vertex << " "; });
    MatrixGraph matrix_graph(7);
    matrix_graph.AddEdge(0, 1);
    matrix_graph.AddEdge(0, 5);
    matrix_graph.AddEdge(1, 2);
    matrix_graph.AddEdge(1, 3);
    matrix_graph.AddEdge(1, 5);
    matrix_graph.AddEdge(1, 6);
    matrix_graph.AddEdge(3, 2);
    matrix_graph.AddEdge(3, 4);
    matrix_graph.AddEdge(3, 6);
    matrix_graph.AddEdge(5, 4);
    matrix_graph.AddEdge(5, 6);
    matrix_graph.AddEdge(6, 4);
    //     mainBFS(matrix_graph, [](const int vertex){ std::cout << vertex << " "; });
    //
    //      MatrixGraph matrix_graph2(matrix_graph);
    //      std::cout << '\n';
    //      mainBFS(matrix_graph2, [](const int vertex){ std::cout << vertex << " "; });
    //
    //      MatrixGraph matrix_graph3(list_graph);
    //      std::cout << '\n';
    //      mainBFS(matrix_graph3, [](const int vertex){ std::cout << vertex << " "; });
    //
    //
    //     ListGraph list_graph3(matrix_graph);
    //     std::cout << '\n';
    //     mainBFS(list_graph3, [](const int vertex){ std::cout << vertex << " "; });


    SetGraph set_graph(7);

    matrix_graph.AddEdge(0, 1);
    matrix_graph.AddEdge(0, 5);
    matrix_graph.AddEdge(1, 2);
    matrix_graph.AddEdge(1, 3);
    matrix_graph.AddEdge(1, 5);
    matrix_graph.AddEdge(1, 6);
    matrix_graph.AddEdge(3, 2);
    matrix_graph.AddEdge(3, 4);
    matrix_graph.AddEdge(3, 6);
    matrix_graph.AddEdge(5, 4);
    matrix_graph.AddEdge(5, 6);
    matrix_graph.AddEdge(6, 4);
    mainBFS(set_graph, [](const int vertex){ std::cout << vertex << " "; });


    std::cout << '\n';
    SetGraph set_graph2(matrix_graph);

    mainBFS(set_graph2, [](const int vertex){ std::cout << vertex << " "; });


    std::cout << "Arc Graph: ";

    ArcGraph arc_graph(7);

    matrix_graph.AddEdge(0, 1);
    matrix_graph.AddEdge(0, 5);
    matrix_graph.AddEdge(1, 2);
    matrix_graph.AddEdge(1, 3);
    matrix_graph.AddEdge(1, 5);
    matrix_graph.AddEdge(1, 6);
    matrix_graph.AddEdge(3, 2);
    matrix_graph.AddEdge(3, 4);
    matrix_graph.AddEdge(3, 6);
    matrix_graph.AddEdge(5, 4);
    matrix_graph.AddEdge(5, 6);
    matrix_graph.AddEdge(6, 4);
    mainBFS(arc_graph, [](const int vertex){ std::cout << vertex << " "; });
    std::cout << "Arc Graph: ";
    ArcGraph arc_graph2(list_graph);
    mainBFS(arc_graph2, [](const int vertex){ std::cout << vertex << " "; });
    return 0;
}
