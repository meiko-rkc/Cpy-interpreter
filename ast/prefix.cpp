#include <ast/prefix.h>
using namespace cpy::ast;
// 空参构造函数
Prefix::Prefix():Expression(NODE_PREFIX)
{
}

// 获取前缀表达式的JSON表示函数
Value Prefix::getJson() const
{
    // 创建一个JSON对象
    Value json;
    // 将类型、运算符和右操作数添加到JSON对象中并返回
    json["type"]=getName();
    json["operator"]=op;
    json["right"]=right->getJson();
    // 返回前缀结点JSON对象
    return json;
}
