#include <ast/in.h>
using namespace cpy::ast;
// 空参构造函数
In::In():Expression(NODE_IN)
{
}

// 获取in节点的JSON表示函数
Value In::getJson() const
{
    // 构造JSON对象
    Value json;
    // 设置节点名称，并设置其左右操作数的JSON表示
    json["type"]=getName();
    json["left"]=left->getJson();
    json["right"]=right->getJson();
    // 返回JSON对象
    return json;
}