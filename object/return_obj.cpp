#include <object/return_obj.h>
using namespace cpy::object;
// 空参构造函数
Return::Return()
{
    init(nullptr);
}

// 带参构造函数
Return::Return(const std::shared_ptr<Object> &value)
{
    init(value);
}

void Return::init(const std::shared_ptr<Object> &value)
{
    this->type = OBJECT_RETURN;
    this->value = value;
}

// return对象返回值字符串化函数
std::string Return::toString() const
{
    return value->toString();
}

// return对象返回值打印函数
void Return::print() const
{
    value->print();
}
