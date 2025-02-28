#include <ast/return.h>
using namespace cpy::ast;
// 空参构造函数
Return::Return():Statement(NODE_RETURN)
{
}

// Return结点的JSON表示函数
Value Return::getJson() const
{
    // 构造JSON对象
    Value json;
    // 设置类型
    json["type"]=getName();
    // 设置值
    json["value"]=value->getJson();
    // 返回Return结点的JSON对象
    return json;
}
