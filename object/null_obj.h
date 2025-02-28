#pragma once
#include <object/base_obj.h>
#include <object/hashable.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace object
    namespace object
    {
        // 定义空对象类,继承自对象基类
        class Null : public Object, public Hashable
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Null();

            /* 析构函数 */
            ~Null()=default;

            /* 公有成员函数 */
            virtual void print() const;            // 整数对象打印函数
            virtual std::string toString() const;  // 整数对象数值字符串化函数
            virtual HashKey hashKey() const;
        };
    }
}