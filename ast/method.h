#pragma once
#include <ast/node.h>
// 一级命名空间   namespace pi
namespace cpy
{
    // 二级命名空间   namespace ast
    namespace ast
    {
        // 定义方法类，继承自Expression类
        class Method : public Expression
        {
        public:
            /* 构造函数 */
            // 默认构造函数
            Method();

            /* 析构函数 */
            ~Method() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取method节点的JSON表示函数

        public:
            /* 公有成员变量 */
            std::shared_ptr<Expression> object;                 // 接收者对象
            std::shared_ptr<Expression> method;                 // 方法名
            std::vector<std::shared_ptr<Expression>> arguments; // 参数列表
        };
    }
}