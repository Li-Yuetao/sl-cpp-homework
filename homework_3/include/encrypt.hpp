#pragma once

#include <iostream>
#include <string>
#include <map>

#include "codebook.hpp"

// 加密函数
void encrypt_letter(std::map<char, char>& codebook_map_letter, std::ifstream &fin, std::ofstream &fout)
{
    std::string line;
    std::getline(fin, line);
    std::string result = line;
    for (char& c : result)
    {
        if (std::isalpha(c))
        {
            char encryptedChar = codebook_map_letter.at(std::tolower(c));
            // 判断原始字符是否为大写，如果是，将加密后的字符也转换为大写
            if (std::isupper(c))
                encryptedChar = std::toupper(encryptedChar);
            c = encryptedChar;
        }
    }
    // 加密后的结果
    std::cout << "原始数据：" << line << std::endl;
    std::cout << "加密后的结果：" << result << std::endl;
    fout << result;
}

void encrypt_number(std::map<int, int>& codebook_map_number, std::ifstream &fin, std::ofstream &fout)
{
    std::vector<int> encrypt_num;
    std::string line;
    // 读取fin文件的内容，也是一段字符串的读取
    std::cout << "原始数据：";
    while(fin >> line)
    {
        // std::cout << "fin.rdstate(): " << fin.rdstate() << std::endl;
        std::cout << line << ' ';
        // 检查line是否为数字
        for (char& c : line)
        {
            if (!std::isdigit(c))
            {
                std::cout << std::endl;
                std::cerr << "输入文件中包含非数字字符，请修改input.txt文件" << std::endl;
                return;
            }
            // 检查数字是否在0~255之间
            if (std::stoi(line) < 0 || std::stoi(line) > 255)
            {
                std::cout << std::endl;
                std::cerr << "输入文件中包含不在0~255之间的数字，请修改input.txt文件" << std::endl;
                return;
            }
        }
        encrypt_num.push_back(codebook_map_number[std::stoi(line)]);
        if(fin.eof()) break;
    }
    std::cout << std::endl;
    // std::cout << "v_num.size(): " << encrypt_num.size() << std::endl;

    // 加密后的结果
    std::cout << "加密后的结果：";
    for (int i = 0; i < encrypt_num.size(); i++)
    {
        std::cout << encrypt_num[i] << " ";
        fout << encrypt_num[i];
        if (i < encrypt_num.size() - 1)
            fout << " ";
    }
    std::cout << std::endl;
}

