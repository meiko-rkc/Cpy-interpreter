#include <object/builtin_obj.h>
#include <evaluator/evaluator.h>
using namespace cpy::object;
using namespace cpy::evaluator;
// 内置函数映射表
std::unordered_map<std::string, Builtin::method> Builtin::methods = {
    {"str", &Builtin::strMethod},
    {"int", &Builtin::intMethod},
    {"float", &Builtin::floatMethod},
    {"bool", &Builtin::boolMethod},
    {"list", &Builtin::listMethod},
    {"hash", &Builtin::hashMethod},
    {"input", &Builtin::inputMethod},
    {"print", &Builtin::printMethod},
    {"len", &Builtin::lenMethod},
    {"lens", &Builtin::lensMethod},
    {"type", &Builtin::typeMethod},
    {"exit", &Builtin::exitMethod},
    {"system", &Builtin::systemMethod},
    {"abs", &Builtin::absMethod},
    {"max", &Builtin::maxMethod},
    {"min", &Builtin::minMethod},
    {"pow", &Builtin::powMethod},
};

// 空参构造函数
Builtin::Builtin() : Object(OBJECT_BUILTIN)
{
}

// 带参构造函数
Builtin::Builtin(const std::string &name)
{
    init(name);
}

// 内置函数对象获取函数
std::shared_ptr<Builtin> Builtin::getBuiltinObj(const std::string &name)
{
    // 如果在映射表中找不到内置函数,返回空指针
    if (methods.find(name) == methods.end())
        return nullptr;
    // 否则返回内置函数对象
    return std::shared_ptr<Builtin>(new Builtin(name));
}

// 内置函数对象调用函数
std::shared_ptr<Object> Builtin::call(const std::vector<std::shared_ptr<Object>> &args)
{
    // 直接调用内置函数
    return (*methods[name])(args);
}

// 内置函数对象初始化函数
void Builtin::init(const std::string &name)
{
    this->name = name;
    this->type = OBJECT_BUILTIN;
}

// 内置函数对象字符串化函数
std::string Builtin::toString() const
{
    return "<builtin function " + name + ">";
}

// 内置函数对象打印函数
void Builtin::print() const
{
    std::cout << toString() << std::endl;
}

// 内置函数对象哈希键值获取函数
HashKey Builtin::hashKey() const
{
    // 哈希键值为对象类型和对象名称的哈希值
    return HashKey(type, std::hash<std::string>()(name));
}

// 内置函数对象字符串化函数实现
std::shared_ptr<Object> Builtin::strMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数大于1,返回错误对象
    if (args.size() > 1)
        return newError("str() expected at most one argument (%d given)", args.size());
    // 如果参数个数为0,返回空字符串对象
    if (args.size() == 0)
        return newString();
    // 将参数中对象转化为字符串对象
    std::shared_ptr<Object> strObj = Evaluator::any2Str(args[0]);
    // 直接返回字符串对象
    return strObj;
}

// 内置函数对象整数化函数实现
std::shared_ptr<Object> Builtin::intMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不等于1,返回错误对象
    if (args.size() > 1)
        return newError("int() expected at most one argument (%d given)", args.size());
    // 如果参数个数为0,返回空整数对象
    if (args.size() == 0)
        return newInteger();
    // 将参数中对象转化为整数对象
    std::shared_ptr<Object> intObj = Evaluator::any2Int(args[0]);
    // 如果转化为空指针,则返回错误对象
    if (intObj == nullptr)
        return newError("int() argument must be a string or a real number, not '%s'", args[0]->getName().c_str());
    // 直接返回整数对象
    return intObj;
}

// 内置函数对象浮点数化函数实现
std::shared_ptr<Object> Builtin::floatMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不等于1,返回错误对象
    if (args.size() > 1)
        return newError("float() expected at most one argument (%d given)", args.size());
    // 如果参数个数为0,返回空浮点数对象
    if (args.size() == 0)
        return newFloat();
    // 将参数中对象转化为浮点数对象
    std::shared_ptr<Object> floatObj = Evaluator::any2Float(args[0]);
    // 如果转化为空指针,则返回错误对象
    if (floatObj == nullptr)
        return newError("float() argument must be a string or a real number, not '%s'", args[0]->getName().c_str());
    // 直接返回浮点数对象
    return floatObj;
}

