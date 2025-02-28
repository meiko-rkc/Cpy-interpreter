#include <object/error_obj.h>
#include "error_obj.h"
using namespace cpy::object;
// 空参构造函数
Error::Error()
{
    init("");
}

// 带参构造函数
Error::Error(const std::string &message)
{
    init(message);
}

// 错误对象初始化函数
void Error::init(const std::string &message)
{
    // 设置错误对象的类型和信息
    this->type = OBJECT_ERROR;
    this->message = message;
}

// 错误对象字符串化函数
std::string Error::toString() const
{
    return "Error: " + message;
}

// 错误对象打印函数
void Error::print() const
{
    // 打印错误对象的信息
    std::cout<<toString()<<std::endl;
}
