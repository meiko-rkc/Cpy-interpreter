#include <ast/string.h>
// 空参构造函数
cpy::ast::String::String():Expression(NODE_STRING)
{
}

// 获取节点的JSON表示函数
Value cpy::ast::String::getJson() const
{
    // 构造JSON对象
    Value json;
    // 填充JSON对象，设置类型和值
    json["type"] = getName();
    json["value"] = value;
    // 返回字符串结点JSON对象
    return json;
}