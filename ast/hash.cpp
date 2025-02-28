#include <ast/hash.h>
using namespace cpy::ast;
// 空参构造函数
Hash::Hash() : Expression(NODE_HASH)
{
}

// 获取哈希表节点的JSON表示函数
Value Hash::getJson() const
{
    // 创建JSON对象
    Value json;
    // 设置哈希节点JSON对象名称
    json["type"] = getName();
    // 设置哈希表的键值对
    Value pairsJson;
    // 遍历哈希表
    for (auto &pair : this->pairs)
    {
        // 创建键值对的JSON
        Value item;
        // 设置键值对的JSON表示
        item["key"] = pair.first->getJson();
        item["value"] = pair.second->getJson();
        // 添加到键值对表JSON数组中
        pairsJson.append(item);
    }
    // 添加到键值对JSON对象中
    json["pairs"] = pairsJson;
    // 返回哈希表节点的JSON对象
    return json;
}