/* 
    功能： 解密系统
    使用方式：
        decrypt 码本文件名 输入文件名 输出文件名
 */

#include "../include/decrypt.h"
#include <iostream>

// 判断码本类型
int judgeCodebookType(std::string line)
{
    int encrypt_type = 0;
    // std::cout << "line.size(): " << line.size() << std::endl;
    if (line.size() == 26)
    {
        encrypt_type = 1;
    }
    else
    {
        encrypt_type = 2;
    }
    return encrypt_type;
}

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
        input_file_name = "encrypted.txt";
        output_file_name = "decrypted.txt";
        // return -1;
    }
    else if (argc == 4)
    {
        codebook_file_name = argv[1]; // "codebook.txt"
        input_file_name = argv[2]; // "input.txt"
        output_file_name = argv[3]; // "output.txt"
    }
    std::string data_path = "../data/";

    std::ifstream fin(data_path + input_file_name);
    std::ofstream fout(data_path + output_file_name);
    std::ifstream codebook_fin(data_path + codebook_file_name);

    if (!fout.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }
    std::string line;
    std::string result;

    // 判断码本类型
    std::getline(codebook_fin, line);
    int encrypt_type = judgeCodebookType(line);

    std::map<char, char> codebook_map_letter;
    std::map<int, int> codebook_map_number;

    codebook_fin.clear(); // 这里需要清除一下状态，使得文件指针回到文件头
    codebook_fin.seekg(0, std::ios::beg);
    if (encrypt_type == 1)
    {
        std::cout << "解密字符串" << std::endl;
        codebook_map_letter = createCodebookMap_letter(codebook_fin);
        // showCodebookMap(codebook_map_letter);
        decrypt_letter(codebook_map_letter, fin, fout);
    }
    else if (encrypt_type == 2)
    {
        std::cout << "解密数字" << std::endl;
        codebook_map_number = createCodebookMap_number(codebook_fin);
        // showCodebookMap(codebook_map_number);
        decrypt_number(codebook_map_number, fin, fout);
    }




    return 0;
}
