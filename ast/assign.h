#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义赋值表达式类，继承自表达式类
        class Assign:public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Assign();

            /* 析构函数 */
            ~Assign() = default;
            
            /* 公有成员函数 */
            virtual Value getJson() const; // 获取赋值表达式节点的JSON表示函数
        
        public:
            /* 公有成员变量 */
            std::shared_ptr<Expression> name;  // 左值表达式（标识符名）
            std::shared_ptr<Expression> value; // 右值表达式
        };
    }
}