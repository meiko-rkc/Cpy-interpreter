#pragma once
#include <object/base_obj.h>
#include <object/hashable.h>
// 一级命名空间   namespace pi
namespace cpy
{
    // 二级命名空间   namespace object
    namespace object
    {
        // 定义Bool类，继承自Object类
        class Bool : public Object, public Hashable
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Bool();
            // 带参构造函数
            Bool(bool value);

            /* 析构函数 */
            ~Bool() = default;

            /* 公有成员函数 */
            void init(bool value);                // 初始化函数
            virtual std::string toString() const; // 布尔对象字符串化函数
            virtual void print() const;           // 布尔对象打印函数
            virtual HashKey hashKey() const;      // 哈希键求值函数

            // 前缀运算函数
            static std::shared_ptr<Object> prefix(const std::string &op, const std::shared_ptr<Object> &self); // 前缀运算符函数

            // 中缀运算函数
            static std::shared_ptr<Object> infix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right); // 中缀运算符函数

        private:
            /* 私有成员函数 */
            /* 运算符支持函数 */
            // 前缀运算符函数
            static std::shared_ptr<Object> lognot(const std::shared_ptr<Object> &self); // 逻辑非运算符函数

            // 中缀运算符函数
            static std::shared_ptr<Object> logand(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right); // 逻辑与运算符函数
            static std::shared_ptr<Object> logor(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);  // 逻辑或运算符函数

        public:
            /* 共有成员变量 */
            bool value; // 布尔值

        private:
            /* 私有成员变量 */
            static const std::unordered_map<std::string, prefixFn> prefixFns; // 前缀运算符函数映射表
            static const std::unordered_map<std::string, infixFn> infixFns;   // 中缀运算符函数映射表
        };
    }
}