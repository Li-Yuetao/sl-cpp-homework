#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

#include "../include/tic_toc.h"

bool check_user_input(std::string input)
{
    for (char c : input) {
        if (!std::isdigit(c) && c != '.' && c != '-')
            return false;
    }
    return true;
}

int main()
{
    srand(time(0));// seed for random number generator
    float my_answer = 0,correct_answer = 0,total_time = 0;
    int score = 0,num_questions = 10,q_level = 1,range = 10;
    char operators[] = {'+', '-', '*', '/'};
    std::cout << "#####数学运算练习题#####" << std::endl;

    // 题目设置
    std::cout << "设置题目数量:";
    std::cin >> num_questions;

    std::cout << "设置运算的大小范围:";
    while (true)
    {
        std::cin >> range;
        if (range <= 0)
        {
            std::cout << "范围不能小于0,请重新输入" << std::endl;
            continue;
        }
        break;
    }

    std::cout << "设置题目难度运(1-加减,2-加减乘除):";
    std::cin >> q_level;
    if (q_level == 1)
    {
        std::cout << "好的," << num_questions <<"道1~" << range << "之间的加减运算练习题" << std::endl;
    }
    else if (q_level == 2)
    {
        std::cout << "好的," << num_questions <<"道1~" << range << "之间的加减乘除运算练习题(除法只需精确到.2f即可)" << std::endl;
    }
    else
    {
        q_level = 1;
        std::cout << "无效的难度设置,默认为加减运算练习题" << std::endl;
    }
    
    std::cout << "让我们开始吧！" << std::endl;
    TicToc timer;
    // double time_used[num_questions];
    std::vector<double> time_used(num_questions);
    std::vector<std::string> wrong_answer_notes;// 错题集
    // 开始答题
    for (int i = 0; i < num_questions; i++)
    {
        int x = rand() % range + 1;
        int y = rand() % range + 1;
        char current_operator;
        if (q_level == 1)
        {
            current_operator = operators[rand() % 2];
        }else if (q_level == 2)
        {
            current_operator = operators[rand() % 4];
        }
        std::cout << x << current_operator << y  << "= ";
        timer.tic();
        // std::cin >> my_answer;
        std::string user_input;
        std::cin >> user_input;
        if(!check_user_input(user_input))
        {
            std::cout << "无效答案，请重新输入:";
            std::cin >> user_input;
        }
        my_answer = std::stof(user_input);

        switch (current_operator)
        {
        case '+':
            correct_answer = x + y;
            break;
        case '-':
            correct_answer = x - y;
            break;
        case '*':
            correct_answer = x * y;
            break;
        case '/':
            correct_answer = std::round(x / float(y) * 100) / 100;// 四舍五入保留两位小数
            break;
        default:
            std::cout << "Invalid operator." << std::endl;

            break;
        }
        time_used[i] = timer.toc() / 1000;
        // std::cout << "Once time used: " << time_used[i] << " s" << std::endl;
        if(my_answer == correct_answer)
        {
            std::cout << "Correct!" << std::endl;
            score++;
        }
        else
        {
            std::cout << "Incorrect!" << std::endl;
            std::string wrong_note = std::to_string(x) + " " + current_operator + " " + std::to_string(y) + " = " + std::to_string(correct_answer);
            // std::cout << "wrong_note:" << wrong_note << std::endl;
            wrong_answer_notes.push_back(wrong_note);
        }
    }
    std::cout << "*****答题结束*****" << std::endl;
    double min_time = time_used[0];
    for(auto& t : time_used)
    {
        total_time += t;
        min_time = std::min(min_time,t);
    }
    std::cout << "平均答题时间: " << total_time / num_questions << " s" << std::endl;
    std::cout << "最短用时: " << min_time << " s" << std::endl;
    std::cout << "您的得分为 " << score << " 分(满分为 " << num_questions << " 分)" << std::endl;
    if (score != num_questions)
    {
        std::cout << "一共错 "<< num_questions-score << " 道题，正确答案如下:" << std::endl;
        for (int i = 0; i < wrong_answer_notes.size(); i++)
        {
            std::cout << wrong_answer_notes[i] << std::endl;
        }
    }
    
    return 0;
}
