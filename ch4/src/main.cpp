#include <iostream>
#include <string>


int main()
{
    std::string str = "Hello, world!";
    const char *ptr = str.c_str();
    std::cout << ptr << std::endl;
    return 0;
}
