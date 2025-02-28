#include <object/string_obj.h>
#include <object/integer_obj.h>
#include <object/list_obj.h>
#include <object/bool_obj.h>
#include "string_obj.h"
using namespace cpy::object;
// 字符串对象长度获取函数
std::shared_ptr<Object> String::lenMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不为0则返回错误对象
    if (args.size() != 0)
        return newError("len() takes no arguments (%d given)", args.size());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> str = std::dynamic_pointer_cast<String>(obj);
    // 返回字符串对象长度
    return newInteger(str->value.size());
}

// 字符串大写转换函数
std::shared_ptr<Object> String::upperMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不为0则返回错误对象
    if (args.size() != 0)
        return newError("upper() takes no arguments (%d given)", args.size());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> str = std::dynamic_pointer_cast<String>(obj);
    // 获取字符串值
    std::string strValue = str->value;
    // 转换为大写
    std::transform(strValue.begin(), strValue.end(), strValue.begin(), ::toupper);
    // 返回转换后的字符串对象
    return newString(strValue);
}

// 字符串小写转换函数
std::shared_ptr<Object> String::lowerMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不为0则返回错误对象
    if (args.size() != 0)
        return newError("lower() takes no arguments (%d given)", args.size());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> str = std::dynamic_pointer_cast<String>(obj);
    // 获取字符串值
    std::string strValue = str->value;
    // 转换为小写
    std::transform(strValue.begin(), strValue.end(), strValue.begin(), ::tolower);
    // 返回转换后的字符串对象
    return newString(strValue);
}

// 字符串对象索引获取函数
std::shared_ptr<Object> String::indexMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 判断参数个数
    switch (args.size())
    {
    // 如果参数个数为0则返回错误对象
    case 0:
        return newError("index() takes at least 1 argument (0 given)");
    // 如果参数个数为1则返回单个字符
    case 1:
        return indexMethod(obj, args[0]);
    // 如果参数个数为2则从指定位置开始查找整个字符串
    case 2:
        return indexMethod(obj, args[0], args[1]);
    // 如果参数个数为3则从指定位置开始查找指定长度的字符串
    case 3:
        return indexMethod(obj, args[0], args[1], args[2]);
    // 如果参数个数大于3则返回错误对象
    default:
        return newError("index() takes at most 3 arguments (%d given)", args.size());
    }
}

// 字符串对象查找函数
std::shared_ptr<Object> String::findMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 判断参数个数
    switch (args.size())
    {
    // 如果参数个数为0则返回错误对象
    case 0:
        return newError("find() takes at least 1 argument (0 given)");
    // 如果参数个数为1则从0开始查找整个字符串
    case 1:
        return findMethod(obj, args[0]);
    // 如果参数个数为2则从指定位置开始查找整个字符串
    case 2:
        return findMethod(obj, args[0], args[1]);
    // 如果参数个数为3则从指定位置开始查找指定长度的字符串
    case 3:
        return findMethod(obj, args[0], args[1], args[2]);
    // 如果参数个数大于3则返回错误对象
    default:
        return newError("find() takes at most 3 arguments (%d given)", args.size());
    }
}

// 字符串对象分割函数
std::shared_ptr<Object> String::splitMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 判断参数个数
    switch (args.size())
    {
    // 如果参数个数为0则忽略空白字符进行分割
    case 0:
        return splitMethod(obj);
    // 如果参数个数为1则根据分割符进行分割
    case 1:
        return splitMethod(obj, args[0]);
    // 如果参数个数为2则根据分隔符和分割次数进行分割
    case 2:
        return splitMethod(obj, args[0], args[1]);
    // 如果参数个数大于2则返回错误对象
    default:
        return newError("split() takes at most 2 arguments (%d given)", args.size());
    }
}

// 前缀判断函数
std::shared_ptr<Object> String::prefixMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不等于1则返回错误对象
    if (args.size() != 1)
        return newError("prefix() takes exactly 1 argument (%d given)", args.size());
    // 调用1参数字符串前缀判断函数
    return prefixMethod(obj, args[0]);
}