// 内置函数对象布尔化函数实现
std::shared_ptr<Object> Builtin::boolMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不等于1,返回错误对象
    if (args.size() > 1)
        return newError("bool() expected at most one argument (%d given)", args.size());
    // 如果参数个数为0,返回空布尔对象
    if (args.size() == 0)
        return newBool();
    // 将参数中对象转化为布尔对象
    return Evaluator::any2Bool(args[0]);
}

// 内置函数对象列表化函数实现
std::shared_ptr<Object> Builtin::listMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数大于1,返回错误对象
    if (args.size() > 1)
        return newError("list() takes at most one argument (%d given)", args.size());
    // 如果参数个数为0,返回空列表对象
    if (args.size() == 0)
        return newList();
    // 将参数中对象转化为列表对象
    return Evaluator::any2List(args[0]);
}

// 内置函数对象哈希化函数实现
std::shared_ptr<Object> Builtin::hashMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数大于1,返回错误对象
    if (args.size() > 1)
        return newError("hash() takes at most one argument (%d given)", args.size());
    // 如果参数个数为0,返回空哈希对象
    if (args.size() == 0)
        return newHash();
    // 将参数中对象转化为哈希对象
    return Evaluator::any2Hash(args[0]);
}

// 内置函数输入函数实现
std::shared_ptr<Object> Builtin::inputMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 输入的字符串
    std::string input;
    // 遍历参数列表
    for (auto &arg : args)
    {
        // 如果参数是字符串对象,则输出字符串对象对应值
        if (arg->getType() == OBJECT_STRING)
        {
            // 将对象指针转换为字符串对象指针
            std::shared_ptr<object::String> strObj = std::dynamic_pointer_cast<object::String>(arg);
            // 输出字符串对象对应值
            std::cout << strObj->value;
        }
        // 否则输出对象字符串化结果
        else
            std::cout << arg->toString();
    }
    // 从标准输入流中读取一行字符串
    std::getline(std::cin, input);
    // 返回输入的字符串对象
    return newString(input);
}

// 内置打印输出函数实现
std::shared_ptr<Object> Builtin::printMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    for (auto &arg : args)
    {
        // 如果参数是字符串对象,则输出字符串对象对应值
        if (arg->getType() == OBJECT_STRING)
        {
            // 将对象指针转换为字符串对象指针
            std::shared_ptr<object::String> strObj = std::dynamic_pointer_cast<object::String>(arg);
            std::cout << strObj->value;
        }
        // 否则输出对象字符串化结果
        else
            std::cout << arg->toString();
    }
    return newNull();
}

// 内置长度获取函数实现
std::shared_ptr<Object> Builtin::lenMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不为1,返回错误对象
    if (args.size() != 1)
        return newError("len() takes exactly one argument (%d given)", args.size());
    // 获取参数对象
    std::shared_ptr<Object> arg = args[0];
    // 根据参数类型进行不同处理
    switch (arg->getType())
    {
    // 如果参数是列表对象,则返回列表对象长度
    case OBJECT_LIST:
    {
        // 将对象指针转换为列表对象指针
        std::shared_ptr<object::List> listObj = std::dynamic_pointer_cast<object::List>(arg);
        // 返回列表对象长度
        return newInteger(listObj->size());
    }
    // 如果参数是字符串对象,则返回字符串对象长度
    case OBJECT_STRING:
    {
        // 将对象指针转换为字符串对象指针
        std::shared_ptr<object::String> strObj = std::dynamic_pointer_cast<object::String>(arg);
        // 返回字符串对象长度
        return newInteger(strObj->size());
    }
    // 如果参数是哈希对象,则返回哈希对象长度
    case OBJECT_HASH:
    {
        // 将对象指针转换为哈希对象指针
        std::shared_ptr<object::Hash> hashObj = std::dynamic_pointer_cast<object::Hash>(arg);
        // 将哈希对象长度转为整数对象指针加入长度列表
        return newInteger(hashObj->size());
    }
    // 否则返回错误对象
    default:
        return newError("len() not supported for type %s", arg->getName().c_str());
    }
}

