#pragma once
#include <ast/node.h>
#include <ast/identifier.h>
#include <ast/block.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        class Function : public Identifier
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Function();

            /* 析构函数 */
            ~Function() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取Function节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::vector<std::shared_ptr<ast::Identifier>> parameters;              // 参数列表
            std::unordered_map<std::string, std::shared_ptr<Expression>> defaults; // 默认参数
            std::shared_ptr<ast::Block> body;                                      // 函数体
        };
    }
}