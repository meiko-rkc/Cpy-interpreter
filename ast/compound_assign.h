#pragma once
#include <ast/node.h>
// 一级命名空间   namespace pi
namespace cpy
{
    // 二级命名空间   namespace ast
    namespace ast
    {
        // 定义复合赋值表达式节点类，继承自表达式节点类
        class CompoundAssign : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            CompoundAssign();

            /* 析构函数 */
            ~CompoundAssign() = default;
            
            /* 公有成员函数 */
            virtual Value getJson() const; // 获取标识符节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::string op; // 运算符
            std::shared_ptr<Expression> left;  // 左表达式
            std::shared_ptr<Expression> right; // 右表达式
        };
    }
}