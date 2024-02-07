# CMake

## 一、开始运行

### 1、构建一个简单的可执行程序

```makefile
# cmake的最低版本
cmake_minimum_required(version 3.15)

# 生成的项目名
project(Tua)
${PROJECT_NAME} #后续出现的可以用这个替代

# add the executable
add_executable(Tua Tua.cpp)
```

tutorial.cpp

```c
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char*argv[]){
    if(argc < 2){
        cout<<"usage: "<<argv[0]<<endl;
        return 1;
    }

    const double inputValue = atof(argv[1]);

    const double outputValue = sqrt(inputValue);

    cout<<"thr qeuart root of "<<inputValue<<
    " is " << outputValue<<endl;
    return 0;
}
```



### 2、规定cxx的版本

```makefile
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
```



### 3、项目的版本号（动态更新）

```makefile
# 添加版本号
project(Tutorial VERSION 1.0)

# 复制输入文件并替换指定的CMAKE变量：
configure_file(TutorialConfig.h.in TutorialConfig.h)

# 指定可执行目标应在何处查找包含文件
target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")

```



Tutorial.h.in

```makefile
// 配置的输入文件
#define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
#define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
```





### 4、对目录进行操作

```makefile
# 查找目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
```





## 二、添加库

### 1、添加子目录

```makefile
add_subdirectory(math)
```



### 2、生成静态库

```makefile
# 指定生成 MathFunctions 链接库
# 在math目录下生成
add_library (MathFunctions ${DIR_LIB_SRCS})
```



### 3、添加链接库

```makefile
#					项目名	 库名
target_link_libraries(Demo MathFunctions)
```



### 4、选择是否添加库

```makefile
# 是否使用自己的 MathFunctions 库
option (USE_MYMATH
	   "Use provided math implementation" ON)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# 是否加入 MathFunctions 库
if(USE_MYMATH)
    # 将math添加到include路径中
    # 这样cmake在编译过程中就能直接找到math中的头文件
    # 编写main的时候就不需要include相对路径了
    include_directories("${PROJECT_SOURCE_DIR}/math")
    add_subdirectory(math)
    # 将 EXTRA_LIBS 的值与字符串 "MathFunctions" 连接，重新赋值给 EXTRA_LIBS
    set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
else()
    # 不链接math库会报错，因为linux中默认没有math库
    LINK_LIBRARIES(m)
endif(USE_MYMATH)
```



## 三、定制安装规则



## 四、支持GDB



## 五、添加环境检查



## 六、添加版本号



## 七、生成安装包



## 八、将其他项目迁移到cmake



