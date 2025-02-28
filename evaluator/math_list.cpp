#include <evaluator/math.h>
using namespace cpy::evaluator;
// 列表前缀运算符函数映射表
const std::unordered_map<std::string, Math::List::listExpPrefixFn> Math::List::listExpPrefixFns = {
    {"+", &List::plus},
    {"-", &List::minus},
};

// 列表中缀运算符函数映射表
const std::unordered_map<std::string, Math::List::listExpInfixFn> Math::List::listExpInfixFns = {
    {"+", &List::add},
    {"-", &List::sub},
};

// 列表中缀比较表达式运算符函数映射表
const std::unordered_map<std::string, Math::List::listCmpInfixFn> Math::List::listCmpInfixFns = {
    {"<", &List::lt},
    {">", &List::gt},
    {"<=", &List::le},
    {">=", &List::ge},
    {"==", &List::eq},
    {"!=", &List::ne},
};

// 原列表计算函数
inline std::vector<std::shared_ptr<Object>> Math::List::plus(const std::vector<std::shared_ptr<Object>> &right)
{
    return right;
}

// 翻转列表计算函数
inline std::vector<std::shared_ptr<Object>> Math::List::minus(const std::vector<std::shared_ptr<Object>> &right)
{
    return std::vector<std::shared_ptr<Object>>(right.rbegin(), right.rend());
}

// 前缀表达式运算符有效性判断函数
std::vector<std::shared_ptr<Object>> Math::List::evalListExpPrefix(const std::string &op, const std::vector<std::shared_ptr<Object>> &right)
{
    return listExpPrefixFns.at(op)(right);
}

// 前缀表达式运算符有效性判断函数
bool Math::List::isValidExpPrefixOp(const std::string &op)
{
    return listExpPrefixFns.find(op) != listExpPrefixFns.end();
}

// 列表加法拼接函数
inline std::vector<std::shared_ptr<Object>> Math::List::add(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right)
{
    // 定义返回结果列表
    std::vector<std::shared_ptr<Object>> result;
    // 预留空间
    result.reserve(left.size() + right.size());
    // 拼接左列表
    for (auto &obj : left)
        result.emplace_back(obj);
    // 拼接右列表
    for (auto &obj : right)
        result.emplace_back(obj);
    // 返回结果列表
    return result;
}

// 列表减法拼接函数
inline std::vector<std::shared_ptr<Object>> Math::List::sub(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right)
{
    return add(left, minus(right));
}

// 列表乘法函数
std::vector<std::shared_ptr<Object>> Math::List::mul(const std::vector<std::shared_ptr<Object>> &left, int64_t right)
{
    // 如果right==0则返回空列表
    if (right == 0)
        return std::vector<std::shared_ptr<Object>>();
    // 定义返回结果列表和片段列表
    std::vector<std::shared_ptr<Object>> result, piece;
    // 如果right>0则片段字符串为left，否则片段字符串为left的翻转并令right变为非负数
    if (right > 0)
        piece = left;
    else
    {
        piece = minus(left);
        right *= -1;
    }
    // 分配空间
    result.reserve(left.size() * right);
    // 进行列表拼接
    while (right > 0)
    {
        for (auto &obj : piece)
            result.emplace_back(obj);
        --right;
    }
    // 返回结果列表
    return result;
}

// 列表小于比较判断函数
std::shared_ptr<Object> Math::List::lt(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right)
{
    for (int64_t i = 0; i < left.size() && i < right.size(); ++i)
    {
        // 如果左右两个对象相等则继续比较下一个对象
        if (Object::isEqual(left[i], right[i]))
            continue;
        // 对左右两个对象进行小于比较
        std::shared_ptr<Object> result = Evaluator::evalInfix("<", left[i], right[i]);
        // 如果出现错误则直接返回错误对象
        if (Evaluator::isError(result))
            return result;
        // 然后返回比较结果对象
        return result;
    }
    // 如果遍历完了还没有返回结果则返回left.size()<right.size()的结果
    return Object::newBool(left.size() < right.size());
}

