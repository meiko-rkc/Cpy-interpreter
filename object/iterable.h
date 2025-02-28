#pragma once
#include <object/base_obj.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace object
    namespace object
    {
        // 定义可迭代对象抽象类
        class Iterable
        {
        public:
            /* 公有成员函数 */
            virtual std::shared_ptr<Object> next() = 0;                // 迭代器下一个元素获取函数
            virtual void reset() = 0;                                  // 迭代器重置函数
            virtual std::shared_ptr<Object> begin() = 0;               // 迭代器开始位置获取函数
            virtual std::shared_ptr<Object> end() { return nullptr; } // 迭代器结束位置获取函数
            virtual size_t size() const = 0;                           // 可迭代对象大小获取函数
        };
    }
}