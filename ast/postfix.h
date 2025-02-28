#pragma once
#include <ast/node.h>
namespace cpy
{
    namespace ast
    {
        class Postfix : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Postfix();

            /* 析构函数 */
            ~Postfix() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::string op;                   // 运算符
            std::shared_ptr<Expression> left; // 左操作数
        };
    }
}