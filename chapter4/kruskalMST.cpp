#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct subset {
    int parent; // to store the name of the current set
    int rank; // to specify the number of elements in the current set
}

struct edge {
    int src;
    int parent;
    int weight;
}

class Graph {
private:
    int V, int E;
    vector<edge> Edge;

    // find the current node set name
    int find(vector<subset>& subsets, int i); 

    // make the union of two sets
    void Union(vector<subset>& subsets, int x, int y);

    struct {
        bool operator() (Edge& edge1, Edge& edge2) {
            return edge1.weight < edge2.weight;
        }
    } 
public:
    Graph(int V, int E);

    // add edge into graph with source node, destinaton node and weight
    void addEdge(int src, int dst, int weight);

    // Kruskal's algorithm to find minimum spanning tree
    void kruskalMST();

};

Graph::Graph(int V, int E) {
    this->V = V;
    this->E = E;    
    Edge.resize(E);
}

int Graph::find(vector<subset>& subsets, int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }

    return subsets[i].parent;
}

void Graph::Union(vector<subset>& subsets, int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else {
        subsets[yroot].parent = xroot;
    }
}

void Graph::addEdge(int src, int dst, int weight) {
    adj[src].push_back(make_pair(dst, weight));
    adj[dst].push_back(make_pair(src, weight));
}

void kruskalMST() {
    vector<Edge> result[V];
    int e = 0;
    int i = 0;

    
}