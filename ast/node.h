#pragma once
#include <memory>
#include <list>
#include <token/token.h>
using namespace cpy::token;
// 一级命名空间   namespace pi
namespace cpy
{
    // 二级命名空间   namespace ast
    namespace ast
    {
        // 抽象语法树节点基类
        class Node
        {
        public:
            enum Type
            {
                NODE_INTEGER=0,             // 整数节点
                NODE_FLOAT,                 // 浮点数节点
                NODE_BOOL,                  // 布尔值节点
                NODE_STRING,                // 字符串节点
                NODE_NULL,                  // 空值节点
                NODE_LIST,                  // 列表节点
                NODE_HASH,                  // 哈希表节点
                NODE_INDEX,                 // 索引节点
                NODE_ASSIGN,                // 赋值表达式节点
                NODE_COMPOUND_ASSIGN,       // 复合赋值表达式节点
                NODE_IDENTIFIER,            // 标识符节点
                NODE_TERNARY,               // 三元表达式节点
                NODE_IF,                    // if语句节点
                NODE_SCENARIO,              // 场景节点
                NODE_SWITCH,                // switch语句节点
                NODE_CASE,                  // case语句节点
                NODE_FOR,                   // for循环节点
                NODE_WHILE,                 // while循环节点
                NODE_BREAK,                 // break语句节点
                NODE_CONTINUE,              // continue语句节点
                NODE_IN,                    // in运算符节点
                NODE_FUNCTION,              // 函数定义节点
                NODE_PROPERTY,              // 属性定义节点
                NODE_METHOD,                // 方法定义节点
                NODE_RETURN,                // return语句节点
                NODE_CALL,                  // 函数调用节点
                NODE_BLOCK,                 // 代码块节点
                NODE_PREFIX,                // 前缀表达式节点
                NODE_INFIX,                 // 中缀表达式节点
                NODE_POSTFIX,               // 后缀表达式节点
                NODE_EXPRESSION_STATEMENT,  // 表达式语句节点
                NODE_PROGRAM,               // 程序根节点
            };
            /* 构造函数 */
            // 默认构造函数
            Node();

            // 带参数的构造函数，用于初始化Node对象的type成员变量
            Node(Type type);

            // 拷贝构造函数
            Node(const Node& other);

            /* 析构函数 */
            virtual ~Node() = default;

            /* 公有成员函数 */
            Type getType() const;              // 获取节点类型函数
            std::string getName() const;       // 获取节点名称函数
            virtual Value getJson() const = 0; // 获取节点的JSON表示函数

        public:
            /* 私有成员变量 */
            Type type;                                                // 节点类型
            Token token;                                              // 节点对应的Token
            static const std::unordered_map<Type, std::string> names; // 节点类型对应的名称映射表
        };

        // 表达式结点派生类
        class Expression:public Node
        {
        public:
            /* 构造函数 */
            // 默认构造函数
            Expression();

            // 带参数的构造函数，用于初始化Expression对象的token成员变量
            Expression(Type type);

            // 拷贝构造函数
            Expression(const Expression& other);

            /* 析构函数 */
            ~Expression() = default;
        };

        class Statement:public Node
        {
        public:
            /* 构造函数 */
            // 默认构造函数
            Statement();

            // 带参数的构造函数，用于初始化Statement对象的token成员变量
            Statement(Type type);

            // 拷贝构造函数
            Statement(const Statement& other);

            /* 析构函数 */
            ~Statement() = default;
        };
    }
}