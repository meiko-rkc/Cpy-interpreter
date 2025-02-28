#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义前缀表达式类
        class Prefix : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Prefix();

            /* 析构函数 */
            ~Prefix() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取前缀节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::string op;                    // 运算符
            std::shared_ptr<Expression> right; // 右操作数
        };
    }
}