#include <cassert>
#include <vector>
#include <set>

#define INT32_MAX 2147483647

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

int main(){
   IO(std::cin, std::cout);
}