#pragma once
#include <vector>
#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Graph
{
    private:
    vector< vector< int > > _adjMatrix;
    vector< list< int > > _adjList;
    vector< bool > _visited;

    public:
    Graph(int n)
    {
        _adjMatrix = vector< vector< int > >(n, vector< int >(n, 0));
        _adjList = vector< list< int > >(n, list< int >());
        _visited = vector< bool >(n, false);
    }

    void addEdge(int u, int v, int w)
    {
        _adjMatrix.at(u).at(v) = w;
        _adjMatrix.at(v).at(u) = w;

        // _adjList.at(u).push_back(v);
        // _adjList.at(v).push_back(u);
    }

    friend ostream& operator<<(ostream& os, const Graph g)
    {
        for(size_t i = 0; i < g._adjMatrix.size(); i++)
        {
            for(size_t j = 0; j < g._adjMatrix.size(); j++)
            {
                os << g._adjMatrix.at(i).at(j) << " ";
            }
            os << endl;
        }
        return os;
    }

    void explore(int v)
    {
        //previsit
        _visited.at(v) = true;
        cout << v << " ";
        for(size_t col = 0; col < _adjMatrix.size(); col++)
        {
            if(_adjMatrix.at(v).at(col) == 1 && !_visited.at(col)) explore(col);
        }
        //postvisit
    }

    void dfs(int v)
    {
        cout << "First graph: " << endl;
        explore(v);
        cout << endl;

        // now unconnected graphs
        for(size_t vertex = 0; vertex < _adjMatrix.size(); vertex++)
        {
            if(!_visited.at(vertex)) 
            {
                std::cout << "New unconnected graph: " << endl;
                explore(vertex);
            }
        }
    }

    void resetVisited()
    {
        for(size_t i = 0; i < _visited.size(); i++)
        {
            _visited.at(i) = false;
        }
    }

    void bfs(int v)
    {
        resetVisited();
        queue<int> q1;

        q1.push(v);
        _visited.at(v) = true;
        while(!q1.empty())
        {
            v = q1.front();
            q1.pop();
            cout << v << " ";
            for(size_t col = 0; col < _adjMatrix.size(); col++)
            {
                if(_adjMatrix.at(v).at(col) == 1 && !_visited.at(col))
                {
                    q1.push(col);
                    _visited.at(col) = true;
                }
            }
        }
    }

    private:
    struct HeapNode
    {
        int v;
        int cost;
        int prev;
    };

    class mycomparison
    {
        bool reverse;
        public:
        mycomparison(const bool& revparam=false)
            {reverse=revparam;}
        bool operator() (const HeapNode& lhs, const HeapNode&rhs) const
        {
            if (reverse) return (lhs.cost<rhs.cost);
            else return (lhs.cost>rhs.cost);
        }
    };

    public:
    void dijkstra(int v)
    {
        HeapNode nodes[_adjMatrix.size()];
        for(size_t i = 0; i < _adjMatrix.size(); i++)
        {
            nodes[i].v = i;
            nodes[i].cost = 9999;
            nodes[i].prev = -1;
        }

        nodes[v].cost = 0;

        priority_queue<HeapNode, vector<HeapNode>, mycomparison> H;
        for(auto& elem : nodes)
        {
            H.push(elem);
        }

        while(!H.empty())
        {
            HeapNode u = H.top();
            // cout << "DEBUG: u.v: " << u.v << endl;
            H.pop();
            for(size_t i = 0; i < _adjMatrix.size(); i++)
            {
                // cout << &nodes[i] << ", " << &u << endl;
                // cout << "DEBUG: _adjMatrix.at(" << u.v << ").at(" << i << "): " << _adjMatrix.at(u.v).at(i) << endl;
                if(_adjMatrix.at(u.v).at(i) == 0) continue;
                // cout << "DEBUG: nodes[" << i << "].cost: " << nodes[i].cost << ":" 
                //      << "u.cost + _adjMatrix.at(" << u.v << ").at(" << i << "): " << u.cost + _adjMatrix.at(u.v).at(i) << endl;
                // cout << &nodes[i] << &u << endl;
                if(nodes[i].cost > nodes[u.v].cost + _adjMatrix.at(u.v).at(i))
                {
                    nodes[i].cost = nodes[u.v].cost + _adjMatrix.at(u.v).at(i);
                    nodes[i].prev = nodes[u.v].v;
                }
            }
            // cout << H.top().v << ", " << H.top().cost << " ";
            // H.pop();
        }

        for(auto elem : nodes)
        {
            cout << elem.v << ": " << elem.cost << ", prev: " << elem.prev << ", ";
        }
        cout << endl;
    }
};