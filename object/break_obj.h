#pragma once
#include <object/base_obj.h>
// 一级命名空间 namespace pi
namespace cpy 
{
    // 一级命名空间 namespace object
    namespace object
    {
        // 定义break对象类,继承自对象类
        class Break : public Object
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Break();

            /* 析构函数 */
            ~Break() = default;

            /* 公有成员函数 */
            virtual std::string toString() const; // break对象字符串化函数
            virtual void print() const;           // break对象打印函数
        };
    }
}