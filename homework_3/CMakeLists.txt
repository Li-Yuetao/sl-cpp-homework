cmake_minimum_required(VERSION 3.15)
project(homework_3)

set(CMAKE_CXX_STANDARD 17)

# 用于加密解密文本文件
add_executable(encrypt src/encrypt.cpp)
add_executable(decrypt src/decrypt.cpp)
# 用于加密解密可执行文件
add_executable(encrypt_exefile src/encrypt_exefile.cpp)
add_executable(decrypt_exefile src/decrypt_exefile.cpp)