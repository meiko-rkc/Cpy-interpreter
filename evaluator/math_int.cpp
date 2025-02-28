#include <evaluator/math.h>
using namespace cpy::evaluator;
// 整数前缀运算符函数映射表
const std::unordered_map<std::string, Math::Integer::intExpPrefixFn> Math::Integer::intExpPrefixFns = {
    {"+",  &Integer::plus},
    {"-",  &Integer::minus},
    {"~",  &Integer::bwnot},
    {"++", &Integer::inc},
    {"--", &Integer::dec},
};

// 整数中缀运算符函数映射表
const std::unordered_map<std::string, Math::Integer::intExpInfixFn> Math::Integer::intExpInfixFns = {
    {"+", &Integer::add},
    {"-", &Integer::sub},
    {"*", &Integer::mul},
    {"/", &Integer::div},
    {"%", &Integer::mod},
    {"**", &Integer::pow},
    {"&", &Integer::bwand},
    {"|", &Integer::bwor},
    {"^", &Integer::bwxor},
    {"<<", &Integer::lshift},
    {">>", &Integer::rshift},
};

// 整数比较运算符函数映射表
const std::unordered_map<std::string, Math::Integer::intCmpInfixFn> Math::Integer::intCmpInfixFns = {
    {"<", &Integer::lt},
    {">", &Integer::gt},
    {"<=", &Integer::le},
    {">=", &Integer::ge},
    {"==", &Integer::eq},
    {"!=", &Integer::ne},
};

// 整数后缀运算符函数映射表
const std::unordered_map<std::string, Math::Integer::intExpPostfixFn> Math::Integer::intExpPostfixFns = {
    {"++", &Integer::inc},
    {"--", &Integer::dec},
};

// 整数正数计算函数
inline int64_t Math::Integer::plus(int64_t right)
{
    return right;
}

// 整数负数计算函数
inline int64_t Math::Integer::minus(int64_t right)
{
    return -right;
}


// 整数按位非计算函数
inline int64_t Math::Integer::bwnot(int64_t right)
{
    return ~right;
}

// 整数自增表达式计算函数
inline int64_t Math::Integer::inc(int64_t right)
{
    return right + 1;
}

// 整数自减表达式计算函数
inline int64_t Math::Integer::dec(int64_t right)
{
    return right - 1;
}

// 整数前缀表达式计算求值函数
int64_t Math::Integer::evalIntExpPrefix(const std::string &op, int64_t right)
{
    return intExpPrefixFns.at(op)(right);
}

// 前缀表达式运算符有效性判断函数
bool Math::Integer::isValidExpPrefixOp(const std::string &op)
{
    return intExpPrefixFns.find(op) != intExpPrefixFns.end();
}

// 整数加法计算函数
inline int64_t Math::Integer::add(int64_t left, int64_t right)
{
    return left + right;
}

// 整数减法计算函数
inline int64_t Math::Integer::sub(int64_t left, int64_t right)
{
    return left - right;
}

// 整数乘法计算函数
inline int64_t Math::Integer::mul(int64_t left, int64_t right)
{
    return left * right;
}

// 整数除法计算函数
inline int64_t Math::Integer::div(int64_t left, int64_t right)
{
    return left / right;
}

// 整数除法计算函数
inline int64_t Math::Integer::mod(int64_t left, int64_t right)
{
    return left % right;
}

// 整数幂运算函数
inline int64_t Math::Integer::pow(int64_t left, int64_t right)
{
    return std::pow(left, right);
}

// 整数按位与运算函数
inline int64_t Math::Integer::bwand(int64_t left, int64_t right)
{
    return left & right;
}

// 整数按位或运算函数
inline int64_t Math::Integer::bwor(int64_t left, int64_t right)
{
    return left | right;
}

// 整数按位异或运算函数
inline int64_t Math::Integer::bwxor(int64_t left, int64_t right)
{
    return left ^ right;
}

// 整数左移运算函数
inline int64_t Math::Integer::lshift(int64_t left, int64_t right)
{
    return left << right;
}

// 整数右移运算函数
inline int64_t Math::Integer::rshift(int64_t left, int64_t right)
{
    return left >> right;
}

// 小于逻辑判断函数
inline bool Math::Integer::lt(int64_t left, int64_t right)
{
    return left < right;
}

// 大于逻辑判断函数
inline bool Math::Integer::gt(int64_t left, int64_t right)
{
    return left > right;
}

// 小于等于逻辑判断函数
inline bool Math::Integer::le(int64_t left, int64_t right)
{
    return left <= right;
}

// 大于等于逻辑判断函数
inline bool Math::Integer::ge(int64_t left, int64_t right)
{
    return left >= right;
}

// 等于逻辑判断函数
inline bool Math::Integer::eq(int64_t left, int64_t right)
{
    return left == right;
}

// 不等于逻辑判断函数
inline bool Math::Integer::ne(int64_t left, int64_t right)
{
    return left != right;
}

// 整数中缀表达式求值函数
int64_t Math::Integer::evalIntExpInfix(const std::string &op, int64_t left, int64_t right)
{
    return intExpInfixFns.at(op)(left, right);
}

// 整数中缀比较运算符求值函数
bool Math::Integer::evalIntCmpInfix(const std::string &op, int64_t left, int64_t right)
{
    return intCmpInfixFns.at(op)(left, right);
}

// 整数中缀运算符有效性判断函数
bool Math::Integer::isValidInfixOp(const std::string &op)
{
    return isValidExpInfixOp(op) && isValidCmpInfixOp(op);
}

// 整数中缀表达式运算符有效性判断函数
bool Math::Integer::isValidExpInfixOp(const std::string &op)
{
    return intExpInfixFns.find(op) != intExpInfixFns.end();
}

// 整数中缀比较运算符有效性判断函数
bool Math::Integer::isValidCmpInfixOp(const std::string &op)
{
    return intCmpInfixFns.find(op) != intCmpInfixFns.end();
}

// 后缀表达式求值函数
int64_t Math::Integer::evalIntExpPostfix(const std::string &op, int64_t right)
{
    return intExpPostfixFns.at(op)(right);
}

// 后缀表达式运算符有效性判断函数
bool Math::Integer::isValidExpPostfixOp(const std::string &op)
{
    return intExpPostfixFns.find(op)!= intExpPostfixFns.end();
}
