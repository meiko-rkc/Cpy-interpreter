#include <ast/method.h>
using namespace cpy::ast;
// 空参构造函数
Method::Method():Expression(NODE_METHOD)
{
}

// 获取method节点的JSON表示函数
Value Method::getJson() const
{
    // 创建方法结点JSON对象
    Value json;
    // 添加方法结点JSON对象的类型，对象和方法名JSON对象
    json["type"] = getName();
    json["object"] = object->getJson();
    json["method"] = method->getJson();
    // 创建参数列表JSON对象
    Value argsJson;
    // 遍历参数列表，将参数节点的JSON表示添加到参数列表JSON对象中
    for (auto &arg : arguments)
    {
        argsJson.append(arg->getJson());
    }
    // 添加参数列表JSON对象到方法结点JSON对象中
    json["arguments"] = argsJson;
    // 返回方法结点JSON对象
    return json;
}