// 后缀判断函数
std::shared_ptr<Object> String::suffixMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不等于1则返回错误对象
    if (args.size() != 1)
        return newError("suffix() takes exactly 1 argument (%d given)", args.size());
    // 调用1参数字符串后缀判断函数
    return suffixMethod(obj, args[0]);
}

// 字符串左修剪函数
std::shared_ptr<Object> String::ltrimMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数大于1则返回错误对象
    if (args.size() > 1)
        return newError("ltrim() takes at most 1 argument (%d given)", args.size());
    // 如果参数个数为0则调用0参数字符串左修剪函数
    if (args.size() == 0)
        return ltrimMethod(obj);
    // 如果参数个数为1则调用1参数字符串左修剪函数
    return ltrimMethod(obj, args[0]);
}

// 字符串右修剪函数
std::shared_ptr<Object> String::rtrimMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数大于1则返回错误对象
    if (args.size() > 1)
        return newError("rtrim() takes at most 1 argument (%d given)", args.size());
    // 如果参数个数为0则调用0参数字符串右修剪函数
    if (args.size() == 0)
        return rtrimMethod(obj);
    // 如果参数个数为1则调用1参数字符串右修剪函数
    return rtrimMethod(obj, args[0]);
}

// 字符串修剪函数
std::shared_ptr<Object> String::trimMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数大于1则返回错误对象
    if (args.size() > 1)
        return newError("trim() takes at most 1 argument (%d given)", args.size());
    // 如果参数个数为0则调用0参数字符串修剪函数
    if (args.size() == 0)
        return trimMethod(obj);
    // 如果参数个数为1则调用1参数字符串修剪函数
    return trimMethod(obj, args[0]);
}

// 字符串裁剪函数
std::shared_ptr<Object> String::substrMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 判断参数个数
    switch (args.size())
    {
    // 如果参数个数为则直接从0开始裁剪到末尾
    case 0:
        return substrMethod(obj);
    // 如果参数个数为1则直接从起始位置开始裁剪到末尾
    case 1:
        return substrMethod(obj, args[0]);
    // 如果参数个数为2则从起始位置开始裁剪到指定位置
    case 2:
        return substrMethod(obj, args[0], args[1]);
    // 否则返回错误对象
    default:
        return newError("substr() takes at most 2 arguments (%d given)", args.size());
    }
}

// 字符串替换函数
std::shared_ptr<Object> String::replaceMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数小于2则返回错误对象
    if (args.size() < 2)
        return newError("replace() takes at least 2 arguments (%d given)", args.size());
    // 如果参数为2则从头开始替换到末尾
    if (args.size() == 2)
        return replaceMethod(obj, args[0], args[1]);
    // 如果参数为3则从头开始替换有限次
    if (args.size() == 3)
        return replaceMethod(obj, args[0], args[1], args[2]);
    // 如果参数个数大于3则返回错误对象
    return newError("replace() takes at most 3 arguments (%d given)", args.size());
}

