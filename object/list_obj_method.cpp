#include <object/list_obj.h>
#include <object/integer_obj.h>
using namespace cpy::object;
// 列表对象长度获取函数
std::shared_ptr<Object> List::lenMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不为0则返回错误对象
    if (args.size() != 0)
        return newError("len() takes no arguments (%d given)", args.size());
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 返回列表对象长度
    return newInteger(listObj->size());
}

// 列表对象统计函数
std::shared_ptr<Object> List::countMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 判断参数个数
    switch (args.size())
    {
    // 如果参数个数为0，则返回错误对象
    case 0:
        return newError("count() takes at least 1 argument (%d given)", args.size());
    // 如果参数个数为1，则调用1参数列表统计函数，从列表头部开始查找匹配的元素个数
    case 1:
        return countMethod(obj, args[0]);
    // 如果参数个数为2，则调用2参数列表统计函数，从指定位置开始查找匹配的元素个数
    case 2:
        return countMethod(obj, args[0], args[1]);
    // 如果参数个数为3，则调用3参数列表统计函数，从指定位置开始到指定位置结束查找匹配的元素个数
    case 3:
        return countMethod(obj, args[0], args[1], args[2]);
    // 如果参数个数大于3，则返回错误对象
    default:
        return newError("count() takes at most 3 arguments (%d given)", args.size());
    }
}

// 列表索引获取函数
std::shared_ptr<Object> List::indexMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 判断参数个数
    switch (args.size())
    {
    // 如果参数个数为0，则返回错误对象
    case 0:
        return newError("index() takes at least 1 argument (%d given)", args.size());
    // 如果参数个数为1，则调用1参数列表索引函数，从列表头部开始查找匹配的第一个元素
    case 1:
        return indexMethod(obj, args[0]);
    // 如果参数个数为2，则调用2参数列表索引函数，从指定位置开始查找匹配的第一个元素
    case 2:
        return indexMethod(obj, args[0], args[1]);
    // 如果参数个数为3，则调用3参数列表索引函数，从指定位置开始到指定位置结束查找匹配的第一个元素
    case 3:
        return indexMethod(obj, args[0], args[1], args[2]);
    // 如果参数个数大于3，则返回错误对象
    default:
        return newError("index() takes at most 3 arguments (%d given)", args.size());
    }
}

// 列表对象索引操作符重载函数
std::shared_ptr<Object> List::appendMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数小于1则返回错误对象
    if (args.size() < 1)
        return newError("append() takes at least 1 argument (%d given)", args.size());
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 遍历参数列表，将每个参数添加到列表对象中
    for (auto &arg : args)
        listObj->elements.emplace_back(arg);
    // 返回空对象
    return newNull();
}

// 列表对象插入函数
std::shared_ptr<Object> List::insertMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数不等于2，则返回错误对象
    if (args.size() != 2)
        return Object::newError("insert() expected 2 arguments (%d given)", args.size());
    // 调用2参数列表插入函数
    return insertMethod(obj, args[0], args[1]);
}

// 列表对象头元素弹出函数
std::shared_ptr<Object> List::shiftMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数不等于0，则返回错误对象
    if (args.size() != 0)
        return Object::newError("shift() takes no arguments (%d given)", args.size());
    // 调用0参数列表头弹出函数
    return shiftMethod(obj);
}

// 列表对象索引操作符重载函数
std::shared_ptr<Object> List::popMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数不等于0，则返回错误对象
    if (args.size() != 0)
        return Object::newError("pop() takes no arguments (%d given)", args.size());
    // 调用0参数列表尾弹出函数
    return popMethod(obj);
}

// 列表对象元素按位删除函数
std::shared_ptr<Object> List::eraseMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数不等于1，则返回错误对象
    if (args.size() != 1)
        return Object::newError("erase() expected 1 argument (%d given)", args.size());
    // 调用1参数列表元素按位删除函数
    return eraseMethod(obj, args[0]);
}

