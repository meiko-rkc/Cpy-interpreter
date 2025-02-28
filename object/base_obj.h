#pragma once
#include <cctype>
#include <vector>
#include <string>
#include <memory>
#include <cstdarg>
#include <sstream>
#include <string_view>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
// 一级命名空间   namespace pi
namespace cpy
{
    // 二级命名空间   namespace object
    namespace object
    {
        // 定义Object对象类，所有对象的基类
        class Object
        {
        public:
            // 内置函数指针
            typedef std::shared_ptr<Object> (*method)(const std::shared_ptr<Object> &self, const std::vector<std::shared_ptr<Object>> &args);

            // 前缀运算函数指针
            typedef std::shared_ptr<Object> (*prefixFn)(const std::shared_ptr<Object> &self);

            // 中缀运算函数指针
            typedef std::shared_ptr<Object> (*infixFn)(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);

            // 后缀运算函数指针
            typedef std::shared_ptr<Object> (*postfixFn)(const std::shared_ptr<Object> &self);

            // Object枚举类型
            enum Type
            {
                OBJECT_ERROR,          // 对象错误
                OBJECT_INTEGER,        // 整数对象
                OBJECT_FLOAT,          // 浮点数对象
                OBJECT_BOOL,           // 布尔对象
                OBJECT_STRING,         // 字符串对象
                OBJECT_NULL,           // 空对象
                OBJECT_LIST,           // 列表对象
                OBJECT_HASH_PAIR,      // 键值对对象
                OBJECT_HASH,           // 哈希对象
                OBJECT_HASH_KEYS,      // 哈希键对象
                OBJECT_HASH_VALUES,    // 哈希值对象
                OBJECT_HASH_ITEMS,     // 哈希项对象
                OBJECT_FUNCTION,       // 函数对象
                OBJECT_BUILTIN,        // 内置函数对象
                OBJECT_BUILTIN_METHOD, // 内置方法对象
                OBJECT_BREAK,          // break对象
                OBJECT_CONTINUE,       // continue对象
                OBJECT_RETURN,         // return对象
                OBJECT_TYPE,           // 类型对象
            };

            /* 构造函数 */
            // 空参构造函数
            Object();
            // 带参构造函数
            Object(Type type);

            /* 析构函数 */
            virtual ~Object() = default;

            /* 公有成员函数 */
            void init(Type type);                                             // 对象初始化函数
            void setType(Type type);                                          // 设置对象类型函数
            Type getType() const;                                             // 获取对象类型函数
            std::string getName() const;                                      // 获取对象类型名称函数
            static std::string getName(Type type);                            // 获取对象类型名称函数
            virtual void print() const = 0;                                   // 对象打印函数
            virtual std::string toString() const = 0;                         // 获取对象字符串值函数

            // 对象工厂函数
            static std::shared_ptr<Object> newError(const char *format, ...);                                  // 获取错误对象函数
            static std::shared_ptr<Object> newInteger(int64_t value = 0);                                      // 获取整数对象函数
            static std::shared_ptr<Object> newFloat(double value = 0.0);                                       // 获取浮点数对象函数
            static std::shared_ptr<Object> newBool(bool value = false);                                        // 获取布尔对象函数
            static std::shared_ptr<Object> newString(const std::string &value = "");                           // 获取字符串对象函数
            static std::shared_ptr<Object> newNull();                                                          // 获取空对象函数
            static std::shared_ptr<Object> newList(const std::vector<std::shared_ptr<Object>> &elements = {}); // 获取列表对象函数
            static std::shared_ptr<Object> newHash();                                                          // 获取哈希对象函数
            static std::shared_ptr<Object> newBreak();                                                         // 获取break对象函数
            static std::shared_ptr<Object> newContinue();                                                      // 获取continue对象函数
            static std::shared_ptr<Object> newType(Type objType);                                              // 获取对象类型对象函数

            // 对象判断函数
            bool isEqual(const std::shared_ptr<Object> &other) const;                                      // 判断两个对象是否相等函数
            static bool isEqual(const std::shared_ptr<Object> &obj1, const std::shared_ptr<Object> &obj2); // 判断两个对象是否相等函数
            static bool isError(const std::shared_ptr<Object> &obj);                                       // 判断对象是否为错误对象函数

            // 对象转化函数
            static std::shared_ptr<Object> int2bool(const std::shared_ptr<Object> &obj);   // 整数对象转化为布尔对象函数
            static std::shared_ptr<Object> float2bool(const std::shared_ptr<Object> &obj); // 浮点数对象转化为布尔对象函数
            static std::shared_ptr<Object> null2bool();                                    // 空对象转化为布尔对象函数
            static std::shared_ptr<Object> toBool(const std::shared_ptr<Object> &obj);     // 对象转化为布尔对象函数

        protected:
            /* 公有成员变量 */
            Type type;                                                // 对象类型
            const static std::unordered_map<Type, std::string> names; // 对象类型映射表
        };
    }
}