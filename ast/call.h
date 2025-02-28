#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义Call函数调用节点类，继承自Expression节点类
        class Call : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Call();

            /* 析构函数 */
            ~Call() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取Call节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::shared_ptr<Expression> function;               // 函数表达式
            std::vector<std::shared_ptr<Expression>> arguments; // 参数列表
        };
    }
}