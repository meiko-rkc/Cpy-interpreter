#include <ast/switch.h>
using namespace cpy::ast;
// 空参构造函数
Switch::Switch():Expression(NODE_SWITCH)
{
}

// 获取switch结点的JSON表示函数
Value Switch::getJson() const
{
    // 创建JSON对象
    Value json;
    // 设置switch结点JSON的类型和对应取值
    json["type"]=getName();
    json["value"]=value->getJson();
    // 遍历cases结点，将其JSON表示添加到cases对应的Json对象结点中
    Value casesJson;
    for(auto& c:cases)
        casesJson.append(c->getJson());
    // 将cases结点JSON表示添加到switch结点JSON对象中
    json["cases"]=casesJson;
    // 返回switch结点JSON对象
    return json;
}