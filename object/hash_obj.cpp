#include <object/hash_obj.h>
using namespace cpy::object;
// 哈希内置方法映射表
const std::unordered_map<std::string, Hash::method> Hash::methods = {
    {"len", &Hash::lenMethod},
    {"keys", &Hash::keysMethod},
    {"values", &Hash::valuesMethod},
    {"items", &Hash::itemsMethod},
    {"find", &Hash::findMethod},
    {"set", &Hash::setMethod},
    {"get", &Hash::getMethod},
    {"remove", &Hash::removeMethod},
    {"update", &Hash::updateMethod},
    {"clear", &Hash::clearMethod},
};
// 哈希对象空参构造函数
Hash::Hash() : Object(OBJECT_HASH)
{
    init(std::unordered_map<HashKey, std::shared_ptr<HashPair>>());
}

// 哈希对象带参构造函数
Hash::Hash(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs) : Object(OBJECT_HASH)
{
    init(pairs);
}

// 哈希对象初始化函数
void Hash::init(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs)
{
    // 初始化哈希表
    this->pairs = pairs;
    // 重置迭代器
    reset();
}

// 哈希对象打印函数
void Hash::print() const
{
    std::cout << toString() << std::endl;
}

// 哈希对象字符串表示函数
std::string Hash::toString() const
{
    std::string hashStr = "{";
    for (std::unordered_map<HashKey, std::shared_ptr<HashPair>>::const_iterator it = pairs.begin(); it != pairs.end(); it++)
    {
        if (it != pairs.begin())
            hashStr += ", " + it->second->toString();
        else
            hashStr += it->second->toString();
    }
    hashStr += "}";
    return hashStr;
}

// 哈希对象智能指针获取函数
std::shared_ptr<Object> Hash::getSharedFromthis() const
{
    // 转换为非const的哈希表对象指针
    return std::const_pointer_cast<Hash>(shared_from_this());
}

// 哈希对象迭代器对象获取函数
std::shared_ptr<Object> Hash::next()
{
    // 如果迭代器已经到达哈希表末尾则返回nullptr
    if (iter == pairs.end())
        return nullptr;
    // 获取当前迭代器指向的键元素
    std::shared_ptr<Object> result = (iter->second)->key;
    // 迭代器后移
    ++iter;
    // 返回迭代结果
    return result;
}

// 哈希键迭代器对象获取函数
std::shared_ptr<Object> Hash::nextKey()
{
    return next();
}

// 哈希值迭代器对象获取函数
std::shared_ptr<Object> Hash::nextValue()
{
    // 如果迭代器已经到达哈希表末尾则返回nullptr
    if (iter == pairs.end())
        return nullptr;
    // 获取当前迭代器指向的键值对元素
    std::shared_ptr<Object> result = (iter->second)->value;
    // 迭代器后移
    ++iter;
    // 返回迭代结果
    return result;
}

// 哈希键值对迭代器对象获取函数
std::shared_ptr<Object> Hash::nextPair()
{
    // 如果迭代器已经到达哈希表末尾则返回nullptr
    if (iter == pairs.end())
        return nullptr;
    // 获取当前迭代器指向的键值对元素
    std::shared_ptr<Object> result = iter->second;
    // 迭代器后移
    ++iter;
    // 返回迭代结果
    return result;
}

// 哈希对象重置函数
void Hash::reset()
{
    iter = pairs.begin();
}

// 哈希迭代器起始元素获取方法
std::shared_ptr<Object> Hash::begin()
{
    // 如果哈希表为空则返回nullptr
    if (pairs.size() == 0)
        return nullptr;
    return (pairs.begin()->second)->key;
}

// 哈希迭代器起始键获取方法
std::shared_ptr<Object> Hash::beginKey()
{
    return begin();
}

// 哈希迭代器起始值获取方法
std::shared_ptr<Object> Hash::beginValue()
{
    // 如果哈希表为空则返回nullptr
    if (pairs.size() == 0)
        return nullptr;
    return (pairs.begin()->second)->value;
}

// 哈希迭代器起始键值对获取方法
std::shared_ptr<Object> Hash::beginPair()
{
    // 如果哈希表为空则返回nullptr
    if (pairs.size() == 0)
        return nullptr;
    return pairs.begin()->second;
}

// 哈希对象长度获取函数
size_t Hash::size() const
{
    return pairs.size();
}

//  哈希表获取函数
const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &Hash::getPairs() const
{
    return pairs;
}

// 哈希表设置函数
void Hash::setPairs(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs)
{
    init(pairs);
}

// 哈希表键值对设置函数
std::shared_ptr<Object> Hash::setPair(const std::shared_ptr<Object> &key, const std::shared_ptr<Object> &value)
{
    // 将键对象转换为可哈希对象
    std::shared_ptr<Hashable> hashable = std::dynamic_pointer_cast<Hashable>(key);
    // 如果键对象无法转换为可哈希对象则返回错误对象
    if (hashable == nullptr)
        return newError("object is unhashable type: '%s'", key->getName().c_str());
    // 创建哈希键值对对象，并将其插入哈希表中
    pairs[hashable->hashKey()] = std::shared_ptr<object::HashPair>(new HashPair(key, value));
    // 返回空对象
    return newNull();
}

// 哈希对象内置方法获取函数
std::shared_ptr<Object> Hash::getBuiltinMethod(const std::string &name) const
{
    // 获取函数名对应的迭代器
    std::unordered_map<std::string, Hash::method>::const_iterator it = methods.find(name);
    // 如果内置方法不存在则返回nullptr
    if (it == methods.end())
        return nullptr;
    // 否则返回内置方法对象
    return std::shared_ptr<BuiltinMethod>(new BuiltinMethod(name, it->second, getSharedFromthis()));
}

// 哈希对象属性获取函数
std::shared_ptr<Object> Hash::getProperty(const std::string &name) const
{
    // 先尝试获取方法属性
    std::shared_ptr<Object> method = getBuiltinMethod(name);
    // 如果方法属性存在于方法对象中则返回方法属性
    if (method != nullptr)
        return method;
    // 否则返回错误对象
    return Object::newError("'hash' object has no property '%s'", name.c_str());
}

// 哈希对象属性设置函数
std::shared_ptr<Object> Hash::setProperty(const std::string &name, const std::shared_ptr<Object> &value)
{
    // 先尝试获取方法属性
    std::shared_ptr<Object> method = getBuiltinMethod(name);
    // 如果方法属性存在于方法对象中则返回错误对象
    if (method != nullptr)
        return Object::newError("'hash' object property '%s' is read-only", name.c_str());
    // 否则返回错误对象
    return Object::newError("'hash' object has no property '%s'", name.c_str());
}
