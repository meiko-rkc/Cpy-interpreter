#include <object/hashpair_obj.h>
using namespace cpy::object;
// 键值对空参构造函数
HashPair::HashPair() : Object(OBJECT_HASH_PAIR)
{
    init(nullptr, nullptr);
}

// 键值对带参构造函数
HashPair::HashPair(const std::shared_ptr<Object> &key, const std::shared_ptr<Object> &value) : Object(OBJECT_HASH_PAIR)
{
    init(key, value);
}

// 哈希键值对初始化函数
void HashPair::init(const std::shared_ptr<Object> &key, const std::shared_ptr<Object> &value)
{
    this->key = key;
    this->value = value;
}

// 哈希键值对打印函数
void HashPair::print() const
{
    std::cout << toString() << std::endl;
}

// 哈希键值对字符串表示函数
std::string HashPair::toString() const
{
    return key->toString() + ": " + value->toString();
}