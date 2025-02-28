#pragma once
#include <object/base_obj.h>
#include <object/hashable.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace object
    namespace object
    {
        // 定义内置对象类,继承自对象类
        class BuiltinMethod : public Object, public Hashable
        {
        public:
            /* 构造函数 */
            // 带参构造函数
            BuiltinMethod(const std::string &name, const method &func, const std::shared_ptr<Object> &self);

            /* 析构函数 */
            ~BuiltinMethod() = default;

            /* 公有成员函数 */
            std::shared_ptr<Object> call(const std::vector<std::shared_ptr<Object>> &args);

            // 基础函数
            virtual void init(const std::string &name, const method &func, const std::shared_ptr<Object> &self); // 内置对象方法初始化函数
            virtual std::string toString() const;                                                                // 内置对象方法字符串化函数
            virtual void print() const;                                                                          // 内置对象方法打印函数
            virtual HashKey hashKey() const;                                                                     // 内置对象方法哈希键值获取函数

        public:
            /* 公有成员变量 */
            std::string name;             // 内置对象方法函数名
            method func;                  // 内置对象方法函数指针
            std::shared_ptr<Object> self; // 内置对象方法函数所属对象指针
        };
    }
}