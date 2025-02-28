#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义字符串结点类,继承自表达式类
        class String : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            String();

            /* 析构函数 */
            ~String() = default;

            /* 公有成员函数 */
            // 获取节点的JSON表示函数
            virtual Value getJson() const;

        public:
            /* 公有成员变量 */
            std::string value; // 字符串值
        };
    }
}