// 字符串连接函数
std::shared_ptr<Object> String::joinMethod(const std::shared_ptr<Object> &obj, const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不等于1则返回错误对象
    if (args.size() != 1)
        return newError("join() takes exactly 1 argument (%d given)", args.size());
    // 将参数转化为可迭代对象
    std::shared_ptr<Iterable> iterable = std::dynamic_pointer_cast<Iterable>(args[0]);
    // 如果参数不能转化为可迭代对象则返回错误对象
    if (iterable == nullptr)
        return newError("join() can only join an iterable object not '%s'", args[0]->getName().c_str());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 获取头元素
    std::shared_ptr<Object> item = iterable->next();
    // 初始化结果字符串
    std::string result;
    // 如果元素不为空则将字符串间隔插入到迭代对象字符串之间
    if (item != nullptr)
    {
        // 如果元素是字符串类型则将
        if (item->getType() == OBJECT_STRING)
        {
            // 将元素转化为字符串对象指针
            std::shared_ptr<String> strElem = std::dynamic_pointer_cast<String>(item);
            // 将元素加入结果字符串
            result += strElem->value;
        }
        // 否则将字符串元素对应的字符串加入结果字符串
        else
            result += item->toString();
        // 获取下一个元素
        item = iterable->next();
        // 循环获取所有元素
        while (item != nullptr)
        {
            // 加入分隔符
            result += strObj->value;
            // 如果元素是字符串类型则将
            if (item->getType() == OBJECT_STRING)
            {
                // 将元素转化为字符串对象指针
                std::shared_ptr<String> strElem = std::dynamic_pointer_cast<String>(item);
                // 将元素加入结果字符串
                result += strElem->value;
            }
            // 否则将字符串元素对应的字符串加入结果字符串
            else
                result += item->toString();
            // 获取元素对应的字符串
            item = iterable->next();
        }
    }
    // 返回结果字符串对象
    return newString(result);
}

// 1参数字符串索引函数
std::shared_ptr<Object> String::indexMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &sub)
{
    // 判断参数类型是否为字符串对象
    if (sub->getType() != OBJECT_STRING)
        return newError("index() argument must be string, not '%s'", sub->getName().c_str());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> subObj = std::dynamic_pointer_cast<String>(sub);
    // 直接查找字符串
    size_t pos = strObj->value.find(subObj->value);
    // 如果没有找到则返回错误对象
    if (pos == std::string::npos)
        return newError("substring not found");
    // 返回索引值
    return newInteger(pos);
}

// 2参数字符串索引函数
std::shared_ptr<Object> String::indexMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &sub, const std::shared_ptr<Object> &start)
{
    // 判断第一个参数类型是否为字符串对象
    if (sub->getType() != OBJECT_STRING)
        return newError("index() argument must be string, not '%s'", sub->getName().c_str());
    // 判断第二个参数类型是否为整数对象
    if (start->getType() != OBJECT_INTEGER)
        return newError("index() argument 2 must be integer, not '%s'", start->getName().c_str());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> subObj = std::dynamic_pointer_cast<String>(sub);
    // 将参数转换为整数对象指针
    std::shared_ptr<Integer> startObj = std::dynamic_pointer_cast<Integer>(start);
    // 从指定位置开始查找字符串
    size_t pos = strObj->value.find(subObj->value, startObj->value);
    // 如果没有找到则返回错误对象
    if (pos == std::string::npos)
        return newError("substring not found");
    // 返回索引值
    return newInteger(pos);
}

// 3参数字符串索引函数
std::shared_ptr<Object> String::indexMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &sub, const std::shared_ptr<Object> &start, const std::shared_ptr<Object> &end)
{
    // 判断第一个参数类型是否为字符串对象
    if (sub->getType() != OBJECT_STRING)
        return newError("find() argument must be string, not '%s'", sub->getName().c_str());
    // 判断第二个参数类型是否为整数对象
    if (start->getType() != OBJECT_INTEGER)
        return newError("find() argument 2 must be integer, not '%s'", start->getName().c_str());
    // 判断第三个参数类型是否为整数对象
    if (end->getType() != OBJECT_INTEGER)
        return newError("find() argument 3 must be integer, not '%s'", end->getName().c_str());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> subObj = std::dynamic_pointer_cast<String>(sub);
    // 将参数转换为整数对象指针
    std::shared_ptr<Integer> startObj = std::dynamic_pointer_cast<Integer>(start);
    // 将参数转换为整数对象指针
    std::shared_ptr<Integer> endObj = std::dynamic_pointer_cast<Integer>(end);
    // 从指定位置开始查找指定长度的字符串
    size_t pos = find(strObj->value, subObj->value, startObj->value, endObj->value);
    // 如果没有找到则返回错误对象
    if (pos == std::string::npos)
        return newError("substring not found");
    // 返回索引值
    return newInteger(pos);
}

