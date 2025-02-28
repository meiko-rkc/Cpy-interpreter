#include <ast/Index.h>
using namespace cpy::ast;
// 空参构造函数
Index::Index():Expression(NODE_INDEX)
{
}

Value Index::getJson() const
{
    // 创建JSON对象
    Value json;
    // 添加节点类型，左操作数和索引值
    json["type"]=getName();
    json["left"]=left->getJson();
    json["index"]=index->getJson();
    // 返回JSON对象
    return json;
}
