#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义列表对象类,继承自表达式类
        class List : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            List();

            /* 析构函数 */
            ~List() = default;

            /* 公有成员函数 */
            // 获取list节点的JSON表示函数
            virtual Value getJson() const;

        public:
            /* 公有成员变量 */
            std::vector<std::shared_ptr<Expression>> elements; // 列表元素列表
        };
    }
}