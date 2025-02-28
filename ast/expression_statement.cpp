#include <ast/expression_statement.h>
using namespace cpy::ast;
// 空参构造函数
ExpressionStatement::ExpressionStatement(): Statement(NODE_EXPRESSION_STATEMENT)
{
}

// 结点信息JSON表示函数
Value ExpressionStatement::getJson() const
{
    Value json;
    json["type"] = getName();
    json["expression"] = expr->getJson();
    return json;
}
