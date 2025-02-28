#include <object/list_obj.h>
#include "list_obj.h"
using namespace cpy::object;
// 列表内置方法映射表
const std::unordered_map<std::string, List::method> List::methods = {
    {"len", &List::lenMethod},
    {"count", &List::countMethod},
    {"index", &List::indexMethod},
    {"append", &List::appendMethod},
    {"insert", &List::insertMethod},
    {"shift", &List::shiftMethod},
    {"pop", &List::popMethod},
    {"erase", &List::eraseMethod},
    {"remove", &List::removeMethod},
    {"extend", &List::extendMethod},
    {"extendat", &List::extendatMethod},
};

// 空参构造函数
List::List() : Object(OBJECT_LIST)
{
    assign(std::vector<std::shared_ptr<Object>>());
}

// 带参构造函数
List::List(const std::vector<std::shared_ptr<Object>> &elements) : Object(OBJECT_LIST)
{
    assign(elements);
}

// 列表对象初始化函数
void List::assign(const std::vector<std::shared_ptr<Object>> &elements)
{
    // 将传入的元素列表赋值给当前对象的元素列表
    this->elements = std::move(elements);
    // 重置迭代器
    reset();
}

// list对象打印函数
void List::print() const
{
    std::cout << toString() << std::endl;
}

// list对象字符串表示函数
std::string List::toString() const
{
    // 遍历列表元素列表，将每个元素的字符串表示拼接起来，返回拼接后的字符串
    std::string str = "[";
    int64_t max = elements.size() - 1;
    // 如果当前索引小于最大索引，则将当前元素的字符串和逗号拼接起来
    for (int64_t i = 0; i < max; ++i)
        str += elements[i]->toString() + ", ";
    // 如果当前索引等于最大索引，则将当前元素的字符串拼接起来
    if (elements.size() > 0)
        str += elements[max]->toString();
    // 拼接右括号
    str += "]";
    // 返回拼接后的字符串
    return str;
}

// 列表对象智能指针获取函数
std::shared_ptr<List> List::getSharedFromthis() const
{
    // 转换为非const的字符串对象指针
    return std::const_pointer_cast<List>(shared_from_this());
}

// 列表索引访问函数
std::shared_ptr<Object> List::operator[](int64_t index) const
{
    // 计算索引上限
    int64_t max = elements.size();
    // 判断索引值是否越界
    if (index >= max || index < -max)
        return newError("list index out of range");
    // 计算索引值
    if (index < 0)
        index += max;
    // 返回索引结果
    return elements[index];
}

// 列表迭代器迭代对象获取方法
std::shared_ptr<Object> List::next()
{
    // 如果迭代器已经到达列表末尾则返回nullptr
    if (iter == elements.end())
        return nullptr;
    // 获取当前迭代器指向的元素
    std::shared_ptr<Object> result = *iter;
    // 迭代器后移
    ++iter;
    // 返回迭代结果
    return result;
}

// 列表迭代器重置方法
void List::reset()
{
    iter = elements.begin();
}

// 列表迭代器起始元素获取方法
std::shared_ptr<Object> List::begin()
{
    // 如果列表为空则返回nullptr
    if (elements.size() == 0)
        return nullptr;
    return elements[0];
}

// 列表长度获取函数
size_t List::size() const
{
    return elements.size();
}

// 列表内置方法获取函数
std::shared_ptr<Object> List::getBuiltinMethod(const std::string &name) const
{
    // 获取函数名对应的迭代器
    std::unordered_map<std::string, List::method>::const_iterator it = methods.find(name);
    // 如果内置方法不存在则返回nullptr
    if (it == methods.end())
        return nullptr;
    // 否则返回内置方法对象
    return std::shared_ptr<BuiltinMethod>(new BuiltinMethod(name, it->second, getSharedFromthis()));
}

// 列表属性获取函数
std::shared_ptr<Object> List::getProperty(const std::string &name) const
{
    // 先尝试获取方法属性
    std::shared_ptr<Object> method = getBuiltinMethod(name);
    // 如果方法属性存在于方法对象中则返回方法属性
    if (method != nullptr)
        return method;
    // 否则返回错误对象
    return Object::newError("'list' object has no property '%s'", name.c_str());
}

// 列表属性设置函数
std::shared_ptr<Object> List::setProperty(const std::string &name, const std::shared_ptr<Object> &value)
{
    // 先尝试获取方法属性
    std::shared_ptr<Object> method = getBuiltinMethod(name);
    // 如果方法属性存在于方法对象中则返回错误对象
    if (method != nullptr)
        return Object::newError("'list' object property '%s' is read-only", name.c_str());
    // 否则返回错误对象
    return Object::newError("'list' object has no property '%s'", name.c_str());
}
