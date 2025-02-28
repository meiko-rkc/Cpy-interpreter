#include <ast/float.h>
using namespace cpy::ast;
// 空参构造函数
Float::Float():Expression(NODE_FLOAT)
{
}

// 获取浮点数节点的JSON表示函数
Value Float::getJson() const
{
    // 生成JSON对象，并添加结点类型和值信息
    Value json;
    json["type"] = getName();
    json["value"] = std::to_string(value);
    // 返回浮点数结点的JSON对象
    return json;
}