// 列表对象元素删除函数
std::shared_ptr<Object> List::removeMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 根据参数个数调用不同的函数
    switch (args.size())
    {
    // 如果参数个数为0，则返回错误对象
    case 0:
        return Object::newError("remove() takes at least 1 argument (%d given)", args.size());
    // 如果参数个数为1，则调用1参数列表元素删除函数，从头开始查找删除匹配的第一个元素
    case 1:
        return removeMethod(obj, args[0]);
    // 如果参数个数为2，则调用2参数列表元素删除函数，从指定位置开始查找删除匹配的第一个元素
    case 2:
        return removeMethod(obj, args[0], args[1]);
    // 如果参数个数为3，则调用3参数列表元素删除函数，从指定位置开始到指定位置结束查找删除匹配的第一个元素
    case 3:
        return removeMethod(obj, args[0], args[1], args[2]);
    // 如果参数个数大于3，则返回错误对象
    default:
        return Object::newError("remove() takes at most 3 arguments (%d given)", args.size());
    }
}

// 列表对象扩展函数
std::shared_ptr<Object> List::extendMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数不等于1，则返回错误对象
    if (args.size() != 1)
        return Object::newError("extend() takes exactly 1 argument (%d given)", args.size());
    // 调用1参数列表扩展函数
    return extendMethod(obj, args[0]);
}

// 列表对象指定位置扩展函数
std::shared_ptr<Object> List::extendatMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数不等于2，则返回错误对象
    if (args.size() != 2)
        return Object::newError("extendat() takes exactly 2 arguments (%d given)", args.size());
    // 调用2参数列表指定位置扩展函数
    return extendatMethod(obj, args[0], args[1]);
}

// 1参数列表元素统计函数
std::shared_ptr<Object> List::countMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val)
{
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 直接调用列表对象统计处理函数
    return newInteger(count(listObj->elements, val, 0, listObj->size()));
}

// 2参数列表元素统计函数
std::shared_ptr<Object> List::countMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val, const std::shared_ptr<Object> &start)
{
    // 判断起始位置参数类型是否为整数
    if (start->getType() != OBJECT_INTEGER)
        return Object::newError("count() argument 2 must be integer, not '%s'", start->getName().c_str());
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 将索引转换为整数对象指针
    std::shared_ptr<Integer> startObj = std::dynamic_pointer_cast<Integer>(start);
    // 直接调用列表对象统计处理函数
    return newInteger(count(listObj->elements, val, startObj->value, listObj->size()));
}

// 3参数列表元素统计函数
std::shared_ptr<Object> List::countMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val, const std::shared_ptr<Object> &start, const std::shared_ptr<Object> &end)
{
    // 判断起始位置参数类型是否为整数
    if (start->getType() != OBJECT_INTEGER)
        return Object::newError("count() argument 2 must be integer, not '%s'", start->getName().c_str());
    // 判断结束位置参数类型是否为整数
    if (end->getType() != OBJECT_INTEGER)
        return Object::newError("count() argument 3 must be integer, not '%s'", end->getName().c_str());
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 将索引转换为整数对象指针
    std::shared_ptr<Integer> startObj = std::dynamic_pointer_cast<Integer>(start);
    // 将索引转换为整数对象指针
    std::shared_ptr<Integer> endObj = std::dynamic_pointer_cast<Integer>(end);
    // 直接调用列表对象统计处理函数
    return newInteger(count(listObj->elements, val, startObj->value, endObj->value));
}

// 列表元素统计处理函数
int64_t List::count(const std::vector<std::shared_ptr<Object>> &elements, const std::shared_ptr<Object> &val, int64_t start, int64_t end)
{
    // 如果区间异常，则返回0
    if (start < 0 || start >= elements.size() || start >= end)
        return 0;
    // 如果终止位置大于列表长度，则将终止位置设置为列表长度
    if (end > elements.size())
        end = elements.size();
    int64_t count = 0;
    // 遍历列表元素，统计匹配的元素个数
    for (int64_t i = start; i < end; ++i)
    {
        // 如果元素相等，则计数器加1
        if (elements[i]->isEqual(val))
            ++count;
    }
    // 返回统计结果
    return count;
}

