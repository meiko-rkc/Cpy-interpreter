#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义空对象类,继承自表达式类
        class Null:public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Null();

            /* 析构函数 */
            ~Null() = default;

            /* 公有成员函数 */
            // 获取null节点的JSON表示函数
            virtual Value getJson() const;
        };
    }
}