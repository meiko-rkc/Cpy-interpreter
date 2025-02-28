#include <ast/list.h>
using namespace cpy::ast;
// 空参构造函数
List::List() : Expression(NODE_LIST)
{
}

// 获取list节点的JSON表示函数
Value List::getJson() const
{
    // 创建一个JSON对象
    Value json;
    // 添加节点类型
    json["type"] = getName();
    // 创建一个表示列表元素的JSON对象
    Value elementsJson;
    for (auto &element : elements)
        elementsJson.append(element->getJson());
    // 添加列表元素
    json["elements"] = elementsJson;
    // 返回list结点JSON对象
    return json;
}
