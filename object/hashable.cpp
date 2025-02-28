#include <object/hashable.h>
using namespace cpy::object;
// 哈希键值空参构造函数
HashKey::HashKey()
{
    init(Object::OBJECT_ERROR, 0);
}

// 哈希键值带参构造函数
HashKey::HashKey(Object::Type type, size_t value)
{
    init(type, value);
}

// 哈希键值初始化函数
void HashKey::init(Object::Type type, size_t value)
{
    this->type = type;
    this->value = value;
}

// 哈希键值相等比较函数
bool HashKey::operator==(const HashKey &other) const
{
    return type == other.type && value == other.value;
}