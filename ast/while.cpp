#include <ast/while.h>
using namespace cpy::ast;
// 空参构造函数
While::While():Expression(NODE_WHILE)
{
}

// 获取while结点的JSON表示函数
Value While::getJson() const
{
    // 创建一个JSON对象
    Value json;
    // 向while结点的JSON对象中添加类型，条件表达式和代码块的JSON表示
    json["type"] = getName();
    json["condition"] = condition->getJson();
    json["body"] = body->getJson();
    // 返回while结点的JSON对象
    return json;
}
