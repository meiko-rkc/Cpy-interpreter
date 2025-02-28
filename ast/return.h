#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义Return节点类，继承自Statement结点类
        class Return : public Statement
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Return();

            /* 析构函数 */
            ~Return() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取Return节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::shared_ptr<Expression> value; // Return语句的值
        };
    }
}