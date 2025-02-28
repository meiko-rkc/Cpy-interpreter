#pragma once
#include <ast/node.h>
namespace cpy
{
    namespace ast
    {
        class In : public Expression
        {
        public:
            /* 构造函数 */
            In();
            
            /* 析构函数 */
            ~In()=default;

            /* 公有成员函数 */
            virtual Value getJson() const; // 获取in节点的JSON表示函数
        
        public:
            /* 公有成员变量 */
            std::shared_ptr<Expression> left;  // 左操作数
            std::shared_ptr<Expression> right; // 右操作数
        };
    }
}