// 1参数列表索引函数
std::shared_ptr<Object> List::indexMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val)
{
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 获取索引值
    int64_t idx = index(listObj->elements, val, 0, listObj->size());
    // 如果索引值为-1，则返回错误对象
    if (index < 0)
        return Object::newError("%s is not in list", val->toString().c_str());
    // 返回索引值
    return newInteger(idx);
}

// 2参数列表索引函数
std::shared_ptr<Object> List::indexMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val, const std::shared_ptr<Object> &start)
{
    // 判断起始位置参数类型是否为整数
    if (start->getType() != OBJECT_INTEGER)
        return Object::newError("index() argument 2 must be integer, not '%s'", start->getName().c_str());
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 将索引转换为整数对象指针
    std::shared_ptr<Integer> startObj = std::dynamic_pointer_cast<Integer>(start);
    // 获取索引值
    int64_t idx = index(listObj->elements, val, startObj->value, listObj->size());
    // 如果索引值为-1，则返回错误对象
    if (index < 0)
        return Object::newError("%s is not in list", val->toString().c_str());
    // 返回索引值
    return newInteger(idx);
}

// 3参数列表索引函数
std::shared_ptr<Object> List::indexMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val, const std::shared_ptr<Object> &start, const std::shared_ptr<Object> &end)
{
    // 判断起始位置参数类型是否为整数
    if (start->getType() != OBJECT_INTEGER)
        return Object::newError("index() argument 2 must be integer, not '%s'", start->getName().c_str());
    // 判断结束位置参数类型是否为整数
    if (end->getType() != OBJECT_INTEGER)
        return Object::newError("index() argument 3 must be integer, not '%s'", end->getName().c_str());
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 将索引转换为整数对象指针
    std::shared_ptr<Integer> startObj = std::dynamic_pointer_cast<Integer>(start);
    // 将索引转换为整数对象指针
    std::shared_ptr<Integer> endObj = std::dynamic_pointer_cast<Integer>(end);
    // 获取索引值
    int64_t idx = index(listObj->elements, val, startObj->value, endObj->value);
    // 如果索引值为-1，则返回错误对象
    if (index < 0)
        return Object::newError("%s is not in list", val->toString().c_str());
    // 返回索引值
    return newInteger(idx);
}

int64_t List::index(const std::vector<std::shared_ptr<Object>> &elements, const std::shared_ptr<Object> &index, int64_t start, int64_t end)
{
    // 如果区间异常，则返回-1
    if (start < 0 || start >= elements.size() || start >= end)
        return -1;
    // 如果终止位置大于列表长度，则将终止位置设置为列表长度
    if (end > elements.size())
        end = elements.size();
    // 遍历列表元素，查找匹配的元素
    for (int64_t i = start; i < end; ++i)
    {
        // 如果元素相等，则返回索引值
        if (elements[i]->isEqual(index))
            return i;
    }
    // 如果没有找到匹配的元素，则返回-1
    return -1;
}

// 2参数列表插入函数
std::shared_ptr<Object> List::insertMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &index, const std::shared_ptr<Object> &val)
{
    // 判断索引参数类型是否为整数
    if (index->getType() != OBJECT_INTEGER)
        return Object::newError("insert() argument must be integer, not '%s'", index->getName().c_str());
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 将索引转换为整数对象指针
    std::shared_ptr<Integer> indexObj = std::dynamic_pointer_cast<Integer>(index);
    // 获取索引值，索引支持负数
    int64_t idx = indexObj->value;
    // 如果索引值小于0，则将索引值转换为正数
    if (idx < 0)
        idx += listObj->size();
    // 判断索引值是否越界
    if (idx < 0 || idx > listObj->size())
        return Object::newError("insert index out of range");
    // 在指定位置插入元素
    listObj->elements.insert(listObj->elements.begin() + idx, val);
    // 返回空对象
    return newNull();
}

