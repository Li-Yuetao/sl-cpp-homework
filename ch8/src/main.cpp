#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::ifstream in("../cpp_homework/ch8/data/test.txt");
    std::ofstream out("../cpp_homework/ch8/data/test_out.txt");
    std::string str;
    while (std::getline(in, str))
    {
        std::cout << str << std::endl;
        out << str << std::endl;
    }
    in.close();
    out.close();
    return 0;
}