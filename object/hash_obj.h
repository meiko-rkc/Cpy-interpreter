#pragma once
#include <object/base_obj.h>
#include <object/hashpair_obj.h>
#include <object/hashable.h>
#include <object/iterable.h>
#include <object/builtin_method.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace object
    namespace object
    {
        // 定义哈希对象类,继承自对象基类
        class Hash : public Object, public Iterable, public std::enable_shared_from_this<Hash>
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Hash();
            // 带参构造函数
            Hash(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs);

            /* 析构函数 */
            ~Hash() = default;

            /* 公有成员函数 */
            void init(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs); // 哈希对象初始化函数
            virtual void print() const;                                                     // 哈希对象打印函数
            virtual std::string toString() const;                                           // 哈希对象字符串化函数
            virtual std::shared_ptr<Object> getSharedFromthis() const;                      // 字符串对象智能指针获取函数

            // 哈希迭代器方法实现
            virtual std::shared_ptr<Object> next();       // 哈希迭代器迭代对象获取方法
            virtual std::shared_ptr<Object> nextKey();    // 哈希迭代器迭代键获取方法
            virtual std::shared_ptr<Object> nextValue();  // 哈希迭代器迭代值获取方法
            virtual std::shared_ptr<Object> nextPair();   // 哈希迭代器迭代键值对获取方法
            virtual void reset();                         // 哈希迭代器重置方法
            virtual std::shared_ptr<Object> begin();      // 哈希迭代器起始元素获取方法
            virtual std::shared_ptr<Object> beginKey();   // 哈希迭代器起始键获取方法
            virtual std::shared_ptr<Object> beginValue(); // 哈希迭代器起始值获取方法
            virtual std::shared_ptr<Object> beginPair();  // 哈希迭代器起始键值对获取方法
            virtual size_t size() const;                  // 哈希对象长度获取函数

            // 获取哈希表函数
            const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &getPairs() const; // 哈希表获取函数
            // 设置哈希表函数
            void setPairs(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs); // 哈希表设置函数
            // 设置键值对函数
            std::shared_ptr<Object> setPair(const std::shared_ptr<Object> &key, const std::shared_ptr<Object> &value); // 哈希键值对设置函数

            // 获取哈希对象内置方法对象函数
            std::shared_ptr<Object> getBuiltinMethod(const std::string &name) const; // 哈希内置方法获取函数
            // 获取哈希对象属性对象函数
            std::shared_ptr<Object> getProperty(const std::string &name) const; // 哈希属性获取函数
            // 设置哈希对象属性对象函数
            std::shared_ptr<Object> setProperty(const std::string &name, const std::shared_ptr<Object> &value); // 哈希属性设置函数

        private:
            /* 私有成员函数 */
            // 哈希对象内置方法
            static std::shared_ptr<Object> lenMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);    // 哈希长度获取函数
            static std::shared_ptr<Object> keysMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);   // 哈希键列表获取函数
            static std::shared_ptr<Object> valuesMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args); // 哈希值列表获取函数
            static std::shared_ptr<Object> itemsMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);  // 哈希键值对列表获取函数
            static std::shared_ptr<Object> findMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);   // 哈希键值查找函数
            static std::shared_ptr<Object> getMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);    // 哈希键值获取函数
            static std::shared_ptr<Object> setMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);    // 哈希键值设置函数
            static std::shared_ptr<Object> removeMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args); // 哈希键值删除函数
            static std::shared_ptr<Object> updateMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args); // 哈希键值更新函数
            static std::shared_ptr<Object> clearMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);  // 哈希键值清空函数

            // 哈希键列表获取处理函数
            static std::vector<std::shared_ptr<Object>> getKeys(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs); // 哈希键列表获取函数

            // 哈希值列表获取处理函数
            static std::vector<std::shared_ptr<Object>> getValues(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs); // 哈希值列表获取函数

            // 哈希键值对列表获取处理函数
            static std::vector<std::shared_ptr<Object>> getItems(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs); // 哈希键值对列表获取函数

            // 哈希键值设置函数
            static std::shared_ptr<Object> setMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &key, const std::shared_ptr<Object> &defaultVaule = Object::newNull()); // 2参数哈希键值设置函数

            // 哈希键值获取函数
            static std::shared_ptr<Object> getMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &key, const std::shared_ptr<Object> &defaultValue = Object::newNull()); // 哈希键值获取函数

            // 哈希键值删除函数
            static std::shared_ptr<Object> removeMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &key, const std::shared_ptr<Object> &defaultValue); // 2参数哈希键值删除函数

        private:
            /* 私有成员变量 */
            std::unordered_map<HashKey, std::shared_ptr<HashPair>> pairs;          // 哈希表
            std::unordered_map<HashKey, std::shared_ptr<HashPair>>::iterator iter; // 哈希迭代器
            static const std::unordered_map<std::string, method> methods;          // 哈希对象内置方法
        };
    }
}