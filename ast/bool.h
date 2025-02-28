#pragma once
#include <ast/node.h>
// 一级命名空间   namespace pi
namespace cpy
{
    // 二级命名空间   namespace ast
    namespace ast
    {
        // 定义布尔值结点派生类
        class Bool : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Bool();

            /* 析构函数 */
            ~Bool() = default;
            
            /* 公有成员函数 */
            virtual Value getJson() const; // 获取布尔节点的JSON表示函数
        
        public:
            /* 公有成员变量 */
            bool value; // 布尔值
        };
    }
}