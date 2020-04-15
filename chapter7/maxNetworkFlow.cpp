#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <vector>

#define V 6

using namespace std;

bool bfs(const vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
    vector<bool> visited(V, false);

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[t] == true);
}

int fordFulkerson(const vector<vector<int>>& graph, int s, int t) {
    // initialize the residual graph as the original graph
    vector<vector<int>> rGraph(graph);

    vector<int> parent(V);

    int max_flow = 0;

    // check where there is path left
    while (bfs(rGraph, s, t, parent)) {
        // find the minimum residual capacity along the path
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // update residual capacity and reverse edges along the path
        // as the backward edge
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() 
{ 
    // Let us create a graph shown in the above example 
    vector<vector<int>> graph = { {0, 16, 13, 0, 0, 0}, 
                        {0, 0, 10, 12, 0, 0}, 
                        {0, 4, 0, 0, 14, 0}, 
                        {0, 0, 9, 0, 0, 20}, 
                        {0, 0, 0, 7, 0, 4}, 
                        {0, 0, 0, 0, 0, 0} 
                      }; 
  
    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 5) << endl;
  
    return 0; 
} 