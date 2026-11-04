#include <iostream>
#include "graph.h"

using namespace std;

int main(int argc, char* argv[])
{
    Graph g1(5);

    // g1.addEdge(0, 1, 4);
    // g1.addEdge(0, 2, 2);
    // g1.addEdge(1, 2, 3);
    // g1.addEdge(1, 3, 2);
    // g1.addEdge(1, 4, 3);
    // g1.addEdge(2, 3, 4);
    // g1.addEdge(2, 4, 5);
    // g1.addEdge(3, 4, 1); 
    // g1.addEdge(5, 6);  

    g1.addEdge(0, 1, 2);
    g1.addEdge(0, 2, 1);
    g1.addEdge(1, 2, 1);
    g1.addEdge(1, 3, 2);
    g1.addEdge(1, 4, 3);
    g1.addEdge(2, 4, 4);
    g1.addEdge(3, 4, 2);

    cout << g1 << endl;

    g1.dijkstra(2);

    // g1.dfs(0);
    // cout << endl;

    // cout << "Breadth First Search: " << endl;
    // g1.bfs(3);
    // cout << endl;

    return 0;
}