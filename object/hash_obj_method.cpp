#include <object/hash_obj.h>
#include <object/hashkeys_obj.h>
#include <object/hashvalues_obj.h>
#include <object/hashitems_obj.h>
using namespace cpy::object;
// 哈希表长度获取函数
// 哈希对象长度方法
std::shared_ptr<Object> Hash::lenMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不为0则返回错误对象
    if (args.size() != 0)
        return newError("len() takes no arguments (%d given)", args.size());
    // 将对象转换为哈希对象指针
    std::shared_ptr<Hash> hashObj = std::dynamic_pointer_cast<Hash>(obj);
    // 返回列表对象长度
    return newInteger(hashObj->size());
}

// 哈希对象键获取方法
std::shared_ptr<Object> Hash::keysMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 判断参数个数
    if (args.size() != 0)
        return newError("keys() takes no arguments (%d given)", args.size());
    // 将对象转换为哈希对象指针
    std::shared_ptr<Hash> hashObj = std::dynamic_pointer_cast<Hash>(obj);
    // 返回哈希键对象
    return std::shared_ptr<HashKeys>(new HashKeys(hashObj));
}

// 哈希对象值获取方法
std::shared_ptr<Object> Hash::valuesMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 判断参数个数
    if (args.size() != 0)
        return newError("values() takes no arguments (%d given)", args.size());
    // 将对象转换为哈希对象指针
    std::shared_ptr<Hash> hashObj = std::dynamic_pointer_cast<Hash>(obj);
    // 返回哈希值对象
    return std::shared_ptr<HashValues>(new HashValues(hashObj));
}

// 哈希对象键值对获取方法
std::shared_ptr<Object> Hash::itemsMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 判断参数个数
    if (args.size() != 0)
        return newError("items() takes no arguments (%d given)", args.size());
    // 将对象转换为哈希对象指针
    std::shared_ptr<Hash> hashObj = std::dynamic_pointer_cast<Hash>(obj);
    // 返回哈希项对象
    return std::shared_ptr<HashItems>(new HashItems(hashObj));
}

// 哈希对象键值查找方法
std::shared_ptr<Object> Hash::findMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 判断参数个数
    if (args.size() != 1)
        return newError("find() takes exactly one argument (%d given)", args.size());
    // 将参数转为可哈希对象指针
    std::shared_ptr<Hashable> hashable = std::dynamic_pointer_cast<Hashable>(args[0]);
    // 如果参数不可哈希则返回错误对象
    if (hashable == nullptr)
        return newError("unhashable type: '%s'", args[0]->getName().c_str());
    // 将对象转换为列表对象指针
    std::shared_ptr<Hash> hashObj = std::dynamic_pointer_cast<Hash>(obj);
    // 返回列表对象键值对
    return newBool(hashObj->pairs.find(hashable->hashKey()) != hashObj->pairs.end());
}

// 哈希对象键值获取方法
std::shared_ptr<Object> Hash::getMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数为0，则返回错误对象
    if (args.size() == 0)
        return newError("get() takes at least one argument (%d given)", args.size());
    // 如果参数个数为1，则调用1参数键值获取方法
    if (args.size() == 1)
        return getMethod(obj, args[0]);
    // 如果参数个数为2，则调用2参数键值获取方法
    if (args.size() == 2)
        return getMethod(obj, args[0], args[1]);
    // 如果参数个数大于2，则返回错误对象
    return newError("get() takes at most two arguments (%d given)", args.size());
}

// 哈希对象键值设置方法
std::shared_ptr<Object> Hash::setMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数为0，则返回错误对象
    if (args.size() == 0)
        return newError("set() takes at least one argument (%d given)", args.size());
    // 如果参数个数为1，则调用1参数设置方法
    if (args.size() == 1)
        return setMethod(obj, args[0]);
    // 如果参数个数为2，则调用2参数设置方法
    if (args.size() == 2)
        return setMethod(obj, args[0], args[1]);
    // 如果参数个数大于2，则返回错误对象
    return newError("set() takes at most two arguments (%d given)", args.size());
}

