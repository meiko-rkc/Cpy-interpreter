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
        class Builtin : public Object, public Hashable
        {
        public:
            // 内置函数指针
            typedef std::shared_ptr<Object> (*method)(const std::vector<std::shared_ptr<Object>> &args);
            /* 构造函数 */
            // 空参构造函数
            Builtin();
            // 带参构造函数
            Builtin(const std::string &name);

            /* 析构函数 */
            ~Builtin() = default;

            /* 公有成员函数 */
            // 核心函数
            static std::shared_ptr<Builtin> getBuiltinObj(const std::string &name);         // 内置函数对象查找函数
            std::shared_ptr<Object> call(const std::vector<std::shared_ptr<Object>> &args); // 内置函数对象调用函数

            // 基础函数
            virtual void init(const std::string &name); // 内置函数对象初始化函数
            virtual std::string toString() const;       // 内置函数对象字符串化函数
            virtual void print() const;                 // 内置函数对象打印函数
            virtual HashKey hashKey() const;            // 内置函数对象哈希键值获取函数

        private:
            /* 私有成员函数 */
            // 核心内置函数实现
            // 类型转化内置函数
            static std::shared_ptr<Object> strMethod(const std::vector<std::shared_ptr<Object>> &args);   // str内置函数实现
            static std::shared_ptr<Object> intMethod(const std::vector<std::shared_ptr<Object>> &args);   // int内置函数实现
            static std::shared_ptr<Object> floatMethod(const std::vector<std::shared_ptr<Object>> &args); // float内置函数实现
            static std::shared_ptr<Object> boolMethod(const std::vector<std::shared_ptr<Object>> &args);  // bool内置函数实现
            static std::shared_ptr<Object> listMethod(const std::vector<std::shared_ptr<Object>> &args);  // list内置函数实现
            static std::shared_ptr<Object> hashMethod(const std::vector<std::shared_ptr<Object>> &args);  // hash内置函数实现

            // 输入输出内置函数
            static std::shared_ptr<Object> inputMethod(const std::vector<std::shared_ptr<Object>> &args); // input内置函数实现
            static std::shared_ptr<Object> printMethod(const std::vector<std::shared_ptr<Object>> &args); // print内置函数实现

            // 基础内置函数
            static std::shared_ptr<Object> lenMethod(const std::vector<std::shared_ptr<Object>> &args);  // len内置函数实现
            static std::shared_ptr<Object> lensMethod(const std::vector<std::shared_ptr<Object>> &args); // lens内置函数实现
            static std::shared_ptr<Object> typeMethod(const std::vector<std::shared_ptr<Object>> &args); // type内置函数实现
            static std::shared_ptr<Object> exitMethod(const std::vector<std::shared_ptr<Object>> &args); // exit内置函数实现

            // 系统内置函数
            static std::shared_ptr<Object> systemMethod(const std::vector<std::shared_ptr<Object>> &args); // system内置函数实现

            // 数学内置函数
            static std::shared_ptr<Object> absMethod(const std::vector<std::shared_ptr<Object>> &args); // abs内置函数实现
            static std::shared_ptr<Object> maxMethod(const std::vector<std::shared_ptr<Object>> &args); // max内置函数实现
            static std::shared_ptr<Object> minMethod(const std::vector<std::shared_ptr<Object>> &args); // min内置函数实现
            static std::shared_ptr<Object> powMethod(const std::vector<std::shared_ptr<Object>> &args); // pow内置函数实现

        public:
            /* 公有成员变量 */
            std::string name; // 内置对象的函数名

        private:
            /* 私有成员变量 */
            static std::unordered_map<std::string, method> methods; // 内置对象的函数表
        };
    }
}