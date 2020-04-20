#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <vector>

#define V 14

using namespace std;

// The maximum matching by using fordFulkerson algorithm
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

void convertGraph(const vector<vector<int>>& bpGraph, vector<vector<int>>& adjMatrix) {
    int numApp = bpGraph.size();
    int numJobs = bpGraph[0].size();

    // add two nodes as the source and dest
    // so the shape of matrix should be (numApp + numJobs + 2) * (numApp + numJobs + 2)
    int dim = numApp + numJobs + 2;
    adjMatrix.resize(dim, vector<int>(dim));

    // first add direct path for the starting node
    for (int i = 1; i <= numApp; i++)
        adjMatrix[0][i] = 1;
    
    // add direct path for the dest node
    for (int i = numApp+1; i < dim-1; i++)
        adjMatrix[i][dim-1] = 1;
    
    // add other values into graph
    for (int app = 0; app < numApp; app++) {
        for (int job = 0; job < numJobs; job++) {
            if (bpGraph[app][job])
                adjMatrix[app+1][job+numApp+1] = 1;
        }
    }
}

// the maximum matching problem
bool bpm(const vector<vector<int>>& bpGraph, int u, 
        vector<bool>& seen, vector<int>& matchR) {
    int numJobs = bpGraph[0].size();
    int numApplicants = bpGraph.size();

    for (int v = 0; v < numJobs; v++) {
        if (bpGraph[u][v] && !seen[v]) {
            seen[v] = true;

            if (matchR[v] == 0 || bpm(bpGraph, matchR[v],
                                    seen, matchR)) {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

int maxBPM(const vector<vector<int>>& bpGraph) {
    int numApplicants = bpGraph.size();
    int numJobs = bpGraph[0].size();

    // store the matched applicant for each job
    vector<int> matchR(numJobs);

    int result = 0;
    for (int u = 0; u < numApplicants; u++) {
        vector<bool> seen(numJobs);
        if (bpm(bpGraph, u, seen, matchR)) {
            result++;
        }
    }
    return result;
}

int main() 
{ 
    // Let us create a graph shown in the above example 
    vector<vector<int>> graph = {{0, 1, 1, 0, 0, 0}, 
                          {1, 0, 0, 1, 0, 0}, 
                          {0, 0, 1, 0, 0, 0}, 
                          {0, 0, 1, 1, 0, 0}, 
                          {0, 0, 0, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 1}}; 
    
    // In order to use the fordFulkerson algorithm, we need to add two extra nodes
    // and change the direct graph
    vector<vector<int>> adjMatrix;
    convertGraph(graph, adjMatrix); 
    int start = 0;
    int dest = adjMatrix.size() - 1;
    cout << "The maximum possible flow by fordFulkerson is " << fordFulkerson(adjMatrix, start, dest) << endl;
    
    cout << "The maximum possible flow by DFS and bp graph is " << maxBPM(graph) << endl;
    return 0; 
} 