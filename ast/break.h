#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义break节点类，继承自语句结点类
        class Break:public Statement
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Break();

            /* 析构函数 */
            ~Break()=default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取break节点的JSON表示函数
        };
    }
}