#pragma once
#include <object/base_obj.h>
#include <object/hashable.h>
namespace cpy
{
    namespace object
    {
        class TypeObj : public Object, public Hashable
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            TypeObj();
            // 带参构造函数
            TypeObj(Type objType);

            /* 析构函数 */
            ~TypeObj() = default;

            /* 公有成员函数 */
            void init(Type objType);              // 对象类型对象初始化函数
            virtual void print() const;           // 对象类型对象打印函数
            virtual std::string toString() const; // 对象类型对象字符串化函数
            virtual HashKey hashKey() const;      // 对象类型对象哈希键值获取函数

        public:
            /* 公有成员变量 */
            Type objType;
        };
    }
}