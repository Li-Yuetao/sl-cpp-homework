#include <iostream>
#include <vector>
#include <algorithm>

int inc(int x)
{
    return x + 1;
}

int dec(int x)
{
    return x - 1;
}

auto fun(bool input)
{
    if (input)
        return inc;
    else
        return dec;
}

int main(int argc, char* argv[])
{
    std::cout << (*fun(true))(100) << std::endl;
    

}

