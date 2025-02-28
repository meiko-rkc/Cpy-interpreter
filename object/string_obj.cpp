#include <object/string_obj.h>
#include "string_obj.h"
using namespace cpy::object;
// 字符串内置方法映射表
const std::unordered_map<std::string, String::method> String::methods = {
    {"len", &String::lenMethod},
    {"upper", &String::upperMethod},
    {"lower", &String::lowerMethod},
    {"index", &String::indexMethod},
    {"find", &String::findMethod},
    {"split", &String::splitMethod},
    {"prefix", &String::prefixMethod},
    {"suffix", &String::suffixMethod},
    {"ltrim", &String::ltrimMethod},
    {"rtrim", &String::rtrimMethod},
    {"trim", &String::trimMethod},
    {"substr", &String::substrMethod},
    {"replace", &String::replaceMethod},
    {"join", &String::joinMethod},
};

// 空参构造函数
String::String() : Object(OBJECT_STRING)
{
    init("");
}

// 带参构造函数
String::String(const std::string &value) : Object(OBJECT_STRING)
{
    init(value);
}

// 字符串对象初始化函数
void String::init(const std::string &value)
{
    this->value = value;
    reset();
}

// 字符串对象打印函数
void String::print() const
{
    std::cout << toString() << std::endl;
}

// 字符串对象数值字符串化函数
std::string String::toString() const
{
    return "\"" + value + "\"";
}

// 字符串对象哈希键值获取函数
HashKey String::hashKey() const
{
    return HashKey(type, std::hash<std::string>()(value));
}

// 获取字符串对象自身的共享指针函数
std::shared_ptr<String> String::getSharedFromthis() const
{
    // 转换为非const的字符串对象指针
    return std::const_pointer_cast<String>(shared_from_this());
}

// 字符串对象索引获取函数
std::shared_ptr<Object> String::operator[](int64_t index) const
{
    // 计算索引上限
    int64_t max = value.size();
    // 判断索引值是否越界
    if (index >= max || index < -max)
        return newError("string index out of range");
    // 计算索引值
    if (index < 0)
        index += max;
    // 返回索引结果
    return std::shared_ptr<String>(new String(value.substr(index, 1)));
}

// 字符串对象迭代器迭代对象获取函数
std::shared_ptr<Object> String::next()
{
    // 如果迭代器已经到达字符串末尾则返回nullptr
    if (iter == value.end())
        return nullptr;
    // 获取当前迭代器指向的元素并转化为字符串对象
    std::shared_ptr<Object> result = newString(std::string(1, *iter));
    // 迭代器后移
    ++iter;
    // 返回迭代结果
    return result;
}

// 字符串对象迭代器重置函数
void String::reset()
{
    iter = value.begin();
}

// 字符串对象迭代器起始对象获取函数
std::shared_ptr<Object> String::begin()
{
    // 如果列表为空则返回nullptr
    if (value.size() == 0)
        return nullptr;
    return newString(std::string(1, *value.begin()));
}

// 字符串对象长度获取函数
size_t String::size() const
{
    return value.size();
}

// 字符串对象内置方法对象获取函数
std::shared_ptr<Object> String::getBuiltinMethod(const std::string &name) const
{
    // 获取函数名对应的迭代器
    std::unordered_map<std::string, String::method>::const_iterator it = methods.find(name);
    // 如果内置方法不存在则返回nullptr
    if (it == methods.end())
        return nullptr;
    // 否则返回内置方法对象
    return std::shared_ptr<BuiltinMethod>(new BuiltinMethod(name, it->second, getSharedFromthis()));
}

// 字符串对象属性获取函数
std::shared_ptr<Object> String::getProperty(const std::string &name) const
{
    // 先尝试获取方法属性
    std::shared_ptr<Object> method = getBuiltinMethod(name);
    // 如果方法属性存在于方法对象中则返回方法属性
    if (method != nullptr)
        return method;
    // 否则返回错误对象
    return Object::newError("'string' object has no property '%s'", name.c_str());
}

// 字符串对象属性设置函数
std::shared_ptr<Object> String::setProperty(const std::string &name, const std::shared_ptr<Object> &value)
{
    // 先尝试获取方法属性
    std::shared_ptr<Object> method = getBuiltinMethod(name);
    // 如果方法属性存在于方法对象中则返回错误对象
    if (method != nullptr)
        return Object::newError("'string' object property '%s' is read-only", name.c_str());
    // 否则返回错误对象
    return Object::newError("'string' object has no property '%s'", name.c_str());
}