#include <ast/infix.h>
using namespace cpy::ast;
// 空参构造函数
Infix::Infix(): Expression(NODE_INFIX)
{
}

// 中缀表达式结点信息JSON表示函数
Value Infix::getJson() const
{
    // 创建JSON对象，并添加结点类型，运算符和左右子树结表达式JSON信息
    Value json;
    json["type"] = getName();
    json["op"] = op;
    json["left"] = left->getJson();
    json["right"] = right->getJson();
    // 返回中缀表达式结点JSON表示
    return json;
}
