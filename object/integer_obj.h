#pragma once
#include <object/base_obj.h>
#include <object/hashable.h>
// 一级命名空间   namespace pi
namespace cpy
{
    // 二级命名空间   namespace object
    namespace object
    {
        // 定义Integer整数对象类，继承自Object对象类
        class Integer: public Object, public Hashable
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Integer();
            // 带参构造函数
            Integer(int64_t value);

            /* 析构函数 */
            ~Integer()=default;

            /* 公有成员函数 */
            void init(int64_t value);              // 整数对象初始化函数
            virtual void print() const;            // 整数对象打印函数
            virtual std::string toString() const;  // 整数对象数值字符串化函数
            virtual HashKey hashKey() const;       // 整数对象哈希键值获取函数

            
        public:
            /* 公有成员变量 */
            int64_t value; // 整数值
        };
    }
}