// 0参数列表对象尾弹出处理函数
std::shared_ptr<Object> List::popMethod(const std::shared_ptr<Object> &obj)
{
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 如果列表为空，则返回错误对象
    if (listObj->elements.empty())
        return Object::newError("pop from empty list");
    // 删除并返回列表最后一个元素
    std::shared_ptr<Object> backElem = listObj->elements.back();
    listObj->elements.pop_back();
    return backElem;
}

// 0参数列表头弹出处理函数
std::shared_ptr<Object> List::shiftMethod(const std::shared_ptr<Object> &obj)
{
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 如果列表为空，则返回错误对象
    if (listObj->elements.empty())
        return Object::newError("shift from empty list");
    // 删除并返回列表第一个元素
    std::shared_ptr<Object> frontElem = listObj->elements.front();
    listObj->elements.erase(listObj->elements.begin());
    return frontElem;
}

// 1参数列表元素按位删除函数
std::shared_ptr<Object> List::eraseMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &index)
{
    // 判断参数类型是否为整数
    if (index->getType() != OBJECT_INTEGER)
        return Object::newError("erase() argument must be integer, not '%s'", index->getName().c_str());
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 将索引转换为整数对象指针
    std::shared_ptr<Integer> indexObj = std::dynamic_pointer_cast<Integer>(index);
    // 如果列表为空，则返回错误对象
    if (listObj->elements.empty())
        return Object::newError("erase from empty list");
    // 获取索引值，索引支持负数
    int64_t idx = indexObj->value;
    // 如果索引值小于0，则将索引值转换为正数
    if (idx < 0)
        idx += listObj->size();
    // 判断索引值是否越界
    if (idx < 0 || idx >= listObj->size())
        return Object::newError("erase index out of range");
    // 删除并返回指定位置的元素
    std::shared_ptr<Object> item = listObj->elements[idx];
    listObj->elements.erase(listObj->elements.begin() + idx);
    return item;
}

// 1参数列表元素删除函数
std::shared_ptr<Object> List::removeMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val)
{
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 调用remove方法，从头开始查找删除匹配的第一个元素
    return newInteger(remove(listObj->elements, val, 0, listObj->size()));
}

// 2参数列表元素删除函数
std::shared_ptr<Object> List::removeMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val, const std::shared_ptr<Object> &start)
{
    // 判断起始参数类型是否为整数
    if (start->getType() != OBJECT_INTEGER)
        return Object::newError("remove() argument 2 must be integer, not '%s'", start->getName().c_str());
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 将起始参数转换为整数对象指针
    std::shared_ptr<Integer> startObj = std::dynamic_pointer_cast<Integer>(start);
    // 调用remove方法，从指定位置开始查找删除匹配的第一个元素
    return newInteger(remove(listObj->elements, val, startObj->value, listObj->size()));
}

// 3参数列表元素删除函数
std::shared_ptr<Object> List::removeMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &val, const std::shared_ptr<Object> &start, const std::shared_ptr<Object> &end)
{
    // 判断起始参数类型是否为整数
    if (start->getType() != OBJECT_INTEGER)
        return Object::newError("remove() argument 2 must be integer, not '%s'", start->getName().c_str());
    // 判断结束参数类型是否为整数
    if (end->getType() != OBJECT_INTEGER)
        return Object::newError("remove() argument 3 must be integer, not '%s'", end->getName().c_str());
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 将起始参数转换为整数对象指针
    std::shared_ptr<Integer> startObj = std::dynamic_pointer_cast<Integer>(start);
    // 将结束参数转换为整数对象指针
    std::shared_ptr<Integer> endObj = std::dynamic_pointer_cast<Integer>(end);
    // 调用remove方法，从指定位置开始到指定位置结束查找删除匹配的第一个元素
    return newInteger(remove(listObj->elements, val, startObj->value, endObj->value));
}

