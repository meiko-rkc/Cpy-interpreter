#include <ast/bool.h>
using namespace cpy::ast;
// 空参构造函数
Bool::Bool():Expression(NODE_BOOL)
{
}

// 获取浮点数节点的JSON表示函数
Value Bool::getJson() const
{
    // 构造JSON对象
    Value json;
    // 设置类型和布尔值
    json["type"]=getName();
    json["value"]=value?"true":"false";
    return json;
}
