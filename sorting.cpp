#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

void buildArray(vector<int>&);
void bubbleSort(vector<int>&);
void mergeSort(vector<int>&, int, int);
void merge(vector<int>&, int, int, int);

int main(int argc, char* argv[])
{
    vector<int> unsorted_numbers;
    

    buildArray(unsorted_numbers);
    vector<int> merge_numbers = unsorted_numbers;

    // auto start = chrono::system_clock::now();
    // bubbleSort(unsorted_numbers);
    // auto end = chrono::system_clock::now();
    // cout << "Bubble Sort: " << (end - start).count() << endl;

    auto start = chrono::system_clock::now();
    cout << "merge_numbers.size(): " << merge_numbers.size() << endl;
    mergeSort(merge_numbers, 0, merge_numbers.size()-1);
    auto end = chrono::system_clock::now();
    cout << "Merge Sort: " << (end - start).count() << endl;
    // cout << boolalpha << "Equal: " << (unsorted_numbers == merge_numbers) << endl;

    for(int i : merge_numbers)
    {
        cout << i << endl;
    }

    return 0;
}

void mergeSort(vector<int>& numbers, int beg, int end)
{
    if (beg >= end) return;

    int mid = beg + (end - beg)/2;
    mergeSort(numbers, beg, mid);
    mergeSort(numbers, mid+1, end);
    merge(numbers, beg, end, mid);
}

void merge(vector<int>& numbers, int beg, int end, int mid)
{
    int leftSize = mid - beg + 1;
    int rightSize = end - mid;
    vector<int> leftNums;
    vector<int> rightNums;
    for(int i = 0; i < leftSize; i++)
    {
        leftNums.push_back(numbers.at(beg + i));
    }
    for(int i = 0; i < rightSize; i++)
    {
        rightNums.push_back(numbers.at(mid + i + 1));
    }

    // cout << "DEBUG: leftNums.size(): " << leftNums.size() << endl;
    // cout << "DEBUG: rightNums.size(): " << rightNums.size() << endl;
    int i, j, k;
    i = 0;
    j = 0;
    k = beg;
    while(i < leftSize && j < rightSize)
    {
        if(leftNums.at(i) <= rightNums.at(j))
        {
            numbers.at(k) = leftNums.at(i);
            i++;
        }
        else
        {
            numbers.at(k) = rightNums.at(j);
            j++;
        }
        k++;
    }
    // cout << "DEBUG: k: " << k << endl;
    // cout << "DEBUG: i: " << i << endl;
    // cout << "DEBUG: j: " << j << endl;
    // cout << "DEBUG: leftSize: " << leftSize << endl;
    // cout << "leftNums.at(i): " << leftNums.at(i) << endl;
    // cout << "DEBUG: rightSize: " << rightSize << endl;
    while(i < leftSize)
    {
        numbers.at(k) = leftNums.at(i);
        i++;
        k++;
    }
    while(j < rightSize)
    {
        numbers.at(k) = rightNums.at(j);
        j++;
        k++;
    }
}

void bubbleSort(vector<int>& uns_arr)
{
    for(int i = 0; i < uns_arr.size(); i++)
    {
        for(int j = 0; j < uns_arr.size()-i-1; j++)
        {
            if(uns_arr.at(j) > uns_arr.at(j+1))
            {
                swap(uns_arr.at(j), uns_arr.at(j+1));
            }
        }
    }
}

void buildArray(vector<int>& numbers)
{
    srand(time(0));
    for(int i = 0; i < 10; i++)
    {
        numbers.push_back(rand());
    }
}