// 列表元素按值删除处理函数
int64_t List::remove(std::vector<std::shared_ptr<Object>> &elements, const std::shared_ptr<Object> &val, int64_t start, int64_t end)
{
    // 如果起始位置小于0或者起始位置大于等于元素个数或者起始位置大于结束位置，则返回-1
    if (start < 0 || start >= elements.size() || start >= end)
        return -1;
    // 如果结束位置大于元素个数，则将结束位置设置为元素个数
    if (end > elements.size())
        end = elements.size();
    // 遍历元素列表，查找匹配的元素并删除
    for (int64_t i = start; i < end; ++i)
    {
        // 如果元素相等，则删除并返回索引值
        if (elements[i]->isEqual(val))
        {
            elements.erase(elements.begin() + i);
            return i;
        }
    }
    // 如果没用删除成功则返回-1
    return -1;
}

// 1参数列表对象尾部扩展函数
std::shared_ptr<Object> List::extendMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &iterable)
{
    // 将参数转化为可迭代对象指针
    std::shared_ptr<Iterable> iterableObj = std::dynamic_pointer_cast<Iterable>(iterable);
    // 如果不是可迭代对象，则返回错误对象
    if (iterableObj == nullptr)
        return Object::newError("extend() argument must be iterable, not '%s'", iterable->getName().c_str());
    // 将对象转换为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 获取可迭代对象的头部元素
    std::shared_ptr<Object> item = iterableObj->next();
    // 循环遍历直到获取到尾部元素
    while (item != nullptr)
    {
        // 将获取到的元素添加到列表的尾部
        listObj->elements.emplace_back(item);
        // 获取下一个元素
        item = iterableObj->next();
    }
    // 将迭代器重置
    iterableObj->reset();
    // 返回空对象
    return newNull();
}

// 2参数列表对象指定位置扩展函数
std::shared_ptr<Object> List::extendatMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &index, const std::shared_ptr<Object> &iterable)
{
    // 判断索引参数类型
    if (index->getType() != OBJECT_INTEGER)
        return Object::newError("extendat() argument 1 must be integer, not '%s'", index->getName().c_str());
    // 将对象转化为列表对象指针
    std::shared_ptr<List> listObj = std::dynamic_pointer_cast<List>(obj);
    // 将索引参数转换为整数对象指针
    std::shared_ptr<Integer> indexObj = std::dynamic_pointer_cast<Integer>(index);
    // 获取索引值，索引支持负数
    int64_t idx = indexObj->value;
    // 如果索引值小于0，则将索引值转换为正数
    if (idx < 0)
        idx += listObj->size();
    // 判断索引值是否越界
    if (idx < 0 || idx > listObj->size())
        return Object::newError("extendat index out of range");
    // 将可迭代对象参数转换为可迭代对象指针
    std::shared_ptr<Iterable> iterableObj = std::dynamic_pointer_cast<Iterable>(iterable);
    // 如果不是可迭代对象，则返回错误对象
    if (iterableObj == nullptr)
        return Object::newError("extendat() argument 2 must be iterable, not '%s'", iterable->getName().c_str());
    // 创建一个临时列表对象
    std::vector<std::shared_ptr<Object>> tempList;
    // 预留空间
    tempList.reserve(iterableObj->size());
    // 获取可迭代对象的头部元素
    std::shared_ptr<Object> item = iterableObj->next();
    // 循环至尾部元素
    while (item != nullptr)
    {
        // 将获取到的元素添加到临时列表尾部
        tempList.emplace_back(item);
        // 获取下一个元素
        item = iterableObj->next();
    }
    // 将迭代器重置
    iterableObj->reset();
    // 将临时列表插入到列表对象的指定位置
    listObj->elements.insert(listObj->elements.begin() + idx, tempList.begin(), tempList.end());
    // 返回空对象
    return newNull();
}
