#include <ast/ternary.h>
using namespace cpy::ast;
// 空参构造函数
Ternary::Ternary():Expression(NODE_TERNARY)
{
}

// 三目运算符结点的JSON表示函数
Value Ternary::getJson() const
{
    // 创建JSON对象
    Value json;
    // 分别设置JSON对像类型、条件、真假表达式的JSON表示
    json["type"] = getName();
    json["condition"] = condition->getJson();
    json["if_true"] = trueExpr->getJson();
    json["if_false"] = falseExpr->getJson();
    // 返回三目运算符JSON对象
    return json;
}
