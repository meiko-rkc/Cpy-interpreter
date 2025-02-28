#pragma once
#include <ast/node.h>
#include <ast/block.h>
// 一级命名空间   namespace pi
namespace cpy
{
    // 二级命名空间   namespace ast
    namespace ast
    {
        // 定义For类结点，继承自Expression类
        class For : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            For();

            /* 析构函数 */
            ~For() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取For节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::vector<std::shared_ptr<Expression>> starters;   // for循环起始表达式
            std::vector<std::shared_ptr<Expression>> conditions; // for循环条件表达式
            std::vector<std::shared_ptr<Expression>> closers;    // for循环步长表达式
            std::shared_ptr<Block> body;                         // for循环循环体代码块
        };
    }
}