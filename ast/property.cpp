#include <ast/property.h>
using namespace cpy::ast;
// 空参构造函数
Property::Property(): Expression(NODE_PROPERTY)
{
}

// 获取属性节点的JSON表示函数
Value Property::getJson() const
{
    // 创建属性结点JSON对象
    Value value;
    // 添加属性结点JSON对象的类型，对象和属性名JSON对象
    value["type"] = getName();
    value["object"] = object->getJson();
    value["property"] = property->getJson();
    // 返回属性结点JSON对象
    return value;
}