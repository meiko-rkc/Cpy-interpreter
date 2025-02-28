#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义中缀表达式类,继承自表达式类
        class Infix:public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Infix();

            /* 析构函数 */
            ~Infix() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取节点的JSON表示函数
            
        public:
            /* 公有成员变量 */
            std::string op;                    // 操作符
            std::shared_ptr<Expression> left;  // 左操作数
            std::shared_ptr<Expression> right; // 右操作数
        };
    }
}