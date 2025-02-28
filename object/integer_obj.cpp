#include <object/integer_obj.h>
using namespace cpy::object;
// 空参构造函数
Integer::Integer()
{
    init(0);
}

// 带参构造函数
Integer::Integer(int64_t value)
{
    init(value);
}

// 整数对象初始化函数
void Integer::init(int64_t value)
{
    // 设置对象类型和整数值
    this->type = OBJECT_INTEGER;
    this->value = value;
}

// 整数对象打印函数
void Integer::print() const
{
    std::cout << value << std::endl;
}

// 整数对象数值字符串化函数
std::string Integer::toString() const
{
    return std::to_string(value);
}

// 整数对象哈希键值获取函数
HashKey Integer::hashKey() const
{
    return HashKey(type, std::hash<int64_t>()(value));
}