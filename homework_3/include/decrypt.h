#pragma once

#include "codebook.hpp"

// 解密函数
bool decrypt_letter(std::map<char, char>& codebook_map_letter, std::ifstream &fin, std::ofstream &fout)
{
    std::string line;
    std::getline(fin, line);
    std::string text_tmp = line;

    for (char& c : text_tmp)
    {
        if (std::isalpha(c))
        {
            char tmp_c = c;
            if (std::isupper(c))
            {
                // std::cout << c << " is upper" << std::endl;
                tmp_c = std::tolower(c);
            }
            // 遍历码本映射表，对比c与value，找到对应的key
            for (std::map<char, char>::iterator iter = codebook_map_letter.begin(); iter != codebook_map_letter.end(); iter++)
            {
                if (iter->second == tmp_c)
                {
                    tmp_c = iter->first;
                    break;
                }
            }
            // 判断原始字符是否为大写，如果是，将加密后的字符也转换为大写
            if (std::isupper(c))
                tmp_c = std::toupper(tmp_c);
            c = tmp_c;
        }
    }
    std::cout << "解密前的数据：" << line << std::endl; // "hello world
    std::cout << "解密后的结果：" << text_tmp << std::endl;
    fout << text_tmp;
    return true;
}

bool decrypt_number(std::map<int, int>& codebook_map_number, std::ifstream &fin, std::ofstream &fout)
{
    // 将codebook_map中的key和value互换
    std::map<int, int> reverse_map;
    std::vector<int> decrypt_num;
    for (auto it = codebook_map_number.begin(); it != codebook_map_number.end(); it++) {
        reverse_map[it->second] = it->first;
    }

    std::string line;
    std::cout << "解密前的数据：";
    while (fin >> line) {
        std::cout << std::stoi(line) << " ";
        decrypt_num.push_back(reverse_map[std::stoi(line)]);
        if(fin.eof()) break;
    }
    std::cout << std::endl;
    // std::cout << "decrypt_num.size(): " << decrypt_num.size() << std::endl;
    // 输出解密后的数据
    std::cout << "解密后的结果：";
    for (int i = 0; i < decrypt_num.size(); i++) {
        std::cout << decrypt_num[i] << " ";
        fout << decrypt_num[i];
        if (i < decrypt_num.size() - 1)
            fout << " ";
    }
    std::cout << std::endl;
    return true;
}