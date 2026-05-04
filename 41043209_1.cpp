#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class WeightedAdjacencyMatrixGraph {
private:
    int n; 
    int e; 
    vector<vector<int>> matrix;

public:
    WeightedAdjacencyMatrixGraph(int vertices) {
        n = vertices;
        e = 0;
        matrix.resize(n, vector<int>(n, 0));
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
        if (matrix[u][v] == 0) {
            e++;
        }
        matrix[u][v] = weight;
        matrix[v][u] = weight;
    }
    bool ExistsEdge(int u, int v) const {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            return false;
        }

        return matrix[u][v] != 0;
    }
    int Degree(int u) const {
        if (u < 0 || u >= n) {
            cout << "Invalid vertex!" << endl;
            return -1;
        }

        int count = 0;

        for (int v = 0; v < n; v++) {
            if (matrix[u][v] != 0) {
                count++;
            }
        }

        return count;
    }
    void DeleteEdge(int u, int v) {
            if (u < 0 || u >= n || v < 0 || v >= n) {
                cout << "Invalid vertex!" << endl;
                return;
            }

            if (matrix[u][v] != 0) {
                matrix[u][v] = 0;
                matrix[v][u] = 0;
                e--;
            }
        }
        void InsertVertex() {
        n++;

        for (int i = 0; i < n - 1; i++) {
            matrix[i].push_back(0);
        }

        matrix.push_back(vector<int>(n, 0));
    }
    void DeleteVertex(int v) {
        if (v < 0 || v >= n) {
            cout << "Invalid vertex!" << endl;
            return;
        }

        for (int i = 0; i < n; i++) {
            if (matrix[v][i] != 0) {
                e--;
            }
        }

        matrix.erase(matrix.begin() + v);

        for (int i = 0; i < n - 1; i++) {
            matrix[i].erase(matrix[i].begin() + v);
        }

        n--;
    }
    void PrintMatrix() const {
        cout << "Adjacency Matrix:" << endl;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(5) << matrix[i][j];
            }
            cout << endl;
        }
    }
};

int main() {
    WeightedAdjacencyMatrixGraph g(5);

    cout << "Initial graph:" << endl;
    cout << "Is empty: " << g.IsEmpty() << endl;
    cout << "Vertices: " << g.NumberOfVertices() << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintMatrix();
    cout << endl;

    g.InsertEdge(0, 1, 20);
    g.InsertEdge(0, 2, 30);
    g.InsertEdge(1, 3, 40);
    g.InsertEdge(2, 4, 50);

    cout << "After inserting edges:" << endl;
    cout << "Vertices: " << g.NumberOfVertices() << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintMatrix();
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
    g.PrintMatrix();
    cout << endl;

    g.InsertVertex();
    cout << "After inserting one vertex:" << endl;
    cout << "Vertices: " << g.NumberOfVertices() << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintMatrix();
    cout << endl;

    g.DeleteVertex(1);
    cout << "After deleting vertex 1:" << endl;
    cout << "Vertices: " << g.NumberOfVertices() << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintMatrix();

    return 0;
}