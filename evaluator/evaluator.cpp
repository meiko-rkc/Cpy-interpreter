#include <exception>
#include <evaluator/math.h>
#include <evaluator/evaluator.h>
using namespace cpy::evaluator;
// 空参构造函数
Evaluator::Evaluator()
{
}

// 错误对象判断函数
bool Evaluator::isError(const std::shared_ptr<Object> &object)
{
    return object->getType() == Object::OBJECT_ERROR;
}

// break对象判断函数
bool Evaluator::isBreak(const std::shared_ptr<Object> &object)
{
    return object->getType() == Object::OBJECT_BREAK;
}

// continue对象判断函数
bool Evaluator::isContinue(const std::shared_ptr<Object> &object)
{
    return object->getType() == Object::OBJECT_CONTINUE;
}

// return对象判断函数
bool Evaluator::isReturn(const std::shared_ptr<Object> &object)
{
    return object->getType() == Object::OBJECT_RETURN;
}

// 对象真假判断函数
bool Evaluator::isTrue(const std::shared_ptr<Object> &object)
{
    // 如果对象为空，返回假
    if (!object)
        return false;
    // 将对象转换为布尔类型对象
    std::shared_ptr<Object> judge = any2Bool(object);
    // 该布尔对象的布尔值
    return std::dynamic_pointer_cast<object::Bool>(judge)->value;
}

// 错误对象生成函数
std::shared_ptr<Object> Evaluator::newError(const char *format, ...)
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
    return std::shared_ptr<object::Error>(new object::Error(buffer));
}

// 整数对象生成函数
std::shared_ptr<Object> Evaluator::newInteger(int64_t value)
{
    return Object::newInteger(value);
}

// 浮点数对象生成函数
std::shared_ptr<Object> Evaluator::newFloat(double value)
{
    return Object::newFloat(value);
}

// 布尔对象生成函数
std::shared_ptr<Object> Evaluator::newBool(bool value)
{
    return Object::newBool(value);
}

// 字符串对象生成函数
std::shared_ptr<Object> Evaluator::newString(const std::string &value)
{
    return Object::newString(value);
}

// 空对象生成函数
std::shared_ptr<Object> Evaluator::newNull()
{
    return Object::newNull();
}

// 列表对象生成函数
std::shared_ptr<Object> Evaluator::newList(const std::vector<std::shared_ptr<Object>> &elements)
{
    return Object::newList(elements);
}

// 哈希对象生成函数
std::shared_ptr<Object> Evaluator::newHash(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs)
{
    // 创建一个哈希对象
    return std::shared_ptr<object::Hash>(new object::Hash(pairs));
}

// break对象生成函数
std::shared_ptr<Object> Evaluator::newBreak()
{
    return Object::newBreak();
}

// continue对象生成函数
std::shared_ptr<Object> Evaluator::newContinue()
{
    return Object::newContinue();
}

// 节点求值函数
std::shared_ptr<Object> Evaluator::eval(const std::shared_ptr<ast::Node> &node, std::shared_ptr<Environment> &env)
{
    switch (node->getType())
    {
    case Node::NODE_INTEGER:
        return evalInteger(std::dynamic_pointer_cast<ast::Integer>(node));
    case Node::NODE_FLOAT:
        return evalFloat(std::dynamic_pointer_cast<ast::Float>(node));
    case Node::NODE_BOOL:
        return evalBool(std::dynamic_pointer_cast<ast::Bool>(node));
    case Node::NODE_STRING:
        return evalString(std::dynamic_pointer_cast<ast::String>(node));
    case Node::NODE_NULL:
        return evalNull(std::dynamic_pointer_cast<ast::Null>(node));
    case Node::NODE_LIST:
        return evalList(std::dynamic_pointer_cast<ast::List>(node), env);
    case Node::NODE_HASH:
        return evalHash(std::dynamic_pointer_cast<ast::Hash>(node), env);
    case Node::NODE_INDEX:
        return evalIndex(std::dynamic_pointer_cast<ast::Index>(node), env);
    case Node::NODE_PROPERTY:
        return evalProperty(std::dynamic_pointer_cast<ast::Property>(node), env);
    case Node::NODE_IDENTIFIER:
        return evalIdentifier(std::dynamic_pointer_cast<ast::Identifier>(node), env);
    case Node::NODE_ASSIGN:
        return evalAssign(std::dynamic_pointer_cast<ast::Assign>(node), env);
    case Node::NODE_COMPOUND_ASSIGN:
        return evalCompoundAssign(std::dynamic_pointer_cast<ast::CompoundAssign>(node), env);
    case Node::NODE_TERNARY:
        return evalTernary(std::dynamic_pointer_cast<ast::Ternary>(node), env);
    case Node::NODE_BLOCK:
        return evalBlock(std::dynamic_pointer_cast<ast::Block>(node), env);
    case Node::NODE_IF:
        return evalIf(std::dynamic_pointer_cast<ast::If>(node), env);
    case Node::NODE_SWITCH:
        return evalSwitch(std::dynamic_pointer_cast<ast::Switch>(node), env);
    case Node::NODE_WHILE:
        return evalWhile(std::dynamic_pointer_cast<ast::While>(node), env);
    case Node::NODE_FOR:
        return evalFor(std::dynamic_pointer_cast<ast::For>(node), env);
    case Node::NODE_BREAK:
        return evalBreak(std::dynamic_pointer_cast<ast::Break>(node));
    case Node::NODE_CONTINUE:
        return evalContinue(std::dynamic_pointer_cast<ast::Continue>(node));
    case Node::NODE_RETURN:
        return evalReturn(std::dynamic_pointer_cast<ast::Return>(node), env);
    case Node::NODE_CALL:
        return evalCall(std::dynamic_pointer_cast<ast::Call>(node), env);
    case Node::NODE_IN:
        return evalIn(std::dynamic_pointer_cast<ast::In>(node), env);
    case Node::NODE_FUNCTION:
        return evalFunction(std::dynamic_pointer_cast<ast::Function>(node), env);
    case Node::NODE_PREFIX:
        return evalPrefix(std::dynamic_pointer_cast<ast::Prefix>(node), env);
    case Node::NODE_INFIX:
        return evalInfix(std::dynamic_pointer_cast<ast::Infix>(node), env);
    case Node::NODE_POSTFIX:
        return evalPostfix(std::dynamic_pointer_cast<ast::Postfix>(node), env);
    case Node::NODE_EXPRESSION_STATEMENT:
        return eval(std::dynamic_pointer_cast<ast::ExpressionStatement>(node)->expr, env);
    case Node::NODE_PROGRAM:
        return evalProgram(std::dynamic_pointer_cast<ast::Program>(node), env);
    default:
    {
        // 返回错误信息erro对象
        return newError("node type error: '%s'", node->getName().c_str());
    }
    }
}

// 程序求值函数
std::shared_ptr<Object> Evaluator::evalProgram(const std::shared_ptr<Program> &program, std::shared_ptr<Environment> &env)
{
    return evalProgram(program->statements, env);
}

// 程序语句列表求值函数
std::shared_ptr<Object> Evaluator::evalProgram(const std::list<std::shared_ptr<Statement>> &statements, std::shared_ptr<Environment> &env)
{
    // 遍历语句列表，逐个语句求值
    std::shared_ptr<Object> result;
    for (std::list<std::shared_ptr<Statement>>::const_iterator it = statements.begin(); it != statements.end(); ++it)
    {
        // 取得计算结果对象
        result = eval(*it, env);
        // 如果计算出错则退出循环
        if (isError(result))
            break;
    }
    // 返回最后一个语句的计算结果
    return result;
}

// 整数求值函数
std::shared_ptr<Object> Evaluator::evalInteger(const std::shared_ptr<ast::Integer> &integer)
{
    // 返回整数对象
    return newInteger(integer->value);
}

// 浮点数求值函数
std::shared_ptr<Object> Evaluator::evalFloat(const std::shared_ptr<ast::Float> &flt)
{
    // 返回浮点数对象
    return newFloat(flt->value);
}

// 布尔求值函数
std::shared_ptr<Object> Evaluator::evalBool(const std::shared_ptr<ast::Bool> &bl)
{
    return newBool(bl->value);
}

// 字符串求值函数
std::shared_ptr<Object> Evaluator::evalString(const std::shared_ptr<ast::String> &str)
{
    return newString(str->value);
}

// 空对象求值函数
std::shared_ptr<Object> Evaluator::evalNull(const std::shared_ptr<ast::Null> &null)
{
    return newNull();
}

// 列表求值函数
std::shared_ptr<Object> Evaluator::evalList(const std::shared_ptr<ast::List> &list, std::shared_ptr<Environment> &env)
{
    // 创建元素列表
    std::vector<std::shared_ptr<Object>> elements;
    // 预留空间
    elements.reserve(list->elements.size());
    // 遍历列表结点的元素列表
    for (auto &element : list->elements)
    {
        // 对元素表达式进行求值
        std::shared_ptr<Object> obj = eval(element, env);
        // 如果元素表达式计算出错，则直接返回错误对象
        if (isError(obj))
            return obj;
        // 将元素对象添加到元素列表中
        elements.emplace_back(obj);
    }
    // 返回列表对象
    return newList(elements);
}

// 哈希结点求值函数
std::shared_ptr<Object> Evaluator::evalHash(const std::shared_ptr<ast::Hash> &hash, std::shared_ptr<Environment> &env)
{
    // 创建哈希表
    std::unordered_map<HashKey, std::shared_ptr<HashPair>> pairs;
    // 遍历哈希结点的键值对列表
    for (auto &pair : hash->pairs)
    {
        // 对键表达式和值表达式分别进行求值
        std::shared_ptr<Object> keyObj = eval(pair.first, env);
        // 如果键表达式计算出错，则直接返回键错误对象
        if (isError(keyObj))
            return keyObj;
        // 强制转换键对象指针为可哈希类型指针
        std::shared_ptr<object::Hashable> hashable = std::dynamic_pointer_cast<object::Hashable>(keyObj);
        // 如果键类型为不支持哈希类型，则返回键错误对象
        if (!hashable)
            return newError("object is unhashable type: '%s'", keyObj->getName().c_str());
        // 对值表达式进行求值
        std::shared_ptr<Object> valueObj = eval(pair.second, env);
        // 如果值表达式计算出错，则直接返回值错误对象
        if (isError(valueObj))
            return valueObj;
        // 将键值对添加到哈希对象中
        pairs[hashable->hashKey()] = std::shared_ptr<HashPair>(new HashPair(keyObj, valueObj));
    }
    // 返回哈希对象
    return newHash(pairs);
}

// 索引结点求值函数
std::shared_ptr<Object> Evaluator::evalIndex(const std::shared_ptr<ast::Index> &indexNode, std::shared_ptr<Environment> &env)
{
    // 对索引结点的左表达式求值
    std::shared_ptr<Object> left = eval(indexNode->left, env);
    // 如果左子表达式计算出错，则直接返回左错误对象
    if (isError(left))
        return left;
    // 对索引结点的索引表达式求值
    std::shared_ptr<Object> index = eval(indexNode->index, env);
    // 如果索引表达式计算出错，则直接返回索引错误对象
    if (isError(index))
        return index;
    return evalIndex(left, index);
}

