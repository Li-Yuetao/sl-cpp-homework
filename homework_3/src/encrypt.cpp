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

    std::string data_path = "../data/";
    std::ifstream fin(data_path + input_file_name);
    std::ofstream fout(data_path + output_file_name);
    std::string codebook_file_path = data_path + codebook_file_name;
    // 询问选择哪种加密方式（1-字符串 2-数字）
    int encrypt_type = 0, update_codebook = 2;
    while(true)
    {
        std::cout << "请选择加密方式(1-字符串 2-数字):";
        std::cin >> encrypt_type;
        if(encrypt_type == 1 || encrypt_type == 2) break;
    }
    // 是否更新码本
    while(true)
    {
        std::cout << "是否更新码本(1-是 0-否):";
        std::cin >> update_codebook;
        if(update_codebook == 1 || update_codebook == 0) break;
    }

    if (update_codebook) generate_code_book(codebook_file_path, encrypt_type); // 根据加密方式生成码本
    std::ifstream codebook_fin(codebook_file_path);

    // 判断文件是否打开成功
    if (!codebook_fin.is_open()) {
        std::cerr << "无法打开码本文件" << std::endl;
        return 1;
    }else if (!fin.is_open()) {
        std::cerr << "无法打开输入文件" << std::endl;
        return 1;
    }else if (!fout.is_open()) {
        std::cerr << "无法打开输出文件" << std::endl;
        return 1;
    }

    std::string line;


    std::map<char, char> codebook_map_letter;
    std::map<int, int> codebook_map_number;
    
    if (encrypt_type == 1)
    {
        std::cout << "字符串加密" << std::endl;
        codebook_map_letter = createCodebookMap_letter(codebook_fin);
        // showCodebookMap(codebook_map_letter);
        encrypt_letter(codebook_map_letter, fin, fout);
    }else if (encrypt_type == 2)
    {
        std::cout << "数字加密" << std::endl;
        codebook_map_number = createCodebookMap_number(codebook_fin);
        // showCodebookMap(codebook_map_number);
        encrypt_number(codebook_map_number, fin, fout);
    }

    // close files
    fin.close();
    fout.close();
    return 0;
}
