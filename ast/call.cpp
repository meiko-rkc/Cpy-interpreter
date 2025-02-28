#include <ast/call.h>
using namespace cpy::ast;
// 空参构造函数
Call::Call() : Expression(NODE_CALL)
{
}

// 获取Call节点的JSON表示函数
Value Call::getJson() const
{
    // 创建Call结点JSON对象
    Value json;
    // 添加节点类型和函数表达式和参数列表的JSON表示
    json["type"] = getName();
    json["function"] = function->getJson();
    // 创建参数列表的JSON表示
    Value argsJson;
    // 遍历参数列表，将每个参数的JSON表示添加到参数列表的JSON表示中
    for (auto &arg : arguments)
        argsJson.append(arg->getJson());
    // 将参数列表的JSON表示添加到Call结点的JSON表示中
    json["arguments"] = argsJson;
    // 返回Call结点的JSON表示
    return json;
}