#include <evaluator/math.h>
using namespace cpy::evaluator;
// 哈希表中缀运算符函数映射表
const std::unordered_map<std::string, Math::Hash::hashExpInfixFn> Math::Hash::hashExpInfixFns = {
    {"&", &Hash::hashInter},
    {"|", &Hash::hashUnion},
};

// 哈希表中缀运算符函数映射表
const std::unordered_map<std::string, Math::Hash::hashCmpInfixFn> Math::Hash::hashCmpInfixFns = {
    {"==", &Hash::eq},
    {"!=", &Hash::ne},
};

// 哈希表交集计算函数
std::unordered_map<HashKey, std::shared_ptr<HashPair>> Math::Hash::hashInter(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &left, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &right)
{
    // 如果左右两个哈希表是否指向同一个对象，则直接返回左哈希表
    if (&left == &right)
        return left;
    // 如果左哈希表大小大于右哈希表大小，则交换左右哈希表
    if (left.size() > right.size())
        return hashInter(right, left);
    // 创建一个空的结果哈希表
    std::unordered_map<HashKey, std::shared_ptr<HashPair>> result;
    // 遍历左哈希表
    for(auto &pair : left)
    {
        // 判断键值对在右哈希表中是否存在，如果存在则将键值对插入到结果哈希表中
        if (right.find(pair.first) != right.end())
            result[pair.first]=pair.second;
    }
    // 返回结果哈希表
    return result;
}

// 哈希表并集计算函数
std::unordered_map<HashKey, std::shared_ptr<HashPair>> Math::Hash::hashUnion(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &left, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &right)
{
    // 如果左右两个哈希表是否指向同一个对象，则直接返回左哈希表
    if (&left == &right)
        return left;
    // 将左哈希表复制到结果哈希表中
    std::unordered_map<HashKey, std::shared_ptr<HashPair>> result(left);
    // 遍历右哈希表
    for(auto &pair : right)
    {
        // 将键值对插入到结果哈希表中
        result[pair.first]=pair.second;
    }
    // 返回结果哈希表
    return result;
}

// 哈希表相等比较函数
std::shared_ptr<Object> Math::Hash::eq(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &left, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &right)
{
    // 如果左右两个哈希表指向同一个对象则返回true
    if (&left == &right)
        return Object::newBool(true);
    // 如果两个哈希表大小不相等则返回false
    if (left.size() != right.size())
        return Object::newBool(false);
    // 遍历左哈希表
    for (auto &pair : left)
    {
        // 计算键值对在右哈希表中的位置
        std::unordered_map<HashKey, std::shared_ptr<HashPair>>::const_iterator rightIter = right.find(pair.first);
        // 如果右哈希表中没有对应的键值对则返回false
        if (rightIter == right.end())
            return Object::newBool(false);
        // /* 处理冲突的情况 */
        // // 如果键对象不相等则返回false
        // if (!Object::isEqual(pair.second.key, rightIter->second.key))
        //     return Object::newBool(false);
    }
    // 返回true
    return Object::newBool(true);
}

// 哈希表不等比较函数
std::shared_ptr<Object> Math::Hash::ne(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &left, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &right)
{
    // 如果左右两个哈希表指向同一个对象则返回false
    if (&left == &right)
        return Object::newBool(false);
    // 如果两个哈希表大小不相等则返回true
    if (left.size()!= right.size())
        return Object::newBool(true);
    // 遍历左哈希表
    for (auto &pair : left)
    {
        // 计算键值对在右哈希表中的位置
        std::unordered_map<HashKey, std::shared_ptr<HashPair>>::const_iterator rightIter = right.find(pair.first);
        // 如果右哈希表中没有对应的键值对则返回true
        if (rightIter == right.end())
            return Object::newBool(true);
        // /* 处理冲突的情况 */
        // // 如果键对象不相等则返回true
        // if (!Object::isEqual(pair.second.key, rightIter->second.key))
        //     return Object::newBool(true);
    }
    // 返回false
    return Object::newBool(false);
}

// 哈希表中缀表达式计算求值函数
std::unordered_map<HashKey, std::shared_ptr<HashPair>> Math::Hash::evalHashExpInfix(const std::string &op, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &left, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &right)
{
    return (*hashExpInfixFns.at(op))(left, right);
}

// 哈希表比较表达式计算求值函数
std::shared_ptr<Object> Math::Hash::evalHashCmpInfix(const std::string &op, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &left, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &right)
{
    return (*hashCmpInfixFns.at(op))(left, right);
}

// 哈希表中缀表达式运算符有效性判断函数
bool Math::Hash::isValidInfixOp(const std::string &op)
{
    return isValidExpInfixOp(op) || isValidCmpInfixOp(op);
}

// 哈希表表达式运算符有效性判断函数
bool Math::Hash::isValidExpInfixOp(const std::string &op)
{
    return hashExpInfixFns.find(op) != hashExpInfixFns.end();
}

// 哈希表比较表达式运算符有效性判断函数
bool Math::Hash::isValidCmpInfixOp(const std::string &op)
{
    return hashCmpInfixFns.find(op) != hashCmpInfixFns.end();
}