// 索引求值函数
std::shared_ptr<Object> Evaluator::evalIndex(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &index)
{
    // 判断左表达式的类型
    switch (left->getType())
    {
    // 如果左表达式是列表类型
    case Object::OBJECT_LIST:
    {
        // 如果索引表达式是整数类型，则对列表进行索引求值
        if (index->getType() == Object::OBJECT_INTEGER)
            return evalListIndex(left, index);
        // 如果索引表达式是布尔类型，则先将布尔类型转换为整数类型，然后对列表进行索引求值
        if (index->getType() == Object::OBJECT_BOOL)
            return evalListIndex(left, bool2Int(index));
    }
    // 如果左表达式是哈希类型
    case Object::OBJECT_HASH:
        return evalHashIndex(left, index);
    // 如果左表达式是字符串类型
    case Object::OBJECT_STRING:
    {
        // 如果索引表达式是整数类型，则对字符串进行索引求值
        if (index->getType() == Object::OBJECT_INTEGER)
            return evalStringIndex(left, index);
        // 如果索引表达式是布尔类型，则先将布尔类型转换为整数类型，然后对字符串进行索引求值
        if (index->getType() == Object::OBJECT_BOOL)
            return evalStringIndex(left, bool2Int(index));
    }
    // 否则，返回错误对象
    default:
        return newError("index operator not support: %s[%s]%", left->getName().c_str(), index->getName().c_str());
    }
}

// 列表索引求值函数
std::shared_ptr<Object> Evaluator::evalListIndex(const std::shared_ptr<Object> &list, const std::shared_ptr<Object> &index)
{
    // 将左操作数对象指针转换为列表对象
    std::shared_ptr<object::List> listObj = std::dynamic_pointer_cast<object::List>(list);
    // 将索引操对象指针转换为整数对象
    std::shared_ptr<object::Integer> indexObj = std::dynamic_pointer_cast<object::Integer>(index);
    // 获取索引值
    int64_t idx = indexObj->value;
    // 返回索引结果
    return (*listObj)[idx];
}

// 字符串索引求值函数
std::shared_ptr<Object> Evaluator::evalStringIndex(const std::shared_ptr<Object> &str, const std::shared_ptr<Object> &index)
{
    // 将左操作数对象指针转换为字符串对象
    std::shared_ptr<object::String> strObj = std::dynamic_pointer_cast<object::String>(str);
    // 将索引操对象指针转换为整数对象
    std::shared_ptr<object::Integer> indexObj = std::dynamic_pointer_cast<object::Integer>(index);
    // 获取索引值
    int64_t idx = indexObj->value;
    // 返回索引结果
    return (*strObj)[idx];
}

// 哈希索引求值函数
std::shared_ptr<Object> Evaluator::evalHashIndex(const std::shared_ptr<Object> &hash, const std::shared_ptr<Object> &index)
{
    // 将左操作数对象指针转换为哈希对象
    std::shared_ptr<object::Hash> hashObj = std::dynamic_pointer_cast<object::Hash>(hash);
    // 将索引操对象指针转换为可哈希对象
    std::shared_ptr<object::Hashable> hashable = std::dynamic_pointer_cast<object::Hashable>(index);
    // 判断索引对象是否可哈希
    if (!hashable)
        return newError("object is unhashable type: '%s'", index->getName().c_str());
    // 计算哈希键值
    std::unordered_map<object::HashKey, std::shared_ptr<object::HashPair>>::const_iterator it = hashObj->getPairs().find(hashable->hashKey());
    // 如果哈希表中不存在该键值，则返回错误对象
    // 判断索引与键值是否相等
    // if (it == hashObj->pairs.end()&&Object::isEqual(it->second.key, index))
    //     return newError("key not found: %s", index->toString().c_str());
    if (it == hashObj->getPairs().end())
        return newError("key not found: %s", index->toString().c_str());
    // 返回哈希表中对应键值的键值对对象
    return it->second->value;
}

// 索引结点赋值求值函数
std::shared_ptr<Object> Evaluator::evalIndexAssign(const std::shared_ptr<ast::Index> &indexNode, const std::shared_ptr<Object> &valObj, std::shared_ptr<Environment> &env)
{
    // 对索引结点的左操作数求值
    std::shared_ptr<Object> leftObj = eval(indexNode->left, env);
    // 如果左操作数对象是错误对象，则直接返回错误对象
    if (isError(leftObj))
        return leftObj;
    // 对索引结点的索引表达式求值
    std::shared_ptr<Object> indexObj = eval(indexNode->index, env);
    // 如果索引表达式对象是错误对象，则直接返回错误对象
    if (isError(indexObj))
        return indexObj;
    // 对索引结点的赋值表达式求值
    return evalIndexAssign(leftObj, indexObj, valObj);
}

// 索引结点赋值求值函数
std::shared_ptr<Object> Evaluator::evalIndexAssign(const std::shared_ptr<Object> &leftObj, const std::shared_ptr<Object> &indexObj, const std::shared_ptr<Object> &valObj)
{
    // 判断左操作数对象的类型
    switch (leftObj->getType())
    {
    // 如果左操作数对象是列表对象，则调用列表索引赋值函数进行赋值
    case Object::OBJECT_LIST:
        return evalListIndexAssign(leftObj, indexObj, valObj);
    // 如果左操作数对象是哈希对象，则调用哈希索引赋值函数进行赋值
    case Object::OBJECT_HASH:
        return evalHashIndexAssign(leftObj, indexObj, valObj);
    // 否则，返回错误对象
    default:
        break;
    }
    return newError("index assignment not support object: '%s'", leftObj->getName().c_str());
}

// 列表索引赋值求值函数
std::shared_ptr<Object> Evaluator::evalListIndexAssign(const std::shared_ptr<Object> &list, const std::shared_ptr<Object> &index, const std::shared_ptr<Object> &val)
{
    // 将左操作数对象指针转换为列表对象
    std::shared_ptr<object::List> listObj = std::dynamic_pointer_cast<object::List>(list);
    std::shared_ptr<Object> newIndex = index;
    // 如果索引表达式是布尔对象转换为整数对象
    if (index->getType() == Object::OBJECT_BOOL)
        newIndex = bool2Int(index);
    // 如果索引表达式不是整数类型，则返回错误对象
    if (newIndex->getType() != Object::OBJECT_INTEGER)
        return newError("index object must be integer");
    // 将索引对象指针转换为整数对象
    std::shared_ptr<object::Integer> indexObj = std::dynamic_pointer_cast<object::Integer>(newIndex);
    // 计算索引值，并计算索引上限
    int64_t idx = indexObj->value;
    int64_t max = listObj->elements.size();
    // 如果索引值小于0
    if (idx < 0)
    {
        // 计算具体索引值
        idx += max;
        // 如果索引值小于0，则返回错误对象
        if (idx < 0)
            return newError("list index out of range");
    }
    // 如果索引值大于等于索引上限，则在列表末尾添加新元素并在最后添加新元素
    else if (idx >= max)
    {
        for (int64_t i = max; i < idx; i++)
            listObj->elements.emplace_back(newNull());
        listObj->elements.emplace_back(val);
    }
    // 否则，将索引位置的元素替换为新元素
    else
        listObj->elements[idx] = val;
    // 返回空对象
    return newNull();
}

// 哈希索引赋值求值函数
std::shared_ptr<Object> Evaluator::evalHashIndexAssign(const std::shared_ptr<Object> &hash, const std::shared_ptr<Object> &index, const std::shared_ptr<Object> &val)
{
    // 将左操作数对象指针转换为哈希对象
    std::shared_ptr<object::Hash> hashObj = std::dynamic_pointer_cast<object::Hash>(hash);
    // 哈希对象调用键值对设置函数
    return hashObj->setPair(index, val);
}

// 属性结点求值函数
std::shared_ptr<Object> Evaluator::evalProperty(const std::shared_ptr<ast::Property> &propertyNode, std::shared_ptr<Environment> &env)
{
    // 计算左表达式对象
    std::shared_ptr<Object> leftObj = eval(propertyNode->object, env);
    // 如果计算结果是错误对象，则返回错误对象
    if (isError(leftObj))
        return leftObj;
    // 将右表达式转化为标识符
    std::shared_ptr<ast::Identifier> ident = std::dynamic_pointer_cast<ast::Identifier>(propertyNode->property);
    // 计算属性对象求值函数
    return evalProperty(leftObj, ident->value);
}

// 属性对象求值函数
std::shared_ptr<Object> Evaluator::evalProperty(const std::shared_ptr<Object> &obj, const std::string &property)
{
    // 判断左表达式对象类型
    switch (obj->getType())
    {
    // 如果左表达式是字符串对象
    case Object::OBJECT_STRING:
    {
        // 将左表达式对象指针转换为字符串对象
        std::shared_ptr<object::String> str = std::dynamic_pointer_cast<object::String>(obj);
        // 获取字符串对象的属性对象
        return str->getProperty(property);
    }
    // 如果左表达式是列表对象
    case Object::OBJECT_LIST:
    {
        // 将左表达式对象指针转换为列表对象
        std::shared_ptr<object::List> list = std::dynamic_pointer_cast<object::List>(obj);
        return list->getProperty(property);
    }
    // 如果左表达式是哈希对象
    case Object::OBJECT_HASH:
    {
        // 将左表达式对象指针转换为哈希对象
        std::shared_ptr<object::Hash> hash = std::dynamic_pointer_cast<object::Hash>(obj);
        return hash->getProperty(property);
    }
    default:
        return Object::newError("'%s' object has no property '%s'", obj->getName().c_str(), property.c_str());
    }
}

// 属性结点赋值求值函数
std::shared_ptr<Object> Evaluator::evalPropertyAssign(const std::shared_ptr<ast::Property> &propertyNode, const std::shared_ptr<Object> &valObj, std::shared_ptr<Environment> &env)
{
    // 计算左对象
    std::shared_ptr<Object> leftObj = eval(propertyNode->object, env);
    // 如果左对象是错误对象，则返回错误对象
    if (isError(leftObj))
        return leftObj;
    // 将右表达式转化为标识符
    std::shared_ptr<ast::Identifier> ident = std::dynamic_pointer_cast<ast::Identifier>(propertyNode->property);
    // 计算属性对象赋值求值函数
    return evalPropertyAssign(leftObj, ident->value, valObj);
}

// 属性结点对象赋值求值函数
std::shared_ptr<Object> Evaluator::evalPropertyAssign(const std::shared_ptr<Object> &obj, const std::string &property, const std::shared_ptr<Object> &val)
{
    // 判断左对象类型
    switch (obj->getType())
    {
    case Object::OBJECT_STRING:
    {
        // 将左对象指针转换为字符串对象
        std::shared_ptr<object::String> str = std::dynamic_pointer_cast<object::String>(obj);
        // 设置字符串对象的属性对象
        return str->setProperty(property, val);
    }
    case Object::OBJECT_LIST:
    {
        // 将左对象指针转换为列表对象
        std::shared_ptr<object::List> list = std::dynamic_pointer_cast<object::List>(obj);
        return list->setProperty(property, val);
    }
    case Object::OBJECT_HASH:
    {
        // 将左对象指针转换为哈希对象
        std::shared_ptr<object::Hash> hash = std::dynamic_pointer_cast<object::Hash>(obj);
        return hash->setProperty(property, val);
    }
    default:
        return Object::newError("'%s' object property assign error", obj->getName().c_str());
    }
}

// 标识符对象求值函数
std::shared_ptr<Object> Evaluator::evalIdentifier(const std::shared_ptr<ast::Identifier> &ident, std::shared_ptr<Environment> &env)
{
    // 在环境中查找标识符对应的对象
    std::shared_ptr<Object> obj = env->get(ident->value);
    // 如果找到了对应的对象，则返回该对象
    if (obj != nullptr)
        return obj;
    // 判断是否为内置函数
    std::shared_ptr<object::Builtin> builtin = object::Builtin::getBuiltinObj(ident->value);
    // 如果是内置函数，则返回内置函数对象
    if (builtin != nullptr)
        return builtin;
    // 否则，返回错误对象
    return newError("identifier not found: %s", ident->value.c_str());
}

