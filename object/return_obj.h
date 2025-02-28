#pragma once
#include <object/base_obj.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace object
    namespace object
    {
        // 定义Return对象类，继承自Object对象类
        class Return : public Object
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Return();
            // 带参构造函数
            Return(const std::shared_ptr<Object> &value);

            /* 析构函数 */
            ~Return() = default;

            /* 公有成员函数 */
            void init(const std::shared_ptr<Object> &value); // return对象初始化函数
            virtual std::string toString() const;            // return对象返回值字符串化函数
            virtual void print() const;                      // return对象返回值打印函数

        public:
            /* 公有成员变量 */
            std::shared_ptr<Object> value; // Return对象的值
        };
    }
}