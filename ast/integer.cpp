#include <ast/integer.h>
using namespace cpy::ast;
// 空参构造函数
Integer::Integer(): Expression(NODE_INTEGER)
{
}

// 整数结点信息JSON表示函数
Value Integer::getJson() const
{
    // 生成JSON对象，并添加结点类型和值信息
    Value json;
    json["type"] = getName();
    json["value"] = value;
    // 返回整数结点的JSON对象
    return json;
}
