#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <token/token.h>
using namespace cpy::token;
// 一级命名空间   namespace pi
namespace cpy
{
    // 二级命名空间   namespace lexer
    namespace lexer
    {
        // 定义词法分析器Lexer类
        class Lexer
        {
        public:
            enum InputType
            {
                INPUT_FILE = 0,
                INPUT_CONTENT,
            };

            /* 构造函数 */
            // 空参构造函数
            Lexer();

            // 带参构造函数，传入文件路径
            Lexer(const std::string &str, InputType inputType = INPUT_FILE);

            /* 析构函数 */
            // 默认析构函数，使用编译器生成的默认实现
            ~Lexer() = default;

            /* 公有成员函数 */
            // 获取下一个Token
            Token nextToken();

            // 初始化Lexer函数，传入文件路径
            void initWithFile(const std::string &file);       // 初始化Lexer函数，传入文件内容
            void initWithContent(const std::string &content); // 初始化Lexer函数，传入具体内容
            void init(const std::string &str, InputType inputType = INPUT_FILE);

        private:
            /* 私有成员函数 */
            // 空白字符跳过函数
            void skipWhitespace();

            // 字符读取函数，移动一格位置
            void readChar();

            // 下个字符读取函数，但不移动位置
            char peekChar();

            // 位置返回函数，返回上一次字符读取位置
            void unreadChar();

            // 数字字符判断函数
            bool isDigit(char ch);

            // 字母字符判断函数
            bool isLetter(char ch);

            // 数字字符串读取函数
            std::string readNumber();

            // 标识符字符串读取函数
            std::string readIdentifier();

            // 单引号字符串读取函数
            std::string readSingleQuoteString();

            // 双引号字符串读取函数
            std::string readDoubleQuoteString();

            // Token对象创建函数
            Token newToken(Token::Type type, const std::string &literal);

        private:
            /* 私有成员变量 */
            std::string file;    // 输入文件路径
            std::string content; // 文件内容
            char ch;             // 当前字符
            size_t pos;          // 当前字符的位置
            size_t line;         // 当前字符的行号
            size_t column;       // 当前字符的列号
            size_t nextPos;      // 下一个字符的位置
        };
    }
}