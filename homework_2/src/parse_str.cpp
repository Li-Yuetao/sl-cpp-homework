#include "../include/parse_str.h"

// 检查字符是否在指定进制的有效范围内
bool ParseStr::isValidDigit(char c, int base) {
    if (base <= 10) {
        return (c >= '0' && c < '0' + base);
    } else {
        return ((c >= '0' && c <= '9') || (c >= 'A' && c < 'A' + base - 10) || (c >= 'a' && c < 'a' + base - 10));
    }
}

// 检查字符串是否在指定进制下合法
bool ParseStr::isValidNumber(const std::string& str, int base) {
    for (char c : str) {
        if (!isValidDigit(c, base)) {
            return false;
        }
    }
    return true;
}

std::string ParseStr::parse_num_str(const std::string& num_str,const int& base)
{
    std::string num_str_parsed;
    if (num_str[0] == '+')
    {
        num_str_parsed = num_str.substr(1);
        remove_leading_zeros(num_str_parsed);
        if(!isValidNumber(num_str_parsed,base)) return "";
    }
    else if (num_str[0] == '-')
    {
        num_str_parsed = num_str.substr(1);
        remove_leading_zeros(num_str_parsed);
        if(!isValidNumber(num_str_parsed,base)) return "";// 这个需要在加上负号前检查，针对"-123"这种情况
        num_str_parsed.insert(num_str_parsed.begin(), '-');
    }
    else
    {
        num_str_parsed = num_str;
        remove_leading_zeros(num_str_parsed);
        if(!isValidNumber(num_str_parsed,base)) return "";
    }
    return num_str_parsed;
}

void ParseStr::remove_leading_zeros(std::string& num_str)
{
    int i = 0;
    int num_zeros = 0;
    
    while (num_str[i] == '0')
    {
        ++i;
        ++num_zeros;
    }
    
    if (num_zeros > 1) {
        num_str = num_str.substr(i);
        if (num_str.empty()) num_str = "0";
    }
}

/**
 * @brief 检查文件中两行数字是否合法
 * @return 0: 两行数字合法
 *         1: 两行数字不合法
 */
int ParseStr::check_num_lines(std::vector<std::string>& num_lines, const int& base)
{
    int flag = 1;
    bool is_valid = false;
    for(auto& line : num_lines)
    {
        std::cout << "Parse the number : " << line << " -> ";
        line = ParseStr::parse_num_str(line, base);
        if (line.empty())
        {
            std::cout << "第"<< flag << "个数字无效" << std::endl;
            is_valid = true;
            ++flag;
            continue;
        }
        std::cout << line << std::endl;
        ++flag;
    }
    if (is_valid)
    {
        return ParseStr::INVALID_NUM;
    }
    return ParseStr::CORRECT_NUM; 
}