/* 
    功能： 解密系统
    使用方式：
        decrypt 码本文件名 输入文件名 输出文件名
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <random>

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
        input_file_name = "test_encrypted";
        output_file_name = "test_decrypted";
        // return -1;
    }
    else if (argc == 4)
    {
        codebook_file_name = argv[1]; // "codebook.txt"
        input_file_name = argv[2]; // "input.txt"
        output_file_name = argv[3]; // "output.txt"
    }
    std::string data_path = "../data/";

    std::ifstream fin(data_path + input_file_name, std::ios::binary);
    std::ofstream fout(data_path + output_file_name, std::ios::binary);
    std::ifstream codebook_fin(data_path + codebook_file_name);

    if (!fout.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }
    std::string line;
    std::string result;
    std::vector<unsigned char> decrypt_num;
    std::map<unsigned char,int> codebook_map;
    // std::getline(codebook_fin,line)这个是直接获取一行，不会因为空格而分割
    unsigned char i = 0;
    while(codebook_fin >> line)
    {
        // 输出流的状态
        // std::cout << "codebook_fin.rdstate(): " << codebook_fin.rdstate() << std::endl;
        // std::cout << line << ' ';
        codebook_map.insert(std::pair<unsigned char, int>(i, std::stoi(line)));
        if (codebook_fin.eof()) break;// 判断是否到达文件末尾
        i++;
    }
    std::cout << "codebook_map.size(): " << codebook_map.size() << std::endl;

    // 将codebook_map中的key和value互换
    std::map<int, unsigned char> reverse_map;
    for (auto it = codebook_map.begin(); it != codebook_map.end(); it++) {
        reverse_map[it->second] = it->first;
    }
    
    while (fin >> line) {
        // 输出前20个加密后的数字
        // if (decrypt_num.size() < 20) std::cout << "static_cast<int>(byte): " << std::stoi(line) << std::endl;
        int encrypted_value = std::stoi(line);
        auto it = reverse_map.find(encrypted_value);
        if (it != reverse_map.end()) {
            decrypt_num.push_back(it->second);
        }
        if (fin.eof()) break;
    }
    std::cout << "decrypt_num.size(): " << decrypt_num.size() << std::endl;

    // 输出解密后的前20个结果
    // for (int i = 0; i < 20; i++)
    // {
    //     std::cout << decrypt_num[i] << ' ';
    // }
    // std::cout << std::endl;

    // 输出解密后的结果
    for (int i = 0; i < decrypt_num.size(); i++)
    {
        fout << static_cast<char>(decrypt_num[i]);
    }

    std::cout << "解密完成！可执行文件已经存放于" << output_file_name << "中" << std::endl;
    
    return 0;
}
