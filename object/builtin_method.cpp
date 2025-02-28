#include <object/builtin_method.h>
using namespace cpy::object;
// 带参构造函数
BuiltinMethod::BuiltinMethod(const std::string &name, const method &func, const std::shared_ptr<Object> &self) : Object(OBJECT_BUILTIN_METHOD)
{
    init(name, func, self);
}

// 调用方法对象函数
std::shared_ptr<Object> BuiltinMethod::call(const std::vector<std::shared_ptr<Object>> &args)
{
    return func(self, args);
}

// 初始化方法对象函数
void BuiltinMethod::init(const std::string &name, const method &func, const std::shared_ptr<Object> &self)
{
    this->name = name;
    this->func = func;
    this->self = self;
}

// 内置方法对象字符串化函数
std::string BuiltinMethod::toString() const
{
    std::ostringstream ss;
    ss << "<builtin method " << name << " of '" << self->getName() << "' at " << std::hex << std::showbase << reinterpret_cast<uintptr_t>(this) << ">";
    return ss.str();
}

// 内置方法对象打印函数
void BuiltinMethod::print() const
{
    std::cout << toString() << std::endl;
}

// 内置方法对象哈希键值获取函数
HashKey BuiltinMethod::hashKey() const
{
    return HashKey(type, std::hash<size_t>()(reinterpret_cast<size_t>(this)));
}
