#include <evaluator/math.h>
using namespace cpy::evaluator;
// 字符串前缀运算符函数映射表
const std::unordered_map<std::string, Math::String::strExpPrefixFn> Math::String::strExpPrefixFns = {
    {"+", &String::plus},
    {"-", &String::minus},
};

// 字符串中缀运算符函数映射表
const std::unordered_map<std::string, Math::String::strExpInfixFn> Math::String::strExpInfixFns = {
    {"+", &String::add},
    {"-", &String::sub},
};

// 字符串逻辑表达式函数映射表
const std::unordered_map<std::string, Math::String::strCmpInfixFn> Math::String::strCmpInfixFns = {
    {"<",  &String::lt},
    {">",  &String::gt},
    {"<=", &String::le},
    {">=", &String::ge},
    {"==", &String::eq},
    {"!=", &String::ne},
};

// 原字符串计算函数
inline std::string Math::String::plus(const std::string &right)
{
    return right;
}

// 翻转字符串计算函数
inline std::string Math::String::minus(const std::string &right)
{
    return std::string(right.rbegin(), right.rend());
}

// 前缀表达式求值函数
std::string Math::String::evalStrExpPrefix(const std::string &op, const std::string &right)
{
    return strExpPrefixFns.at(op)(right);
}

// 前缀表达式运算符有效性判断函数
bool Math::String::isValidExpPrefixOp(const std::string &op)
{
    return strExpPrefixFns.find(op) != strExpPrefixFns.end();
}

// 字符串拼接函数
inline std::string Math::String::add(const std::string &left, const std::string &right)
{
    return left + right;
}

// 字符串逆转拼接函数
inline std::string Math::String::sub(const std::string &left, const std::string &right)
{
    return left + minus(right);
}

// 字符串乘法函数
std::string Math::String::mul(const std::string &left, int64_t right)
{
    if (right == 0)
        return "";
    // 定义返回结果字符串和片段字符串
    std::string result, piece;
    // 如果right>0则片段字符串为left，否则片段字符串为left的翻转并令right变为非负数
    if (right > 0)
        piece = left;
    else
    {
        piece = minus(left);
        right *= -1;
    }
    // 进行字符串拼接
    while (right > 0)
    {
        result += piece;
        --right;
    }
    return result;
}

// 字符串小于逻辑判断函数
inline bool Math::String::lt(const std::string &left, const std::string &right)
{
    return left < right;
}

// 字符串大于逻辑判断函数
inline bool Math::String::gt(const std::string &left, const std::string &right)
{
    return left > right;
}

// 字符串小于等于逻辑判断函数
inline bool Math::String::le(const std::string &left, const std::string &right)
{
    return left <= right;
}

// 字符串大于等于逻辑判断函数
inline bool Math::String::ge(const std::string &left, const std::string &right)
{
    return left >= right;
}

// 字符串等于逻辑判断函数
inline bool Math::String::eq(const std::string &left, const std::string &right)
{
    return left == right;
}

// 字符串不等于逻辑判断函数
inline bool Math::String::ne(const std::string &left, const std::string &right)
{
    return left != right;
}

// 中缀表达式求值函数
std::string Math::String::evalStrExpInfix(const std::string &op, const std::string &left, const std::string &right)
{
    return strExpInfixFns.at(op)(left, right);
}

// 比较运算符中缀表达式求值函数
bool Math::String::evalStrCmpInfix(const std::string &op, const std::string &left, const std::string &right)
{
    return strCmpInfixFns.at(op)(left, right);
}

// 中缀运算符有效性判断函数
bool Math::String::isValidInfixOp(const std::string &op)
{
    return isValidExpInfixOp(op) && isValidCmpInfixOp(op);
}

// 中缀表达式运算符有效性判断函数
bool Math::String::isValidExpInfixOp(const std::string &op)
{
    return strExpInfixFns.find(op) != strExpInfixFns.end();
}

// 中缀逻辑运算符有效性判断函数
bool Math::String::isValidCmpInfixOp(const std::string &op)
{
    return strCmpInfixFns.find(op) != strCmpInfixFns.end();
}