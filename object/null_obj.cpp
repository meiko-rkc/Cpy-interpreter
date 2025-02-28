#include <object/null_obj.h>
using namespace cpy::object;
// 空参构造函数
Null::Null():Object(OBJECT_NULL)
{
}

// null对象打印函数
void Null::print() const
{
    std::cout << toString() << std::endl;
}

// null对象字符串表示函数
std::string Null::toString() const
{
    return "null";
}

// null对象哈希键值获取函数
HashKey Null::hashKey() const
{
    return HashKey(type, 0);
}
