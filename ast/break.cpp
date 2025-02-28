#include <ast/break.h>
using namespace cpy::ast;
// 空参构造函数
Break::Break():Statement(NODE_BREAK)
{
}

// Break结点的JSON表示函数
Value Break::getJson() const
{
    // 构造JSON对象
    Value json;
    // 设置类型
    json["type"]=getName();
    // 返回Break结点的JSON对象
    return json;
}
