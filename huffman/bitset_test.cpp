#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main(int argc, char* argv[])
{
    std::bitset<16> foo;
    std::bitset<16> bar (0xfa2);
    std::bitset<16> baz (std::string("0101111001"));

    bitset<8> test(string("01101010"));

    std::cout << "foo: " << foo << '\n';
    std::cout << "bar: " << bar << '\n';
    std::cout << "baz: " << baz << '\n';
    cout << "test: " << (char)test.to_ulong() << endl;
    return 0;
}