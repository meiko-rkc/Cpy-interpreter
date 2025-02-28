#include <object/bool_obj.h>
#include "bool_obj.h"
using namespace cpy::object;
// 前缀运算符函数映射表
const std::unordered_map<std::string, Bool::prefixFn> Bool::prefixFns={
    {"!", &Bool::lognot},
};

// 中缀运算符函数映射表
const std::unordered_map<std::string, Bool::infixFn> Bool::infixFns={
    {"&&", &Bool::logand},
    {"||", &Bool::logor},
};

// 空参构造函数
Bool::Bool()
{
    init(false);
}

// 带参构造函数
Bool::Bool(bool value)
{
    init(value);
}

// 初始化函数
void Bool::init(bool value)
{
    // 设置对象类型和整数值
    this->type = OBJECT_BOOL;
    this->value = value;
}

// 布尔对象字符串化函数
std::string Bool::toString() const
{
    return value ? "true" : "false";
}

// 布尔对象打印函数
void Bool::print() const
{
    std::cout << (value ? "true" : "false") << std::endl;
}

// 布尔对象哈希键值获取函数
HashKey Bool::hashKey() const
{
    return HashKey(type, std::hash<bool>()(value));
}

// 前缀运算符函数
std::shared_ptr<Object> Bool::prefix(const std::string &op, const std::shared_ptr<Object> &self)
{
    // 查找运算符函数
    std::unordered_map<std::string, prefixFn>::const_iterator it = prefixFns.find(op);
    // 如果找到运算符函数
    if(it != prefixFns.end())
        // 返回运算符函数的结果
        return it->second(self);
    // 返回空对象指针
    return newError("unknown operator: %s '%s'", op.c_str(), self->getName().c_str());
}

// 中缀运算符函数
std::shared_ptr<Object> Bool::infix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 查找运算符函数
    std::unordered_map<std::string, infixFn>::const_iterator it = infixFns.find(op);
    // 如果找到运算符函数
    if(it!= infixFns.end())
        // 返回运算符函数的结果
        return it->second(left, right);
    // 返回空对象指针
    return newError("unknown operator: '%s' %s '%s'", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 逻辑非运算符函数
std::shared_ptr<Object> Bool::lognot(const std::shared_ptr<Object> &self)
{
    // 将对象指针转为布尔对象指针
    std::shared_ptr<Bool> boolSelf = std::static_pointer_cast<Bool>(self);
    // 创建新的布尔对象
    return newBool(!boolSelf->value);
}

// 逻辑与运算符函数
std::shared_ptr<Object> Bool::logand(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 如果左对象是错误对象
    if(isError(left))
        return left;
    // 将左对象指针转为布尔对象指针
    std::shared_ptr<Bool> boolLeft = std::dynamic_pointer_cast<Bool>(toBool(left));
    // 如果左对象是假值，返回左对象
    if(!boolLeft->value)
        return boolLeft;
    // 如果右对象是错误对象
    if(isError(right))
        return right;
    // 返回右对象对应的布尔对象
    return toBool(right);
}


// 逻辑或运算符函数
std::shared_ptr<Object> Bool::logor(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 如果左对象是错误对象
    if(isError(left))
        return left;
    // 将左对象指针转为布尔对象指针
    std::shared_ptr<Bool> boolLeft = std::dynamic_pointer_cast<Bool>(toBool(left));
    // 如果左对象是真值，返回左对象
    if(boolLeft->value)
        return boolLeft;
    // 如果右对象是错误对象
    if(isError(right))
        return right;
    // 返回右对象对应的布尔对象
    return toBool(right);
}
