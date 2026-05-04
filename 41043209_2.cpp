#include <iostream>
#include <vector>
using namespace std;

struct EdgeNode {
    int vertex;
    int weight;
};

class WeightedAdjacencyListGraph {
private:
    int n;
    int e;
    vector<vector<EdgeNode>> adjList;

public:
    WeightedAdjacencyListGraph(int vertices) {
        n = vertices;
        e = 0;
        adjList.resize(n);
    }
    bool IsEmpty() const {
        return n == 0;
    }

    int NumberOfVertices() const {
        return n;
    }

    int NumberOfEdges() const {
        return e;
    }
    void InsertEdge(int u, int v, int weight) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "Invalid vertex!" << endl;
            return;
        }

        if (weight <= 0) {
            cout << "Weight must be positive!" << endl;
            return;
        }

        for (int i = 0; i < adjList[u].size(); i++) {
            if (adjList[u][i].vertex == v) {
                adjList[u][i].weight = weight;

                for (int j = 0; j < adjList[v].size(); j++) {
                    if (adjList[v][j].vertex == u) {
                        adjList[v][j].weight = weight;
                        return;
                    }
                }
            }
        }

        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
        e++;
    }
    void PrintList() const {
        cout << "Adjacency List:" << endl;

        for (int i = 0; i < n; i++) {
            cout << i << ": ";

            for (int j = 0; j < adjList[i].size(); j++) {
                cout << "(" << adjList[i][j].vertex 
                    << ", " << adjList[i][j].weight << ") ";
            }

            cout << endl;
        }
    }
    bool ExistsEdge(int u, int v) const {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            return false;
        }

        for (int i = 0; i < adjList[u].size(); i++) {
            if (adjList[u][i].vertex == v) {
                return true;
            }
        }

        return false;
    }

    int Degree(int u) const {
        if (u < 0 || u >= n) {
            cout << "Invalid vertex!" << endl;
            return -1;
        }

        return adjList[u].size();
    }
    void DeleteEdge(int u, int v) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "Invalid vertex!" << endl;
            return;
        }

        bool found = false;

        for (int i = 0; i < adjList[u].size(); i++) {
            if (adjList[u][i].vertex == v) {
                adjList[u].erase(adjList[u].begin() + i);
                found = true;
                break;
            }
        }

        for (int i = 0; i < adjList[v].size(); i++) {
            if (adjList[v][i].vertex == u) {
                adjList[v].erase(adjList[v].begin() + i);
                break;
            }
        }

        if (found) {
            e--;
        }
    }
    void InsertVertex() {
        adjList.push_back(vector<EdgeNode>());
        n++;
    }
    void DeleteVertex(int v) {
        if (v < 0 || v >= n) {
            cout << "Invalid vertex!" << endl;
            return;
        }

        // 先扣掉跟 v 相連的邊數
        e -= adjList[v].size();

        // 刪掉第 v 個 adjacency list
        adjList.erase(adjList.begin() + v);
        n--;

        // 處理其他頂點的 adjacency list
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < adjList[i].size(); j++) {

                // 如果有邊連到被刪掉的頂點 v，就刪掉
                if (adjList[i][j].vertex == v) {
                    adjList[i].erase(adjList[i].begin() + j);
                    j--;
                }

                // 如果頂點編號比 v 大，刪除後要往前移一格
                else if (adjList[i][j].vertex > v) {
                    adjList[i][j].vertex--;
                }
            }
        }
    }
};

int main() {
    WeightedAdjacencyListGraph g(5);

    cout << "Initial graph:" << endl;
    cout << "Is empty: " << g.IsEmpty() << endl;
    cout << "Vertices: " << g.NumberOfVertices() << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintList();

    cout << endl;

    g.InsertEdge(0, 1, 20);
    g.InsertEdge(0, 2, 30);
    g.InsertEdge(1, 3, 40);
    g.InsertEdge(2, 4, 50);

    cout << "After inserting edges:" << endl;
    cout << "Vertices: " << g.NumberOfVertices() << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintList();

    cout << endl;

    cout << "Degree of vertex 0: " << g.Degree(0) << endl;
    cout << "Degree of vertex 1: " << g.Degree(1) << endl;

    cout << endl;

    cout << "Exists edge (0, 1): " << g.ExistsEdge(0, 1) << endl;
    cout << "Exists edge (3, 4): " << g.ExistsEdge(3, 4) << endl;

    cout << endl;

    g.DeleteEdge(0, 1);

    cout << "After deleting edge (0, 1):" << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintList();

    cout << endl;

    g.InsertVertex();

    cout << "After inserting one vertex:" << endl;
    cout << "Vertices: " << g.NumberOfVertices() << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintList();

    cout << endl;

    g.DeleteVertex(2);

    cout << "After deleting vertex 2:" << endl;
    cout << "Vertices: " << g.NumberOfVertices() << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintList();

    return 0;
}