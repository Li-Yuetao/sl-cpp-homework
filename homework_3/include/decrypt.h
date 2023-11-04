#pragma once

#include "codebook.hpp"

// 解密函数
std::string decrypt(const std::string& text, std::map<char,char> keyMap)
{
    std::string text_tmp = text;
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
            for (std::map<char, char>::iterator iter = keyMap.begin(); iter != keyMap.end(); iter++)
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
    return text_tmp;
}