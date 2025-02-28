#include <token/token.h>
#include "token.h"
using namespace cpy::token;
// 实现静态哈希表names，将Token::Type映射到对应的字符串表示
const std::unordered_map<Token::Type, std::string> Token::names = {
    {TOKEN_ILLEGAL, "illegal"},
    {TOKEN_EOF, "eof"},
    {TOKEN_INTEGER, "integer"},
    {TOKEN_FLOAT, "float"},
    {TOKEN_STRING, "string"},
    {TOKEN_PLUS, "+"},
    {TOKEN_MINUS, "-"},
    {TOKEN_ASTERISK, "*"},
    {TOKEN_POW, "**"},
    {TOKEN_SLASH, "/"},
    {TOKEN_MODULO, "%"},
    {TOKEN_TILDE, "~"},
    {TOKEN_BWAND, "&"},
    {TOKEN_BWOR, "|"},
    {TOKEN_BWXOR, "^"},
    {TOKEN_LSHIFT, "<<"},
    {TOKEN_RSHIFT, ">>"},
    {TOKEN_LT, "<"},
    {TOKEN_GT, ">"},
    {TOKEN_LE, "<="},
    {TOKEN_GE, ">="},
    {TOKEN_EQ, "=="},
    {TOKEN_NE, "!="},
    {TOKEN_AND, "&&"},
    {TOKEN_OR, "||"},
    {TOKEN_NOT, "!"},
    {TOKEN_LPAREN, "("},
    {TOKEN_RPAREN, ")"},
    {TOKEN_LBRACKET, "["},
    {TOKEN_RBRACKET, "]"},
    {TOKEN_LBRACE, "{"},
    {TOKEN_RBRACE, "}"},
    {TOKEN_COMMA, ","},
    {TOKEN_SEMICOLON, ";"},
    {TOKEN_IDENTIFIER, "identifier"},
    {TOKEN_TRUE, "true"},
    {TOKEN_FALSE, "false"},
    {TOKEN_NULL, "null"},
    {TOKEN_IF, "if"},
    {TOKEN_ELIF, "elif"},
    {TOKEN_ELSE, "else"},
    {TOKEN_SWITCH, "switch"},
    {TOKEN_CASE, "case"},
    {TOKEN_DEFAULT, "default"},
    {TOKEN_WHILE, "while"},
    {TOKEN_FOR, "for"},
    {TOKEN_BREAK, "break"},
    {TOKEN_CONTINUE, "continue"},
    {TOKEN_IN, "in"},
    {TOKEN_FUNCTION, "function"},
    {TOKEN_RETURN, "return"},
    {TOKEN_ASSIGN, "="},
    {TOKEN_PLUS_ASSIGN, "+="},
    {TOKEN_MINUS_ASSIGN, "-="},
    {TOKEN_ASTERISK_ASSIGN, "*="},
    {TOKEN_POW_ASSIGN, "**="},
    {TOKEN_SLASH_ASSIGN, "/="},
    {TOKEN_MODULO_ASSIGN, "%="},
    {TOKEN_BWAND_ASSIGN, "&="},
    {TOKEN_BWOR_ASSIGN, "|="},
    {TOKEN_BWXOR_ASSIGN, "^="},
    {TOKEN_LSHIFT_ASSIGN, "<<="},
    {TOKEN_RSHIFT_ASSIGN, ">>="},
    {TOKEN_INC, "++"},
    {TOKEN_DEC, "--"},
    {TOKEN_QUESTION, "?"},
    {TOKEN_COLON, ":"},
    {TOKEN_DOT, "."},
};

// 实现静态哈希表keywords，将字符串映射到对应的Token::Type
const std::unordered_map<std::string, Token::Type> Token::keywords = {
    {"true", TOKEN_TRUE},
    {"false", TOKEN_FALSE},
    {"null", TOKEN_NULL},
    {"if", TOKEN_IF},
    {"elif", TOKEN_ELIF},
    {"else", TOKEN_ELSE},
    {"switch", TOKEN_SWITCH},
    {"case", TOKEN_CASE},
    {"default", TOKEN_DEFAULT},
    {"while", TOKEN_WHILE},
    {"for", TOKEN_FOR},
    {"break", TOKEN_BREAK},
    {"continue", TOKEN_CONTINUE},
    {"in", TOKEN_IN},
    {"fn", TOKEN_FUNCTION},
    {"return", TOKEN_RETURN},
};

// 默认构造函数
Token::Token() : type(TOKEN_ILLEGAL), line(0), column(0)
{
}

// 带参数的构造函数
Token::Token(Type type, const std::string &literal, size_t line, size_t column) : type(type), literal(literal), line(line), column(column)
{
}

// 拷贝构造函数
Token::Token(const Token &other)
{
    // 检查自赋值
    if (this == &other)
        return;
    // 拷贝构造函数
    type = other.type;
    literal = other.literal;
}

// 赋值运算符重载
Token &Token::operator=(const Token &other)
{
    // 检查自赋值
    if (this == &other)
        return *this;
    // 赋值
    type = other.type;
    literal = other.literal;
    line = other.line;
    column = other.column;
    // 返回当前对象的引用，便于链式赋值
    return *this;
}

// 获取Token的枚举类型Type
Token::Type Token::getType() const
{
    // 返回token类型type
    return type;
}

// 获取Token的行号
size_t Token::getLine() const
{
    return line;
}

// 获取Token的列号
size_t Token::getColumn() const
{
    return column;
}

// 获取Token的类型对应的字符串
std::string Token::getName() const
{
    return getName(type);
}

// 根据Type类型获取对应的字符串名字
std::string Token::getName(Type type)
{
    // 通过names哈希表映射查找type对应的name
    if (names.find(type) != names.end())
        return names.at(type);
    return "";
}

// 获取Token的字面量
std::string Token::getLiteral()
{
    // 返回字面量literal
    return literal;
}

// 获取关键字的Token类型
Token::Type Token::getKeywordType(const std::string &identifier)
{
    // 通过keywords哈希表映射查找identifier对应的type
    if (keywords.find(identifier) != keywords.end())
        return keywords.at(identifier);
    // 如果不是关键字，返回标识符类型
    return TOKEN_IDENTIFIER;
}

// 打印Token的信息
void Token::show() const
{
    printf("Token(type=%d name='%s' literal='%s' line=%d column=%d)\n", type, getName().c_str(), literal.c_str(), line, column);
}

// Token信息转换为Json::Value对象
Value Token::getJson() const
{
    // 构造Json::Value对象并根据Token信息初始化
    Value json;
    json["type"] = getName();
    json["literal"] = literal;
    json["line"] = line;
    json["column"] = column;
    // 返回Json::Value对象
    return json;
}