// 内置长度获取函数实现
std::shared_ptr<Object> Builtin::lensMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不为1,返回错误对象
    if (args.size() < 1)
        return newError("lens() takes exactly at least one argument (%d given)", args.size());
    // 创建长度列表
    std::vector<std::shared_ptr<Object>> lenElems;
    // 预分配长度列表空间
    lenElems.reserve(args.size());
    // 遍历参数列表
    for (auto &arg : args)
    {
        // 根据参数类型进行不同处理
        switch (arg->getType())
        {
        // 如果参数是列表对象,则返回列表对象长度
        case OBJECT_LIST:
        {
            // 将对象指针转换为列表对象指针
            std::shared_ptr<object::List> listObj = std::dynamic_pointer_cast<object::List>(arg);
            // 返回列表对象长度
            lenElems.emplace_back(newInteger(listObj->size()));
            break;
        }
        // 如果参数是字符串对象,则返回字符串对象长度
        case OBJECT_STRING:
        {
            // 将对象指针转换为字符串对象指针
            std::shared_ptr<object::String> strObj = std::dynamic_pointer_cast<object::String>(arg);
            // 将字符串长度转为整数对象指针加入长度列表
            lenElems.emplace_back(newInteger(strObj->size()));
            break;
        }
        // 如果参数是哈希对象,则返回哈希对象长度
        case OBJECT_HASH:
        {
            // 将对象指针转换为哈希对象指针
            std::shared_ptr<object::Hash> hashObj = std::dynamic_pointer_cast<object::Hash>(arg);
            // 将哈希对象长度转为整数对象指针加入长度列表
            lenElems.emplace_back(newInteger(hashObj->size()));
            break;
        }
        // 否则返回错误对象
        default:
            return newError("len() not supported for type %s", arg->getName().c_str());
        }
    }
    // 返回长度列表
    return newList(lenElems);
}

// 内置类型获取函数实现
std::shared_ptr<Object> Builtin::typeMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不为1,返回错误对象
    if (args.size() != 1)
        return newError("type() takes exactly one argument (%d given)", args.size());
    // 获取参数对象
    std::shared_ptr<Object> arg = args[0];
    // 返回参数对象类型对象
    return newType(arg->getType());
}

// 内置退出函数实现
std::shared_ptr<Object> Builtin::exitMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数大于1，返回错误对象
    if (args.size() > 1)
        return newError("exit() takes at most one argument (%d given)", args.size());
    // 如果参数个数为0，则直接退出程序
    if (args.size() == 0)
        exit(0);
    // 否则如果参数为整数对象，则返回参数值作为退出码
    if (args[0]->getType() == OBJECT_INTEGER)
    {
        // 将对象指针转换为整数对象指针
        std::shared_ptr<object::Integer> intObj = std::dynamic_pointer_cast<object::Integer>(args[0]);
        // 整数对象值作为退出码
        std::exit(int(intObj->value));
    }
    // 否则将参数的字符串化结果信息打印
    else
    {
        // 如果参数为字符串对象，则打印字符串对象值到标准错误流中
        if (args[0]->getType() == OBJECT_STRING)
        {
            // 将对象指针转换为字符串对象指针
            std::shared_ptr<object::String> strObj = std::dynamic_pointer_cast<object::String>(args[0]);
            // 打印字符串对象值
            std::cerr << strObj->value << std::endl;
        }
        // 否则将参数的字符串化结果信息打印到标准错误流中
        else
            std::cerr << args[0]->toString() << std::endl;
        // 1作为退出码
        std::exit(1);
    }
    // 返回空对象
    return newNull();
}

// 内置系统函数实现
std::shared_ptr<Object> Builtin::systemMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不为1,返回错误对象
    if (args.size() != 1)
        return newError("system() takes exactly one argument (%d given)", args.size());
    // 获取参数对象
    std::shared_ptr<Object> arg = args[0];
    // 如果参数不是字符串对象,返回错误对象
    if (arg->getType() != OBJECT_STRING)
        return newError("system() argument must be a string, not '%s'", arg->getName().c_str());
    // 将对象指针转换为字符串对象指针
    std::shared_ptr<object::String> strObj = std::dynamic_pointer_cast<object::String>(arg);
    // 执行系统命令
    std::system(strObj->value.c_str());
    // 返回空对象
    return newNull();
}