// 赋值运算符求值函数
std::shared_ptr<Object> Evaluator::evalAssign(const std::shared_ptr<ast::Assign> &assign, std::shared_ptr<Environment> &env)
{
    // 对赋值运算符的右子表达式进行求值
    std::shared_ptr<object::Object> obj = eval(assign->value, env);
    // 如果赋值运算符的右子表达式计算出错，则直接返回右错误对象
    if (isError(obj))
        return obj;
    // 判断赋值运算符的左子表达式的类型
    switch (assign->name->getType())
    {
    // 如果赋值运算符的左子表达式是标识符类型
    case Node::NODE_IDENTIFIER:
    {
        std::shared_ptr<ast::Identifier> ident = std::dynamic_pointer_cast<ast::Identifier>(assign->name);
        env->set(ident->value, obj);
        return newNull();
    }
    // 如果赋值运算符的左子表达式是索引类型
    case Node::NODE_INDEX:
    {
        std::shared_ptr<ast::Index> indexNode = std::dynamic_pointer_cast<ast::Index>(assign->name);
        return evalIndexAssign(indexNode, obj, env);
    }
    // 如果赋值运算符左子表达式是属性类型
    case Node::NODE_PROPERTY:
    {
        std::shared_ptr<ast::Property> propertyNode = std::dynamic_pointer_cast<ast::Property>(assign->name);
        return evalPropertyAssign(propertyNode, obj, env);
    }
    default:
        // 否则返回错误对象
        return newError("unknown operator: %s %s %s", assign->name->getName().c_str(), "=", assign->value->getName().c_str());
    }
}

// 复合赋值运算符求值函数
std::shared_ptr<Object> Evaluator::evalCompoundAssign(const std::shared_ptr<ast::CompoundAssign> &cassign, std::shared_ptr<Environment> &env)
{
    // 对左子表达式求值
    std::shared_ptr<object::Object> left = eval(cassign->left, env);
    // 如果左子表达式计算出错，则直接返回左错误对象
    if (isError(left))
        return left;
    // 对右子表达式求值
    std::shared_ptr<object::Object> right = eval(cassign->right, env);
    // 如果右子表达式计算出错，则直接返回右错误对象
    if (isError(right))
        return right;
    // 通过复合赋值运算结点的运算符获取运算符字符串，即去除末尾的等号字符
    // += to +
    // >>= to >>
    std::string op = cassign->op.substr(0, cassign->op.size() - 1);
    // 对复合赋值运算进行中缀计算
    std::shared_ptr<Object> result = evalInfix(op, left, right);
    // 如果复合赋值运算计算出错，则直接返回复合赋值运算错误对象
    if (isError(result))
        return result;
    // 判断左子表达式的类型
    switch (cassign->left->getType())
    {
    // 如果左子表达式是标识符类型
    case Node::NODE_IDENTIFIER:
    {
        // 对左子表达式进行类型转换并将结果存储到对应的标识符中
        std::shared_ptr<ast::Identifier> ident = std::dynamic_pointer_cast<ast::Identifier>(cassign->left);
        env->set(ident->value, result);
        // 返回空对象
        return newNull();
    }
    // 如果左子表达式是索引类型
    case Node::NODE_INDEX:
    {
        // 对左子表达式进行类型转换并将结果存储到对应的索引中
        std::shared_ptr<ast::Index> indexNode = std::dynamic_pointer_cast<ast::Index>(cassign->left);
        return evalIndexAssign(indexNode, result, env);
    }
    // 如果左子表达式是属性类型
    case Node::NODE_PROPERTY:
    {
        // 对左子表达式进行类型转换并将结果存储到对应的属性中
        std::shared_ptr<ast::Property> propertyNode = std::dynamic_pointer_cast<ast::Property>(cassign->left);
        return evalPropertyAssign(propertyNode, result, env);
    }
    default:
        // 如果左子表达式不是标识符类型，则返回错误对象
        return newError("unknown operator: %s %s %s", left->getName().c_str(), cassign->op.c_str(), right->getName().c_str());
    }
}

// 三元运算符求值函数
std::shared_ptr<Object> Evaluator::evalTernary(const std::shared_ptr<ast::Ternary> &ternary, std::shared_ptr<Environment> &env)
{
    // 对条件表达式求值
    std::shared_ptr<Object> condition = eval(ternary->condition, env);
    // 如果条件表达式计算出错，则直接返回条件错误对象
    if (isError(condition))
        return condition;
    // 如果条件表达式为真，则对真分支表达式求值并返回结果
    if (isTrue(condition))
        return eval(ternary->trueExpr, env);
    // 否则条件表达式为假，则对假分支表达式求值并返回结果
    return eval(ternary->falseExpr, env);
}

// 代码块求值函数
std::shared_ptr<Object> Evaluator::evalBlock(const std::shared_ptr<ast::Block> &block, std::shared_ptr<Environment> &env)
{
    // 遍历代码块中的所有语句，并对每个语句求值
    for (auto &stmt : block->statements)
    {
        // 对语句表达式结点求值
        std::shared_ptr<Object> result = eval(stmt, env);
        // 如果求值结果为错误对象，则直接返回该错误对象
        if (isError(result))
            return result;
        // 处理 return，break，continue
        // 如果计算结果是break,continue或return对象，则直接返回该对象
        switch (result->getType())
        {
        case Object::OBJECT_BREAK:
        case Object::OBJECT_CONTINUE:
        case Object::OBJECT_RETURN:
            return result;
        default:
            break;
        }
    }
    // 返回空对象
    return newNull();
}

// if结点求值函数
std::shared_ptr<Object> Evaluator::evalIf(const std::shared_ptr<ast::If> &ifNode, std::shared_ptr<Environment> &env)
{
    // 遍历if结点内场景列表
    for (auto &scenario : ifNode->scenarios)
    {
        // 计算当前场景下的条件表达式
        std::shared_ptr<Object> condition = eval(scenario->condition, env);
        // 如果条件表达式计算结果为错误对象，返回该错误对象
        if (isError(condition))
            return condition;
        // 如果条件表达式计算结果为真
        if (isTrue(condition))
        {
            // 计算当前场景下的语句块
            std::shared_ptr<Object> result = eval(scenario->body, env);
            // 如果计算结果为错误对象，返回错误对象
            if (isError(result))
                return result;
            /* 处理 return，break，continue */
            // 如果计算结果为break,continue或return对象，则直接返回该对象
            switch (result->getType())
            {
            case Object::OBJECT_BREAK:
            case Object::OBJECT_CONTINUE:
            case Object::OBJECT_RETURN:
                return result;
            default:
                break;
            }
            // 跳出场景列表遍历
            break;
        }
    }
    // 返回空对象
    return newNull();
}

// switch结点求值函数
std::shared_ptr<Object> Evaluator::evalSwitch(const std::shared_ptr<ast::Switch> &switchNode, std::shared_ptr<Environment> &env)
{
    // 对switch结点的值求表达式值
    std::shared_ptr<Object> result = eval(switchNode->value, env);
    // 创建default结点
    std::shared_ptr<ast::Case> defaultCase = nullptr;
    // 创建代码块结果结点
    std::shared_ptr<Object> blockResult = nullptr;
    // 判断是否已经匹配到case结点
    bool isMatch = false;
    // 如果表达式值计算结果为错误对象，返回错误对象
    if (isError(result))
        return result;
    for (auto &caseNode : switchNode->cases)
    {
        // 判断case结点是否为default结点
        if (caseNode->isDefault)
        {
            // 如果已经存在default结点，返回错误对象，因为switch语句中只能有一个default结点
            if (defaultCase)
                return newError("multiple default cases in switch statement");
            // 如果没有default结点，将当前case结点赋值给defaultCase
            defaultCase = caseNode;
            // 进行下一个case结点的解析
            continue;
        }
        // 否则，计算case结点的值列表中的每个表达式值
        for (auto &value : caseNode->values)
        {
            // 对当前case结点求表达式值
            std::shared_ptr<Object> valueResult = eval(value, env);
            // 如果求值出错，则返回错误对象
            if (isError(valueResult))
                return valueResult;
            // 如果之前未发生过成功匹配，则进行匹配判断
            if (!isMatch)
                isMatch = Object::isEqual(result, valueResult);
            // 如果之前已经成功匹配当前case结点的列表中的表达式值与switch结点的值相等则进行代码块计算
            if (isMatch)
            {
                // 执行当前case结点的代码块
                blockResult = evalBlock(caseNode->body, env);
                // 如果代码块执行结果为错误对象或者return对象则直接返回
                if (isError(blockResult) || isReturn(blockResult))
                    return blockResult;
                // 如果代码执行结果为break对象，则跳出循环返回空对象
                else if (isBreak(blockResult))
                    return newNull();
                // 否则如果成功执行，则跳出循环，继续下一个case结点的解析
                break;
            }
        }
    }
    // 如果存在default结点且之前未提前结束，则执行default结点的代码块
    if (defaultCase)
    {
        // 执行default结点的代码块
        blockResult = evalBlock(defaultCase->body, env);
        // 如果代码块执行结果发生错误则返回错误对象，否则返回空对象
        if (isError(blockResult) || isReturn(blockResult))
            return blockResult;
    }
    // 返回空对象
    return newNull();
}

// while结点求值函数
std::shared_ptr<Object> Evaluator::evalWhile(const std::shared_ptr<ast::While> &whileNode, std::shared_ptr<Environment> &env)
{
    // 计算while结点的条件表达式
    std::shared_ptr<Object> condition = eval(whileNode->condition, env);
    // 如果条件表达式计算结果为错误对象，返回错误对象
    if (isError(condition))
        return condition;
    while (isTrue(condition))
    {
        // 计算while结点的代码块
        std::shared_ptr<Object> result = evalBlock(whileNode->body, env);
        // 如果计算结果为错误对象，返回错误对象
        if (isError(result))
            return result;
        // 处理 return，break，continue
        Object::Type type = result->getType();
        // 如果计算结果为break对象，跳出循环
        if (type == Object::OBJECT_BREAK)
            break;
        // 如果计算结果为return对象，则返回结果对象
        else if (type == Object::OBJECT_RETURN)
            return result;
        // 否则继续计算while结点的条件表达式，判断是否能继续执行循环
        condition = eval(whileNode->condition, env);
        // 如果计算结果为错误对象，返回错误对象
        if (isError(condition))
            return condition;
    }
    return newNull();
}

// for结点求值函数
std::shared_ptr<Object> Evaluator::evalFor(const std::shared_ptr<ast::For> &forNode, std::shared_ptr<Environment> &env)
{
    std::shared_ptr<Object> starterObj;
    std::shared_ptr<Object> condObj;
    std::shared_ptr<Object> closerObj;
    std::shared_ptr<Object> result;
    bool isMatch = true;
    // 计算for结点的起始表达式
    for (auto &starter : forNode->starters)
    {
        starterObj = eval(starter, env);
        // 如果起始表达式计算结果为错误对象，返回错误对象
        if (isError(starterObj))
            return starterObj;
    }
    while (true)
    {
        // 计算条件表达式
        for (auto &condition : forNode->conditions)
        {
            // 计算for结点的条件表达式
            condObj = eval(condition, env);
            // 如果条件表达式计算结果为错误对象，返回错误对象
            if (isError(condObj))
                return condObj;
            // 如果条件表达式计算结果为假，则跳出循环
            if (!isTrue(condObj))
            {
                isMatch = false;
                break;
            }
        }
        // 如果条件表达式计算结果为假，则跳出循环
        if (!isMatch)
            break;
        // 计算for结点的循环体代码块
        result = evalBlock(forNode->body, env);
        // 如果计算结果为错误对象，返回错误对象
        if (isError(result))
            return result;
        // 处理 return，break，continue
        Object::Type type = result->getType();
        // 如果计算结果为break对象，跳出循环
        if (type == Object::OBJECT_BREAK)
            break;
        // 如果计算结果为return对象，则返回结果对象
        else if (type == Object::OBJECT_RETURN)
            return result;
        // 计算步进表达式
        for (auto &closer : forNode->closers)
        {
            // 计算步进表达式
            closerObj = eval(closer, env);
            // 如果计算结果为错误对象，返回错误对象
            if (isError(closerObj))
                return closerObj;
        }
    }
    return newNull();
}

