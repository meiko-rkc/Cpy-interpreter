#pragma once
#include <ast/node.h>
#include <ast/block.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义场景结点类,继承自表达式类
        class Scenario : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Scenario();

            /* 析构函数 */
            ~Scenario() = default;

            /* 公有成员函数 */
            // 获取场景节点的JSON表示函数
            virtual Value getJson() const;

        public:
            /* 公有成员变量 */
            std::shared_ptr<Expression> condition;
            std::shared_ptr<Block> body;
        };
    }
}