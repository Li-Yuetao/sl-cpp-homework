#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace ParseStr
{
    enum ERROR_NUM_FLAG { CORRECT_NUM = 0, INVALID_NUM }; 
    // 检查数字在指定进制下是否合法
    bool isValidNumber(const std::string& str, int base);
    bool isValidDigit(char c, int base);
    // 解析数字字符串，将"+123"转换为"123"，"-0123"转换为"-123"
    std::string parse_num_str(const std::string& num_str,const int& base);
    // 将"000123"转换为"123"
    void remove_leading_zeros(std::string& num_str);
    // 检查文件中两行数字是否合法
    int check_num_lines(std::vector<std::string>& num_lines, const int& base);
}