// break结点求值函数
std::shared_ptr<Object> Evaluator::evalBreak(const std::shared_ptr<ast::Break> &breakNode)
{
    return newBreak();
}

// continue结点求值函数
std::shared_ptr<Object> Evaluator::evalContinue(const std::shared_ptr<ast::Continue> &continueNode)
{
    return newContinue();
}

// return结点求值函数
std::shared_ptr<Object> Evaluator::evalReturn(const std::shared_ptr<ast::Return> &returnNode, std::shared_ptr<Environment> &env)
{
    // 对return结点的表达式求值
    std::shared_ptr<Object> retValue = eval(returnNode->value, env);
    // 如果表达式求值出错，则返回错误对象
    if (isError(retValue))
        return retValue;
    // 创建return对象
    std::shared_ptr<object::Return> retObj(new object::Return(retValue));
    // 返回return对象
    return retObj;
}

// call结点求值函数
std::shared_ptr<Object> Evaluator::evalCall(const std::shared_ptr<ast::Call> &callNode, std::shared_ptr<Environment> &env)
{
    // 对call结点的函数表达式求值
    std::shared_ptr<Object> obj = eval(callNode->function, env);
    // 如果函数表达式计算结果为错误对象，返回错误对象
    if (isError(obj))
        return obj;
    // 创建参数对象列表
    std::vector<std::shared_ptr<Object>> argsObj;
    // 对call结点的参数列表遍历求值
    for (auto &arg : callNode->arguments)
    {
        // 对每个参数求值
        std::shared_ptr<Object> argObj = eval(arg, env);
        // 如果参数求值结果为错误对象，返回错误对象
        if (isError(argObj))
            return argObj;
        // 将参数对象添加到参数对象列表中
        argsObj.emplace_back(argObj);
    }
    // 调用call求值函数，传入对象表达式值，参数对象列表和环境对象
    return evalCall(obj, argsObj, env);
}

// call调用求值函数
std::shared_ptr<Object> Evaluator::evalCall(const std::shared_ptr<Object> &obj, std::vector<std::shared_ptr<Object>> &args, std::shared_ptr<Environment> &env)
{
    // 判断表达式对象类型
    switch (obj->getType())
    {
    // 如果函数表达式是函数对象，调用函数对象的call函数
    case Object::OBJECT_FUNCTION:
        return evalCallFunction(obj, args, env);
    // 如果函数表达式是内置函数对象，调用内置函数对象的call函数
    case Object::OBJECT_BUILTIN:
        return evalCallBuiltin(obj, args);
    // 如果函数表达式是方法对象，调用方法对象的call函数
    case Object::OBJECT_BUILTIN_METHOD:
        return evalCallMethod(obj, args);
    default:
        return newError("object is not callable type: '%s'", obj->getName().c_str());
    }
}

// 函数调用求值函数
std::shared_ptr<Object> Evaluator::evalCallFunction(const std::shared_ptr<Object> &obj, std::vector<std::shared_ptr<Object>> &args, std::shared_ptr<Environment> &env)
{
    // 将对象表达式值指针转换为函数对象
    std::shared_ptr<object::Function> funcObj = std::dynamic_pointer_cast<object::Function>(obj);
    /* 处理默认参数 */
    // 如果参数列表长度小于函数对象的参数列表长度，则将默认参数添加到参数对象列表中
    for (size_t i = args.size(); i < funcObj->parameters.size(); i++)
    {
        // 获取函数对象的参数列表中第i个参数的对应迭代器
        std::unordered_map<std::string, std::shared_ptr<Expression>>::iterator iter = funcObj->defaults.find(funcObj->parameters[i]->value);
        // 如果函数对象的参数列表中第i个参数不存在默认参数，则返回错误对象
        if (iter == funcObj->defaults.end())
            return newError("function %s() missing %d required positional arguments", funcObj->name.c_str(), funcObj->parameters.size() - args.size());
        // 对每个参数求值
        std::shared_ptr<Object> argObj = eval(iter->second, env);
        // 如果参数求值结果为错误对象，返回错误对象
        if (isError(argObj))
            return argObj;
        // 将参数对象添加到参数对象列表中
        args.emplace_back(argObj);
    }
    // 对函数环境进行扩展，传入函数对象和参数对象列表，函数调用时的作用域
    std::shared_ptr<Environment> extendEnv = extendFunctionEnv(funcObj, args);
    // 如果函数环境扩展失败，则返回错误对象
    if (!extendEnv)
        return newError("function %s() takes %d positional arguments but %d were given", funcObj->name.c_str(), funcObj->parameters.size(), args.size());
    // 对函数对象的函数体求值
    std::shared_ptr<Object> result = evalBlock(funcObj->body, extendEnv);
    // 如果计算结果为返回对象，则返回返回对象的表达式值对象
    if (result->getType() == Object::OBJECT_RETURN)
    {
        // 将计算结果指针转换为返回对象指针
        std::shared_ptr<object::Return> retObj = std::dynamic_pointer_cast<object::Return>(result);
        // 返回返回对象的表达式值对象
        return retObj->value;
    }
    // 否则直接返回计算结果
    return result;
}

// 内置函数调用求值函数
std::shared_ptr<Object> Evaluator::evalCallBuiltin(const std::shared_ptr<Object> &obj, std::vector<std::shared_ptr<Object>> &args)
{
    // 将对象表达式值指针转换为内置函数对象
    std::shared_ptr<object::Builtin> builtin = std::dynamic_pointer_cast<object::Builtin>(obj);
    // 调用内置函数对象的call函数，传入参数对象列表
    return builtin->call(args);
}

// 方法调用求值函数
std::shared_ptr<Object> Evaluator::evalCallMethod(const std::shared_ptr<Object> &obj, std::vector<std::shared_ptr<Object>> &args)
{
    // 将对象表达式值指针转换为方法对象
    std::shared_ptr<object::BuiltinMethod> method = std::dynamic_pointer_cast<object::BuiltinMethod>(obj);
    // 调用方法对象的call函数，传入参数对象列表
    return method->call(args);
}

// 函数环境扩展函数
std::shared_ptr<Environment> Evaluator::extendFunctionEnv(const std::shared_ptr<object::Function> &funcObj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果函数对象的参数列表长度与参数对象列表长度不相等，则返回false
    if (funcObj->parameters.size() != args.size())
        return nullptr;
    // 创建函数对象的外部环境指针
    std::shared_ptr<Environment> env(new Environment(funcObj->env));
    // 遍历函数对象的参数列表
    for (size_t i = 0; i < funcObj->parameters.size(); i++)
    {
        // 将参数对象添加到函数对象的外部环境中
        env->set(funcObj->parameters[i]->value, args[i]);
    }
    return env;
}

// in结点求值函数
std::shared_ptr<Object> Evaluator::evalIn(const std::shared_ptr<ast::In> &in, std::shared_ptr<Environment> &env)
{
    // 对in结点的左操作数求值
    std::shared_ptr<Object> left = eval(in->left, env);
    // 如果左操作数计算结果为错误对象，返回错误对象
    if (isError(left))
        return left;
    // 对in结点的右操作数求值
    std::shared_ptr<Object> right = eval(in->right, env);
    // 如果右操作数计算结果为错误对象，返回错误对象
    if (isError(right))
        return right;
    // 调用in运算求值函数，传入左操作数对象和右操作数对象
    return evalIn(left, right);
}

// in运算求值函数
std::shared_ptr<Object> Evaluator::evalIn(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 判断右操作数对象的类型
    switch (right->getType())
    {
    // 如果右操作数对象是列表对象，则调用in列表求值函数
    case Object::OBJECT_LIST:
        return evalInList(left, right);
    // 如果右操作数对象是字符串对象，则调用in字符串求值函数
    case Object::OBJECT_STRING:
        return evalInStr(left, right);
    // 如果右操作数对象是哈希对象，则调用in哈希求值函数
    case Object::OBJECT_HASH:
        return evalInHash(left, right);
    default:
        break;
    }
    // 如果未能成功匹配类型，则返回错误对象
    return newError("in operator not support type: %s", right->getName().c_str());
}

// in列表求值函数
std::shared_ptr<Object> Evaluator::evalInList(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &list)
{
    // 将右操作数对象指针转换为列表对象
    std::shared_ptr<object::List> listObj = std::dynamic_pointer_cast<object::List>(list);
    // 遍历列表元素，判断是否有元素与左操作数对象相等，如果有则返回true布尔对象
    for (auto &item : listObj->elements)
        if (item->isEqual(left))
            return newBool(true);
    // 如果没有元素与左操作数对象相等，则返回false布尔对象
    return newBool(false);
}

// in字符串求值函数
std::shared_ptr<Object> Evaluator::evalInStr(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &str)
{
    // 如果左操作数对象不是字符串对象则直接返回false布尔对象
    if (left->getType() != Object::OBJECT_STRING)
        return newBool(false);
    // 将左操作数对象指针转换为字符串对象
    std::shared_ptr<object::String> leftStr = std::dynamic_pointer_cast<object::String>(left);
    // 将右操作数对象指针转换为字符串对象
    std::shared_ptr<object::String> rightStr = std::dynamic_pointer_cast<object::String>(str);
    // 在右操作数字符串中查找左操作数字符串
    size_t pos = rightStr->value.find(leftStr->value);
    // 如果查找失败，则返回false布尔对象，否则返回true布尔对象
    return pos == std::string::npos ? newBool(false) : newBool(true);
}

// in哈希求值函数
std::shared_ptr<Object> Evaluator::evalInHash(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &hash)
{
    // 将右操作数对象指针转换为哈希对象
    std::shared_ptr<object::Hash> hashObj = std::dynamic_pointer_cast<object::Hash>(hash);
    // 判断左操作数对象是否为可哈希对象，则返回错误对象
    std::shared_ptr<object::Hashable> hashable = std::dynamic_pointer_cast<object::Hashable>(left);
    if (!hashable)
        return newError("object is unhashable type: '%s'", left->getName().c_str());
    // 判断哈希表中是否存在该键值，如果存在则返回true布尔对象，否则返回false布尔对象
    std::unordered_map<object::HashKey, std::shared_ptr<object::HashPair>>::const_iterator iter = hashObj->getPairs().find(hashable->hashKey());
    return iter != hashObj->getPairs().end() ? newBool(true) : newBool(false);
}

// 函数结点求值函数
std::shared_ptr<Object> Evaluator::evalFunction(const std::shared_ptr<ast::Function> &func, std::shared_ptr<Environment> &env)
{
    // 创建函数对象
    std::shared_ptr<object::Function> funcObj(new object::Function(func->value, func->parameters, func->defaults, func->body, env));
    // 将函数对象添加到环境中
    env->set(funcObj->name, funcObj);
    // 返回函数对象
    return newNull();
}

// 整数转浮点数对象函数
std::shared_ptr<Object> Evaluator::int2Float(const std::shared_ptr<Object> &integer)
{
    // 通过动态类型转换将对象转换为整数对象
    std::shared_ptr<object::Integer> intObj = std::dynamic_pointer_cast<object::Integer>(integer);
    return newFloat(double(intObj->value));
}

// 整数转布尔对象函数
std::shared_ptr<Object> Evaluator::int2Bool(const std::shared_ptr<Object> &integer)
{
    // 通过动态类型转换将对象转换为整数对象
    std::shared_ptr<object::Integer> intObj = std::dynamic_pointer_cast<object::Integer>(integer);
    return newBool(intObj->value != 0);
}

