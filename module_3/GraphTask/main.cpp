#include <functional>
#include <iostream>
#include <queue>
#include <stack>

#include "include/ArcGraph.hpp"
#include "include/IGraph.hpp"
#include "include/ListGraph.hpp"
#include "include/MatrixGraph.hpp"
#include "include/SetGraph.hpp"

void DFS(const IGraph& graph, const int vertex, std::vector<bool>& visited, const std::function<void(int)>& func) {
    visited[vertex] = true;
    func(vertex);

    for (const int next_vertex : graph.GetNextVertices(vertex)) {
        if (!visited[next_vertex]) {
            DFS(graph, next_vertex, visited, func);
        }
    }
}


void mainDFS(const IGraph& graph, const std::function<void(int)>& func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            DFS(graph, i, visited, func);
        }
    }
}

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

    std::cout << "List Graph BFS\n";

    mainBFS(list_graph, [](const int vertex){ std::cout << vertex << " "; });
    std::cout << "\nList Graph DFS\n";
    mainDFS(list_graph, [](const int vertex){ std::cout << vertex << " "; });

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
    std::cout << "\nMatrix Graph BFS\n";
    mainBFS(matrix_graph, [](const int vertex){ std::cout << vertex << " "; });
    std::cout << "\nMatrix Graph DFS\n";
    mainDFS(matrix_graph, [](const int vertex){ std::cout << vertex << " "; });
    std::cout << "\nMatrix Graph from List Graph BFS\n";
    MatrixGraph matrix_graph2(matrix_graph);

    mainBFS(matrix_graph2, [](const int vertex){ std::cout << vertex << " "; });
    std::cout << "\nMatrix Graph from List Graph DFS\n";
    mainDFS(matrix_graph2, [](const int vertex){ std::cout << vertex << " "; });

    ArcGraph arc_graph(7);
    arc_graph.AddEdge(0, 1);
    arc_graph.AddEdge(0, 5);
    arc_graph.AddEdge(1, 2);
    arc_graph.AddEdge(1, 3);
    arc_graph.AddEdge(1, 5);
    arc_graph.AddEdge(1, 6);
    arc_graph.AddEdge(3, 2);
    arc_graph.AddEdge(3, 4);
    arc_graph.AddEdge(3, 6);
    arc_graph.AddEdge(5, 4);
    arc_graph.AddEdge(5, 6);
    arc_graph.AddEdge(6, 4);

    std::cout << "\nArc Graph BFS\n";
    mainBFS(arc_graph, [](const int vertex){ std::cout << vertex << " "; });
    std::cout << "\nArc Graph DFS\n";
    mainDFS(arc_graph, [](const int vertex){ std::cout << vertex << " "; });

    std::cout << "\nArc Graph from List Graph BFS\n";
    ArcGraph arc_graph2(list_graph);
    mainBFS(arc_graph2, [](const int vertex){ std::cout << vertex << " "; });

    std::cout << "\nArc Graph from Matrix Graph from List Graph BFS\n";
    ArcGraph arc_graph3(matrix_graph2);
    mainBFS(arc_graph3, [](const int vertex){ std::cout << vertex << " "; });

    SetGraph set_graph(7);
    set_graph.AddEdge(0, 1);
    set_graph.AddEdge(0, 5);
    set_graph.AddEdge(1, 2);
    set_graph.AddEdge(1, 3);
    set_graph.AddEdge(1, 5);
    set_graph.AddEdge(1, 6);
    set_graph.AddEdge(3, 2);
    set_graph.AddEdge(3, 4);
    set_graph.AddEdge(3, 6);
    set_graph.AddEdge(5, 4);
    set_graph.AddEdge(5, 6);
    set_graph.AddEdge(6, 4);

    std::cout << "\nSet Graph BFS\n";
    mainBFS(set_graph, [](const int vertex){ std::cout << vertex << " "; });
    std::cout << "\nSet Graph DFS\n";
    mainDFS(set_graph, [](const int vertex){ std::cout << vertex << " "; });

    std::cout << "\nSet Graph from List Graph BFS\n";
    SetGraph set_graph2(list_graph);
    mainBFS(set_graph2, [](const int vertex){ std::cout << vertex << " "; });

    std::cout << "\nSet Graph from Arc Graph from Matrix Graph from List Graph BFS\n";
    SetGraph set_graph3(arc_graph3);
    mainBFS(set_graph3, [](const int vertex){ std::cout << vertex << " "; });
    return 0;
}
