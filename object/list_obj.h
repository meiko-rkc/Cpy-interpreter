#pragma once
#include <object/base_obj.h>
#include <object/iterable.h>
#include <object/builtin_method.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace object
    namespace object
    {
        // 定义列表对象类,继承自对象基类
        class List : public Object, public Iterable, public std::enable_shared_from_this<List>
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            List();
            // 带参构造函数
            List(const std::vector<std::shared_ptr<Object>> &elements);

            /* 析构函数 */
            ~List() = default;

            /* 公有成员函数 */
            void assign(const std::vector<std::shared_ptr<Object>> &elements); // 列表对象初始化函数
            virtual void print() const;                                        // 列表对象打印函数
            virtual std::string toString() const;                              // 列表对象字符串化函数
            virtual std::shared_ptr<List> getSharedFromthis() const;           // 列表对象智能指针获取函数
            std::shared_ptr<Object> operator[](int64_t index) const;           // 列表索引操作符重载函数

            // 列表迭代器方法实现
            virtual std::shared_ptr<Object> next();  // 列表迭代器迭代对象获取方法
            virtual void reset();                    // 列表迭代器重置方法
            virtual std::shared_ptr<Object> begin(); // 列表迭代器起始元素获取方法
            virtual size_t size() const;             // 列表长度获取函数

            // 获取列表内置方法对象函数
            std::shared_ptr<Object> getBuiltinMethod(const std::string &name) const; // 列表内置方法获取函数
            // 获取列表属性对象函数
            std::shared_ptr<Object> getProperty(const std::string &name) const; // 列表属性获取函数
            // 设置列表属性对象函数
            std::shared_ptr<Object> setProperty(const std::string &name, const std::shared_ptr<Object> &value); // 列表属性设置函数

        private:
            /* 私有成员函数 */
            // 列表内置方法实现
            static std::shared_ptr<Object> lenMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);      // 列表长度获取函数
            static std::shared_ptr<Object> countMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);    // 列表元素统计函数
            static std::shared_ptr<Object> indexMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);    // 列表索引获取函数
            static std::shared_ptr<Object> appendMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);   // 列表追加函数
            static std::shared_ptr<Object> insertMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);   // 列表插入函数
            static std::shared_ptr<Object> shiftMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);    // 列表头弹出函数
            static std::shared_ptr<Object> popMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);      // 列表尾弹出函数
            static std::shared_ptr<Object> eraseMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);    // 列表元素按位删除函数
            static std::shared_ptr<Object> removeMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);   // 列表元素按值删除函数
            static std::shared_ptr<Object> extendMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);   // 列表扩展函数
            static std::shared_ptr<Object> extendatMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args); // 列表指定位置扩展函数

            // 列表统计处理函数
            static std::shared_ptr<Object> countMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val);                                                                           // 1参数列表元素统计函数
            static std::shared_ptr<Object> countMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val, const std::shared_ptr<Object> &start);                                     // 2参数列表元素统计函数
            static std::shared_ptr<Object> countMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val, const std::shared_ptr<Object> &start, const std::shared_ptr<Object> &end); // 3参数列表元素统计函数
            static int64_t count(const std::vector<std::shared_ptr<Object>> &elements, const std::shared_ptr<Object> &val, int64_t start, int64_t end);                                                   // 列表元素统计处理函数

            // 列表索引处理函数
            static std::shared_ptr<Object> indexMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val);                                                                           // 1参数列表索引函数
            static std::shared_ptr<Object> indexMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val, const std::shared_ptr<Object> &start);                                     // 2参数列表索引函数
            static std::shared_ptr<Object> indexMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val, const std::shared_ptr<Object> &start, const std::shared_ptr<Object> &end); // 3参数列表索引函数
            static int64_t index(const std::vector<std::shared_ptr<Object>> &elements, const std::shared_ptr<Object> &val, int64_t start, int64_t end);                                                   // 列表索引处理函数

            // 列表插入处理函数
            static std::shared_ptr<Object> insertMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &index, const std::shared_ptr<Object> &val); // 2参数列表插入函数

            // 列表尾弹出处理函数
            static std::shared_ptr<Object> popMethod(const std::shared_ptr<Object> &obj); // 0参数列表弹出函数

            // 列表头弹出处理函数
            static std::shared_ptr<Object> shiftMethod(const std::shared_ptr<Object> &obj); // 0参数列表弹出函数

            // 列表元素按位删除处理函数
            static std::shared_ptr<Object> eraseMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &index); // 1参数列表元素按位删除函数

            // 列表元素按值删除处理函数
            static std::shared_ptr<Object> removeMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val);                                                                           // 1参数列表元素按值删除函数
            static std::shared_ptr<Object> removeMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val, const std::shared_ptr<Object> &start);                                     // 2参数列表元素按值删除函数
            static std::shared_ptr<Object> removeMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val, const std::shared_ptr<Object> &start, const std::shared_ptr<Object> &end); // 3参数列表元素按值删除函数
            static int64_t remove(std::vector<std::shared_ptr<Object>> &elements, const std::shared_ptr<Object> &val, int64_t start, int64_t end);                                                         // 列表元素按值删除处理函数

            // 列表扩展处理函数
            static std::shared_ptr<Object> extendMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &iterable); // 1参数列表扩展函数

            // 列表指定位置扩展处理函数
            static std::shared_ptr<Object> extendatMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &index, const std::shared_ptr<Object> &iterable); // 2参数列表指定位置扩展函数

        public:
            /* 公有成员变量 */
            std::vector<std::shared_ptr<Object>> elements; // 列表元素列表

        private:
            /* 私有成员变量 */
            std::vector<std::shared_ptr<Object>>::iterator iter;          // 列表迭代器
            static const std::unordered_map<std::string, method> methods; // 列表方法映射表
        };
    }
}