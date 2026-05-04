#include <iostream>
#include <vector>
using namespace std;

struct EdgeNode {
    int ivex;
    int jvex;
    int weight;
    EdgeNode* ilink;
    EdgeNode* jlink;
};

struct VertexNode {
    EdgeNode* firstEdge;
};

class WeightedAdjacencyMultilistGraph {
private:
    int n;
    int e;
    vector<VertexNode> vertices;
    void RemoveEdgeFromVertex(int vertex, EdgeNode* target) {
        EdgeNode* current = vertices[vertex].firstEdge;
        EdgeNode* previous = nullptr;

        while (current != nullptr) {
            if (current == target) {
                if (previous == nullptr) {
                    if (current->ivex == vertex) {
                        vertices[vertex].firstEdge = current->ilink;
                    } else {
                        vertices[vertex].firstEdge = current->jlink;
                    }
                } else {
                    if (previous->ivex == vertex) {
                        if (current->ivex == vertex) {
                            previous->ilink = current->ilink;
                        } else {
                            previous->ilink = current->jlink;
                        }
                    } else {
                        if (current->ivex == vertex) {
                            previous->jlink = current->ilink;
                        } else {
                            previous->jlink = current->jlink;
                        }
                    }
                }

                return;
            }

            previous = current;

            if (current->ivex == vertex) {
                current = current->ilink;
            } else {
                current = current->jlink;
            }
        }
    }
public:
    WeightedAdjacencyMultilistGraph(int verticesCount) {
        n = verticesCount;
        e = 0;

        vertices.resize(n);

        for (int i = 0; i < n; i++) {
            vertices[i].firstEdge = nullptr;
        }
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

        EdgeNode* newEdge = new EdgeNode;
        newEdge->ivex = u;
        newEdge->jvex = v;
        newEdge->weight = weight;

        newEdge->ilink = vertices[u].firstEdge;
        vertices[u].firstEdge = newEdge;

        newEdge->jlink = vertices[v].firstEdge;
        vertices[v].firstEdge = newEdge;

        e++;
    }
    void PrintMultilist() const {
        cout << "Adjacency Multilist:" << endl;

        for (int i = 0; i < n; i++) {
            cout << i << ": ";

            EdgeNode* current = vertices[i].firstEdge;

            while (current != nullptr) {
                int neighbor;

                if (current->ivex == i) {
                    neighbor = current->jvex;
                    cout << "(" << neighbor << ", " << current->weight << ") ";
                    current = current->ilink;
                } else {
                    neighbor = current->ivex;
                    cout << "(" << neighbor << ", " << current->weight << ") ";
                    current = current->jlink;
                }
            }

            cout << endl;
        }
    }
    bool ExistsEdge(int u, int v) const {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            return false;
        }

        EdgeNode* current = vertices[u].firstEdge;

        while (current != nullptr) {
            if (current->ivex == u) {
                if (current->jvex == v) {
                    return true;
                }
                current = current->ilink;
            } else {
                if (current->ivex == v) {
                    return true;
                }
                current = current->jlink;
            }
        }

        return false;
    }
    int Degree(int u) const {
        if (u < 0 || u >= n) {
            cout << "Invalid vertex!" << endl;
            return -1;
        }

        int count = 0;
        EdgeNode* current = vertices[u].firstEdge;

        while (current != nullptr) {
            count++;

            if (current->ivex == u) {
                current = current->ilink;
            } else {
                current = current->jlink;
            }
        }

        return count;
    }
    void DeleteEdge(int u, int v) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "Invalid vertex!" << endl;
            return;
        }

        EdgeNode* current = vertices[u].firstEdge;
        EdgeNode* target = nullptr;

        while (current != nullptr) {
            if (current->ivex == u) {
                if (current->jvex == v) {
                    target = current;
                    break;
                }
                current = current->ilink;
            } else {
                if (current->ivex == v) {
                    target = current;
                    break;
                }
                current = current->jlink;
            }
        }

        if (target == nullptr) {
            return;
        }

        RemoveEdgeFromVertex(u, target);
        RemoveEdgeFromVertex(v, target);

        delete target;
        e--;
    }
    void InsertVertex() {
        VertexNode newVertex;
        newVertex.firstEdge = nullptr;

        vertices.push_back(newVertex);
        n++;
    }
    void DeleteVertex(int v) {
        if (v < 0 || v >= n) {
            cout << "Invalid vertex!" << endl;
            return;
        }

        while (vertices[v].firstEdge != nullptr) {
            EdgeNode* edge = vertices[v].firstEdge;

            int other;
            if (edge->ivex == v) {
                other = edge->jvex;
            } else {
                other = edge->ivex;
            }

            DeleteEdge(v, other);
        }

        vertices.erase(vertices.begin() + v);
        n--;

        for (int i = 0; i < n; i++) {
            EdgeNode* current = vertices[i].firstEdge;

            while (current != nullptr) {
                if (current->ivex > v) {
                    current->ivex--;
                }

                if (current->jvex > v) {
                    current->jvex--;
                }

                if (current->ivex == i) {
                    current = current->ilink;
                } else {
                    current = current->jlink;
                }
            }
        }
    }
};

int main() {
    WeightedAdjacencyMultilistGraph g(5);

    cout << "Initial graph:" << endl;
    cout << "Is empty: " << g.IsEmpty() << endl;
    cout << "Vertices: " << g.NumberOfVertices() << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintMultilist();

    cout << endl;

    g.InsertEdge(0, 1, 20);
    g.InsertEdge(0, 2, 30);
    g.InsertEdge(1, 3, 40);
    g.InsertEdge(2, 4, 50);

    cout << "After inserting edges:" << endl;
    cout << "Vertices: " << g.NumberOfVertices() << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintMultilist();
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
    g.PrintMultilist();
    cout << endl;

    g.InsertVertex();
    cout << "After inserting one vertex:" << endl;
    cout << "Vertices: " << g.NumberOfVertices() << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintMultilist();
    cout << endl;

    g.DeleteVertex(1);
    cout << "After deleting vertex 1:" << endl;
    cout << "Vertices: " << g.NumberOfVertices() << endl;
    cout << "Edges: " << g.NumberOfEdges() << endl;
    g.PrintMultilist();

    return 0;
}