#include <object/function_obj.h>
using namespace cpy::object;
// 空参构造函数
Function::Function() : Object(OBJECT_FUNCTION)
{
}

// 带参构造函数
Function::Function(const std::string &name, const std::vector<std::shared_ptr<ast::Identifier>> &parameters, const std::unordered_map<std::string, std::shared_ptr<ast::Expression>> &defaults, const std::shared_ptr<ast::Block> &body, const std::shared_ptr<evaluator::Environment> &env)
{
    init(name, parameters, defaults, body, env);
}

// 函数对象初始化函数
void Function::init(const std::string &name, const std::vector<std::shared_ptr<ast::Identifier>> &parameters, const std::unordered_map<std::string, std::shared_ptr<ast::Expression>> &defaults, const std::shared_ptr<ast::Block> &body, const std::shared_ptr<evaluator::Environment> &env)
{
    this->type = OBJECT_FUNCTION;
    this->name = name;
    this->parameters = parameters;
    this->defaults = defaults;
    this->body = body;
    this->env = env;
}

// 函数对象字符串化函数
std::string Function::toString() const
{
    std::ostringstream ss;
    ss << "<function " << name << " at " << std::hex << std::showbase << reinterpret_cast<uintptr_t>(this) << ">";
    return ss.str();
}

// 函数对象打印函数
void Function::print() const
{
    std::cout << toString() << std::endl;
}

// 函数对象哈希键值获取函数
HashKey Function::hashKey() const
{
    // 哈希键值为对象类型和对象地址的哈希值
    return HashKey(type, std::hash<size_t>()(reinterpret_cast<size_t>(this)));
}