// 内置函数对象绝对值函数实现
std::shared_ptr<Object> Builtin::absMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数不为1,返回错误对象
    if (args.size() != 1)
        return newError("abs() takes exactly one argument (%d given)", args.size());
    // 获取参数对象
    std::shared_ptr<Object> arg = args[0];
    // 如果参数是整数对象
    if (arg->getType() == OBJECT_INTEGER)
    {
        // 将对象指针转换为整数对象指针
        std::shared_ptr<object::Integer> intObj = std::dynamic_pointer_cast<object::Integer>(arg);
        // 返回整数对象绝对值
        return newInteger(std::abs(intObj->value));
    }
    // 如果参数是浮点数对象
    else if (arg->getType() == OBJECT_FLOAT)
    {
        // 将对象指针转换为浮点数对象指针
        std::shared_ptr<object::Float> floatObj = std::dynamic_pointer_cast<object::Float>(arg);
        // 返回浮点数对象绝对值
        return newFloat(std::abs(floatObj->value));
    }
    // 否则返回错误对象
    else
        return newError("abs() argument must be a number, not '%s'", arg->getName().c_str());
}

// 内建最大值函数实现
std::shared_ptr<Object> Builtin::maxMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数小于1,返回错误对象
    if (args.size() < 1)
        return newError("max() takes at least one argument (%d given)", args.size());
    // 设置最大值为第一个参数
    std::shared_ptr<Object> maxObj = args[0];
    // 遍历参数列表
    for (auto &arg : args)
    {
        // 对比参数和最大值的大小
        std::shared_ptr<Object> obj = Evaluator::evalInfix(">", arg, maxObj);
        // 如果结果为错误对象,返回错误对象
        if (obj->getType() == OBJECT_ERROR)
            return obj;
        // 将对象指针转换为布尔对象指针
        std::shared_ptr<object::Bool> boolObj = std::dynamic_pointer_cast<object::Bool>(obj);
        // 如果结果为真,则更新最大值
        if (boolObj->value)
            maxObj = arg;
    }
    // 返回最大值
    return maxObj;
}

// 内建最小值函数实现
std::shared_ptr<Object> Builtin::minMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数小于1,返回错误对象
    if (args.size() < 1)
        return newError("min() takes at least one argument (%d given)", args.size());
    // 设置最小值为第一个参数
    std::shared_ptr<Object> minObj = args[0];
    // 遍历参数列表
    for (auto &arg : args)
    {
        // 对比参数和最小值的大小
        std::shared_ptr<Object> obj = Evaluator::evalInfix("<", arg, minObj);
        // 如果结果为错误对象,返回错误对象
        if (obj->getType() == OBJECT_ERROR)
            return obj;
        // 将对象指针转换为布尔对象指针
        std::shared_ptr<object::Bool> boolObj = std::dynamic_pointer_cast<object::Bool>(obj);
        // 如果结果为真,则更新最小值
        if (boolObj->value)
            minObj = arg;
    }
    // 返回最小值
    return minObj;
}

// 内建幂函数实现
std::shared_ptr<Object> Builtin::powMethod(const std::vector<std::shared_ptr<Object>> &args)
{
    // 如果参数个数大于3，返回错误对象
    if (args.size() > 3)
        return newError("pow() takes at most 3 arguments (%d given)", args.size());
    // 如果参数有为0返回错误对象
    if (args.size() == 0)
        return newError("pow() missing required argument 'base' (pos 1)");
    // 如果参数个数为1,返回错误对象
    if (args.size() == 1)
        return newError("pow() missing required argument 'exp' (pos 2)");
    // 进行幂指运算
    std::shared_ptr<Object> obj = Evaluator::evalInfix("**", args[0], args[1]);
    // 如果结果为错误对象,返回错误对象
    if (obj->getType() == OBJECT_ERROR)
        return obj;
    // 如果参数个数为3,进行取余运算
    if (args.size() == 3)
    {
        // 进行取余运算
        obj = Evaluator::evalInfix("%", obj, args[2]);
    }
    // 返回结果
    return obj;
}
