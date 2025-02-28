#include <ast/continue.h>
using namespace cpy::ast;
// 空参构造函数
Continue::Continue():Statement(NODE_CONTINUE)
{
}

// 获取continue节点的JSON表示函数
Value Continue::getJson() const
{
   // 构造JSON对象
    Value json;
    // 设置类型
    json["type"]=getName();
    // 返回continue结点的JSON对象
    return json;
}
