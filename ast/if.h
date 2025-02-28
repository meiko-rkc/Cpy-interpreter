#pragma once
#include <ast/node.h>
#include <ast/scenario.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        class If : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            If();

            /* 析构函数 */
            ~If() = default;

            /* 公有成员函数 */
            // 获取if节点的JSON表示函数
            virtual Value getJson() const;

        public:
            /* 公有成员变量 */
            std::list<std::shared_ptr<Scenario>> scenarios; // 场景列表
        };
    }
}
