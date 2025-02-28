#include <ast/assign.h>
using namespace cpy::ast;
// 空参构造函数
Assign::Assign():Expression(NODE_ASSIGN)
{
}

// 获取赋值表达式节点的JSON表示函数
Value Assign::getJson() const
{
    // 构造JSON对象
    Value json;
    // 获取节点名称
    json["type"]=getName();
    // 设置标识符名称和其对应值表达式的JSON表示
    json["name"]=name->getJson();
    json["value"]=value->getJson();
    // 返回赋值结点的JSON对象
    return json;
}