#include <ast/compound_assign.h>
using namespace cpy::ast;
// 空参构造函数
CompoundAssign::CompoundAssign():Expression(NODE_COMPOUND_ASSIGN)
{
}

// 复合赋值表达式类的Json表示函数
Value CompoundAssign::getJson() const
{
    // 创建Json对象
    Value json;
    // 添加类型和运算符，并添加左值和右值的Json表示
    json["type"] = getName();
    json["operator"] = op;
    json["left"] = left->getJson();
    json["right"] = right->getJson();
    // 返回Json对象
    return json;
}
