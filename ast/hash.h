#pragma once
#include <ast/node.h>
namespace cpy
{
    namespace ast
    {
        class Hash : public Expression
        {
        public:
            /* 构造函数 */
            Hash();

            /* 析构函数 */
            ~Hash() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取哈希节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::unordered_map<std::shared_ptr<Expression>, std::shared_ptr<Expression>> pairs; // 键值对
        };
    }
}