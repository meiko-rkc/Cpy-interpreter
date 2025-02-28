#include <ast/scenario.h>
using namespace cpy::ast;
// 空参构造函数
Scenario::Scenario():Expression(NODE_SCENARIO)
{
}

// 获取场景结点的json表示函数
Value Scenario::getJson() const
{
    // 创建场景结点json对象
    Value json;
    // 添加场景结点json对象的类型，条件，以及代码块对应的json对象
    json["type"]=getName();
    json["condition"]=condition->getJson();
    json["body"]=body->getJson();
    // 返回场景结点json对象
    return json;
}