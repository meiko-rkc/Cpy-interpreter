#pragma once
#include <ast/node.h>
#include <ast/block.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义While类，继承自表达式类
        class While:public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            While();

            /* 析构函数 */
            ~While()=default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取while结点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::shared_ptr<Expression> condition; // 条件表达式结点
            std::shared_ptr<Block> body;           // 代码块结点
        };
    }
}