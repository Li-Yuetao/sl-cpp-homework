#pragma once

#include <iostream>
#include <string>
#include <map>

#include "codebook.hpp"

// 加密函数
std::string encrypt(const std::string& text, const std::map<char, char>& keyMap)
{
    std::string text_tmp = text;
    for (char& c : text_tmp)
    {
        if (std::isalpha(c))
        {
            char encryptedChar = keyMap.at(std::tolower(c));
            // 判断原始字符是否为大写，如果是，将加密后的字符也转换为大写
            if (std::isupper(c))
                encryptedChar = std::toupper(encryptedChar);
            c = encryptedChar;
        }
    }
    return text_tmp;
}

