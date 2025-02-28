#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义三元表达式结点类,继承自表达式类
        class Ternary : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Ternary();

            /* 析构函数 */
            ~Ternary() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取三目运算节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::shared_ptr<Expression> condition; // 条件表达式
            std::shared_ptr<Expression> trueExpr;  // 条件为真时的表达式
            std::shared_ptr<Expression> falseExpr; // 条件为假时的表达式
        };
    }
}