// 哈希对象键值删除方法
std::shared_ptr<Object> Hash::removeMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数为0，则返回错误对象
    if (args.size() == 0)
        return newError("remove() takes at least one argument (%d given)", args.size());
    // 如果参数个数为1，则调用无默认值删除方法
    if (args.size() == 1)
        return removeMethod(obj, args[0], newError("key not found: %s", args[0]->toString().c_str()));
    // 如果参数个数为2，则调用默认值删除方法
    if (args.size() == 2)
        return removeMethod(obj, args[0], args[1]);
    // 如果参数个数大于2，则返回错误对象
    return newError("remove() takes at most two arguments (%d given)", args.size());
}

// 哈希对象键值更新方法
std::shared_ptr<Object> Hash::updateMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数不等于1则返回错误对象
    if (args.size() != 1)
        return newError("update() takes exactly one argument (%d given)", args.size());
    // 如果参数为哈希表
    if (args[0]->getType() == OBJECT_HASH)
    {
        // 将参数转为哈希对象
        std::shared_ptr<Hash> otherHash = std::dynamic_pointer_cast<Hash>(args[0]);
        // 将对象转换为哈希对象指针
        std::shared_ptr<Hash> hashObj = std::dynamic_pointer_cast<Hash>(obj);
        // 遍历哈希表并将键值对加入哈希表
        for (std::unordered_map<HashKey, std::shared_ptr<HashPair>>::const_iterator it = otherHash->pairs.begin(); it != otherHash->pairs.end(); it++)
            hashObj->pairs[it->first] = it->second;
    }
    // 如果参数为其他类型
    else
    {
        // 将参数转为可迭代对象
        std::shared_ptr<Iterable> iterable = std::dynamic_pointer_cast<Iterable>(args[0]);
        // 如果参数为不可迭代对象则返回错误对象
        if (iterable == nullptr)
            return newError("'%s' object is not iterable", args[0]->getName().c_str());
        // 将对象转换为哈希对象指针
        std::shared_ptr<Hash> hashObj = std::dynamic_pointer_cast<Hash>(obj);
        // 获取头元素
        std::shared_ptr<Object> item = iterable->next();
        // 创建位置索引
        size_t pos = 0;
        // 遍历迭代器
        while (item != nullptr)
        {
            // 判断元素是否为可迭代对象
            std::shared_ptr<Iterable> itemIter = std::dynamic_pointer_cast<Iterable>(item);
            size_t len = (itemIter == nullptr) ? 1 : itemIter->size();
            // 如果元素长度不为2则返回错误对象
            if (len != 2)
                return newError("hash update sequence element #%d has length %d; 2 is required", pos, len);
            // 获取元素的第一个迭代对象
            std::shared_ptr<Object> key = itemIter->next();
            // 获取元素的第二个迭代对象
            std::shared_ptr<Object> value = itemIter->next();
            // 重置迭代器
            itemIter->reset();
            // 将键转为可哈希对象
            std::shared_ptr<Hashable> hashable = std::dynamic_pointer_cast<Hashable>(key);
            // 判断键是否可哈希
            if (hashable == nullptr)
                return newError("unhashable type: '%s'", key->getName().c_str());
            // 将键值对加入哈希表
            hashObj->pairs[hashable->hashKey()] = std::make_shared<HashPair>(key, value);
            // 位置索引加1
            pos++;
            // 获取下一个元素
            item = iterable->next();
        }
        // 重置迭代器
        iterable->reset();
    }
    // 返回空对象
    return newNull();
}

// 哈希对象键值清空方法
std::shared_ptr<Object> Hash::clearMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不为0则返回错误对象
    if (args.size() != 0)
        return newError("clear() takes no arguments (%d given)", args.size());
    // 将对象转换为哈希对象指针
    std::shared_ptr<Hash> hashObj = std::dynamic_pointer_cast<Hash>(obj);
    // 清空哈希对象
    hashObj->pairs.clear();
    // 返回空对象
    return newNull();
}

// 哈希键列表获取函数
std::vector<std::shared_ptr<Object>> Hash::getKeys(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs)
{
    // 创建键列表
    std::vector<std::shared_ptr<Object>> keys;
    // 预留空间
    keys.reserve(pairs.size());
    // 遍历哈希表
    for (std::unordered_map<HashKey, std::shared_ptr<HashPair>>::const_iterator it = pairs.begin(); it != pairs.end(); it++)
    {
        // 将键加入列表
        keys.emplace_back(it->second->key);
    }
    // 返回键列表
    return keys;
}

