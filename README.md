# compiler

我的编译器程序

### 第一步词法分析已经完成

词法分析包括getsym.c，symfuncs.c两个文件，前者是主函数，后者是辅助函数。头文件compiler.h用来定义全局变量，function.h用来声明所定义的函数，variable.h用来声明所定义的变量，const.h用来声明所定义的常量和类型。

### 第二步语法分析
语法分析包括grammar.c这一个文件。目前这版中还没有建立符号表，错误处理功能也不完善。
