#include <ast/program.h>
using namespace cpy::ast;
// 空参构造函数
Program::Program(): Statement(NODE_PROGRAM)
{
}

// 程序根节点信息JSON表示函数
Value Program::getJson() const
{
    // 根节点信息JSON表示
    Value json;
    json["type"] = getName();
    // 将所有语句的JSON表示添加到根节点信息JSON表示中
    Value stmts;
    for(std::list<std::shared_ptr<Statement>>::const_iterator it = statements.begin(); it != statements.end(); it++)
        stmts.append((*it)->getJson());
    json["statements"] = stmts;
    // 返回根节点信息JSON表示
    return json;
}
