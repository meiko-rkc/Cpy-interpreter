#include <ast/block.h>
#include "block.h"
using namespace cpy::ast;
// 公有成员函数
Block::Block():Statement(NODE_BLOCK)
{
}

// 获取代码块结点的Json表示函数
Value Block::getJson() const
{
    // 构造Json对象
    Value json;
    // 构造代码块内语句列表Json对象
    Value stmtsJson;
    // 添加代码块结点类型到Json对象中
    json["type"] = getName();
    // 遍历代码块内语句列表，将每个语句的Json表示添加到代码块内语句列表Json对象中
    for(auto& statement:statements)
        stmtsJson.append(statement->getJson());
    // 将代码块内语句列表Json对象添加到代码块结点的Json对象中，并返回代码块结点的Json对象
    json["statements"] = stmtsJson;
    return json;
}

// 添加代码块语句函数
void Block::appendBlock(const std::shared_ptr<Block> &block)
{
    // 将代码块语句添加到代码块内语句列表中
    statements.splice(statements.end(),block->statements);
}