// 浮点数转整数对象函数
std::shared_ptr<Object> Evaluator::float2Int(const std::shared_ptr<Object> &flt)
{
    // 通过动态类型转换将对象转换为浮点数对象
    std::shared_ptr<object::Float> fltObj = std::dynamic_pointer_cast<object::Float>(flt);
    return newInteger(int64_t(fltObj->value));
}

// 浮点数转布尔对象函数
std::shared_ptr<Object> Evaluator::float2Bool(const std::shared_ptr<Object> &flt)
{
    // 通过动态类型转换将对象转换为浮点数对象
    std::shared_ptr<object::Float> fltObj = std::dynamic_pointer_cast<object::Float>(flt);
    return newBool(fltObj->value != 0.0);
}

// 布尔转整数对象函数
std::shared_ptr<Object> Evaluator::bool2Int(const std::shared_ptr<Object> &bl)
{
    // 通过动态类型转换将对象转换为布尔数对象
    std::shared_ptr<object::Bool> blObj = std::dynamic_pointer_cast<object::Bool>(bl);
    return newInteger(int64_t(blObj->value));
}

// 布尔转浮点数对象函数
std::shared_ptr<Object> Evaluator::bool2Float(const std::shared_ptr<Object> &bl)
{
    // 通过动态类型转换将对象转换为布尔数对象
    std::shared_ptr<object::Bool> blObj = std::dynamic_pointer_cast<object::Bool>(bl);
    return newFloat(double(blObj->value));
}

// 字符串转整数对象函数
std::shared_ptr<Object> Evaluator::str2Int(const std::shared_ptr<Object> &str)
{
    // 将对象转换为字符串对象
    std::shared_ptr<object::String> strObj = std::dynamic_pointer_cast<object::String>(str);
    try
    {
        // 字符串读取的最后位置
        size_t pos;
        // 将字符串转换为整数
        int64_t value = std::stoll(strObj->value, &pos);
        // 如果字符串读取的最后位置不等于字符串的长度，则说明字符串无法转换为整数
        if (pos != strObj->value.size())
            return newError("string '%s' can't convert to integer", strObj->value.c_str());
        // 返回整数对象
        return newInteger(value);
    }
    // 捕获转换异常
    catch (const std::exception &e)
    {
        // 返回错误对象
        return newError("string '%s' can't convert to integer", strObj->value.c_str());
    }
}

// 字符串转浮点数对象函数
std::shared_ptr<Object> Evaluator::str2Float(const std::shared_ptr<Object> &str)
{
    // 将对象转换为字符串对象
    std::shared_ptr<object::String> strObj = std::dynamic_pointer_cast<object::String>(str);
    try
    {
        // 字符串读取的最后位置
        size_t pos;
        // 将字符串转换为浮点数
        double value = std::stod(strObj->value, &pos);
        // 如果字符串读取的最后位置不等于字符串的长度，则说明字符串无法转换为浮点数
        if (pos != strObj->value.size())
            return newError("string '%s' can't convert to float", strObj->value.c_str());
        // 返回整数对象
        return newFloat(value);
    }
    // 捕获转换异常
    catch (const std::exception &e)
    {
        // 返回错误对象
        return newError("string '%s' can't convert to float", strObj->value.c_str());
    }
}

// 字符串转布尔对象函数
std::shared_ptr<Object> Evaluator::str2Bool(const std::shared_ptr<Object> &str)
{
    // 通过动态类型转换将对象转换为字符串对象
    std::shared_ptr<object::String> strObj = std::dynamic_pointer_cast<object::String>(str);
    return newBool(!strObj->value.empty());
}

// 字符串转列表对象函数
std::shared_ptr<Object> Evaluator::str2List(const std::shared_ptr<Object> &str)
{
    // 通过动态类型转换将对象转换为字符串对象
    std::shared_ptr<object::String> strObj = std::dynamic_pointer_cast<object::String>(str);
    // 创建字符列表
    std::vector<std::shared_ptr<Object>> charElems;
    // 字符列表预分配内存
    charElems.reserve(strObj->value.size());
    // 遍历字符串中的每个字符
    for (auto &ch : strObj->value)
    {
        // 创建字符对象并添加到字符列表中
        charElems.emplace_back(newString(std::string(1, ch)));
    }
    // 返回列表对象
    return newList(charElems);
}

// 空值转布尔对象函数
std::shared_ptr<Object> Evaluator::null2Bool()
{
    // 空值对象直接转为false布尔数对象
    return newBool(false);
}

// 列表转布尔对象函数
std::shared_ptr<Object> Evaluator::list2Bool(const std::shared_ptr<Object> &list)
{
    // 通过动态类型转换将对象转换为列表对象
    std::shared_ptr<object::List> listObj = std::dynamic_pointer_cast<object::List>(list);
    return newBool(!listObj->elements.empty());
}

// 列表转哈希表对象函数
std::shared_ptr<Object> Evaluator::list2Hash(const std::shared_ptr<Object> &list)
{
    // 通过动态类型转换将对象转换为列表对象
    std::shared_ptr<object::List> listObj = std::dynamic_pointer_cast<object::List>(list);
    // 创建哈希表
    std::unordered_map<object::HashKey, std::shared_ptr<object::HashPair>>
        pairs;
    // 遍历列表中的每个元素
    for (size_t i = 0; i < listObj->elements.size(); i++)
    {
        // 获取元素对象
        std::shared_ptr<Object> elem = listObj->elements[i];
        // 判断元素类型
        switch (elem->getType())
        {
        // 如果元素是列表类型对象
        case Object::OBJECT_LIST:
        {
            // 强制将元素对象转化为列表对象
            std::shared_ptr<object::List> listElem = std::dynamic_pointer_cast<object::List>(elem);
            // 判断列表元素个数是否为2
            if (listElem->size() != 2)
                return newError("hash update sequence element #%d has length %d; 2 is required", i, listElem->size());
            // 将列表元素中的第一个元素转化为可哈希类型
            std::shared_ptr<object::Hashable> hashableElem = std::dynamic_pointer_cast<object::Hashable>(listElem->elements[0]);
            // 如果列表元素中的第一个元素不是可哈希类型
            if (!hashableElem)
                return newError("unhashable type: '%s'", listElem->elements[0]->getName().c_str());
            // 将哈希键值对对象添加到哈希表中
            pairs[hashableElem->hashKey()] = std::shared_ptr<object::HashPair>(new HashPair(listElem->elements[0], listElem->elements[1]));
            break;
        }
        // 如果元素是哈希类型对象
        case Object::OBJECT_HASH:
        {
            // 强制将元素对象转化为哈希表对象
            std::shared_ptr<object::Hash> hashElem = std::dynamic_pointer_cast<object::Hash>(elem);
            // 判断哈希表元素个数是否为2
            if (hashElem->size() != 2)
                return newError("hash update sequence element #%d has length %d; 2 is required", i, hashElem->size());
            // 获取哈希表
            std::unordered_map<object::HashKey, std::shared_ptr<object::HashPair>> hashPairs = hashElem->getPairs();
            // 遍历哈希表元素并分别确定为哈希键和哈希值
            std::unordered_map<object::HashKey, std::shared_ptr<object::HashPair>>::iterator iter = hashPairs.begin();
            // 获取键对象
            std::shared_ptr<Object> key = iter->second->key;
            // 将键对象转化为可哈希类型
            std::shared_ptr<object::Hashable> hashableKey = std::dynamic_pointer_cast<object::Hashable>(key);
            // 迭代器后移
            ++iter;
            // 获取值对象
            std::shared_ptr<Object> value = iter->second->key;
            // 将哈希键值对添加到哈希表中
            pairs[hashableKey->hashKey()] = std::shared_ptr<object::HashPair>(new HashPair(key, value));
            break;
        }
        // 如果元素是字符串类型对象
        case Object::OBJECT_STRING:
        {
            // 强制将元素对象转化为字符串对象
            std::shared_ptr<object::String> strElem = std::dynamic_pointer_cast<object::String>(elem);
            // 判断字符串长度是否为2
            if (strElem->size() != 2)
                return newError("hash update sequence element #%d has length %d; 2 is required", i, strElem->size());
            // 将字符串第一个字符作为键对象
            std::shared_ptr<Object> key = newString(strElem->value.substr(0, 1));
            // 将键对象转化为可哈希类型
            std::shared_ptr<object::Hashable> hashableKey = std::dynamic_pointer_cast<object::Hashable>(key);
            // 将字符串第二个字符作为值对象
            std::shared_ptr<Object> value = newString(strElem->value.substr(1, 1));
            // 将哈希键值对添加到哈希表中
            pairs[hashableKey->hashKey()] = std::shared_ptr<object::HashPair>(new HashPair(key, value));
            break;
        }
        // 如果为其他类型对象，则返回错误对象
        default:
            return newError("cannot convert hash update sequence element #%d to a hash key-value pair", i);
        }
    }
    // 返回哈希表对象
    return newHash(pairs);
}

// 哈希表转布尔对象函数
std::shared_ptr<Object> Evaluator::hash2Bool(const std::shared_ptr<Object> &hash)
{
    // 通过动态类型转换将对象转换为哈希表对象
    std::shared_ptr<object::Hash> hashObj = std::dynamic_pointer_cast<object::Hash>(hash);
    return newBool(!hashObj->getPairs().empty());
}

// 哈希表转列表对象函数
std::shared_ptr<Object> Evaluator::hash2List(const std::shared_ptr<Object> &hash)
{
    // 通过动态类型转换将对象转换为哈希表对象
    std::shared_ptr<object::Hash> hashObj = std::dynamic_pointer_cast<object::Hash>(hash);
    // 创建关键字列表
    std::vector<std::shared_ptr<Object>> keyElems;
    // 关键字列表预分配内存
    keyElems.reserve(hashObj->size());
    // 遍历哈希表中的每个键值对
    for (auto &pair : hashObj->getPairs())
    {
        // 创建关键字对象并添加到关键字列表中
        keyElems.emplace_back(pair.second->key);
    }
    // 返回列表对象
    return newList(keyElems);
}

// 任意类型转布尔对象函数
std::shared_ptr<Object> Evaluator::any2Bool(const std::shared_ptr<Object> &obj)
{
    // 判断对象类型
    switch (obj->getType())
    {
    // 布尔数类型
    case Object::OBJECT_BOOL:
        return obj;
    // 整数类型
    case Object::OBJECT_INTEGER:
        return int2Bool(obj);
    // 浮点数类型
    case Object::OBJECT_FLOAT:
        return float2Bool(obj);
    // 空值类型
    case Object::OBJECT_NULL:
        return null2Bool();
    }
    // 将对象转为可迭代对象
    std::shared_ptr<Iterable> iterable = std::dynamic_pointer_cast<Iterable>(obj);
    // 如果为可迭代对象，则返迭代对象长度转布尔类型，否则返回布尔对象True
    return (iterable != nullptr) ? newBool(iterable->size()) : newBool(true);
}

// 将任意类型转换为字符串对象
std::shared_ptr<Object> Evaluator::any2Str(const std::shared_ptr<Object> &any)
{
    // 如果对象类型是字符串类型，则直接返回该对象
    if (any->getType() == Object::OBJECT_STRING)
        return any;
    // 否则将对象转换为字符串对象并返回
    else
        return newString(any->toString());
}