// 1参数字符串查找函数
std::shared_ptr<Object> String::findMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &sub)
{
    // 判断参数类型是否为字符串对象
    if (sub->getType() != OBJECT_STRING)
        return newError("find() argument must be string, not '%s'", sub->getName().c_str());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> subObj = std::dynamic_pointer_cast<String>(sub);
    // 直接查找字符串
    return newInteger(strObj->value.find(subObj->value));
}

// 2参数字符串查找函数
std::shared_ptr<Object> String::findMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &sub, const std::shared_ptr<Object> &start)
{
    // 判断第一个参数类型是否为字符串对象
    if (sub->getType() != OBJECT_STRING)
        return newError("find() argument must be string, not '%s'", sub->getName().c_str());
    // 判断第二个参数类型是否为整数对象
    if (start->getType() != OBJECT_INTEGER)
        return newError("find() argument 2 must be integer, not '%s'", start->getName().c_str());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> subObj = std::dynamic_pointer_cast<String>(sub);
    // 将参数转换为整数对象指针
    std::shared_ptr<Integer> startObj = std::dynamic_pointer_cast<Integer>(start);
    // 从指定位置开始查找字符串
    return newInteger(strObj->value.find(subObj->value, startObj->value));
}

// 3参数字符串查找函数
std::shared_ptr<Object> String::findMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &sub, const std::shared_ptr<Object> &start, const std::shared_ptr<Object> &end)
{
    // 判断第一个参数类型是否为字符串对象
    if (sub->getType() != OBJECT_STRING)
        return newError("find() argument must be string, not '%s'", sub->getName().c_str());
    // 判断第二个参数类型是否为整数对象
    if (start->getType() != OBJECT_INTEGER)
        return newError("find() argument 2 must be integer, not '%s'", start->getName().c_str());
    // 判断第三个参数类型是否为整数对象
    if (end->getType() != OBJECT_INTEGER)
        return newError("find() argument 3 must be integer, not '%s'", end->getName().c_str());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> subObj = std::dynamic_pointer_cast<String>(sub);
    // 将参数转换为整数对象指针
    std::shared_ptr<Integer> startObj = std::dynamic_pointer_cast<Integer>(start);
    // 将参数转换为整数对象指针
    std::shared_ptr<Integer> endObj = std::dynamic_pointer_cast<Integer>(end);
    // 从指定位置开始查找指定长度的字符串
    return newInteger(find(strObj->value, subObj->value, startObj->value, endObj->value));
}

// 字符串查找函数
size_t String::find(const std::string &str, const std::string &sub, size_t start, size_t end)
{
    // 如果终止位置大于字符串长度，则将终止位置设置为字符串长度
    end = std::min(end, str.size());
    // 如果起始位置大于终止位置或者字串长度大于切割长度则返回npos
    if (start >= end || sub.size() > (end - start))
        return std::string::npos;
    // 如果子串为空则返回起始位置
    if (sub.empty())
        return start;
    // 创建string_view，获取从start到end的位置的字符串视图
    std::string_view strView(str.data() + start, end - start);
    // 查找子字符串
    size_t pos = strView.find(sub);
    // 如果找到则返回起始位置加偏移量，否则返回npos
    return (pos == std::string::npos) ? std::string::npos : start + pos;
}

// 0参数字符串分割函数
std::shared_ptr<Object> String::splitMethod(const std::shared_ptr<Object> &obj)
{
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> str = std::dynamic_pointer_cast<String>(obj);
    // 进行空白字符串分割
    return newList(splitByWhitespace(str->value, -1));
}

// 1参数字符串分割函数
std::shared_ptr<Object> String::splitMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &delim)
{
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> str = std::dynamic_pointer_cast<String>(obj);
    // 如果参数为null则忽略空白字符进行分割
    if (delim->getType() == OBJECT_NULL)
        return newList(splitByWhitespace(str->value, -1));
    // 如果参数为字符串对象则根据分割符进行分割
    if (delim->getType() == OBJECT_STRING)
    {
        // 将参数转换为字符串对象指针
        std::shared_ptr<String> delimObj = std::dynamic_pointer_cast<String>(delim);
        // 如果分割字符为空字符串则返回错误对象
        if (delimObj->value.empty())
            return newError("split() argument 1 must not be empty");
        // 进行字符串分割
        return newList(splitByDelimiter(str->value, delimObj->value, -1));
    }
    return newError("split() argument must be string or null, not '%s'", delim->getName().c_str());
}

