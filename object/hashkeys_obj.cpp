#include <object/hashkeys_obj.h>
using namespace cpy::object;
// 带参构造函数
HashKeys::HashKeys(const std::shared_ptr<Hash> &hash) : Object(OBJECT_HASH_KEYS)
{
    assign(hash);
}

// 哈希键对象初始化函数
void HashKeys::assign(const std::shared_ptr<Hash> &hash)
{
    this->hash = hash;
    reset();
}

// 哈希键对象打印函数
void HashKeys::print() const
{
    std::cout << toString() << std::endl;
}

// 哈希键对象字符串化函数
std::string HashKeys::toString() const
{
    // 创建输出字符串流
    std::ostringstream oss;
    // 添加左边部分
    oss << "hash_keys([";
    // 获取哈希对象的头元素
    std::shared_ptr<Object> item = hash->nextKey();
    // 如果头元素不为空
    if (item != nullptr)
    {
        // 添加头元素对应的字符串
        oss << item->toString();
        // 获取下一个元素
        item = hash->nextKey();
        // 如果下一个元素不为空
        while (item != nullptr)
        {
            // 添加逗号分隔符
            oss << ", ";
            // 添加下一个元素对应的字符串
            oss << item->toString();
            // 获取下一个元素
            item = hash->nextKey();
        }
        // 重置哈希对象的迭代器
        hash->reset();
    }
    // 添加右边部分
    oss << "])";
    // 返回输出字符串
    return oss.str();
}

// 哈希键迭代器方法实现
std::shared_ptr<Object> HashKeys::next()
{
    return hash->nextKey();
}

// 迭代器重置函数
void HashKeys::reset()
{
    hash->reset();
}

// 迭代器开始位置获取函数
std::shared_ptr<Object> HashKeys::begin()
{
    return hash->beginKey();
}

// 可迭代对象大小获取函数
size_t HashKeys::size() const
{
    return hash->size();
}

// 哈希键对象相等性比较函数
std::shared_ptr<Object> HashKeys::eq(const std::shared_ptr<HashKeys> &other) const
{
    // 如果两个哈希键对象是同一个对象,则返回true
    if (this== other.get())
        return newBool(true);
    // 如果两个哈希键长度不想等,则返回false
    if (hash->size() != other->size())
        return newBool(false);
    // 遍历两个哈希键对象
    std::shared_ptr<Object> item = hash->nextKey();
    while (item!= nullptr)
    {
        // 如果两个哈希键对象对应的元素不相等,则返回false
        std::shared_ptr<Object> other_item = other->next();
        if (!item->isEqual(other_item))
            return newBool(false);
        // 获取下一个元素
        item = hash->nextKey();
    }
    // 返回true
    return newBool(true);
}

// 哈希键对象不相等性比较函数
std::shared_ptr<Object> HashKeys::ne(const std::shared_ptr<HashKeys> &other) const
{
    // 如果两个哈希键对象是同一个对象,则返回true
    if (this== other.get())
        return newBool(false);
    // 如果两个哈希键长度不想等,则返回false
    if (hash->size() != other->size())
        return newBool(true);
    // 遍历两个哈希键对象
    std::shared_ptr<Object> item = hash->nextKey();
    while (item!= nullptr)
    {
        // 如果两个哈希键对象对应的元素不相等,则返回false
        std::shared_ptr<Object> other_item = other->next();
        if (!item->isEqual(other_item))
            return newBool(true);
        // 获取下一个元素
        item = hash->nextKey();
    }
    // 返回true
    return newBool(false);
}
