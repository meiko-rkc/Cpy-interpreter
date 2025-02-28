#pragma once
#include <object/base_obj.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace object
    namespace object
    {
        // 定义哈希键值对对象类
        class HashPair : public Object
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            HashPair();
            // 带参构造函数
            HashPair(const std::shared_ptr<Object> &key, const std::shared_ptr<Object> &value);

            /* 析构函数 */
            ~HashPair() = default;

            /* 公有成员函数 */
            void init(const std::shared_ptr<Object> &key, const std::shared_ptr<Object> &value); // 哈希键值对对象初始化函数
            virtual void print() const;                                                          // 哈希键值对对象打印函数
            virtual std::string toString() const;                                                // 哈希键值对对象字符串化函数

        public:
            /* 公有成员变量 */
            std::shared_ptr<Object> key;   // 哈希键
            std::shared_ptr<Object> value; // 哈希值
        };
    }
}