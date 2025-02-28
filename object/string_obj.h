#pragma once
#include <object/base_obj.h>
#include <object/builtin_method.h>
#include <object/hashable.h>
#include <object/iterable.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace object
    namespace object
    {
        // 定义字符串对象类,继承自对象类
        class String : public Object, public Hashable, public Iterable, public std::enable_shared_from_this<String>
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            String();
            // 带参构造函数
            String(const std::string &value);

            /* 析构函数 */
            ~String() = default;

            /* 公有成员函数 */
            void init(const std::string &value);                       // 字符串对象初始化函数
            virtual void print() const;                                // 字符串对象打印函数
            virtual std::string toString() const;                      // 字符串对象数值字符串化函数
            virtual HashKey hashKey() const;                           // 字符串对象哈希键值获取函数
            virtual std::shared_ptr<String> getSharedFromthis() const; // 字符串对象智能指针获取函数
            std::shared_ptr<Object> operator[](int64_t index) const;   // 字符串索引操作符重载函数

            // 字符串迭代器方法实现
            virtual std::shared_ptr<Object> next();  // 字符串迭代器迭代对象获取方法
            virtual void reset();                    // 字符串迭代器重置方法
            virtual std::shared_ptr<Object> begin(); // 字符串迭代器起始元素获取方法
            virtual size_t size() const;             // 字符串对象长度获取函数

            // 获取字符串内置方法对象函数
            std::shared_ptr<Object> getBuiltinMethod(const std::string &name) const; // 字符串内置方法获取函数
            // 获取字符串属性对象函数
            std::shared_ptr<Object> getProperty(const std::string &name) const; // 字符串属性获取函数
            // 设置字符串属性对象函数
            std::shared_ptr<Object> setProperty(const std::string &name, const std::shared_ptr<Object> &value); // 字符串属性设置函数

        private:
            /* 私有成员函数 */
            // 字符串对象内置方法
            static std::shared_ptr<Object> lenMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);     // 字符串长度获取函数
            static std::shared_ptr<Object> upperMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);   // 字符串大写转换函数
            static std::shared_ptr<Object> lowerMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);   // 字符串小写转换函数
            static std::shared_ptr<Object> indexMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);   // 字符串索引获取函数
            static std::shared_ptr<Object> findMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);    // 字符串查找函数
            static std::shared_ptr<Object> splitMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);   // 字符串分割函数
            static std::shared_ptr<Object> prefixMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);  // 字符串前缀判断函数
            static std::shared_ptr<Object> suffixMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);  // 字符串后缀判断函数
            static std::shared_ptr<Object> ltrimMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);   // 字符串左修剪函数
            static std::shared_ptr<Object> rtrimMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);   // 字符串右修剪函数
            static std::shared_ptr<Object> trimMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);    // 字符串修剪函数
            static std::shared_ptr<Object> substrMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);  // 字符串裁剪函数
            static std::shared_ptr<Object> replaceMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args); // 字符串替换函数
            static std::shared_ptr<Object> joinMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args);    // 字符串连接函数

            // 索引字符串处理函数
            static std::shared_ptr<Object> indexMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &sub);                                                                           // 1参数字符串索引函数
            static std::shared_ptr<Object> indexMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &sub, const std::shared_ptr<Object> &start);                                     // 2参数字符串索引函数
            static std::shared_ptr<Object> indexMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &sub, const std::shared_ptr<Object> &start, const std::shared_ptr<Object> &end); // 3参数字符串索引函数

            // 查找字符串处理函数
            static std::shared_ptr<Object> findMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &sub);                                                                           // 1参数字符串查找函数
            static std::shared_ptr<Object> findMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &sub, const std::shared_ptr<Object> &start);                                     // 2参数字符串查找函数
            static std::shared_ptr<Object> findMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &sub, const std::shared_ptr<Object> &start, const std::shared_ptr<Object> &end); // 3参数字符串查找函数
            static size_t find(const std::string &str, const std::string &sub, size_t start, size_t end);                                                                                                // 字符串查找函数

            // 分割字符串处理函数
            static std::shared_ptr<Object> splitMethod(const std::shared_ptr<Object> &obj);                                                                                // 0参数字符串分割函数
            static std::shared_ptr<Object> splitMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &delim);                                          // 1参数字符串分割函数
            static std::shared_ptr<Object> splitMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &delim, const std::shared_ptr<Object> &maxSplit); // 2参数字符串分割函数
            static std::vector<std::shared_ptr<Object>> splitByWhitespace(const std::string &str, int64_t maxSplit);                                                       // 空白符字符串分割函数
            static std::vector<std::shared_ptr<Object>> splitByDelimiter(const std::string &str, const std::string &delim, int64_t maxSplit);                              // 分隔符字符串分割函数

            // 前缀判断函数
            static std::shared_ptr<Object> prefixMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &prefix); // 字符串前缀判断函数
            static bool isPrefix(const std::string &str, const std::string &prefix);                                                // 字符串前缀判断函数

            // 后缀判断函数
            static std::shared_ptr<Object> suffixMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &suffix); // 字符串后缀判断函数
            static bool isSuffix(const std::string &str, const std::string &suffix);                                                // 字符串后缀判断函数

            // 字符串修剪函数
            static std::shared_ptr<Object> ltrimMethod(const std::shared_ptr<Object> &obj);                                       // 0参数字符串左修剪函数
            static std::shared_ptr<Object> ltrimMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &chars); // 1参数字符串左修剪函数
            static std::shared_ptr<Object> rtrimMethod(const std::shared_ptr<Object> &obj);                                       // 0参数字符串右修剪函数
            static std::shared_ptr<Object> rtrimMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &chars); // 1参数字符串右修剪函数
            static std::shared_ptr<Object> trimMethod(const std::shared_ptr<Object> &obj);                                        // 0参数字符串修剪函数
            static std::shared_ptr<Object> trimMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &chars);  // 1参数字符串修剪函数
            static std::string ltrim(const std::string &str, const std::string &chars = " \r\n\t");                               // 字符串左修剪函数
            static std::string rtrim(const std::string &str, const std::string &chars = " \r\n\t");                               // 字符串右修剪函数
            static std::string trim(const std::string &str, const std::string &chars = " \r\n\t");                                // 字符串修剪函数

            // 字符串裁剪函数
            static std::shared_ptr<Object> substrMethod(const std::shared_ptr<Object> &obj);                                                                           // 0参数字符串裁剪函数
            static std::shared_ptr<Object> substrMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &start);                                     // 1参数字符串裁剪函数
            static std::shared_ptr<Object> substrMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &start, const std::shared_ptr<Object> &end); // 2参数字符串裁剪函数

            // 字符串替换函数
            static std::shared_ptr<Object> replaceMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &oldValue, const std::shared_ptr<Object> &newValue);                                       // 字符串替换函数
            static std::shared_ptr<Object> replaceMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &oldValue, const std::shared_ptr<Object> &newValue, const std::shared_ptr<Object> &count); // 字符串替换函数
            static std::string replace(const std::string &str, const std::string &oldValue, const std::string &newValue, int64_t count);                                                                              // 字符串替换函数

        public:
            /* 公有成员变量 */
            std::string value; // 字符串值

        private:
            /* 私有成员变量 */
            std::string::iterator iter;
            static const std::unordered_map<std::string, method> methods;
        };
    }
}