// 任意类型转整数对象函数
std::shared_ptr<Object> Evaluator::any2Int(const std::shared_ptr<Object> &any)
{
    // 判断对象类型，并根据不同类型进行对应处理
    switch (any->getType())
    {
    // 字符串类型，调用字符串转整数函数
    case Object::OBJECT_STRING:
        return str2Int(any);
    // 整数类型，直接返回该对象
    case Object::OBJECT_INTEGER:
        return any;
    // 浮点数类型，调用浮点数转整数函数
    case Object::OBJECT_FLOAT:
        return float2Int(any);
    // 布尔数类型，调用布尔数转整数函数
    case Object::OBJECT_BOOL:
        return bool2Int(any);
    // 其他类型，返回空指针
    default:
        return nullptr;
    }
}

// 任意类型转浮点数对象函数
std::shared_ptr<Object> Evaluator::any2Float(const std::shared_ptr<Object> &any)
{
    // 判断对象类型，并根据不同类型进行对应处理
    switch (any->getType())
    {
    // 字符串类型，调用字符串转浮点数函数
    case Object::OBJECT_STRING:
        return str2Float(any);
    // 整数类型，调用整数转浮点数函数
    case Object::OBJECT_INTEGER:
        return int2Float(any);
    // 浮点数类型，直接返回该对象
    case Object::OBJECT_FLOAT:
        return any;
    // 布尔类型，调用布尔转浮点数函数
    case Object::OBJECT_BOOL:
        return bool2Float(any);
    // 其他类型，返回空指针
    default:
        return nullptr;
    }
}

// 任意类型转列表对象函数
std::shared_ptr<Object> Evaluator::any2List(const std::shared_ptr<Object> &any)
{
    // 将参数转为可迭代对象
    std::shared_ptr<Iterable> iterable = std::dynamic_pointer_cast<Iterable>(any);
    // 如果对象不可迭代，则返回错误对象
    if (iterable == nullptr)
        return newError("'%s' object is not iterable");
    // 创建元素列表
    std::vector<std::shared_ptr<Object>> elements;
    // 预留空间
    elements.reserve(iterable->size());
    // 获取迭代器第一个元素
    std::shared_ptr<Object> item = iterable->next();
    // 遍历元素列表
    while (item != nullptr)
    {
        // 将元素添加到列表中
        elements.emplace_back(item);
        // 获取下一个元素
        item = iterable->next();
    }
    // 迭代器重置
    iterable->reset();
    // 返回列表对象
    return newList(elements);
}

// 任意类型转哈希对象函数
std::shared_ptr<Object> Evaluator::any2Hash(const std::shared_ptr<Object> &any)
{
    // 将参数转为可迭代对象
    std::shared_ptr<Iterable> iterable = std::dynamic_pointer_cast<Iterable>(any);
    // 如果对象不可迭代，则返回错误对象
    if (iterable == nullptr)
        return newError("'%s' object is not iterable");
    // 创建哈希表
    std::unordered_map<object::HashKey, std::shared_ptr<object::HashPair>> pairs;
    // 获取迭代器第一个元素
    std::shared_ptr<Object> item = iterable->next();
    // 创建位置索引
    size_t pos = 0;
    // 遍历元素列表
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
        pairs[hashable->hashKey()] = std::make_shared<HashPair>(key, value);
        // 位置索引加1
        ++pos;
        // 获取下一个元素
        item = iterable->next();
    }
    // 迭代器重置
    iterable->reset();
    // 返回哈希对象
    return newHash(pairs);
}

// prefix前缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalPrefix(const std::shared_ptr<ast::Prefix> &prefix, std::shared_ptr<Environment> &env)
{
    // 获取运算符，并判断是否为自变化运算符
    std::string op = prefix->op;
    if (op == "++" || op == "--")
    {
        // 如果是则进行自变化运算
        return evalChgPrefix(prefix, env);
    }
    // 对右子表达式求值
    std::shared_ptr<Object> right = eval(prefix->right, env);
    // 如果右子表达式计算出错，则直接返回右错误对象
    if (isError(right))
        return right;
    // 判断运算符是否为逻辑运算符
    if (Math::Bool::isValidLogPrefixOp(op))
        // 如果是则进行相应的前缀逻辑运算
        return evalBoolLogPrefix(op, any2Bool(right));
    else
        // 否则进行相应的表达式前缀运算
        return evalObjExpPrefix(op, right);
}

// 标识符自变化运算符前缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalChgPrefix(const std::shared_ptr<ast::Prefix> &prefix, std::shared_ptr<Environment> &env)
{
    // 获取运算符和右子表达式
    std::string op = prefix->op;
    std::shared_ptr<ast::Expression> exp = prefix->right;
    // 判断右子表达式类型
    switch (exp->getType())
    {
    // 如果是标识符类型
    case Node::NODE_IDENTIFIER:
    {
        // 强制类型转化为标识符结点
        std::shared_ptr<Identifier> ident = std::dynamic_pointer_cast<ast::Identifier>(exp);
        return evalIdentChgPrefix(op, ident, env);
    }
    // 如果是索引类型
    case Node::NODE_INDEX:
    {
        // 强转索引结点
        std::shared_ptr<Index> index = std::dynamic_pointer_cast<ast::Index>(exp);
        return evalIndexChgPrefix(op, index, env);
    }
    // 如果是属性类型
    case Node::NODE_PROPERTY:
    {
        // 强转属性结点
        std::shared_ptr<Property> prop = std::dynamic_pointer_cast<ast::Property>(exp);
        return evalPropertyChgPrefix(op, prop, env);
    }
    // 其他类型，返回错误对象
    default:
        return newError("unknown operator: %s%s", op.c_str(), exp->getName().c_str());
    }
}

std::shared_ptr<Object> Evaluator::evalIdentChgPrefix(const std::string &op, const std::shared_ptr<ast::Identifier> &ident, std::shared_ptr<Environment> &env)
{
    // 获取标识符名称
    std::string name = ident->value;
    // 获取右标识符值对象
    std::shared_ptr<Object> right = evalIdentifier(ident, env);
    // 如果计算错误，则直接返回错误对象
    if (isError(right))
        return right;
    // 对右表达式进行相应表达式前缀运算
    std::shared_ptr<Object> result = evalObjChgPrefix(op, right);
    // 如果计算没有出错则对标识符对应的环境变量赋值，并返回结果值
    if (!isError(result))
        env->set(name, result);
    return result;
}

// 索引自变化运算符前缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalIndexChgPrefix(const std::string &op, const std::shared_ptr<ast::Index> &index, std::shared_ptr<Environment> &env)
{
    // 对索引结点的左表达式求值
    std::shared_ptr<Object> leftObj = eval(index->left, env);
    // 如果左子表达式计算出错，则直接返回左错误对象
    if (isError(leftObj))
        return leftObj;
    // 对索引结点的索引表达式求值
    std::shared_ptr<Object> indexObj = eval(index->index, env);
    // 如果索引表达式计算出错，则直接返回索引错误对象
    if (isError(indexObj))
        return indexObj;
    // 计算value对象
    std::shared_ptr<Object> valueObj = evalIndex(leftObj, indexObj);
    // 如果计算错误，则直接返回错误对象
    if (isError(valueObj))
        return valueObj;
    // 对value对象进行相应前缀运算
    std::shared_ptr<Object> result = evalObjChgPrefix(op, valueObj);
    // 如果没有计算出错则对索引结点进行赋值，并返回结果值
    if (!isError(result))
        evalIndexAssign(leftObj, indexObj, result);
    return result;
}

// 属性自变化运算符前缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalPropertyChgPrefix(const std::string &op, const std::shared_ptr<ast::Property> &property, std::shared_ptr<Environment> &env)
{
    // 对属性结点求值
    std::shared_ptr<Object> propertyObj = evalProperty(property, env);
    // 如果计算错误，则直接返回错误对象
    if (isError(propertyObj))
        return propertyObj;
    // 对属性计算结果进行相应前缀运算
    std::shared_ptr<Object> result = evalObjChgPrefix(op, propertyObj);
    // 如果没有计算出错则对属性结点进行赋值，并返回结果值
    if (!isError(result))
        evalPropertyAssign(property, result, env);
    return result;
}

// 对象自变化运算符前缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalObjChgPrefix(const std::string &op, const std::shared_ptr<Object> &obj)
{
    // 判断对象类型
    switch (obj->getType())
    {
    // 右子表达式为整数
    case Object::OBJECT_INTEGER:
        return evalIntExpPrefix(op, obj);
    // 右子表达式为浮点数
    case Object::OBJECT_FLOAT:
        return evalFloatExpPrefix(op, obj);
    // 右子表达式为布尔数
    case Object::OBJECT_BOOL:
        return evalIntExpPrefix(op, bool2Int(obj));
    // 返回错误对象
    default:
        return newError("unknown operator: %s%s", op.c_str(), obj->getName().c_str());
    }
}

// 对象前缀求值函数
std::shared_ptr<Object> Evaluator::evalObjExpPrefix(const std::string &op, const std::shared_ptr<Object> &right)
{
    // 判断右子表达式类型
    switch (right->getType())
    {
    // 右子表达式为整数
    case Object::OBJECT_INTEGER:
        return evalIntExpPrefix(op, right);
    // 右子表达式为浮点数
    case Object::OBJECT_FLOAT:
        return evalFloatExpPrefix(op, right);
    // 右子表达式为布尔数
    case Object::OBJECT_BOOL:
        return evalIntExpPrefix(op, bool2Int(right));
    // 右子表达式为字符串
    case Object::OBJECT_STRING:
        return evalStrExpPrefix(op, right);
    // 右子表达式为列表
    case Object::OBJECT_LIST:
        return evalListExpPrefix(op, right);
    // 否则返回错误对象
    default:
        return newError("unknown operator: %s%s", op.c_str(), right->getName().c_str());
    }
}

// 整数前缀表达式求值函数
inline std::shared_ptr<Object> Evaluator::evalIntExpPrefix(const std::string &op, const std::shared_ptr<Object> &right)
{
    // 对右表达式进行相应表达式前缀运算，并返回整数类型对象
    return newInteger(Math::Integer::evalIntExpPrefix(op, std::dynamic_pointer_cast<object::Integer>(right)->value));
}

// 浮点数前缀表达式求值函数
inline std::shared_ptr<Object> Evaluator::evalFloatExpPrefix(const std::string &op, const std::shared_ptr<Object> &right)
{
    // 对右表达式进行相应表达式前缀运算，并返回浮点数类型对象
    return newFloat(Math::Float::evalFloatExpPrefix(op, std::dynamic_pointer_cast<object::Float>(right)->value));
}

// 字符串前缀表达式求值函数
inline std::shared_ptr<Object> Evaluator::evalStrExpPrefix(const std::string &op, const std::shared_ptr<Object> &right)
{
    // 对右表达式进行相应表达式前缀运算，并返回字符串类型对象
    return newString(Math::String::evalStrExpPrefix(op, std::dynamic_pointer_cast<object::String>(right)->value));
}

// 布尔数前缀表达式求值函数
inline std::shared_ptr<Object> Evaluator::evalBoolLogPrefix(const std::string &op, const std::shared_ptr<Object> &right)
{
    // 对右表达式做布尔逻辑运算，并返回对应布尔值
    return newBool(Math::Bool::evalBoolLogPrefix(op, std::dynamic_pointer_cast<object::Bool>(right)->value));
}

// 列表前缀表达式求值函数
inline std::shared_ptr<Object> Evaluator::evalListExpPrefix(const std::string &op, const std::shared_ptr<Object> &right)
{
    // 对右表达式进行相应表达式前缀运算，并返回列表类型对象
    return newList(Math::List::evalListExpPrefix(op, std::dynamic_pointer_cast<object::List>(right)->elements));
}

