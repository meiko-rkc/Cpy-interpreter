#include <ast/function.h>
using namespace cpy::ast;
// 空参构造函数
Function::Function()
{
    type = NODE_FUNCTION;
}

// 获取Function节点的JSON表示函数
Value Function::getJson() const
{
    // 创建Function结点JSON对象
    Value json;
    // 设置Function结点的类型名称
    json["type"] = getName();
    // 设置Function结点的函数名称
    json["name"] = value;
    // 创建Function结点的参数列表JSON对象
    Value paramsJson;
    // 遍历Function结点的参数列表，将每个参数的JSON表示添加到参数列表JSON对象中
    for (auto& param : parameters)
        paramsJson.append(param->getJson());
    // 将参数列表JSON对象添加到Function结点的JSON对象中
    json["parameters"] = paramsJson;
    // 创建Function结点的默认参数列表JSON对象
    Value defaultsJson;
    // 遍历Function结点的默认参数列表，将每个默认参数的参数名及其JSON对应表示添加到默认参数列表JSON对象中
    for(auto& param:defaults)
        defaultsJson[param.first] = param.second->getJson();
    // 将默认参数列表JSON对象添加到Function结点的JSON对象中
    json["defaults"] = defaultsJson;
    // 将Function结点的函数体的JSON表示添加到Function结点的JSON对象中
    json["body"] = body->getJson();
    // 返回Function结点的JSON对象
    return json;
}