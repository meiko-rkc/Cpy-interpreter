#pragma once
#include <ast/node.h>
#include <ast/block.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义Case节点类，继承自Expression结点类
        class Case : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Case();

            /* 析构函数 */
            ~Case() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取case节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::list<std::shared_ptr<Expression>> values; // case结点相匹配的值
            std::shared_ptr<Block> body;                   // case结点的代码块
            bool isDefault = false;                        // 是否是default结点
        };
    }
}