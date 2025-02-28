#include <ast/if.h>
using namespace cpy::ast;
// 空参构造函数
If::If():Expression(NODE_IF)
{
}

// 获取if节点的JSON表示函数
Value If::getJson() const
{
    // 创建一个if结点的JSON对象，以及对应场景列表的JSON对象
    Value json;
    Value scenariosJson;
    // 添加结点类型名称到if结点的JSON对象中
    json["type"] = getName();
    // 遍历场景列表，获取每个场景的JSON表示，添加到场景列表的JSON对象中
    for (auto& scenario : scenarios)
        scenariosJson.append(scenario->getJson());
    // 将场景列表的JSON对象添加到if结点的JSON对象中
    json["scenarios"] = scenariosJson;
    // 返回if结点的JSON对象
    return json;
}