// infix中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalInfix(const std::shared_ptr<ast::Infix> &infix, std::shared_ptr<Environment> &env)
{
    // 先对左子表达式求值
    std::shared_ptr<Object> left = eval(infix->left, env);
    // 如果左子表达式计算出错，则直接返回左表达式错误对象
    if (isError(left))
        return left;
    // 再对右子表达式求值
    std::shared_ptr<Object> right = eval(infix->right, env);
    // 如果右子表达式计算出错，则直接返回右错误对象
    if (isError(right))
        return right;
    // 对左右子表达式进行计算
    return evalInfix(infix->op, left, right);
}

// infix中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 如果当前中缀运算符为逻辑运算
    if (Math::Bool::isValidLogInfixOp(op))
        // 对左右子表达式进行逻辑计算
        return evalBoolInfix(op, any2Bool(left), any2Bool(right));
    // 否则进行算术运算或者比较运算
    else
    {
        /* 判断左表达式类型 */
        switch (left->getType())
        {
        /* 判断右表达式类型 */
        // 左表达式为整数
        case Object::OBJECT_INTEGER:
        {
            // 如果是字符串或者列表，且操作符为*，则对左右子表达式进行字符串或列表计算
            if (op == "*")
            {
                if (right->getType() == Object::OBJECT_STRING)
                    return newString(Math::String::mul(std::dynamic_pointer_cast<object::String>(right)->value, std::dynamic_pointer_cast<object::Integer>(left)->value));
                if (right->getType() == Object::OBJECT_LIST)
                    return newList(Math::List::mul(std::dynamic_pointer_cast<object::List>(right)->elements, std::dynamic_pointer_cast<object::Integer>(left)->value));
            }
            // 如果是整数，则对左右子表达式进行整数计算
            if (right->getType() == Object::OBJECT_INTEGER)
                return evalIntInfix(op, left, right);
            // 如果是浮点数，则对左右子表达式进行浮点数计算
            else if (right->getType() == Object::OBJECT_FLOAT)
                return evalFloatInfix(op, int2Float(left), right);
            // 如果是布尔数，则对左右子表达式进行整数计算
            else if (right->getType() == Object::OBJECT_BOOL)
                return evalIntInfix(op, left, bool2Int(right));
            // 否则处理不同类型处理程序
            else
                return evalDiffTypeInfix(op, left, right);
            break;
        }
        // 左表达式为浮点数
        case Object::OBJECT_FLOAT:
        {
            // 如果是整数或浮点数，则对左右子表达式进行浮点数计算
            if (right->getType() == Object::OBJECT_INTEGER)
                return evalFloatInfix(op, left, int2Float(right));
            else if (right->getType() == Object::OBJECT_FLOAT)
                return evalFloatInfix(op, left, right);
            // 如果是布尔数，则对左右子表达式进行浮点数计算
            else if (right->getType() == Object::OBJECT_BOOL)
                return evalFloatInfix(op, left, bool2Float(right));
            // 否则处理不同类型处理程序
            else
                return evalDiffTypeInfix(op, left, right);
            break;
        }
        // 左表达式为布尔数
        case Object::OBJECT_BOOL:
        {
            // 如果是字符串或者列表，且操作符为*，则对左右子表达式进行字符串或者列表计算
            if (op == "*")
            {
                if (right->getType() == Object::OBJECT_STRING)
                    return newString(Math::String::mul(std::dynamic_pointer_cast<object::String>(right)->value, int64_t(std::dynamic_pointer_cast<object::Bool>(left)->value)));
                if (right->getType() == Object::OBJECT_LIST)
                    return newList(Math::List::mul(std::dynamic_pointer_cast<object::List>(right)->elements, int64_t(std::dynamic_pointer_cast<object::Bool>(left)->value)));
            }
            // 如果是整数，则对左右子表达式进行整数计算
            if (right->getType() == Object::OBJECT_INTEGER)
                return evalIntInfix(op, bool2Int(left), right);
            // 如果是浮点数，则对左右子表达式进行浮点数计算
            else if (right->getType() == Object::OBJECT_FLOAT)
                return evalFloatInfix(op, bool2Float(left), right);
            // 如果是布尔数，则对左右子表达式进行整数计算
            else if (right->getType() == Object::OBJECT_BOOL)
                return evalIntInfix(op, bool2Int(left), bool2Int(right));
            // 否则处理不同类型处理程序
            else
                return evalDiffTypeInfix(op, left, right);
            break;
        }
        // 左表达式为字符串
        case Object::OBJECT_STRING:
        {
            // 如果是整数或布尔数，且操作符为*，则对左右子表达式进行字符串对应计算
            if (op == "*")
            {
                if (right->getType() == Object::OBJECT_INTEGER)
                    return newString(Math::String::mul(std::dynamic_pointer_cast<object::String>(left)->value, std::dynamic_pointer_cast<object::Integer>(right)->value));
                if (right->getType() == Object::OBJECT_BOOL)
                    return newString(Math::String::mul(std::dynamic_pointer_cast<object::String>(left)->value, int64_t(std::dynamic_pointer_cast<object::Bool>(right)->value)));
            }
            // 如果是字符串，则对左右子表达式进行字符串对应计算
            if (right->getType() == Object::OBJECT_STRING)
                return evalStrInfix(op, left, right);
            else
                return evalDiffTypeInfix(op, left, right);
            break;
        }
        // 左表达式为空值
        case Object::OBJECT_NULL:
        {
            if (right->getType() == Object::OBJECT_NULL)
                return evalNullInfix(op, left, right);
            else
                return evalDiffTypeInfix(op, left, right);
            break;
        }
        // 左表达式为列表
        case Object::OBJECT_LIST:
        {
            // 如果是整数或布尔数，且操作符为*，则对左右子表达式进行列表对应计算
            if (op == "*")
            {
                if (right->getType() == Object::OBJECT_INTEGER)
                    return newList(Math::List::mul(std::dynamic_pointer_cast<object::List>(left)->elements, std::dynamic_pointer_cast<object::Integer>(right)->value));
                if (right->getType() == Object::OBJECT_BOOL)
                    return newList(Math::List::mul(std::dynamic_pointer_cast<object::List>(left)->elements, int64_t(std::dynamic_pointer_cast<object::Bool>(right)->value)));
            }
            // 如果是列表，则对左右子表达式进行列表对应计算
            if (right->getType() == Object::OBJECT_LIST)
                return evalListInfix(op, left, right);
            else
                return evalDiffTypeInfix(op, left, right);
        }
        // 左表达式为哈希表
        case Object::OBJECT_HASH:
        {
            // 如果是哈希表，则对左右子表达式进行哈希表对应计算
            if (right->getType() == Object::OBJECT_HASH)
                return evalHashInfix(op, left, right);
            else
                return evalDiffTypeInfix(op, left, right);
        }
        // 左表达式为哈希键对象
        case Object::OBJECT_HASH_KEYS:
        {
            if (right->getType() == Object::OBJECT_HASH_KEYS)
                return evalHashKeysInfix(op, left, right);
            else
                return evalDiffTypeInfix(op, left, right);
        }
        // 左表达式为哈希值对象
        case Object::OBJECT_HASH_VALUES:
        {
            if (right->getType() == Object::OBJECT_HASH_VALUES)
                return evalHashValuesInfix(op, left, right);
            else
                return evalDiffTypeInfix(op, left, right);
        }
        // 左表达式为类型对象
        case Object::OBJECT_TYPE:
        {
            // 如果是类型对象，则对左右子表达式进行类型对象对应计算
            if (right->getType() == Object::OBJECT_TYPE)
                return evalTypeInfix(op, left, right);
            else
                return evalDiffTypeInfix(op, left, right);
        }
        // 左表达式为函数对象
        case Object::OBJECT_FUNCTION:
        {
            if (right->getType() == Object::OBJECT_FUNCTION)
                return evalFunctionInfix(op, left, right);
            else
                return evalDiffTypeInfix(op, left, right);
        }
        // 左表达式为内置函数对象
        case Object::OBJECT_BUILTIN:
        {
            if (right->getType() == Object::OBJECT_BUILTIN)
                return evalBuiltinInfix(op, left, right);
            else
                return evalDiffTypeInfix(op, left, right);
        }
        // 左表达式为内置方法对象
        case Object::OBJECT_BUILTIN_METHOD:
        {
            if (right->getType() == Object::OBJECT_BUILTIN_METHOD)
                return evalBuiltinMethodInfix(op, left, right);
            else
                return evalDiffTypeInfix(op, left, right);
        }
        default:
            break;
        }
    }
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 整数中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalIntInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 取得左右子表达式的值
    int64_t leftValue = std::dynamic_pointer_cast<object::Integer>(left)->value;
    int64_t rightValue = std::dynamic_pointer_cast<object::Integer>(right)->value;
    // 判断运算符类型
    // 如果为表达式类型
    if (Math::Integer::isValidExpInfixOp(op))
        // 如果合法，则对左右子表达式进行计算
        return newInteger(Math::Integer::evalIntExpInfix(op, leftValue, rightValue));
    // 如果为逻辑运算类型
    if (Math::Integer::isValidCmpInfixOp(op))
        // 如果合法，则对左右子表达式进行逻辑计算
        return newBool(Math::Integer::evalIntCmpInfix(op, leftValue, rightValue));
    // 否则返回错误对象
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 浮点数中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalFloatInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 取得左右子表达式的值
    double leftValue = std::dynamic_pointer_cast<object::Float>(left)->value;
    double rightValue = std::dynamic_pointer_cast<object::Float>(right)->value;
    // 判断运算符类型
    // 如果为表达式类型
    if (Math::Float::isValidExpInfixOp(op))
        // 如果合法，则对左右子表达式进行计算
        return newFloat(Math::Float::evalFloatExpInfix(op, leftValue, rightValue));
    // 如果为逻辑运算类型
    if (Math::Float::isValidCmpInfixOp(op))
        // 如果合法，则对左右子表达式进行逻辑计算
        return newBool(Math::Float::evalFloatCmpInfix(op, leftValue, rightValue));
    // 否则返回错误对象
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 布尔数中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalBoolInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    return newBool(Math::Bool::evalBoolLogInfix(op, std::dynamic_pointer_cast<object::Bool>(left)->value, std::dynamic_pointer_cast<object::Bool>(right)->value));
}

