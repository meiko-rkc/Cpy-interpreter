#pragma once
#include <ast/node.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace ast
    namespace ast
    {
        // 定义程序类,继承自语句类
        class Program : public Statement
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Program();

            /* 析构函数 */
            ~Program() = default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取节点的JSON表示函数
            
        public:
            /* 公有成员变量 */
            std::list<std::shared_ptr<Statement>> statements; // 语句列表
        };
    }
}