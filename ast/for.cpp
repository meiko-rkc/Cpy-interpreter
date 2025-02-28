#include <ast/for.h>
using namespace cpy::ast;
// 空参构造函数
For::For() : Expression(NODE_FOR)
{
}

// 获取For节点的JSON表示函数
Value For::getJson() const
{
    // 创建JSON对象
    Value json;
    // 添加节点类型
    json["type"] = getName();
    // 创建For节点初始条件表达式、条件表达式、步长表达式和循环体代码块的JSON表示
    Value startersJson;
    for (auto &start : starters)
    {
        startersJson.append(start->getJson());
    }
    Value conditionsJson;
    for (auto &condition : conditions)
    {
        conditionsJson.append(condition->getJson());
    }
    Value closersJson;
    for (auto &close : closers)
    {
        closersJson.append(close->getJson());
    }
    // 添加For节点初始条件表达式、条件表达式、步长表达式和循环体代码块的JSON表示
    json["starters"] = startersJson;
    json["conditions"] = conditionsJson;
    json["closers"] = closersJson;
    json["block"] = body->getJson();
    // 返回For结点JSON对象
    return json;
}
