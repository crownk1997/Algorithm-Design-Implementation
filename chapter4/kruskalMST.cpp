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
    } compEdge;
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
    Edge[src].src = src;
    Edge[src].parent = dst;
    Edge[src].weight = weight;
}

void kruskalMST() {
    vector<Edge> result[V];
    int e = 0;
    int i = 0;

    sort(Edge.begin(), Edge.end(), compEdge);

    vector<subset> subsets(V);

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }   

    while (e < V - 1 && i < E) {

        edge next_edge = Edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.parent);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    cout<<"Following are the edges in the constructed MST\n";  
    for (i = 0; i < e; ++i)  
        cout<<result[i].src<<" -- "<<result[i].parent<<" == "<<result[i].weight<<endl;  
}

// Driver code 
int main()  
{  
    /* Let us create following weighted graph  
            10  
        0--------1  
        | \ |  
    6| 5\ |15  
        | \ |  
        2--------3  
            4 */
    int V = 4; // Number of vertices in graph  
    int E = 5; // Number of edges in graph  
    Graph graph(V, E);
  
  
    // add edge 0-1  
    graph->edge[0].src = 0;  
    graph->edge[0].dest = 1;  
    graph->edge[0].weight = 10;  
  
    // add edge 0-2  
    graph->edge[1].src = 0;  
    graph->edge[1].dest = 2;  
    graph->edge[1].weight = 6;  
  
    // add edge 0-3  
    graph->edge[2].src = 0;  
    graph->edge[2].dest = 3;  
    graph->edge[2].weight = 5;  
  
    // add edge 1-3  
    graph->edge[3].src = 1;  
    graph->edge[3].dest = 3;  
    graph->edge[3].weight = 15;  
  
    // add edge 2-3  
    graph->edge[4].src = 2;  
    graph->edge[4].dest = 3;  
    graph->edge[4].weight = 4;  
  
    KruskalMST(graph);  
    
    return 0;
}