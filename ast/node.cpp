#include <ast/node.h>
using namespace cpy::ast;
// 节点类型对应的名称映射表
const std::unordered_map<Node::Type, std::string> Node::names = {
    {Node::NODE_INTEGER, "Integer"},                          // 整数节点
    {Node::NODE_FLOAT, "Float"},                              // 浮点数节点
    {Node::NODE_BOOL, "Bool"},                                // 布尔值节点
    {Node::NODE_STRING, "String"},                            // 字符串节点
    {Node::NODE_NULL, "Null"},                                // 空值节点
    {Node::NODE_LIST, "List"},                                // 列表节点
    {Node::NODE_HASH, "Hash"},                                // 哈希表节点
    {Node::NODE_INDEX, "Index"},                              // 索引节点
    {Node::NODE_ASSIGN, "Assign"},                            // 赋值表达式节点
    {Node::NODE_COMPOUND_ASSIGN, "CompoundAssign"},           // 复合赋值表达式节点
    {Node::NODE_IDENTIFIER, "Identifier"},                    // 标识符节点
    {Node::NODE_TERNARY, "Ternary"},                          // 三元表达式节点
    {Node::NODE_IF, "If"},                                    // if语句节点
    {Node::NODE_SCENARIO, "Scenario"},                        // 场景节点
    {Node::NODE_SWITCH, "Switch"},                            // switch语句节点
    {Node::NODE_CASE, "Case"},                                // case节点
    {Node::NODE_WHILE, "While"},                              // while循环节点
    {Node::NODE_FOR, "For"},                                  // for循环节点
    {Node::NODE_BREAK, "Break"},                              // break语句节点
    {Node::NODE_CONTINUE, "Continue"},                        // continue语句节点
    {Node::NODE_IN, "In"},                                    // in运算符节点
    {Node::NODE_FUNCTION, "Function"},                        // 函数节点
    {Node::NODE_PROPERTY, "Property"},                        // 属性节点
    {Node::NODE_METHOD, "Method"},                            // 方法节点
    {Node::NODE_RETURN, "Return"},                            // return语句节点
    {Node::NODE_CALL, "Call"},                                // 函数调用节点
    {Node::NODE_BLOCK, "Block"},                              // 代码块节点
    {Node::NODE_PREFIX, "Prefix"},                            // 前缀表达式节点
    {Node::NODE_INFIX, "Infix"},                              // 中缀表达式节点
    {Node::NODE_POSTFIX, "Postfix"},                          // 后缀表达式节点
    {Node::NODE_EXPRESSION_STATEMENT, "ExpressionStatement"}, // 表达式语句节点
    {Node::NODE_PROGRAM, "Program"},                          // 程序根节点
};

// 节点空参构造函数
Node::Node()
{
}

// 节点带参构造函数
Node::Node(Type type) : type(type)
{
}

// 节点拷贝构造函数
Node::Node(const Node &other)
{
    // 检查自赋值
    if (this == &other)
        return;
    // 复制成员变量
    this->type = other.type;
    this->token = other.token;
}

// 获取节点类型
Node::Type Node::getType() const
{
    return type;
}

// 获取节点名称
std::string Node::getName() const
{
    if (names.find(type) != names.end())
        return names.at(type);
    return "";
}

// 表达式节点空参构造函数
Expression::Expression() : Node()
{
}

// 表达式节点带参构造函数
Expression::Expression(Type type) : Node(type)
{
}

// 表达式节点拷贝构造函数
Expression::Expression(const Expression &other) : Node(other)
{
}

// 语句节点空参构造函数
Statement::Statement() : Node()
{
}

// 语句节点带参构造函数
Statement::Statement(Type type) : Node(type)
{
}

// 语句节点拷贝构造函数
Statement::Statement(const Statement &other) : Node(other)
{
}
