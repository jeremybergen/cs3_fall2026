#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int node1;
    int node2;
    int weight;
};

int find(int, vector<int>);
void unify(int, int, vector<int>&, vector<int>&, vector<Edge>&, Edge);

int main(int argc, char* argv[])
{
    vector<Edge> edges;
    vector<Edge> mst;
    vector<int> roots;
    vector<int> ranks;

    edges.push_back({0, 1, 3});
    edges.push_back({0, 2, 8});
    edges.push_back({0, 3, 3});
    edges.push_back({0, 4, 1});
    edges.push_back({0, 5, 3});
    edges.push_back({1, 4, 7});
    edges.push_back({1, 2, 5});
    edges.push_back({2, 3, 1});
    edges.push_back({2, 5, 2});
    edges.push_back({2, 4, 3});

    for(int i = 0; i < 6; i++)
    {
        roots.push_back(-1);
        ranks.push_back(1);
    }
    // cout << "roots.size(): " << roots.size() << endl;
    // cout << "ranks.size(): " << ranks.size() << endl;

    // int root1 = find(0, roots);
    // int root2 = find(1, roots);

    while(!edges.empty())
    {
        int position = 0;
        Edge smallestEdge = edges.front();
        for(size_t i = 1; i < edges.size(); i++)
        {
            if(smallestEdge.weight > edges.at(i).weight)
            {
                smallestEdge = edges.at(i);
                position = i;
            }
        }
        edges.erase(edges.begin() + position);
        // cout << "smallestEdge: " << smallestEdge.node1 << ", " << smallestEdge.node2 << ", " << smallestEdge.weight << endl;

        // for(auto elem : roots)
        // {
        //     cout << elem << " ";
        // }
        // cout << endl;
        // for(auto elem : ranks)
        // {
        //     cout << elem << " ";
        // }
        // cout << endl;
        

        int root1 = find(smallestEdge.node1, roots);
        int root2 = find(smallestEdge.node2, roots);

        unify(root1, root2, ranks, roots, mst, smallestEdge);
    }

    // cout << "After while" << endl;
    for(auto elem : mst)
    {
        cout << elem.node1 << " - " << elem.node2 << ": " << elem.weight << endl;
    }
    

    return 0;
}

void unify(int node1, int node2, vector<int>& ranks, vector<int>& roots, vector<Edge>& mst, Edge edge)
{
    if(node1 == node2) return;
    if(ranks.at(node1) > ranks.at(node2))
    {
        ranks.at(node1) += ranks.at(node2);
        roots.at(node2) = node1;
    }
    else
    {
        ranks.at(node2) += ranks.at(node1);
        roots.at(node1) = node2;
    }
    mst.push_back(edge);
}

int find(int node, vector<int> roots)
{
    //Iterative
    int parent = node;

    while(roots.at(parent) != -1)
    {
        parent = roots.at(parent);
    }

    return parent;

    // //Recursive
    // if(roots.at(node) == -1) return node;

    // return find(roots.at(node), roots);
}

