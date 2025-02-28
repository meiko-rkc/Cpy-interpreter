#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义表达式语句类,继承自语句类
        class ExpressionStatement : public Statement
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            ExpressionStatement();

            /* 析构函数 */
            ~ExpressionStatement() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取节点的JSON表示函数
            
        public:
            /* 公有成员变量 */
            std::shared_ptr<Expression> expr; // 表达式
        };
    }
}