// 2参数字符串分割函数
std::shared_ptr<Object> String::splitMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &delim, const std::shared_ptr<Object> &maxSplit)
{
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> str = std::dynamic_pointer_cast<String>(obj);
    // 如果参数为null则忽略空白字符进行分割
    if (delim->getType() == OBJECT_NULL)
    {
        // 判断参数类型是否为整数对象
        if (maxSplit->getType() != OBJECT_INTEGER)
            return newError("split() pos 2 argument must be integer, not '%s'", maxSplit->getName().c_str());
        // 将参数转换为整数对象指针
        std::shared_ptr<Integer> maxSplitObj = std::dynamic_pointer_cast<Integer>(maxSplit);
        // 进行空白字符串分割
        return newList(splitByWhitespace(str->value, maxSplitObj->value));
    }
    // 判断参数类型是否为字符串对象
    if (delim->getType() == OBJECT_STRING)
    {
        // 如果参数不为整数对象则返回错误对象
        if (maxSplit->getType() != OBJECT_INTEGER)
            return newError("split() pos 2 argument must be integer, not '%s'", maxSplit->getName().c_str());
        // 将参数转换为字符串对象指针
        std::shared_ptr<String> delimObj = std::dynamic_pointer_cast<String>(delim);
        // 将参数转换为整数对象指针
        std::shared_ptr<Integer> maxSplitObj = std::dynamic_pointer_cast<Integer>(maxSplit);
        // 如果分割字符为空字符串则返回错误对象
        if (delimObj->value.empty())
            return newError("split() argument 1 must not be empty");
        // 进行字符串分割
        return newList(splitByDelimiter(str->value, delimObj->value, maxSplitObj->value));
    }
    // 返回错误对象
    return newError("split() argument must be string or null, not '%s'", delim->getName().c_str());
}

// 空白符字符串分割函数
std::vector<std::shared_ptr<Object>> String::splitByWhitespace(const std::string &str, int64_t maxSplit)
{
    // 定义分割结果向量
    std::vector<std::shared_ptr<Object>> strList;
    // 定义分割位置
    size_t start = 0;
    size_t end = 0;
    // 如果最大分割次数小于0则分割到底
    if (maxSplit < 0)
    {
        // 遍历字符串直到结束
        while (end < str.size())
        {
            // 如果当前字符为空白字符
            if (std::isspace(str[end]))
            {
                // 如果两指针之间有字符则进行分割
                if (end - start > 0)
                {
                    // 将分割结果添加到字符串对象列表中
                    strList.emplace_back(newString(str.substr(start, end - start)));
                    // 更新分割位置
                    start = end;
                }
                // 跳过空白字符
                ++start;
            }
            ++end;
        }
        // 如果两指针之间有字符则进行分割
        if (end - start > 0)
            // 将分割结果添加到字符串对象列表中
            strList.emplace_back(newString(str.substr(start)));
    }
    // 否则进行有限分割
    else
    {
        // 当字符串遍历到末尾或者分割次数达到上限时结束
        while (end < str.size() && maxSplit > 0)
        {
            // 如果当前字符为分隔符
            if (std::isspace(str[end]))
            {
                // 如果两指针之间有字符则进行分割
                if (end - start > 0)
                {
                    // 将分割结果添加到字符串对象列表中
                    strList.emplace_back(newString(str.substr(start, end - start)));
                    // 更新分割位置
                    start = end;
                    // 分割次数减1
                    --maxSplit;
                }
                // 跳过分隔符
                ++start;
            }
            ++end;
        }
        // 如果end指针未到达末尾则将剩余字符添加到字符串对象列表中
        if (end < str.size())
        {
            // 设置end指针为字符串末尾
            end = str.size();
            // 如果start指针未到达末且指向空白字符则跳过
            while (start < str.size() && std::isspace(str[start]))
                ++start;
        }
        // 如果两指针之间有字符则进行分割
        if (end - start > 0)
            // 将分割结果添加到字符串对象列表中
            strList.emplace_back(newString(str.substr(start)));
    }
    return strList;
}

