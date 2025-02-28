#include <object/break_obj.h>
using namespace cpy::object;
// 空参构造函数
Break::Break() : Object(OBJECT_BREAK)
{
}

// break对象字符串
std::string Break::toString() const
{
    return "break";
}

// break对象打印函数
void Break::print() const
{
    std::cout << toString() << std::endl;
}