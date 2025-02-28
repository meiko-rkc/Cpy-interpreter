#include <ast/null.h>
using namespace cpy::ast;
// 空参构造函数
Null::Null():Expression(NODE_NULL)
{
}

// 获取空值节点的JSON表示函数
Value Null::getJson() const
{
    // 生成JSON对象，并添加结点类型和值信息
    Value json;
    json["type"] = getName();
    // 返回空结点的JSON对象
    return json;
}
