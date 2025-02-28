#include <ast/postfix.h>
using namespace cpy::ast;
// 空参构造函数
Postfix::Postfix():Expression(NODE_POSTFIX)
{
}

// 后缀表达式结点的JSON表示函数
Value Postfix::getJson() const
{
    // 初始化JSON对象
    Value json;
    // 设置结点类型,运算符,左子结点
    json["type"]=getName();
    json["operator"]=op;
    json["left"]=left->getJson();
    // 返回后缀结点的JSON对象
    return json;
}