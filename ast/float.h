#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 一级命名空间 namespace ast
    namespace ast
    {
        // 定义浮点数节点类
        class Float : public Expression
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Float();

            /* 析构函数 */
            ~Float() = default;
            
            /* 公有成员函数 */
            virtual Value getJson() const; // 获取浮点数节点的JSON表示函数

        public:
            /* 公有成员变量 */
            double value; // 浮点数值
        };
    }
}