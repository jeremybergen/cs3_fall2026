#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
struct Edge
{
    int node1, node2;
};

class UnionFind
{
    private:
    vector<int> _parent, _rank;

    public:
    UnionFind(int size)
    {
        _parent.resize(size, -1);
        _rank.resize(size, 1);
    }
    int find(int node)
    {
        while(_parent.at(node) != -1)
        {
            node = _parent.at(node);
        }
        return node;
    }

    void unify(int node1, int node2)
    {
        int root1 = find(node1);
        int root2 = find(node2);

        if (root1 == root2) return;

        if(_rank.at(root1) < _rank.at(root2))
        {
            _parent.at(root1) = root2;
        }
        else if(_rank.at(root1) > _rank.at(root2))
        {
            _parent.at(root2) = root1;
        }
        else
        {
            _parent.at(root2) = root1;
            _rank.at(root1)++;
        }
    }
};

class Maze
{
    private:
    int _height, _width;
    int _startx, _starty;
    int _endx, _endy;
    vector<bool> _verticalWalls;
    vector<bool> _horizontalWalls;

    public:
    Maze(int height, int width) : _height(height), _width(width)
    {
        _verticalWalls.resize((_width-1) * _height, true);
        _horizontalWalls.resize((_height-1) * _width, true);
        _startx = 0;
        _starty = 0;
        _endx = _width - 1;
        _endy = _height - 1;
    }
    
    void generate()
    {
        vector<Edge> edges;
        UnionFind uf(_height * _width);

        for(int i = 0; i < _height; i++)
        {
            for(int j = 0; j < _width; j++)
            {
                // edges.push_back((_width*i-j), )
                if(j < _width - 1)
                {
                    edges.push_back({(_width * i) +j, (_width * i) + j + 1});
                }
                if(i < _height - 1)
                {
                    edges.push_back({(_width * i) +j, (_width * i) + j + _width});
                }
            }
        }

        random_device rd;
        mt19937 g(rd());
        shuffle(edges.begin(), edges.end(), g);

        for(auto edge : edges)
        {
            int root1 = uf.find(edge.node1);
            int root2 = uf.find(edge.node2);

            if(root1 != root2)
            {
                uf.unify(root1, root2);

                int ax = edge.node1 % _width;
                int ay = edge.node1 / _width;
                int bx = edge.node2 % _width;
                int by = edge.node2 / _width;

                if(ax == bx)
                {
                    _horizontalWalls.at(min(ay, by) * _width + ax) = false;
                }
                else
                {
                    _verticalWalls.at(ay * (_width -1) + min(ax, bx)) = false;
                }
            }
        }
    }

    void print()
    {
        for(int x = 0; x < _width; x++)
        {
            cout << "+";
            if(x == _startx)
            {
                cout << "   ";
            }
            else
            {
                cout << "---";
            }
        }
        cout << "+" << endl;

        for(int y = 0; y < _height; y++)
        {
            cout << "|";
            for(int x = 0; x < _width; x++)
            {
                cout << "   ";
                if(x < _width -1 && !_verticalWalls.at(y*(_width - 1) + x))
                {
                    cout << " ";
                }
                else
                {
                    cout << "|";
                }
            }

            cout << endl;

            for(int x = 0; x < _width; x++)
            {
                cout << "+";
                if(y == _endy && x == _endx)
                {
                    cout << "   ";
                }
                else if(y < _height - 1 && !_horizontalWalls.at(y * _width + x))
                {
                    cout << "   ";
                }
                else
                {
                    cout << "---";
                }
            }
            cout << endl;
        }
    }
};

int main(int argc, char* argv[])
{
    int height = 20;
    int width = 20;

    Maze maze(height, width);

    maze.generate();
    maze.print();
    return 0;
}