#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义属性类，继承自Expression类
        class Property : public Expression
        {
        public:
            /* 构造函数 */
            // 默认构造函数
            Property();

            /* 析构函数 */
            ~Property() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取属性节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::shared_ptr<Expression> object;   // 接收者对象
            std::shared_ptr<Expression> property; // 属性名
        };
    }
}