#include <lexer/lexer.h>
#include "lexer.h"
using namespace cpy::lexer;
// 默认构造函数
Lexer::Lexer()
{
    init("", INPUT_CONTENT);
}

// 带参构造函数，传入相关字符串和输入类型
Lexer::Lexer(const std::string &str, InputType inputType)
{
    init(str, inputType);
}

// 获取下一个Token
Token Lexer::nextToken()
{
    // 读取下一个字符
    readChar();
    // 跳过空白字符
    skipWhitespace();
    // 根据读取字符的值，返回对应的Token对象
    switch (ch)
    {
    case '+':
    {
        // 如果下一个字符为'+'，则返回'++'Token对象
        if (peekChar() == '+')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_INC, "++");
        }
        // 如果下一个字符是'='，则返回'+='Token对象
        else if (peekChar() == '=')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_PLUS_ASSIGN, "+=");
        }
        // 否则，返回'+'Token对象
        else
            return newToken(Token::TOKEN_PLUS, "+");
    }
    case '-':
    {
        // 如果下一个字符为'-'，则返回'--'Token对象
        if (peekChar() == '-')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_DEC, "--");
        }
        // 如果下一个字符是'='，则返回'-='Token对象
        else if (peekChar() == '=')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_MINUS_ASSIGN, "-=");
        }
        // 否则，返回'-'Token对象
        else
            return newToken(Token::TOKEN_MINUS, "-");
    }
    case '*':
    {
        if (peekChar() == '*')
        {
            // 读取下一个字符
            readChar();
            if (peekChar() == '=')
            {
                // 读取下一个字符
                readChar();
                return newToken(Token::TOKEN_POW_ASSIGN, "**=");
            }
            else
                return newToken(Token::TOKEN_POW, "**");
        }
        // 如果下一个字符是'='，则返回'*='Token对象
        else if (peekChar() == '=')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_ASTERISK_ASSIGN, "*=");
        }
        // 否则，返回'*'Token对象
        else
            return newToken(Token::TOKEN_ASTERISK, "*");
    }
    case '/':
    {
        // 如果下一个字符是'='，则返回'/='Token对象
        if (peekChar() == '=')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_SLASH_ASSIGN, "/=");
        }
        // 否则，返回'/'Token对象
        else
            return newToken(Token::TOKEN_SLASH, "/");
    }
    case '%':
    {
        // 如果下一个字符是'='，则返回'%='Token对象
        if (peekChar() == '=')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_MODULO_ASSIGN, "%=");
        }
        // 否则，返回'%'Token对象
        else
            return newToken(Token::TOKEN_MODULO, "%");
    }
    case '~':
        return newToken(Token::TOKEN_TILDE, "~");
    case '&':
    {
        // 如果下一个字符是'&'，则返回'&&'Token对象
        if (peekChar() == '&')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_AND, "&&");
        }
        else if (peekChar() == '=')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_BWAND_ASSIGN, "&=");
        }
        // 否则，返回'&'Token对象
        else
            return newToken(Token::TOKEN_BWAND, "&");
    }
    case '|':
    {
        // 如果下一个字符是'|'，则返回'||'Token对象
        if (peekChar() == '|')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_OR, "||");
        }
        else if (peekChar() == '=')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_BWOR_ASSIGN, "|=");
        }
        // 否则，返回'|'Token对象
        else
            return newToken(Token::TOKEN_BWOR, "|");
    }
    case '^':
    {
        // 如果下一个字符是'='，则返回'^='Token对象
        if (peekChar() == '=')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_BWOR_ASSIGN, "^=");
        }
        // 否则，返回'^'Token对象
        else
            return newToken(Token::TOKEN_BWXOR, "^");
    }
    case '<':
    {
        // 读取下一个字符
        if (peekChar() == '<')
        {
            // 读取下一个字符
            readChar();
            if (peekChar() == '=')
            {
                // 读取下一个字符
                readChar();
                return newToken(Token::TOKEN_LSHIFT_ASSIGN, "<<=");
            }
            else
                return newToken(Token::TOKEN_LSHIFT, "<<");
        }
        else if (peekChar() == '=')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_LE, "<=");
        }
        else
            return newToken(Token::TOKEN_LT, "<");
    }
    case '>':
    {
        if (peekChar() == '>')
        {
            // 读取下一个字符
            readChar();
            if (peekChar() == '=')
            {
                // 读取下一个字符
                readChar();
                return newToken(Token::TOKEN_RSHIFT_ASSIGN, ">>=");
            }
            else
                return newToken(Token::TOKEN_RSHIFT, ">>");
        }
        // 读取下一个字符
        else if (peekChar() == '=')
        {
            // 读取下一个字符
            readChar();
            return newToken(Token::TOKEN_GE, ">=");
        }
        else
            return newToken(Token::TOKEN_GT, ">");
    }
    case '=':
    {
        // 读取下一个字符
        readChar();
        if (ch == '=')
            return newToken(Token::TOKEN_EQ, "==");
        else
        {
            // 回退一个字符
            unreadChar();
            return newToken(Token::TOKEN_ASSIGN, "=");
        }
    }
    case '!':
    {
        // 读取下一个字符
        readChar();
        if (ch == '=')
            return newToken(Token::TOKEN_NE, "!=");
        else
        {
            // 回退一个字符
            unreadChar();
            return newToken(Token::TOKEN_NOT, "!");
        }
    }
    case '(':
        return newToken(Token::TOKEN_LPAREN, "(");
    case ')':
        return newToken(Token::TOKEN_RPAREN, ")");
    case '[':
        return newToken(Token::TOKEN_LBRACKET, "[");
    case ']':
        return newToken(Token::TOKEN_RBRACKET, "]");
    case '{':
        return newToken(Token::TOKEN_LBRACE, "{");
    case '}':
        return newToken(Token::TOKEN_RBRACE, "}");
    case '\'':
        // 读取字符串，并返回双引号字符串Token对象
        return newToken(Token::TOKEN_STRING, readSingleQuoteString());
    case '"':
        // 读取字符串，并返回双引号字符串Token对象
        return newToken(Token::TOKEN_STRING, readDoubleQuoteString());
    case '?':
        return newToken(Token::TOKEN_QUESTION, "?");
    case ':':
        return newToken(Token::TOKEN_COLON, ":");
    case ',':
        return newToken(Token::TOKEN_COMMA, ",");
    case ';':
        return newToken(Token::TOKEN_SEMICOLON, ";");
    case '.':
        return newToken(Token::TOKEN_DOT, ".");
    case '\0':
        return newToken(Token::TOKEN_EOF, "");
    default:
    {
        if (isDigit(ch))
        {
            // 读取数字
            std::string integer = readNumber();
            if (ch == '.')
            {
                // 读取下一个字符
                readChar();
                // 读取小数部分
                std::string fraction = readNumber();
                // 回退一个字符,避免漏读字符
                unreadChar();
                // 返回浮点数Token对象
                return newToken(Token::TOKEN_FLOAT, integer + "." + fraction);
            }
            // 回退一个字符,避免漏读字符
            unreadChar();
            // 返回整数Token对象
            return newToken(Token::TOKEN_INTEGER, integer);
        }
        else if (isLetter(ch))
        {
            // 读取标识符
            std::string identifier = readIdentifier();
            // 判断标识符是否为关键字
            Token::Type tokenType = Token::getKeywordType(identifier);
            unreadChar();
            // 如果是关键字，则返回关键字对应的Token对象
            // 否则，返回标识符对应的Token对象
            return newToken(tokenType, identifier);
        }
        else
        {
            // 返回非法Token对象
            return newToken(Token::TOKEN_ILLEGAL, std::string(1, ch));
        }
    }
    }
    return Token();
}

