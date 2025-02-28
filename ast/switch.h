#pragma once
#include <ast/case.h>
namespace cpy
{
    namespace ast
    {
        class Switch : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Switch();

            /* 析构函数 */
            ~Switch() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取switch节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::shared_ptr<Expression> value;      // switch语句的值
            std::list<std::shared_ptr<Case>> cases; // case节点的列表
        };
    }
}