#include <iostream>

using namespace std;

long fib(int n)
{
    int nums[2] = {0, 1};
    for(int i = 2; i < n; i++)
    {
        int sum = nums[0] + nums[1];
        nums[0] = nums[1];
        nums[1] = sum;
    }
    return nums[1];

}

int main(int argc, char* argv[])
{
    int num = 14;

    cout << fib(num) << endl;

    return 0;
}