// 传入文件路径初始化Lexer函数
void Lexer::initWithFile(const std::string &file)
{
    /* 打开文件，读取文件内容到content成员变量 */
    // 创建一个文件流对象fs，打开文件file
    std::fstream fs(file);
    // 检查文件是否打开成功
    if (!fs.good())
    {
        // 输出错误信息
        std::cout << "failed to open file:" << file << std::endl;
        return;
    }
    // 创建一个字符串流对象ss
    std::stringstream ss;
    // 将ss的缓冲区内容读取到content成员变量中
    ss << fs.rdbuf();
    // 初始化Lexer对象的成员变量
    initWithContent(ss.str());
    this->file = file;
}

// 传入文本内容初始化Lexer函数
void Lexer::initWithContent(const std::string &content)
{
    // 初始化Lexer对象的成员变量
    ch = '\0';
    pos = 0;
    nextPos = 0;
    line = 1;
    column = 1;
    this->content.assign(content);
}

// 初始化Lexer函数
void Lexer::init(const std::string &str, InputType inputType)
{
    // 根据输入类型，调用相应的初始化函数
    switch (inputType)
    {
    case InputType::INPUT_FILE:
    {
        // 调用文件函数初始化Lexer对象
        initWithFile(str);
        break;
    }
    case InputType::INPUT_CONTENT:
    {
        // 调用内容函数初始化Lexer对象
        initWithContent(str);
        break;
    }
    default:
        break;
    }
}

