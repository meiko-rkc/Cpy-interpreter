#include <ast/identifier.h>
using namespace cpy::ast;
// 空参构造函数
Identifier::Identifier():Expression(NODE_IDENTIFIER)
{
}

// 获取标识符节点的JSON表示函数
Value Identifier::getJson() const
{
    Value json;
    json["type"] = getName();
    json["value"] = value;
    return json;
}