// 字符串中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalStrInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 取得左右子表达式的值
    std::string leftValue = std::dynamic_pointer_cast<object::String>(left)->value;
    std::string rightValue = std::dynamic_pointer_cast<object::String>(right)->value;
    // 判断运算符类型
    // 如果为表达式类型
    if (Math::String::isValidExpInfixOp(op))
        // 如果合法，则对左右子表达式进行计算
        return newString(Math::String::evalStrExpInfix(op, leftValue, rightValue));
    // 如果为比较运算类型
    if (Math::String::isValidCmpInfixOp(op))
        // 如果合法，则对左右子表达式进行比较计算
        return newBool(Math::String::evalStrCmpInfix(op, leftValue, rightValue));
    // 否则返回错误对象
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 空值中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalNullInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    if (op == "==")
        return newBool(true);
    if (op == "!=")
        return newBool(false);
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 列表中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalListInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 将左右对象强转成列表对象
    std::shared_ptr<object::List> leftList = std::dynamic_pointer_cast<object::List>(left);
    std::shared_ptr<object::List> rightList = std::dynamic_pointer_cast<object::List>(right);
    // 判断运算符类型
    // 如果为表达式类型
    if (Math::List::isValidExpInfixOp(op))
        // 如果合法，则对左右子表达式进行计算
        return newList(Math::List::evalListExpInfix(op, leftList->elements, rightList->elements));
    // 如果为比较运算类型
    if (Math::List::isValidCmpInfixOp(op))
        return Math::List::evalListCmpInfix(op, leftList->elements, rightList->elements);
    // 否则返回错误对象
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 哈希表中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalHashInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 将左右对象强转成哈希表对象
    std::shared_ptr<object::Hash> leftHash = std::dynamic_pointer_cast<object::Hash>(left);
    std::shared_ptr<object::Hash> rightHash = std::dynamic_pointer_cast<object::Hash>(right);
    // 判断运算符类型
    // 如果为表达式类型
    if (Math::Hash::isValidExpInfixOp(op))
        // 如果合法，则对左右子表达式进行计算
        return newHash(Math::Hash::evalHashExpInfix(op, leftHash->getPairs(), rightHash->getPairs()));
    // 如果为比较运算类型
    if (Math::Hash::isValidCmpInfixOp(op))
        // 如果合法，则对左右子表达式进行比较计算
        return Math::Hash::evalHashCmpInfix(op, leftHash->getPairs(), rightHash->getPairs());
    // 否则返回错误对象
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 哈希键对象中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalHashKeysInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 将左右对象强转成哈希键对象
    std::shared_ptr<object::HashKeys> leftHashKeys = std::dynamic_pointer_cast<object::HashKeys>(left);
    std::shared_ptr<object::HashKeys> rightHashKeys = std::dynamic_pointer_cast<object::HashKeys>(right);
    // 判断运算符类型
    // 如果为等号
    if (op == "==")
        // 如果左右哈希键对象的哈希表相同，则返回真，否则返回假
        return leftHashKeys->eq(rightHashKeys);
    // 如果为不等号
    if (op == "!=")
        // 如果左右哈希键对象的哈希表不同，则返回真，否则返回假
        return leftHashKeys->ne(rightHashKeys);
    // 否则返回错误对象
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 哈希值对象中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalHashValuesInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 将左右对象强转成哈希键对象
    std::shared_ptr<object::HashValues> leftHashValues = std::dynamic_pointer_cast<object::HashValues>(left);
    std::shared_ptr<object::HashValues> rightHashKeys = std::dynamic_pointer_cast<object::HashValues>(right);
    // 判断运算符类型
    // 如果为等号
    if (op == "==")
        // 如果左右哈希键对象的哈希表相同，则返回真，否则返回假
        return leftHashValues->eq(rightHashKeys);
    // 如果为不等号
    if (op == "!=")
        // 如果左右哈希键对象的哈希表不同，则返回真，否则返回假
        return leftHashValues->ne(rightHashKeys);
    // 否则返回错误对象
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 类型对象中缀表达式求值函数
std::shared_ptr<Object> cpy::evaluator::Evaluator::evalTypeInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 将左右对象强转成类型对象
    std::shared_ptr<object::TypeObj> leftType = std::dynamic_pointer_cast<object::TypeObj>(left);
    std::shared_ptr<object::TypeObj> rightType = std::dynamic_pointer_cast<object::TypeObj>(right);
    // 判断运算符类型
    // 如果为等号
    if (op == "==")
        // 如果左右类型相同，则返回真，否则返回假
        return newBool(leftType->objType == rightType->objType);
    // 如果为不等号
    if (op == "!=")
        // 如果左右类型不同，则返回真，否则返回假
        return newBool(leftType->objType != rightType->objType);
    // 否则返回错误对象
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 函数对象中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalFunctionInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    if (op == "==")
        return newBool(left == right);
    if (op == "!=")
        return newBool(left != right);
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 内置函数对象中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalBuiltinInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 将左右对象强转成内置函数对象
    std::shared_ptr<object::Builtin> leftBuiltin = std::dynamic_pointer_cast<object::Builtin>(left);
    std::shared_ptr<object::Builtin> rightBuiltin = std::dynamic_pointer_cast<object::Builtin>(right);
    // 判断运算符类型
    // 如果为等号
    if (op == "==")
        // 如果左右内置函数名相同，则返回真，否则返回假
        return newBool(leftBuiltin->name == rightBuiltin->name);
    // 如果为不等号
    if (op == "!=")
        // 如果左右内置函数名不同，则返回真，否则返回假
        return newBool(leftBuiltin->name != rightBuiltin->name);
    // 否则返回错误对象
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 内置方法对象中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalBuiltinMethodInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    // 将左右对象强转成内置方法对象
    std::shared_ptr<object::BuiltinMethod> leftBuiltinMethod = std::dynamic_pointer_cast<object::BuiltinMethod>(left);
    std::shared_ptr<object::BuiltinMethod> rightBuiltinMethod = std::dynamic_pointer_cast<object::BuiltinMethod>(right);
    // 判断运算符类型
    // 如果为等号
    if (op == "==")
        // 如果左右内置方法指向的对象相同，且函数指针相同，则返回真，否则返回假
        return newBool(leftBuiltinMethod->self == rightBuiltinMethod->self && leftBuiltinMethod->func == rightBuiltinMethod->func);
    if (op == "!=")
        // 如果左右内置方法指向的对象不同，或函数指针不同，则返回真，否则返回假
        return newBool(!(leftBuiltinMethod->self == rightBuiltinMethod->self && leftBuiltinMethod->func == rightBuiltinMethod->func));
    // 否则返回错误对象
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 不同类型中缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalDiffTypeInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right)
{
    if (op == "==")
        return newBool(false);
    if (op == "!=")
        return newBool(true);
    return newError("unknown operator: %s %s %s", left->getName().c_str(), op.c_str(), right->getName().c_str());
}

// 后缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalPostfix(const std::shared_ptr<ast::Postfix> &postfix, std::shared_ptr<Environment> &env)
{
    // 获取运算符，并判断是否为自变化运算符号
    std::string op = postfix->op;
    if (op == "++" || op == "--")
    {
        // 如果是则进行相应的自变化运算
        return evalChgPostfix(postfix, env);
    }
    // 对左表达式求值
    std::shared_ptr<Object> left = eval(postfix->left, env);
    // 如果左子表达式求值出错
    if (isError(left))
        return left;
    // 否则进行相应的后缀运算
    return evalObjExpPostfix(op, left);
}

// 标识符后缀表达式自变化求值函数
std::shared_ptr<Object> Evaluator::evalChgPostfix(const std::shared_ptr<ast::Postfix> &postfix, std::shared_ptr<Environment> &env)
{
    // 获取运算符和左子表达式
    std::string op = postfix->op;
    std::shared_ptr<ast::Expression> exp = postfix->left;
    // 判断左子表达式类型
    switch (exp->getType())
    {
    // 如果是标识符类型
    case Node::NODE_IDENTIFIER:
    {
        // 强制类型转化为标识符结点
        std::shared_ptr<Identifier> ident = std::dynamic_pointer_cast<ast::Identifier>(exp);
        return evalIdentChgPostfix(op, ident, env);
    }
    // 如果是索引类型
    case Node::NODE_INDEX:
    {
        // 强制类型转化为索引结点
        std::shared_ptr<Index> index = std::dynamic_pointer_cast<ast::Index>(exp);
        return evalIndexChgPostfix(op, index, env);
    }
    // 如果是属性类型
    case Node::NODE_PROPERTY:
    {
        // 强制类型转化为属性结点
        std::shared_ptr<Property> property = std::dynamic_pointer_cast<ast::Property>(exp);
        return evalPropertyChgPostfix(op, property, env);
    }
    // 否则返回错误对象
    default:
        return newError("(%d,%d) unknown operator: %s%s", postfix->token.getLine(), postfix->token.getColumn(), exp->getName().c_str(), op.c_str());
    }
}

// 标识符后缀表达式自变化求值函数
std::shared_ptr<Object> Evaluator::evalIdentChgPostfix(const std::string &op, const std::shared_ptr<ast::Identifier> &ident, std::shared_ptr<Environment> &env)
{
    // 获取标识符名称
    std::string name = ident->value;
    // 计算左表达式值
    std::shared_ptr<Object> left = evalIdentifier(ident, env);
    // 如果计算错误提前返回
    if (isError(left))
        return left;
    // 对左表达式进行相应后缀运算
    std::shared_ptr<Object> result = evalObjExpPostfix(op, left);
    // 如果计算错误，则返回错误对象
    if (isError(result))
        return result;
    // 否则对标识符对应的环境变量赋值，并返回原始值
    env->set(name, result);
    return left;
}

// 索引后缀表达式自变化求值函数
std::shared_ptr<Object> Evaluator::evalIndexChgPostfix(const std::string &op, const std::shared_ptr<ast::Index> &index, std::shared_ptr<Environment> &env)
{
    // 对索引结点的左表达式求值
    std::shared_ptr<Object> leftObj = eval(index->left, env);
    // 如果左子表达式计算出错，则直接返回左错误对象
    if (isError(leftObj))
        return leftObj;
    // 对索引结点的索引表达式求值
    std::shared_ptr<Object> indexObj = eval(index->index, env);
    // 如果索引表达式计算出错，则直接返回索引错误对象
    if (isError(indexObj))
        return indexObj;
    // 计算value对象
    std::shared_ptr<Object> valueObj = evalIndex(leftObj, indexObj);
    // 如果计算错误，则直接返回错误对象
    if (isError(valueObj))
        return valueObj;
    // 对value对象进行相应后缀运算
    std::shared_ptr<Object> result = evalObjExpPostfix(op, valueObj);
    // 如果发生计算错误，则直接返回错误对象
    if (isError(result))
        return result;
    // 对索引结点进行赋值
    evalIndexAssign(leftObj, indexObj, result);
    return valueObj;
}

// 属性后缀表达式自变化求值函数
std::shared_ptr<Object> Evaluator::evalPropertyChgPostfix(const std::string &op, const std::shared_ptr<ast::Property> &property, std::shared_ptr<Environment> &env)
{
    // 对属性结点的左对象求值
    std::shared_ptr<Object> leftObj = eval(property->object, env);
    // 如果左子表达式计算出错，则直接返回左错误对象
    if (isError(leftObj))
        return leftObj;
    // 将右属性名强制类型转化为标识符结点
    std::shared_ptr<Identifier> ident = std::dynamic_pointer_cast<ast::Identifier>(property->property);
    // 对属性结点的属性名求值
    std::shared_ptr<Object> valueObj = evalProperty(leftObj, ident->value);
    // 如果属性名计算出错，则直接返回属性名错误对象
    if (isError(valueObj))
        return valueObj;
    // 对value对象进行相应后缀运算
    std::shared_ptr<Object> result = evalObjExpPostfix(op, valueObj);
    // 如果发生计算错误，则直接返回错误对象
    if (isError(result))
        return result;
    // 对属性结点进行赋值
    evalPropertyAssign(leftObj, ident->value, result);
    return valueObj;
}

// 后缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalObjExpPostfix(const std::string &op, const std::shared_ptr<Object> &left)
{
    // 判断左子表达式类型
    switch (left->getType())
    {
    // 如果为整数类型，则对左子表达式进行后缀表达式计算
    case Object::OBJECT_INTEGER:
        return evalIntExpPostfix(op, left);
    // 如果为浮点数类型，则对左子表达式进行后缀表达式计算
    case Object::OBJECT_FLOAT:
        return evalFloatExpPostfix(op, left);
    // 如果是布尔数类型，则对左子表达式进行后缀表达式计算
    case Object::OBJECT_BOOL:
        return evalIntExpPostfix(op, bool2Int(left));
    // 否则返回错误对象
    default:
        return newError("postfix not support: %s%s", left->getName().c_str(), op.c_str());
    }
}

// 整数后缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalIntExpPostfix(const std::string &op, const std::shared_ptr<Object> &left)
{
    return newInteger(Math::Integer::evalIntExpPostfix(op, std::dynamic_pointer_cast<object::Integer>(left)->value));
}

// 浮点数后缀表达式求值函数
std::shared_ptr<Object> Evaluator::evalFloatExpPostfix(const std::string &op, const std::shared_ptr<Object> &left)
{
    return newFloat(Math::Float::evalFloatExpPostfix(op, std::dynamic_pointer_cast<object::Float>(left)->value));
}
