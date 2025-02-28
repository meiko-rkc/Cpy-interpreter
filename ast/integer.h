#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义整数类,继承自表达式类
        class Integer : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Integer();

            /* 析构函数 */
            ~Integer() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取节点的JSON表示函数

        public:
            /* 公有成员变量 */
            int64_t value; // 整数值
        };
    }
}