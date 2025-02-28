#pragma once
#include <string>
#include <unordered_map>
#include <json/json.h>
using namespace Json;
// 一级命名空间   namespace pi
namespace cpy
{
    // 一级命名空间   namespace pi
    namespace token
    {
        // 定义Token类
        class Token
        {
        public:
            // Token枚举类型
            enum Type
            {
                TOKEN_ILLEGAL = 0,     // illegal
                TOKEN_EOF,             // eof
                TOKEN_INTEGER,         // integer
                TOKEN_FLOAT,           // float
                TOKEN_STRING,          // string
                TOKEN_PLUS,            // +
                TOKEN_MINUS,           // -
                TOKEN_ASTERISK,        // *
                TOKEN_POW,             // **
                TOKEN_SLASH,           // /
                TOKEN_MODULO,          // %
                TOKEN_TILDE,           // ~
                TOKEN_BWAND,           // &
                TOKEN_BWOR,            // |
                TOKEN_BWXOR,           // ^
                TOKEN_LSHIFT,          // <<
                TOKEN_RSHIFT,          // >>
                TOKEN_LT,              // <
                TOKEN_GT,              // >
                TOKEN_LE,              // <=
                TOKEN_GE,              // >=
                TOKEN_EQ,              // ==
                TOKEN_NE,              // !=
                TOKEN_AND,             // &&
                TOKEN_OR,              // ||
                TOKEN_NOT,             // !
                TOKEN_LPAREN,          // (
                TOKEN_RPAREN,          // )
                TOKEN_LBRACKET,        // [
                TOKEN_RBRACKET,        // ]
                TOKEN_LBRACE,          // {
                TOKEN_RBRACE,          // }
                TOKEN_COMMA,           // ,
                TOKEN_SEMICOLON,       // ;
                TOKEN_IDENTIFIER,      // identifier
                TOKEN_TRUE,            // true
                TOKEN_FALSE,           // false
                TOKEN_NULL,            // null
                TOKEN_IF,              // if
                TOKEN_ELIF,            // elif
                TOKEN_ELSE,            // else
                TOKEN_SWITCH,          // switch
                TOKEN_CASE,            // case
                TOKEN_DEFAULT,         // default
                TOKEN_WHILE,           // while
                TOKEN_FOR,             // for
                TOKEN_BREAK,           // break
                TOKEN_CONTINUE,        // continue
                TOKEN_IN,              // in
                TOKEN_FUNCTION,        // function
                TOKEN_RETURN,          // return
                TOKEN_ASSIGN,          // =
                TOKEN_PLUS_ASSIGN,     // +=
                TOKEN_MINUS_ASSIGN,    // -=
                TOKEN_ASTERISK_ASSIGN, // *=
                TOKEN_POW_ASSIGN,      // **=
                TOKEN_SLASH_ASSIGN,    // /=
                TOKEN_MODULO_ASSIGN,   // %=
                TOKEN_BWAND_ASSIGN,    // &=
                TOKEN_BWOR_ASSIGN,     // |=
                TOKEN_BWXOR_ASSIGN,    // ^=
                TOKEN_LSHIFT_ASSIGN,   // <<=
                TOKEN_RSHIFT_ASSIGN,   // >>=
                TOKEN_INC,             // ++
                TOKEN_DEC,             // --
                TOKEN_QUESTION,        // ?
                TOKEN_COLON,           //:
                TOKEN_DOT,             //.
            };

            /* 构造函数 */
            // 默认构造函数
            Token();

            // 带参数的构造函数，用于初始化Token对象的type，literal成员变量，line，column成员变量
            Token(Type type, const std::string &literal, size_t line, size_t column);

            // 拷贝构造函数
            // 使用编译器生成的默认实现
            Token(const Token &other);

            // 赋值运算符重载
            // 使用编译器生成的默认实现
            Token &operator=(const Token &other);

            /* 析构函数 */
            // 使用编译器生成的默认实现
            ~Token() = default;

            /* 公有成员函数 */
            // 获取Token的枚举类型Type
            Type getType() const;

            // 获取Token的行号size_t
            size_t getLine() const;

            // 获取Token的列号size_t
            size_t getColumn() const;

            // 获取Token的名称string
            std::string getName() const;
            static std::string getName(Type type);

            // 获取Token的字面量string
            std::string getLiteral();

            // 获取关键字的Token类型
            static Type getKeywordType(const std::string &identifier);

            // 打印Token的信息
            void show() const;

            // 转换Token信息为Json::Value对象
            Value getJson() const;

        private:
            /* 私有成员变量 */
            Type type;                                                   // Token的类型
            std::string literal;                                         // Token的字面量
            size_t line;                                                 // Token所在的行号
            size_t column;                                               // Token所在的列号
            static const std::unordered_map<Type, std::string> names;    // Token的名称映射表
            static const std::unordered_map<std::string, Type> keywords; // Token的关键字映射表
        };
    }
}