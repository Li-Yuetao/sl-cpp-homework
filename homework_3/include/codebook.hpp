#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include <random>
#include <fstream>
#include <vector>
#include <sstream>

bool generate_code_book(const std::string &codebook_file_path, int encrypt_type)
{
    // 打开文件以写入码本
    std::ofstream codebookFile(codebook_file_path);
    if (!codebookFile.is_open()) {
        std::cerr << "Error: Cannot open codebook file for writing." << std::endl;
        return false;
    }
    // 使用随机数生成器打乱顺序
    std::random_device rd;
    std::mt19937 gen(rd());
    if (encrypt_type == 1)
    {
        // 生成字符串码本
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

        std::shuffle(alphabet.begin(), alphabet.end(), gen);

        std::cout << "字符串码本: " << alphabet << std::endl;
        codebookFile << alphabet;
    }
    else if (encrypt_type == 2)
    {
        // 创建一个包含 256 个数字的数组，按顺序初始化
        std::vector<int> codebook(256);
        for (int i = 0; i < 256; ++i) {
            codebook[i] = i;
        }

        std::shuffle(codebook.begin(), codebook.end(), gen);

        // 将打乱顺序后的码本写入文件
        for (int i = 0; i < 256; ++i) {
            codebookFile << codebook[i];
            if (i < 255) {
                codebookFile << " ";
            }
        }
        codebookFile.close(); 
    }
    return true;
}

// 创建码本映射
std::map<char, char> createCodebookMap_letter(std::ifstream& codebook_fin)
{
    char c;
    std::map<char, char> codebook_map;// 码本映射表
    // 按一个字符的读取codebook_file_name，初始化codebook_map
    for (int i = 0; i < 26; i++)
    {
        codebook_fin.get(c);
        codebook_map.insert(std::pair<char, char>('a' + i, c));
    }
    return codebook_map;
}

// 创建码本映射
std::map<int,int> createCodebookMap_number(std::ifstream& codebook_fin)
{
    std::map<int,int> codebook_map;
    // std::getline(codebook_fin,line)这个是直接获取一行，不会因为空格而分割
    int i = 0;
    std::string line;
    while(codebook_fin >> line)
    {
        // 输出流的状态
        // std::cout << "codebook_fin.rdstate(): " << codebook_fin.rdstate() << std::endl;
        // std::cout << line << ' ';
        codebook_map.insert(std::pair<int, int>(i, std::stoi(line)));
        if (codebook_fin.eof()) break;// 判断是否到达文件末尾
        i++;
    }
    return codebook_map;
}

// 显示码本映射表
void showCodebookMap(std::map<char, char>& keyMap)
{
    std::cout << "码本映射表：\n";
    for (std::map<char, char>::iterator iter = keyMap.begin(); iter != keyMap.end(); iter++)
    {
        std::cout << iter->first << " -> " << iter->second << std::endl;
    }
}
// 显示码本映射表
void showCodebookMap(std::map<int, int>& keyMap)
{
    std::cout << "码本映射表：\n";
    for (std::map<int, int>::iterator iter = keyMap.begin(); iter != keyMap.end(); iter++)
    {
        std::cout << iter->first << " -> " << iter->second << std::endl;
    }
}