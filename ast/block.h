#pragma once
#include <ast/node.h>
namespace cpy
{
    namespace ast
    {
        // 代码块节点
        class Block : public Statement
        {
        public:
            /* 构造函数 */
            // 默认构造函数
            Block();

            /* 析构函数 */
            ~Block() = default;

            /* 公有成员函数 */
            virtual Value getJson() const;                   // 获取代码块节点的JSON表示函数
            void appendBlock(const std::shared_ptr<Block> &block); // 添加代码块节点函数

        public:
            /* 公有成员变量 */
            std::list<std::shared_ptr<Statement>> statements; // 语句列表
        };
    }
}