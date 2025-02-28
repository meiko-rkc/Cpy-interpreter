#include <object/object.h>
#include "base_obj.h"
using namespace cpy::object;
// 对象类型名称映射表
const std::unordered_map<Object::Type, std::string> Object::names = {
    {OBJECT_ERROR, "error"},                   // 错误类型对象
    {OBJECT_INTEGER, "integer"},               // 整数类型对象
    {OBJECT_FLOAT, "float"},                   // 浮点数类型对象
    {OBJECT_BOOL, "bool"},                     // 布尔类型对象
    {OBJECT_STRING, "string"},                 // 字符串类型对象
    {OBJECT_NULL, "null"},                     // 空值对象
    {OBJECT_LIST, "list"},                     // 列表类型对象
    {OBJECT_HASH, "hash"},                     // 哈希类型对象
    {OBJECT_HASH_PAIR, "hash_pair"},           // 哈希键值对类型对象
    {OBJECT_HASH_KEYS, "hash_keys"},           // 哈希键类型对象
    {OBJECT_HASH_VALUES, "hash_values"},       // 哈希值类型对象
    {OBJECT_HASH_ITEMS, "hash_items"},         // 哈希项类型对象
    {OBJECT_FUNCTION, "function"},             // 函数类型对象
    {OBJECT_BUILTIN, "builtin"},               // 内置函数类型对象
    {OBJECT_BUILTIN_METHOD, "builtin_method"}, // 内置函数方法类型对象
    {OBJECT_BREAK, "break"},                   // 中断类型对象
    {OBJECT_CONTINUE, "continue"},             // 继续类型对象
    {OBJECT_RETURN, "return"},                 // 返回类型对象
    {OBJECT_TYPE, "type"},                     // 对象类型对象
};
// 空参构造函数
Object::Object()
{
    init(OBJECT_ERROR);
}
// 带参构造函数
Object::Object(Type type)
{
    init(type);
}

// 初始化函数函数
void Object::init(Type type)
{
    setType(type);
}

// 设置对象类型函数
void Object::setType(Type type)
{
    this->type = type;
}

// 获取对象类型函数
Object::Type Object::getType() const
{
    return type;
}

// 获取对象类型名称函数
std::string Object::getName() const
{
    return getName(type);
}

// 获取对象类型名称函数
std::string Object::getName(Type type)
{
    /* 在类型名称表中查找类型名称 */
    // 如果找到，则返回类型名称，否则返回空字符串
    if (names.find(type) != names.end())
        return names.at(type);
    return "";
}

// 生成错误对象函数
std::shared_ptr<Object> Object::newError(const char *format, ...)
{
    // 创建一个缓冲区来存储格式化后的错误消息
    char buffer[1024] = {'\0'};
    // 初始化可变参数列表
    va_list args;
    va_start(args, format);
    // 使用 vsnprintf 安全地格式化错误消息到缓冲区
    vsnprintf(buffer, sizeof(buffer), format, args);
    // 清理可变参数列表
    va_end(args);
    // 创建一个错误对象并返回其指针
    return std::shared_ptr<Error>(new Error(buffer));
}

// 生成整数对象函数
std::shared_ptr<Object> Object::newInteger(int64_t value)
{
    // 创建一个整数对象并返回其指针
    return std::shared_ptr<Integer>(new Integer(value));
}

// 生成浮点数对象函数
std::shared_ptr<Object> Object::newFloat(double value)
{
    // 创建一个浮点数对象并返回其指针
    return std::shared_ptr<Float>(new Float(value));
}

// 生成布尔类型对象函数
std::shared_ptr<Object> Object::newBool(bool value)
{
    // 创建一个布尔对象并返回其指针
    return std::shared_ptr<Bool>(new Bool(value));
}

// 生成字符串对象函数
std::shared_ptr<Object> Object::newString(const std::string &value)
{
    // 创建一个字符串对象并返回其指针
    return std::shared_ptr<String>(new String(value));
}

// 生成空值对象函数
std::shared_ptr<Object> Object::newNull()
{
    // 创建一个空值对象并返回其指针
    return std::shared_ptr<Null>(new Null());
}

// 生成列表对象函数
std::shared_ptr<Object> Object::newList(const std::vector<std::shared_ptr<Object>> &elements)
{
    return std::shared_ptr<Object>(new List(elements));
}

// 生成哈希对象函数
std::shared_ptr<Object> Object::newHash()
{
    return std::shared_ptr<Object>(new Hash());
}

// 生成break对象函数
std::shared_ptr<Object> Object::newBreak()
{
    return std::shared_ptr<Break>(new Break());
}

// 生成continue对象函数
std::shared_ptr<Object> Object::newContinue()
{
    return std::shared_ptr<Continue>(new Continue());
}

// 生成type对象函数
std::shared_ptr<Object> cpy::object::Object::newType(Type objType)
{
    return std::shared_ptr<TypeObj>(new TypeObj(objType));
}

// 判断两个对象是否相等
bool Object::isEqual(const std::shared_ptr<Object> &other) const
{
    return type == other->type && toString() == other->toString();
}

// 判断两个对象是否相等
bool Object::isEqual(const std::shared_ptr<Object> &obj1, const std::shared_ptr<Object> &obj2)
{
    return obj1->isEqual(obj2);
}

// 判断对象是否为错误对象
bool Object::isError(const std::shared_ptr<Object> &obj)
{
    return obj->getType() == OBJECT_ERROR;
}

// 整数对象转换为布尔对象
std::shared_ptr<Object> Object::int2bool(const std::shared_ptr<Object> &obj)
{
    // 将整数对象转为布尔对象
    return newBool(std::dynamic_pointer_cast<Integer>(obj)->value != 0);
}

// 浮点数对象转换为布尔对象
std::shared_ptr<Object> Object::float2bool(const std::shared_ptr<Object> &obj)
{
    // 将浮点数对象转为布尔对象
    return newBool(std::dynamic_pointer_cast<Float>(obj)->value!= 0.0);
}

// 空值对象转换为布尔对象
std::shared_ptr<Object> Object::null2bool()
{
    // 将空值对象转为布尔对象
    return newBool(false);
}

// 对象转换为布尔对象
std::shared_ptr<Object> Object::toBool(const std::shared_ptr<Object> &obj)
{
    // 判断对象类型
    switch (obj->getType())
    {
    // 布尔数类型
    case Object::OBJECT_BOOL:
        // 将布尔对象转为布尔对象
        return std::dynamic_pointer_cast<Bool>(obj);
    // 整数类型
    case Object::OBJECT_INTEGER:
        return int2bool(obj);
    // 浮点数类型
    case Object::OBJECT_FLOAT:
        return float2bool(obj);
    // 空值类型
    case Object::OBJECT_NULL:
        return null2bool();
    }
    // 将对象转为可迭代对象
    std::shared_ptr<Iterable> iterable = std::dynamic_pointer_cast<Iterable>(obj);
    // 如果为可迭代对象，则返迭代对象长度转布尔类型，否则返回布尔对象True
    return (iterable != nullptr) ? newBool(iterable->size()) : newBool(true);
}
