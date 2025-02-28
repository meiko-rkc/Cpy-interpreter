#include <evaluator/math.h>
using namespace cpy::evaluator;
// 浮点数前缀运算符函数映射表
const std::unordered_map<std::string, Math::Float::floatExpPrefixFn> Math::Float::floatExpPrefixFns = {
    {"+",  &Float::plus},
    {"-",  &Float::minus},
    {"++", &Float::inc},
    {"--", &Float::dec},
};

// 浮点数中缀运算符函数映射表
const std::unordered_map<std::string, Math::Float::floatExpInfixFn> Math::Float::floatExpInfixFns = {
    {"+",  &Float::add},
    {"-",  &Float::sub},
    {"*",  &Float::mul},
    {"/",  &Float::div},
    {"%",  &Float::mod},
    {"**", &Float::pow},
};

// 浮点数比较表达式函数映射表
const std::unordered_map<std::string, Math::Float::floatCmpInfixFn> Math::Float::floatCmpInfixFns = {
    {"<",  &Float::lt},
    {">",  &Float::gt},
    {"<=", &Float::le},
    {">=", &Float::ge},
    {"==", &Float::eq},
    {"!=", &Float::ne},
};

// 浮点数后缀表达式函数映射表
const std::unordered_map<std::string, Math::Float::floatExpPostfixFn> Math::Float::floatExpPostfixFns = {
    {"++", &Float::inc},
    {"--", &Float::dec},
};

// 浮点数正数计算函数
inline double Math::Float::plus(double right)
{
    return right;
}

// 浮点数负数计算函数
inline double Math::Float::minus(double right)
{
    return -right;
}

// 浮点数自增计算函数
inline double Math::Float::inc(double right)
{
    return right+1.0;
}

// 浮点数自减计算函数
inline double Math::Float::dec(double right)
{
    return right-1.0;
}

// 前缀表达式求值函数
double Math::Float::evalFloatExpPrefix(const std::string &op, double right)
{
    return floatExpPrefixFns.at(op)(right);
}

// 前缀表达式运算符有效性判断函数
bool Math::Float::isValidExpPrefixOp(const std::string &op)
{
    return floatExpPrefixFns.find(op) != floatExpPrefixFns.end();
}

// 浮点数加法计算函数
inline double Math::Float::add(double left, double right)
{
    return left + right;
}

// 浮点数减法计算函数
inline double Math::Float::sub(double left, double right)
{
    return left - right;
}

// 浮点数乘法计算函数
inline double Math::Float::mul(double left, double right)
{
    return left * right;
}

// 浮点数除法计算函数
inline double Math::Float::div(double left, double right)
{
    return left / right;
}

// 浮点数取模计算函数
inline double Math::Float::mod(double left, double right)
{
    return std::fmod(left, right);
}

// 浮点数幂运算函数
inline double Math::Float::pow(double left, double right)
{
    return std::pow(left, right);
}

// 浮点数小于逻辑判断函数
inline bool Math::Float::lt(double left, double right)
{
    return left < right;
}

// 浮点数大于逻辑判断函数
inline bool Math::Float::gt(double left, double right)
{
    return left > right;
}

// 浮点数小于等于逻辑判断函数
inline bool Math::Float::le(double left, double right)
{
    return left <= right;
}

// 浮点数大于等于逻辑判断函数
inline bool Math::Float::ge(double left, double right)
{
    return left >= right;
}

// 浮点数等于逻辑判断函数
inline bool Math::Float::eq(double left, double right)
{
    return left == right;
}

// 浮点数不等于逻辑判断函数
inline bool Math::Float::ne(double left, double right)
{
    return left != right;
}

// 中缀表达式求值函数
double Math::Float::evalFloatExpInfix(const std::string &op, double left, double right)
{
    return floatExpInfixFns.at(op)(left, right);
}

// 中缀比较运算符求值函数
bool Math::Float::evalFloatCmpInfix(const std::string &op, double left, double right)
{
    return floatCmpInfixFns.at(op)(left, right);
}

// 中缀运算符有效性判断函数
bool Math::Float::isValidInfixOp(const std::string &op)
{
    return isValidExpInfixOp(op) && isValidCmpInfixOp(op);
}

// 中缀表达式运算符有效性判断函数
bool Math::Float::isValidExpInfixOp(const std::string &op)
{
    return floatExpInfixFns.find(op) != floatExpInfixFns.end();
}

// 中缀逻辑运算符有效性判断函数
bool Math::Float::isValidCmpInfixOp(const std::string &op)
{
    return floatCmpInfixFns.find(op) != floatCmpInfixFns.end();
}

// 后缀表达式求值函数
double Math::Float::evalFloatExpPostfix(const std::string &op, double right)
{
    return floatExpPostfixFns.at(op)(right);
}

// 后缀表达式运算符有效性判断函数
bool Math::Float::isValidExpPostfixOp(const std::string &op)
{
    return floatExpPostfixFns.find(op)!= floatExpPostfixFns.end();
}