// 哈希值列表获取函数
std::vector<std::shared_ptr<Object>> Hash::getValues(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs)
{
    // 创建值列表
    std::vector<std::shared_ptr<Object>> values;
    // 预留空间
    values.reserve(pairs.size());
    // 遍历哈希表
    for (std::unordered_map<HashKey, std::shared_ptr<HashPair>>::const_iterator it = pairs.begin(); it != pairs.end(); it++)
    {
        // 将值加入列表
        values.emplace_back(it->second->value);
    }
    // 返回值列表
    return values;
}

// 哈希键值对列表获取函数
std::vector<std::shared_ptr<Object>> Hash::getItems(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs)
{
    // 创建键值对列表
    std::vector<std::shared_ptr<Object>> items;
    // 预留空间
    items.reserve(pairs.size());
    // 遍历哈希表
    for (std::unordered_map<HashKey, std::shared_ptr<HashPair>>::const_iterator it = pairs.begin(); it != pairs.end(); it++)
    {
        // 将键值对加入列表
        items.emplace_back(newList({it->second->key, it->second->value}));
    }
    // 返回键值对列表
    return items;
}

// 哈希对象键值设置方法
std::shared_ptr<Object> Hash::setMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &key, const std::shared_ptr<Object> &defaultVaule)
{
    // 判断参数是否可哈希
    std::shared_ptr<Hashable> hashable = std::dynamic_pointer_cast<Hashable>(key);
    // 如果参数不可哈希则返回错误对象
    if (hashable == nullptr)
        return newError("unhashable type: '%s'", key->getName().c_str());
    // 将对象转换为哈希对象指针
    std::shared_ptr<Hash> hashObj = std::dynamic_pointer_cast<Hash>(obj);
    // 获取哈希键
    HashKey hashKey = hashable->hashKey();
    // 获取哈希键对应的迭代器
    std::unordered_map<HashKey, std::shared_ptr<HashPair>>::const_iterator it = hashObj->pairs.find(hashKey);
    // 获取返回值
    std::shared_ptr<Object> value = (it != hashObj->pairs.end()) ? it->second->value : defaultVaule;
    // 更新键值对
    hashObj->pairs[hashKey] = std::shared_ptr<HashPair>(new HashPair(key, defaultVaule));
    // 返回值
    return value;
}

// 哈希对象键值获取方法
std::shared_ptr<Object> Hash::getMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &key, const std::shared_ptr<Object> &defaultValue)
{
    // 判断参数是否可哈希
    std::shared_ptr<Hashable> hashable = std::dynamic_pointer_cast<Hashable>(key);
    // 如果参数不可哈希则返回错误对象
    if (hashable == nullptr)
        return newError("unhashable type: '%s'", key->getName().c_str());
    // 将对象转换为哈希对象指针
    std::shared_ptr<Hash> hashObj = std::dynamic_pointer_cast<Hash>(obj);
    // 获取哈希键
    HashKey hashKey = hashable->hashKey();
    // 获取哈希键对应的迭代器
    std::unordered_map<HashKey, std::shared_ptr<HashPair>>::const_iterator it = hashObj->pairs.find(hashKey);
    // 返回对应的值
    return it != hashObj->pairs.end() ? it->second->value : defaultValue;
}

// 2参数哈希键值删除函数
std::shared_ptr<Object> Hash::removeMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &key, const std::shared_ptr<Object> &defaultValue)
{
    // 判断参数是否可哈希
    std::shared_ptr<Hashable> hashable = std::dynamic_pointer_cast<Hashable>(key);
    // 如果参数不可哈希则返回错误对象
    if (hashable == nullptr)
        return newError("unhashable type: '%s'", key->getName().c_str());
    // 将对象转换为哈希对象指针
    std::shared_ptr<Hash> hashObj = std::dynamic_pointer_cast<Hash>(obj);
    // 获取哈希键
    HashKey hashKey = hashable->hashKey();
    // 获取哈希键对应得键值对
    std::unordered_map<HashKey, std::shared_ptr<HashPair>>::const_iterator it = hashObj->pairs.find(hashKey);
    // 如果键值对不存在则返回默认值
    if (it == hashObj->pairs.end())
        return defaultValue;
    // 否则键值对存在则删除并返回值
    // 获取值
    std::shared_ptr<Object> value = it->second->value;
    // 删除键值对
    hashObj->pairs.erase(it);
    // 返回删除的值
    return it->second->value;
}
