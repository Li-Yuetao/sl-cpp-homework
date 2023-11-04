/* 
    功能： 加密系统
    使用方式：
        encrypt 码本文件名 输入文件名 输出文件名
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "../include/encrypt.hpp"

int main(int argc, char *argv[])
{
    
    std::string codebook_file_name;
    std::string input_file_name;
    std::string output_file_name;
    // 检查是否输入了文件名
    if (argc != 4)
    {
        // std::cout << "Please input 3 file names:\t码本文件名 输入文件名 输出文件名\n" << std::endl;
        codebook_file_name = "codebook.txt";
        input_file_name = "input.txt";
        output_file_name = "encrypted.txt";
        // return -1;
    }
    else if (argc == 4)
    {
        codebook_file_name = argv[1]; // "codebook.txt"
        input_file_name = argv[2]; // "input.txt"
        output_file_name = argv[3]; // "encrypted.txt"
    }

    std::string data_path = "/home/lyt/WorkSpace/sl_homework/cpp_homework/homework_3/data/";
    std::ifstream fin(data_path + input_file_name);
    std::ofstream fout(data_path + output_file_name);
    std::string codebook_file_path = data_path + codebook_file_name;
    // 是否更新码本
    bool update_codebook = true;
    if (update_codebook) generate_code_book(codebook_file_path);
    std::ifstream codebook_fin(codebook_file_path);

    if (!fout.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    std::string line;
    std::string result;

    std::map<char, char> codebook_map = createCodebookMap(codebook_fin);
    // showCodebookMap(codebook_map);
    std::getline(fin, line);
    result = encrypt(line,codebook_map);
        
    // 加密后的结果
    std::cout << "原始数据：" << line << std::endl;
    std::cout << "加密后的结果：" << result << std::endl;

    fout << result;

    fout.close();
    
    return 0;
}
