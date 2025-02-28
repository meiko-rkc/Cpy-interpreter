#pragma once
#include <object/base_obj.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace object
    namespace object
    {
        // 定义错误对象类,继承自对象类
        class Error : public Object
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Error();
            // 带参构造函数
            Error(const std::string &message);

            /* 析构函数 */
            ~Error() = default;

            /* 公有成员函数 */
            void init(const std::string &message);                   // 初始化函数
            virtual std::string toString() const;                    // 错误对象字符串化函数
            virtual void print() const;                              // 错误对象打印函数

        public:
            /* 公有成员变量 */
            std::string message; // 错误消息
        };
    }
}