// 分隔符字符串分割函数
std::vector<std::shared_ptr<Object>> String::splitByDelimiter(const std::string &str, const std::string &delim, int64_t maxSplit)
{
    // 创建字符串对象列表
    std::vector<std::shared_ptr<Object>> strList;
    // 如果分隔符为空则直接添加原字符串
    if (delim.empty())
    {
        strList.emplace_back(newString(str));
        return strList;
    }
    // 定义分割位置
    size_t start = 0;
    size_t end = str.find(delim);
    // 如果最大分割次数小于0则分割到底
    if (maxSplit < 0)
    {
        // 当无法找到分隔符时退出
        while (end != std::string::npos)
        {
            // 直接添加当前段（可能是空字符串）
            strList.emplace_back(newString(str.substr(start, end - start)));
            // 更新起始位置
            start = end + delim.length();
            // 继续查找分隔符
            end = str.find(delim, start);
        }
    }
    // 否则进行有限分割
    else
    {
        // 当字符串遍历到末尾或者分割次数达到上限时结束
        while (end != std::string::npos && maxSplit > 0)
        {
            // 直接添加当前段（可能是空字符串）
            strList.emplace_back(newString(str.substr(start, end - start)));
            // 更新起始位置
            start = end + delim.length();
            // 继续查找分隔符
            end = str.find(delim, start);
            // 分割次数减1
            --maxSplit;
        }
    }
    // 添加剩余部分（可能是空字符串）
    strList.emplace_back(newString(str.substr(start)));
    // 返回字符串对象列表
    return strList;
}

// 1参数字串前缀判断函数
std::shared_ptr<Object> String::prefixMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &prefix)
{
    // 判断参数类型是否为字符串对象
    if (prefix->getType() != OBJECT_STRING)
        return newError("prefix() argument must be string, not '%s'", prefix->getName().c_str());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> prefixObj = std::dynamic_pointer_cast<String>(prefix);
    // 调用字符串前缀判断函数
    return newBool(isPrefix(strObj->value, prefixObj->value));
}

// 字符串前缀判断函数
bool String::isPrefix(const std::string &str, const std::string &prefix)
{
    // 如果前缀长度大于字符串长度则返回false
    if (prefix.size() > str.size())
        return false;
    // 创建string_view，获取从start到end的位置的字符串视图
    std::string_view strView(str.data(), prefix.size());
    // 比较字符串
    return strView == prefix;
}

// 1参数字串后缀判断函数
std::shared_ptr<Object> String::suffixMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &suffix)
{
    // 判断参数类型是否为字符串对象
    if (suffix->getType() != OBJECT_STRING)
        return newError("suffix() argument must be string, not '%s'", suffix->getName().c_str());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> suffixObj = std::dynamic_pointer_cast<String>(suffix);
    // 调用字符串后缀判断函数
    return newBool(isSuffix(strObj->value, suffixObj->value));
}

// 字串后缀判断函数
bool String::isSuffix(const std::string &str, const std::string &suffix)
{
    // 如果后缀长度大于字符串长度则返回false
    if (suffix.size() > str.size())
        return false;
    // 创建string_view，获取从start到end的位置的字符串视图
    std::string_view strView(str.data() + str.size() - suffix.size(), suffix.size());
    // 比较字符串
    return strView == suffix;
}

// 0参数字串左修剪函数
std::shared_ptr<Object> String::ltrimMethod(const std::shared_ptr<Object> &obj)
{
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 调用字符串左修剪函数
    return newString(ltrim(strObj->value));
}

