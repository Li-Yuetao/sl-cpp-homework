/* 
    功能： 加密系统
    使用方式：
        encrypt 码本文件名 输入文件名 输出文件名
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

// 创建码本映射
bool createCodebookMap(const std::string &codebook_file_path)
{
    // 创建一个包含 256 个数字的数组，按顺序初始化
    std::vector<int> codebook(256);
    for (int i = 0; i < 256; ++i) {
        codebook[i] = i;
    }

    // 使用随机数生成器打乱顺序
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(codebook.begin(), codebook.end(), gen);

    // 打开文件以写入码本
    std::ofstream codebookFile(codebook_file_path);
    if (!codebookFile.is_open()) {
        std::cerr << "Error: Cannot open codebook file for writing." << std::endl;
        return false;
    }

    // 将打乱顺序后的码本写入文件
    for (int i = 0; i < 256; ++i) {
        codebookFile << codebook[i];
        if (i < 255) {
            codebookFile << " ";
        }
    }
    codebookFile.close();   
    return true;
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
        input_file_name = "test";
        output_file_name = "test_encrypted";
        // return -1;
    }
    else if (argc == 4)
    {
        codebook_file_name = argv[1]; // "codebook.txt"
        input_file_name = argv[2]; // "input.txt"
        output_file_name = argv[3]; // "encrypted.txt"
    }

    std::string data_path = "/home/lyt/WorkSpace/sl_homework/cpp_homework/homework_3/data/";
    std::ifstream fin(data_path + input_file_name, std::ios::binary);
    std::ofstream fout(data_path + output_file_name, std::ios::binary);
    std::string codebook_file_path = data_path + codebook_file_name;
    bool update_codebook = false;
    if (update_codebook)
    {
        if(!createCodebookMap(codebook_file_path)) return -1;
    }
    std::ifstream codebook_fin(codebook_file_path);

    if (!fout.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    std::string line;
    std::string result;
    std::vector<int> encrypt_num;
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
    // std::cout << std::endl;

    char byte;
    while (fin.get(byte)) {
        // std::cout << "byte: " << static_cast<int>(byte) << std::endl;
        // std::cout << "line: " << std::stoi(line) << std::endl;
        encrypt_num.push_back(codebook_map[static_cast<unsigned char>(byte)]);
        if(fin.eof()) break;
    }    
    std::cout << "encrypt_num.size(): " << encrypt_num.size() << std::endl;

    // 输出加密后的结果
    for (int i = 0; i < encrypt_num.size(); i++)
    {
        fout << encrypt_num[i];
        if (i < encrypt_num.size() - 1)
            fout << " ";
    }

    // // 读取fin文件的内容，也是一段字符串的读取
    // while(fin >> line)
    // {
    //     // std::cout << "fin.rdstate(): " << fin.rdstate() << std::endl;
    //     std::cout << line << ' ';
    //     encrypt_num.push_back(codebook_map[std::stoi(line)]);
    //     if(fin.eof()) break;
    // }
    // std::cout << "v_num.size(): " << encrypt_num.size() << std::endl;

    // // 输出加密后的结果
    // for (int i = 0; i < encrypt_num.size(); i++)
    // {
    //     fout << encrypt_num[i];
    //     if (i < encrypt_num.size() - 1)
    //         fout << " ";
    // }

    
    return 0;
}
