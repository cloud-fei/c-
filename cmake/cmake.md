# cmake语法
[从零开始介绍cmake](https://www.cnblogs.com/angelia-wang/p/16916509.html)  如有侵权请联系删除
## PROJECT关键字
用来指定工程的名字和支持的语言，默认支持所有语言。
```
PROJECT (HELLO)         # 指定了工程的名字，并且支持所有语言—建议
PROJECT (HELLO CXX)     # 指定了工程的名字，并且支持语言是C++
PROJECT (HELLO C CXX)   # 指定了工程的名字，并且支持语言是C和C++
```
该指定隐式定义了两个CMAKE的变量

- <projectname>_BINARY_DIR，本例中是 HELLO_BINARY_DIR

- <projectname>_SOURCE_DIR，本例中是 HELLO_SOURCE_DIR

MESSAGE 关键字就可以直接使用者两个变量，当前都指向当前的工作目录

## SET关键字
用来指定变量
```
SET(SRC_LIST main.cpp)                  # SRC_LIST 变量就包含了main.cpp
SET(SRC_LIST main.cpp t1.cpp t2.cpp)    # SRC_LIST 变量包含多个文件
```

## MESSAGE关键字
向终端输出用户自定义的信息。

主要包含三种信息：
- SEND_ERROR，产生错误，生成过程被跳过。
- SATUS，输出指定信息内容。
- FATAL_ERROR，立即终止所有 cmake 过程。

## ADD_EXECUTABLE关键字
生成可执行文件
```
ADD_EXECUTABLE(hello ${SRC_LIST})  

#生成的可执行文件名是hello，源文件读取变量SRC_LIST中的内容
#也可以直接写 ADD_EXECUTABLE(hello hello.cpp)
```


# 语法注意事项

- 变量使用 ${} 方式取值，但是在 IF 控制语句中是直接使用变量名。

- 指令(参数 1 参数 2...) 参数使用括弧括起，参数之间使用空格或分号分开。

- ADD_EXECUTABLE(hello hello) 后缀可以不写，他会自动去找.c和.cpp，最好不要这样写，可能会有这两个文件hello.cpp和hello。


## 内部构建和外部构建

- 内部构建：cmake生产的临时文件特别多，不方便清理，影响寻找源文件
- 外部构建：新建一个build目录，把生成的临时文件放在build目录下，这样不会对源文件有任何影响（推荐）。


## 将目标文件放入构建目录的 bin 子目录
每个目录下都要有一个CMakeLists.txt说明
```
[root@localhost cmake]# tree
.
├── build
├── CMakeLists.txt
└── src
    ├── CMakeLists.txt
    └── hello.cpp
```

- 根目录下的CMakeLists.txt
```
PROJECT(HELLO)
ADD_SUBDIRECTORY(src bin)    
#将 src 子目录加入工程并指定编译输出(包含编译中间结果)路径为 bin 目录
#如果不进行 bin 目录的指定，那么编译结果(包括中间结果)都将存放在 build/src 目录
```

- src下的 CMakeLists.txt
```
ADD_EXECUTABLE(hello main.cpp)
```

### 更改二进制的保存路径
通过 SET 指令重新定义 EXECUTABLE_OUTPUT_PATH 和 LIBRARY_OUTPUT_PATH 变量，来指定最终的目标二进制的位置。

```
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
```
问：要加在哪个CMakeLists.txt中？
答：哪里要改变目标存放路径，就在哪里加入上述的定义，所以应该在src下的CMakeLists.txt下写


## 使用make安装
- 一种是代码编译后直接 make install 安装
- 另一种是指定目录：make install DESTDIR=/tmp/test  或者：./configure –prefix=/usr

### 安装文件
使用CMAKE一个新的指令：INSTALL

INSTALL的安装可以包括：二进制、动态库、静态库以及文件、目录、脚本等

使用CMAKE一个新的变量：CMAKE_INSTALL_PREFIX，默认 /usr/local/
```
#目录树结构
[root@localhost cmake]# tree
.
├── build
├── CMakeLists.txt
├── COPYRIGHT
├── doc
│   └── hello.txt
├── README
├── runhello.sh
└── src
    ├── CMakeLists.txt
    └── main.cpp
```
我们安装当前目录的 COPYRIGHT 和 README 文件到 ${CMAKE_INSTALL_PREFIX}/share/doc/cmake/ 目录。在根目录的 CMakeLists.txt 文件中添加：
```
INSTALL(FILES COPYRIGHT README DESTINATION share/doc/cmake/)
```
FILES：关键字，表示文件。后跟文件路径（所在 Source 目录的相对路径）

DESTINATION：关键字，表示安装到什么路径。后跟目标路径：

CMAKE_INSTALL_PREFIX默认是 /usr/local/，可通过以下命令在 cmake 的时候指定 CMAKE_INSTALL_PREFIX变量的路径，也可通过 SET 命令更改该变量的值。
```
cmake -DCMAKE_INSTALL_PREFIX=/usr 
```

### 安装脚本
我们安装当前目录的脚本 runhello.sh 到 ${CMAKE_INSTALL_PREFIX}/bin/ 目录，也就是默认为/usr/local/bin/。
```
INSTALL(PROGRAMS runhello.sh DESTINATION bin)
```
PROGRAMS：关键字，表示非目标文件的可执行程序安装(比如脚本之类)

### 安装doc中的说明文件hello.txt
方法一、通过在 doc 目录建立CMakeLists.txt ，通过 install 安装。

方法二、直接在工程根目录的 CMakeLists.txt 添加 install：
```
INSTALL(DIRECTORY doc/ DESTINATION share/doc/cmake)
```
安装过程
```
cd build
cmake ..
make
make install
```











