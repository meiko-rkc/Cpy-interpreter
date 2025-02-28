#pragma once
#include <object/base_obj.h>
namespace cpy
{
    namespace object
    {
       // 定义哈希值对象类
        class HashKey
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            HashKey();
            // 带参构造函数
            HashKey(Object::Type type, size_t value);

            /* 析构函数 */
            ~HashKey() = default;

            /* 公有成员函数 */
            void init(Object::Type type, size_t value); // 哈希键值初始化函数
            bool operator==(const HashKey &other) const;            // 哈希键值相等比较函数

        public:
            Object::Type type; // 对象类型
            size_t value;      // 对象数据哈希值
        };

        // 定义哈希使能对象类
        class Hashable
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Hashable() = default;
            /* 析构函数 */
            ~Hashable() = default;

            /* 公有成员函数 */
            virtual HashKey hashKey() const = 0; // 哈希键值获取函数
        }; 
    }
}

// 标准库命名空间std
namespace std
{
    // 定义哈希键值对象类的哈希函数
    template <>
    struct hash<cpy::object::HashKey>
    {
        // 重载()运算符，计算HashKey对象的哈希值
        size_t operator()(const cpy::object::HashKey &key) const
        {
            return std::hash<size_t>()(key.value);
        }
    };
}