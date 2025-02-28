#pragma once
#include <object/base_obj.h>
#include <object/hashable.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace object
    namespace object
    {
        // 定义Float类,继承自对象类
        class Float : public Object, public Hashable
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Float();
            // 带参构造函数
            Float(double value);

            /* 析构函数 */
            ~Float() = default;

            /* 公有成员函数 */
            void init(double value);              // 初始化函数
            virtual std::string toString() const; // 错误对象字符串化函数
            virtual void print() const;           // 错误对象打印函数
            virtual HashKey hashKey() const;      // 哈希键值获取函数

        public:
            /* 公有成员变量 */
            double value; // 浮点数值
        };
    }
}