#include <ast/case.h>
using namespace cpy::ast;
// 空参构造函数
Case::Case():Expression(NODE_CASE)
{
}

// 获取case结点的JSON表示函数
Value Case::getJson() const
{
    // 创建json对象
    Value json;
    // 设置case结点的类型
    json["type"] = getName();
    // 创建case值列表对应的Json对象
    Value valuesJson;
    // 遍历values，并将其添加到case值列表对应的Json中
    for(auto& value:values)
        valuesJson.append(value->getJson());
    // 设置case值列表，代码块结点，是否为默认条件下的JSON对象
    json["values"] = valuesJson;
    json["body"] = body->getJson();
    json["default"] = isDefault? "true" : "false";
    // 返回case结点的JSON对象
    return json;
}