// 跳过空白字符
void Lexer::skipWhitespace()
{
    // 循环读取字符，直到ch不是空白字符为止
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
    {
        // 如果是空白字符，则列数加1
        if(ch==' ')
            ++column;
        // 如果是换行符，则将行数加1，列数重置为1
        else if(ch=='\n')
        {
            ++line;
            column=1;
        }
        // 如果是制表符，则将列数加4
        else if(ch=='\t')
            column+=4;
        // 读取下一个字符
        readChar();
    }
    return;
}

// 读取下一个字符
void Lexer::readChar()
{
    /* 检查是否到达文件末尾 */
    // 如果到达文件末尾，则将ch设置为'\0'
    // 否则，将ch设置为content中下一个位置的字符
    if (nextPos >= content.length())
        ch = '\0';
    else
        ch = content[nextPos];
    // 更新pos和nextPos的值
    pos = nextPos;
    nextPos++;
}

// 读取下一个字符，但不移动当前位置
char Lexer::peekChar()
{
    // 如果到达文件末尾，则返回'\0'，否则返回content中下一个位置的字符
    return nextPos >= content.length() ? '\0' : content[nextPos];
}

// 不读取字符
void Lexer::unreadChar()
{
    // 返回上一次字符读取位置
    nextPos = pos;
    pos--;
}

// 判断当前字符是否为数字
bool Lexer::isDigit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

// 判断当前字符是否为字母
bool Lexer::isLetter(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

// 读取数字并返回数字字符串
std::string Lexer::readNumber()
{
    // 保存当前位置
    int tempPos = this->pos;
    // 循环读取字符，直到ch不是数字为止
    while (isDigit(ch))
        readChar();
    // 返回数字字符串
    return content.substr(tempPos, this->pos - tempPos);
}

// 读取标识符并返回标识符字符串
std::string Lexer::readIdentifier()
{
    // 保存当前位置
    int tempPos = this->pos;
    // 循环读取字符，直到ch不是字母或数字为止
    while (isLetter(ch) || isDigit(ch))
        readChar();
    // 返回标识符字符串
    return content.substr(tempPos, this->pos - tempPos);
}

// 读取单引号字符串并返回字符串
std::string Lexer::readSingleQuoteString()
{
    std::string str;
    // 循环读取字符，直到ch不是单引号或文件末尾为止
    while (true)
    {
        // 读取下一个字符
        readChar();
        // 如果ch是单引号或文件末尾，则跳出循环
        if (ch == '\'' || ch == '\0')
            break;
        /* 处理转义字符 */
        if (ch == '\\')
        {
            switch (peekChar())
            {
            case '\'':
                readChar();
                ch = '\'';
                break;
            case '\\':
                readChar();
                ch = '\\';
                break;
            case 'n':
                readChar();
                ch = '\n';
                break;
            case 'r':
                readChar();
                ch = '\r';
                break;
            case 't':
                readChar();
                ch = '\t';
                break;
            default:
                break;
            }
        }
        // 字符拼接
        str += ch;
    }
    // 返回单引号字符串
    return str;
}

// 读取双引号字符串并返回字符串
std::string Lexer::readDoubleQuoteString()
{
    std::string str;
    // 循环读取字符，直到ch不是单引号或文件末尾为止
    while (true)
    {
        // 读取下一个字符
        readChar();
        // 如果ch是单引号或文件末尾，则跳出循环
        if (ch == '"' || ch == '\0')
            break;
        /* 处理转义字符 */
        if (ch == '\\')
        {
            switch (peekChar())
            {
            case '"':
                readChar();
                ch = '"';
                break;
            case '\\':
                readChar();
                ch = '\\';
                break;
            case 'n':
                readChar();
                ch = '\n';
                break;
            case 'r':
                readChar();
                ch = '\r';
                break;
            case 't':
                readChar();
                ch = '\t';
                break;
            default:
                break;
            }
        }
        // 字符拼接
        str += ch;
    }
    // 返回双引号字符串
    return str;
}

// 根据Token类型和字面量创建新的Token对象
Token Lexer::newToken(Token::Type type, const std::string &literal)
{
    // 创建新的Token对象
    Token token(type, literal, line, column);
    // 更新列号，列号加上字面量的长度
    column+=literal.length();
    // 如果是字符串类型，则列号加2
    if(type==Token::TOKEN_STRING)
        column+=2;
    return token;
}