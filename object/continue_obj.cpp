#include <object/continue_obj.h>
using namespace cpy::object;
// 空参构造函数
Continue::Continue() : Object(OBJECT_CONTINUE)
{
}

// continue对象字符串
std::string Continue::toString() const
{
    return "continue";
}

// continue对象打印函数
void Continue::print() const
{
    std::cout << toString() << std::endl;
}