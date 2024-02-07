cmake_minimum_required(VERSION 3.15)

# # 规定c++版本
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# # 添加版本号
# project(Tutorial VERSION 1.0)

# # 复制输入文件并替换指定的CMAKE变量：
# configure_file(TutorialConfig.h.in TutorialConfig.h)

# # 指定可执行目标应在何处查找包含文件
# target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")

# #  添加库

project(demo1)

aux_source_directory(. DIR_SRCS)




add_executable(demo )