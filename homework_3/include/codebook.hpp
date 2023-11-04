#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include <random>
#include <fstream>

void generate_code_book(const std::string &codebook_file_path)
{
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(alphabet.begin(), alphabet.end(), g);

    std::cout << alphabet << std::endl;

    std::ofstream fout(codebook_file_path);
    fout << alphabet;
}

// 创建码本映射
std::map<char, char> createCodebookMap(std::ifstream& codebook_fin)
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

// 显示码本映射表
void showCodebookMap(std::map<char, char>& keyMap)
{
    std::cout << "码本映射表：\n";
    for (std::map<char, char>::iterator iter = keyMap.begin(); iter != keyMap.end(); iter++)
    {
        std::cout << iter->first << " -> " << iter->second << std::endl;
    }
}