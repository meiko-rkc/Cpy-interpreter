#pragma once
#include <object/base_obj.h>
#include <object/hash_obj.h>
#include <object/iterable.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace object
    namespace object
    {
        // 定义哈希值对象类,继承自对象基类
        class HashValues : public Object, public Iterable
        {
        public:
            /* 构造函数 */
            // 带参构造函数
            HashValues(const std::shared_ptr<Hash> &hash);

            /* 析构函数 */
            ~HashValues() = default;

            /* 公有成员函数 */
            void assign(const std::shared_ptr<Hash> &hash); // 哈希键对象初始化函数
            virtual void print() const;                     // 哈希键对象打印函数
            virtual std::string toString() const;           // 哈希键对象字符串化函数

            // 哈希值迭代器方法实现
            virtual std::shared_ptr<Object> next();  // 迭代器下一个元素获取函数
            virtual void reset();                    // 迭代器重置函数
            virtual std::shared_ptr<Object> begin(); // 迭代器开始位置获取函数
            virtual size_t size() const;             // 可迭代对象大小获取函数

            // 支持运算方法
            std::shared_ptr<Object> eq(const std::shared_ptr<HashValues> &other) const; // 哈希值对象相等判断函数
            std::shared_ptr<Object> ne(const std::shared_ptr<HashValues> &other) const; // 哈希值对象不相等判断函数

        private:
            /* 私有成员函数 */
            // 哈希键迭代器方法实现
            std::shared_ptr<Hash> hash; // 哈希表对象
        };
    }
}