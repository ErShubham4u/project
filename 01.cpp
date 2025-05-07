#include <iostream> 
#include <vector> 
#include <queue> 
#include <stack> 
#include <omp.h> 
using namespace std; 
 
class Graph { 
    int V; 
    vector<vector<int>> adj; 
 
public: 
    Graph(int V) : V(V), adj(V) {} 
    void addEdge(int v, int w) { 
        adj[v].push_back(w); 
        adj[w].push_back(v); 
    } 
 
    void parallelBFS(int start) { 
        vector<bool> visited(V, false); 
        queue<int> q; 
        visited[start] = true; 
        q.push(start); 
 
        while (!q.empty()) { 
            int curr = q.front(); q.pop(); 
            cout << curr << " "; 
 
            #pragma omp parallel for 
            for (int i = 0; i < adj[curr].size(); ++i) { 
                int neighbor = adj[curr][i]; 
                if (!visited[neighbor]) { 
                    #pragma omp critical 
                    { 
                        if (!visited[neighbor]) { 
                            visited[neighbor] = true; 
                            q.push(neighbor); 
                        } 
                    } 
                } 
            } 
        } 
    } 
 
    void parallelDFS(int start) { 
        vector<bool> visited(V, false); 
        stack<int> st; 
        st.push(start); 
 
        while (!st.empty()) { 
            int curr = st.top(); st.pop(); 
            if (!visited[curr]) { 
                cout << curr << " "; 
                visited[curr] = true; 
            } 
 
            #pragma omp parallel for 
            for (int i = 0; i < adj[curr].size(); ++i) { 
                int neighbor = adj[curr][i]; 
                if (!visited[neighbor]) { 
                    #pragma omp critical 
                    st.push(neighbor); 
                } 
            } 
        } 
    } 
}; 
 
int main() { 
    Graph g(6); 
    g.addEdge(0, 1); g.addEdge(0, 2); 
    g.addEdge(1, 2); g.addEdge(2, 3); 
    g.addEdge(3, 4); g.addEdge(4, 5); 
 
    int start; 
    char choice; 
    do { 
        cout << "\nEnter starting node: "; 
        cin >> start; 
        cout << "Parallel BFS from " << start << ":\n"; 
        g.parallelBFS(start); 
        cout << "\nParallel DFS from " << start << ":\n"; 
        g.parallelDFS(start); 
 
        cout << "\nContinue? (y/n): "; 
        cin >> choice; 
    } while (choice == 'y' || choice == 'Y'); 
 
    return 0; 
} 


// Enter starting node: 2
// Parallel BFS from 2:
// 2 0 1 3 4 5 
// Parallel DFS from 2:
// 2 3 4 5 0 1 
// Continue? (y/n): y

// Enter starting node: 0
// Parallel BFS from 0:
// 0 1 2 3 4 5 
// Parallel DFS from 0:
// 0 2 3 4 5 1 
// Continue? (y/n): n



// int main() {
//     int V, E;
//     cout << "Enter the number of nodes: ";
//     cin >> V;
//     cout << "Enter the number of edges: ";
//     cin >> E;

//     Graph g(V);

//     cout << "Enter the edges (format: u v):" << endl;
//     for (int i = 0; i < E; i++) {
//         int u, v;
//         cin >> u >> v;
//         g.addEdge(u, v);
//     }

//     int start;
//     char choice;
//     do {
//         cout << "\nEnter starting node: ";
//         cin >> start;

//         cout << "Parallel BFS from " << start << ":\n";
//         g.parallelBFS(start);

//         cout << "\nParallel DFS from " << start << ":\n";
//         g.parallelDFS(start);

//         cout << "\nContinue? (y/n): ";
//         cin >> choice;
//     } while (choice == 'y' || choice == 'Y');

//     return 0;
// }