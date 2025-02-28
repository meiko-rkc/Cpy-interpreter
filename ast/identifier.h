#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义标识符类，继承自表达式类
        class Identifier:public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Identifier();

            /* 析构函数 */
            ~Identifier() = default;
            
            /* 公有成员函数 */
            virtual Value getJson() const; // 获取标识符节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::string value; // 字符串值
        };
    }
}