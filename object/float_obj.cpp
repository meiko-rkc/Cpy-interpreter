#include <object/float_obj.h>
#include <iomanip>
using namespace cpy::object;
// 空参构造函数
Float::Float()
{
    init(0.0);
}

// 带参构造函数
Float::Float(double value)
{
    init(value);
}

// 浮点数数对象初始化函数
void Float::init(double value)
{
    // 设置对象类型和整数值
    this->type = OBJECT_FLOAT;
    this->value = value;
}

// 浮点数对象字符串化函数
std::string Float::toString() const
{
    // 设置浮点数输出精度
    std::ostringstream oss;
    oss << std::setprecision(15) << value;
    // 判断浮点数是否为整数，若是则末尾添加输出".0"
    if (value == int64_t(value))
        oss << ".0";
    // 返回浮点数字符串
    return oss.str();
}

// 浮点数对象打印函数
void Float::print() const
{
    // 设置浮点数输出精度
    std::cout << std::setprecision(15) << value;
    // 判断浮点数是否为整数，若是则末尾添加输出".0"
    if (value == int64_t(value))
        std::cout << ".0";
    std::cout << std::endl;
}

// 浮点数对象哈希键值获取函数
HashKey Float::hashKey() const
{
    return HashKey(type, std::hash<double>()(value));
}