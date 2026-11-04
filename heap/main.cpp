#include <iostream>
#include <vector>

using namespace std;

class Heap
{
    private:
    vector<int> _array;
    public:
    Heap() = default;

    void heapify(int index)
    {
        int largest = index;
        int left = 2*index + 1;
        int right = 2*index + 2;

        if(left < _array.size() && _array.at(left) > _array.at(largest))
        {
            largest = left;
        }

        if(right < _array.size() && _array.at(right) > _array.at(largest))
        {
            largest = right;
        }

        if(largest != index)
        {
            swap(_array.at(index), _array.at(largest));
            heapify(largest);
        }
    }

    void insert(int num)
    {
        _array.push_back(num);
        // heapify(_array.size()-1);

        int i = _array.size()-1;
        while(i != 0 && _array.at((i - 1)/2) < _array.at(i))
        {
            swap(_array.at((i - 1)/2), _array.at(i));
            i = (i-1)/2;
        }
    }

    int remove()
    {
        int toReturn;
        if(_array.size() == 0)
        {
            cerr << "Heap empty" << endl;
            return -1;
        }

        if(_array.size() == 1)
        {
            toReturn = _array.back();
            _array.pop_back();
            return toReturn;
        }

        swap(_array.at(0), _array.at(_array.size() - 1));
        toReturn = _array.at(_array.size() - 1);
        _array.pop_back();

        heapify(0);

        return toReturn;
    }

    friend ostream& operator<<(ostream& os, const Heap h1)
    {
        for(auto elem : h1._array)
        {
            os << elem << " ";
        }
        return os;
    }
};

int main(int argc, char* argv[])
{
    Heap myHeap;
    myHeap.insert(42);
    cout << myHeap << endl;
    myHeap.insert(23);
    cout << myHeap << endl;
    myHeap.insert(15);
    cout << myHeap << endl;
    myHeap.insert(100);
    cout << myHeap << endl;
    myHeap.insert(123);
    cout << myHeap << endl;

    cout << myHeap.remove() << endl;
    cout << myHeap << endl;

    return 0;
}