#include <evaluator/environment.h>
using namespace cpy::evaluator;
// 空参构造函数
Environment::Environment() : outer(nullptr)
{
}

// 带参构造函数
Environment::Environment(const std::shared_ptr<Environment> &outer) : outer(outer)
{
}

// 设置环境变量在变量映射哈希表中的值
void Environment::set(const std::string &name, const std::shared_ptr<Object> &value)
{
    // 在变量映射哈希表中设置变量的值
    store[name] = value;
}

// 获取环境变量在变量映射哈希表中的值
std::shared_ptr<Object> Environment::get(const std::string &name)
{
    // 先在当前环境中查找变量
    if (store.find(name) != store.end())
        // 如果找到了，返回变量的对象值
        return store.at(name);
    // 如果没有找到，在外层环境中查找变量
    if (outer != nullptr)
        // 进行递归查找
        return outer->get(name);
    // 如果始终没有找到，返回空指针
    return nullptr;
}

// 判断环境变量是否存在
bool Environment::isExist(const std::string &name)
{
    return store.find(name) != store.end();
}

// 删除环境变量
void Environment::remove(const std::string &name)
{
    // 先在当前环境中查找变量
    if (store.find(name) != store.end())
        // 如果找到了，删除变量
        store.erase(name);
}

// 清空环境变量
void Environment::clear()
{
    store.clear();
}