// 1参数字串左修剪函数
std::shared_ptr<Object> String::ltrimMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &chars)
{
    // 判断参数类型是否为字符串对象
    if (chars->getType() != OBJECT_STRING)
        return newError("ltrim() argument must be string, not '%s'", chars->getName().c_str());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> charsObj = std::dynamic_pointer_cast<String>(chars);
    // 调用字符串左修剪函数
    return newString(ltrim(strObj->value, charsObj->value));
}

// 0参数字串右修剪函数
std::shared_ptr<Object> String::rtrimMethod(const std::shared_ptr<Object> &obj)
{
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 调用字符串右修剪函数
    return newString(rtrim(strObj->value));
}

// 1参数字串右修剪函数
std::shared_ptr<Object> String::rtrimMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &chars)
{
    // 判断参数类型是否为字符串对象
    if (chars->getType() != OBJECT_STRING)
        return newError("rtrim() argument must be string, not '%s'", chars->getName().c_str());
    // 将对象转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> charsObj = std::dynamic_pointer_cast<String>(chars);
    // 调用字符串右修剪函数
    return newString(rtrim(strObj->value, charsObj->value));
}

// 0参数字串修剪函数
std::shared_ptr<Object> String::trimMethod(const std::shared_ptr<Object> &obj)
{
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 调用字符串修剪函数
    return newString(trim(strObj->value));
}

// 1参数字串修剪函数
std::shared_ptr<Object> String::trimMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &chars)
{
    // 判断参数类型是否为字符串对象
    if (chars->getType() != OBJECT_STRING)
        return newError("trim() argument must be string, not '%s'", chars->getName().c_str());
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> charsObj = std::dynamic_pointer_cast<String>(chars);
    // 调用字符串修剪函数
    return newString(trim(strObj->value, charsObj->value));
}

// 字串左修剪函数
std::string String::ltrim(const std::string &str, const std::string &chars)
{
    // 查找第一个非指定字符的位置
    size_t left = str.find_first_not_of(chars);
    // 如果未找到则返回空字符串，否则返回从该位置开始截取的子串
    return left == std::string::npos ? "" : str.substr(left);
}

// 字串右修剪函数
std::string String::rtrim(const std::string &str, const std::string &chars)
{
    size_t right = str.find_last_not_of(chars);
    // 如果未找到则返回空字符串，否则返回从0到该位置的子串
    return right == std::string::npos ? "" : str.substr(0, right + 1);
}

// 字串修剪函数
std::string String::trim(const std::string &str, const std::string &chars)
{
    // 调用字串左修剪函数和右修剪函数
    return rtrim(ltrim(str, chars), chars);
}

// 0参数字串裁剪函数
std::shared_ptr<Object> String::substrMethod(const std::shared_ptr<Object> &obj)
{
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 调用字符串裁剪函数
    return newString(strObj->value.substr());
}

// 1参数字串裁剪函数
std::shared_ptr<Object> String::substrMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &start)
{
    // 判断参数类型是否为整数对象
    if (start->getType() != OBJECT_INTEGER)
        return newError("substr() argument 1 must be integer, not '%s'", start->getName().c_str());
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为整数对象指针
    std::shared_ptr<Integer> startObj = std::dynamic_pointer_cast<Integer>(start);
    // 调用字符串裁剪函数
    return newString(strObj->value.substr(startObj->value));
}

// 2参数字串裁剪函数
std::shared_ptr<Object> String::substrMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &start, const std::shared_ptr<Object> &end)
{
    // 判断参数类型是否为整数对象
    if (start->getType() != OBJECT_INTEGER)
        return newError("substr() argument 1 must be integer, not '%s'", start->getName().c_str());
    // 判断参数类型是否为整数对象
    if (end->getType() != OBJECT_INTEGER)
        return newError("substr() argument 2 must be integer, not '%s'", end->getName().c_str());
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为整数对象指针
    std::shared_ptr<Integer> startObj = std::dynamic_pointer_cast<Integer>(start);
    // 将参数转换为整数对象指针
    std::shared_ptr<Integer> endObj = std::dynamic_pointer_cast<Integer>(end);
    // 调用字符串裁剪函数
    return newString(strObj->value.substr(startObj->value, endObj->value - startObj->value));
}

