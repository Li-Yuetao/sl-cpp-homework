/* 
    功能： 读取文件中的两行长数字，计算两个数字的和
    Input： 文件名
    Output： 两个数字的和
    注意：
        需要检查文件是否合法，文件中是否含有两行数字，数字是否合法
        处理不合法的数字
 */

#include <iostream>
#include <fstream> // 文件读写
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

#include "../include/parse_str.h"
#include "../include/tic_toc.h"

// 将字符转换为对应的整数值
int charToInt(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    } else {
        // 非法字符
        return -1;
    }
}

// 将字符串表示的数字按指定进制转换为十进制
long convertToDecimal(const std::string& numStr, int base) {
    long decimalValue = 0;
    int exponent = 0;
    int startIndex = 0;

    // 检查是否有负号
    if (numStr[0] == '-') {
        startIndex = 1;
    }
    
    for (int i = numStr.length() - 1; i >= startIndex; --i) {
        int digitValue = charToInt(numStr[i]);
        if (digitValue == -1 || digitValue >= base) {
            std::cerr << "Error: Invalid digit in input number." << std::endl;
            exit(1);
        }
        decimalValue += digitValue * pow(base, exponent);
        ++exponent;
    }

    // 处理负号
    if (startIndex == 1) decimalValue = -decimalValue;

    // 进制转换结果
    std::cout << base << "->10进制: " << numStr << " -> "<< decimalValue << std::endl;
    return decimalValue;
}

// 函数用于将十进制数字转换为指定进制的字符串
std::string convertToBase(int decimalValue, int base) {
    if (decimalValue == 0) {
        return "0";
    }
    bool isNegative = (decimalValue < 0);
    decimalValue = abs(decimalValue);
    
    std::string result = "";
    while (decimalValue > 0) {
        int remainder = decimalValue % base;
        char digit;
        if (remainder < 10) {
            digit = '0' + remainder;
        } else {
            digit = 'a' + remainder - 10;
        }
        result = digit + result;
        decimalValue /= base;
    }
    if (isNegative) {
        result.insert(result.begin(), '-');
    }
    return result;
}

int main(int argc, char* argv[])
{
    std::cout << "********长整数加法运算********" << std::endl;
    int input_base = 10,out_base = 10; // 默认输入输出十进制
    // 检查是否输入了文件名
    if (argc < 2)
    {
        std::cout << "Please input file name" << std::endl;
        return -1;
    }else if (argc == 2){
        std::cout << "采用默认输入输出十进制" << std::endl;
    }
    else if (argc == 3)
    {
        input_base = atoi(argv[2]);
        out_base = atoi(argv[2]);// 输出进制默认与输入进制相同
    }else if (argc == 4)
    {
        input_base = atoi(argv[2]);
        out_base = atoi(argv[3]);
    }
    std::string file_name = argv[1];

    std::cout << "输入进制：" << input_base << " 输出进制：" << out_base << std::endl;

    if (input_base < 2 || input_base > 36 || out_base < 2 || out_base > 36)
    {
        std::cout << "进制输入错误，请输入2-36之间的进制" << std::endl;
        return -1;
    }

    // 读取文件中的两行数字
    std::vector<std::string> num_lines;
    std::string line;
    std::ifstream file(file_name);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            num_lines.push_back(line);
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
        return 0;
    }
    // 检查文件中是否含有两行
    if (num_lines.size() != 2)
    {
        std::cout << "文件中不含有两行数字，请检查文件" << std::endl;
        return -1;
    }

    // 检查文件中两行数字是否合法
    std::cout << "********解析文件中两行数字********" << std::endl;
    switch (ParseStr::check_num_lines(num_lines, input_base))
    {
    case ParseStr::INVALID_NUM:
        std::cout << "文件中含有非法数字，请检查文件" << std::endl;
        return -1;
    }
    std::vector<long> nums_decimal;
    if(input_base != 10)
    {
        std::cout << "********将" << input_base << "进制转换为10进制********" << std::endl;
        TicToc tic_toc;
        for (auto& line : num_lines)
        {
            nums_decimal.emplace_back(convertToDecimal(line, input_base));
        }
    }else 
    {
        for (auto& line : num_lines)
        {
            nums_decimal.emplace_back(atol(line.c_str()));
        }
    }
    // TODO 判断是否数字溢出
    std::cout << "********在10进制下进行加法运算********" << std::endl;
    std::cout << "num1 = " << nums_decimal[0] << std::endl;
    std::cout << "num2 = " << nums_decimal[1] << std::endl;
    long sum_in_decimal = nums_decimal[0] + nums_decimal[1];
    std::cout << "num1 + num2 = " << sum_in_decimal << std::endl;
    std::string sum_in_base;
    if(out_base != 10)
    {
        sum_in_base = convertToBase(sum_in_decimal, out_base);
    }else
    {
        sum_in_base = std::to_string(sum_in_decimal);
    }
    std::cout << "********以" << out_base << "进制输出结果********" << std::endl;
    std::cout << " num_str = " << sum_in_base << std::endl;
}