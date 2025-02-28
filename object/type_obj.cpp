#include <object/type_obj.h>
using namespace cpy::object;
// 空参构造函数
TypeObj::TypeObj() : Object(OBJECT_TYPE)
{
    init(OBJECT_ERROR);
}

// 带参构造函数
TypeObj::TypeObj(Type objType) : Object(OBJECT_TYPE)
{
    init(objType);
}

// 初始化函数
void TypeObj::init(Type objType)
{
    this->objType = objType;
}

// 对象类型对象打印函数
void TypeObj::print() const
{
    std::cout << toString() << std::endl;
}

// 对象类型对象字符串化函数
std::string TypeObj::toString() const
{
    return "<class '" + getName(objType) + "'>";
}

// 对象类型对象哈希函数
HashKey TypeObj::hashKey() const
{
    return HashKey(type, std::hash<std::size_t>()(objType));
}