// 2参数字串替换函数
std::shared_ptr<Object> String::replaceMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &oldValue, const std::shared_ptr<Object> &newValue)
{
    // 判断参数类型是否为字符串类型
    if (oldValue->getType() != OBJECT_STRING)
        return newError("replace() argument 2 must be string, not '%s'", oldValue->getName().c_str());
    // 判断参数类型是否为字符串类型
    if (newValue->getType() != OBJECT_STRING)
        return newError("replace() argument 3 must be string, not '%s'", newValue->getName().c_str());
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> oldValueObj = std::dynamic_pointer_cast<String>(oldValue);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> newValueObj = std::dynamic_pointer_cast<String>(newValue);
    // 调用字符串替换函数
    return newString(replace(strObj->value, oldValueObj->value, newValueObj->value, -1));
}

// 3参数字串替换函数
std::shared_ptr<Object> String::replaceMethod(const std::shared_ptr<Object> &obj, const std::shared_ptr<Object> &oldValue, const std::shared_ptr<Object> &newValue, const std::shared_ptr<Object> &count)
{
    // 判断参数类型是否为字符串类型
    if (oldValue->getType() != OBJECT_STRING)
        return newError("replace() argument 1 must be string, not '%s'", oldValue->getName().c_str());
    // 判断参数类型是否为字符串类型
    if (newValue->getType() != OBJECT_STRING)
        return newError("replace() argument 2 must be string, not '%s'", newValue->getName().c_str());
    // 判断参数类型是否为整数类型
    if (count->getType() != OBJECT_INTEGER)
        return newError("replace() argument 3 must be integer, not '%s'", count->getName().c_str());
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> strObj = std::dynamic_pointer_cast<String>(obj);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> oldValueObj = std::dynamic_pointer_cast<String>(oldValue);
    // 将参数转换为字符串对象指针
    std::shared_ptr<String> newValueObj = std::dynamic_pointer_cast<String>(newValue);
    // 将参数转换为整数对象指针
    std::shared_ptr<Integer> countObj = std::dynamic_pointer_cast<Integer>(count);
    // 调用字符串替换函数
    return newString(replace(strObj->value, oldValueObj->value, newValueObj->value, countObj->value));
}

// 字串替换函数
std::string String::replace(const std::string &str, const std::string &oldValue, const std::string &newValue, int64_t count)
{
    // 创建输出字符串流
    std::ostringstream oss;
    // 创建字符串的上一次和当前位置的指针
    size_t pos = 0;
    size_t lastPos = 0;
    pos = str.find(oldValue, pos);
    // 如果count小于0则替换所有匹配项
    if (count < 0)
    {
        while (pos != std::string::npos)
        {
            // 将上一次匹配项和当前匹配项之间的部分以及替换字符串添加到输出字符串流中
            oss << str.substr(lastPos, pos - lastPos) << newValue;
            // 更新匹配位置
            pos += oldValue.length();
            lastPos = pos;
            // 查找下一个匹配项
            pos = str.find(oldValue, pos);
        }
    }
    // 否则替换指定数量的匹配项
    else
    {
        while (count > 0 && pos != std::string::npos)
        {
            // 将上一次匹配项和当前匹配项之间的部分以及替换字符串添加到输出字符串流中
            oss << str.substr(lastPos, pos - lastPos) << newValue;
            // 更新匹配位置
            pos += oldValue.length();
            lastPos = pos;
            // 查找下一个匹配项
            pos = str.find(oldValue, pos);
            // 减少替换次数
            --count;
        }
    }
    // 将剩余部分添加到输出字符串流中
    oss << str.substr(lastPos);
    // 返回替换后的字符串
    return oss.str();
}