// 列表大于比较判断函数
std::shared_ptr<Object> Math::List::gt(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right)
{
    for (int64_t i = 0; i < left.size() && i < right.size(); ++i)
    {
        // 如果左右两个对象相等则继续比较下一个对象
        if (Object::isEqual(left[i], right[i]))
            continue;
        // 对左右两个对象进行大于比较
        std::shared_ptr<Object> result = Evaluator::evalInfix(">", left[i], right[i]);
        // 如果出现错误则直接返回错误对象
        if (Evaluator::isError(result))
            return result;
        // 然后返回比较结果对象
        return result;
    }
    // 如果遍历完了还没有返回结果则返回left.size()>right.size()的结果
    return Object::newBool(left.size() > right.size());
}

// 列表小于等于比较判断函数
std::shared_ptr<Object> Math::List::le(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right)
{
    for(int64_t i = 0; i < left.size() && i < right.size(); ++i)
    {
        // 如果左右两个对象相等则继续比较下一个对象
        if (Object::isEqual(left[i], right[i]))
            continue;
        // 对左右两个对象进行小于等于比较
        std::shared_ptr<Object> result = Evaluator::evalInfix("<=", left[i], right[i]);
        // 如果出现错误则直接返回错误对象
        if (Evaluator::isError(result))
            return result;
        // 然后返回比较结果对象
        return result;
    }
    // 如果遍历完了还没有返回结果则返回left.size()<=right.size()的结果
    return Object::newBool(left.size() <= right.size());
}

// 列表大于等于比较判断函数
std::shared_ptr<Object> Math::List::ge(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right)
{
     for(int64_t i = 0; i < left.size() && i < right.size(); ++i)
    {
        // 如果左右两个对象相等则继续比较下一个对象
        if (Object::isEqual(left[i], right[i]))
            continue;
        // 对左右两个对象进行大于等于比较
        std::shared_ptr<Object> result = Evaluator::evalInfix(">=", left[i], right[i]);
        // 如果出现错误则直接返回错误对象
        if (Evaluator::isError(result))
            return result;
        // 然后返回比较结果对象
        return result;
    }
    // 如果遍历完了还没有返回结果则返回left.size()<=right.size()的结果
    return Object::newBool(left.size() >= right.size());
}

// 列表等于比较判断函数
std::shared_ptr<Object> Math::List::eq(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right)
{
    // 如果两个列表指向同一个对象则返回true
    if (&left == &right)
        return Object::newBool(true);
    // 如果长度不相等则返回false
    if (left.size() != right.size())
        return Object::newBool(false);
    // 遍历列表
    for (int64_t i = 0; i < left.size(); ++i)
    {
        // 如果不相等则返回false对象
        if (!Object::isEqual(left[i], right[i]))
            return Object::newBool(false);
    }
    // 返回true对象
    return Object::newBool(true);
}

// 列表不等于比较判断函数
std::shared_ptr<Object> Math::List::ne(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right)
{
    // 如果两个列表指向同一个对象则返回false
    if (&left == &right)
        return Object::newBool(false);
    // 如果长度不相等则返回true
    if (left.size() != right.size())
        return Object::newBool(true);
    // 遍历列表
    for (int64_t i = 0; i < left.size(); ++i)
    {
        // 如果不相等则返回true对象
        if (!Object::isEqual(left[i], right[i]))
            return Object::newBool(true);
    }
    // 返回false对象
    return Object::newBool(false);
}

// 列表中缀表达式计算函数
std::vector<std::shared_ptr<Object>> Math::List::evalListExpInfix(const std::string &op, const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right)
{
    return listExpInfixFns.at(op)(left, right);
}

// 列表中缀比较表达式计算函数
std::shared_ptr<Object> Math::List::evalListCmpInfix(const std::string &op, const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right)
{
    return listCmpInfixFns.at(op)(left, right);
}

// 中缀运算符有效性判断函数
bool Math::List::isValidInfixOp(const std::string &op)
{
    return isValidExpInfixOp(op) || isValidCmpInfixOp(op);
}

// 中缀表达式运算符有效性判断函数
bool Math::List::isValidExpInfixOp(const std::string &op)
{
    return listExpInfixFns.find(op) != listExpInfixFns.end();
}

// 中缀比较运算符有效性判断函数
bool Math::List::isValidCmpInfixOp(const std::string &op)
{
    return listCmpInfixFns.find(op) != listCmpInfixFns.end();
}
