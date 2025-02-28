#include <object/hashvalues_obj.h>
using namespace cpy::object;
// 带参构造函数
HashValues::HashValues(const std::shared_ptr<Hash> &hash) : Object(OBJECT_HASH_VALUES)
{
    assign(hash);
}

// 赋值函数
void HashValues::assign(const std::shared_ptr<Hash> &hash)
{
    this->hash = hash;
    reset();
}

// 哈希值对象打印函数
void HashValues::print() const
{
    std::cout << std::string() << std::endl;
}

// 哈希值对象字符串化函数
std::string HashValues::toString() const
{
    // 创建输出字符串流
    std::ostringstream oss;
    // 添加左边部分
    oss << "hash_values([";
    // 获取哈希对象的头元素
    std::shared_ptr<Object> item = hash->nextValue();
    // 如果头元素不为空
    if (item != nullptr)
    {
        // 添加头元素对应的字符串
        oss << item->toString();
        // 获取下一个元素
        item = hash->nextValue();
        // 如果下一个元素不为空
        while (item != nullptr)
        {
            // 添加逗号分隔符
            oss << ", ";
            // 添加下一个元素对应的字符串
            oss << item->toString();
            // 获取下一个元素
            item = hash->nextValue();
        }
        // 重置哈希对象的迭代器
        hash->reset();
    }
    // 添加右边部分
    oss << "])";
    // 返回输出字符串
    return oss.str();
}

// 哈希值迭代器元素获取函数
std::shared_ptr<Object> HashValues::next()
{
    return hash->nextValue();
}

// 哈希值迭代器重置函数
void HashValues::reset()
{
    hash->reset();
}

// 哈希值迭代器起始元素获取函数
std::shared_ptr<Object> HashValues::begin()
{
    return hash->beginValue();
}

// 哈希值迭代器元素个数获取函数
size_t HashValues::size() const
{
    return hash->size();
}

// 哈希值对象相等判断函数
std::shared_ptr<Object> HashValues::eq(const std::shared_ptr<HashValues> &other) const
{
    // 如果两个哈希值对象是同一个对象,则返回true
    if (this== other.get())
        return newBool(true);
    // 如果两个哈希值长度不想等,则返回false
    if (hash->size() != other->size())
        return newBool(false);
    // 遍历两个哈希值对象
    std::shared_ptr<Object> item = hash->nextValue();
    while (item!= nullptr)
    {
        // 如果两个哈希值对象对应的元素不相等,则返回false
        std::shared_ptr<Object> other_item = other->next();
        if (!item->isEqual(other_item))
            return newBool(false);
        // 获取下一个元素
        item = hash->nextValue();
    }
    // 返回true
    return newBool(true);
}

// 哈希值对象不等判断函数
std::shared_ptr<Object> HashValues::ne(const std::shared_ptr<HashValues> &other) const
{
    // 如果两个哈希值对象是同一个对象,则返回true
    if (this== other.get())
        return newBool(false);
    // 如果两个哈希值长度不想等,则返回false
    if (hash->size() != other->size())
        return newBool(true);
    // 遍历两个哈希值对象
    std::shared_ptr<Object> item = hash->nextValue();
    while (item!= nullptr)
    {
        // 如果两个哈希键对象对应的元素不相等,则返回false
        std::shared_ptr<Object> other_item = other->next();
        if (!item->isEqual(other_item))
            return newBool(true);
        // 获取下一个元素
        item = hash->nextValue();
    }
    // 返回true
    return newBool(false);
}
