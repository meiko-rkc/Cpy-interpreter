#include <evaluator/math.h>
using namespace cpy::evaluator;
// 布尔前缀逻辑运算符函数映射表
const std::unordered_map<std::string, Math::Bool::boolLogPrefixFn> Math::Bool::boolLogPrefixFns = {
    {"!", &Bool::lognot},
};

// 布尔中缀逻辑运算符函数映射表
const std::unordered_map<std::string, Math::Bool::boolLogInfixFn> Math::Bool::boolLogInfixFns = {
    {"&&", &Bool::logand},
    {"||", &Bool::logor},
};

// 逻辑非运算函数
inline bool Math::Bool::lognot(bool right)
{
    return !right;
}

// 逻辑前缀表达式计算求值函数
bool Math::Bool::evalBoolLogPrefix(const std::string &op, bool right)
{
    return boolLogPrefixFns.at(op)(right);
}

// 逻辑前缀表达式运算符有效性判断函数
bool Math::Bool::isValidLogPrefixOp(const std::string &op)
{
    return boolLogPrefixFns.find(op)!= boolLogPrefixFns.end();
}

// 逻辑与运算函数
inline bool Math::Bool::logand(bool left, bool right)
{
    return left && right;
}

// 逻辑或运算函数
inline bool Math::Bool::logor(bool left, bool right)
{
    return left || right;
}

// 逻辑中缀表达式计算求值函数
bool Math::Bool::evalBoolLogInfix(const std::string &op, bool left, bool right)
{
    return boolLogInfixFns.at(op)(left, right);
}

// 逻辑中缀表达式运算符有效性判断函数
bool Math::Bool::isValidLogInfixOp(const std::string &op)
{
    return boolLogInfixFns.find(op)!= boolLogInfixFns.end();
}