#pragma once
#include <object/base_obj.h>
// 一级命名空间 namespace pi
namespace cpy 
{
    // 一级命名空间 namespace object
    namespace object
    {
        class Continue : public Object
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Continue();

            /* 析构函数 */
            ~Continue() = default;

            /* 公有成员函数 */
            virtual std::string toString() const; // continue对象字符串化函数
            virtual void print() const;           // continue对象打印函数
        };
    }
}