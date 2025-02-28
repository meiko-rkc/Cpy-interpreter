#pragma once
#include <ast/ast.h>
#include <object/object.h>
#include <evaluator/environment.h>
using namespace cpy::ast;
using namespace cpy::object;
// 一级命名空间   namespace pi
namespace cpy
{
    // 一级命名空间   namespace pi
    namespace evaluator
    {
        // 定义求值Evaluator类
        class Evaluator
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Evaluator();

            /* 析构函数 */
            ~Evaluator() = default;

            /* 公有成员函数 */
            static bool isError(const std::shared_ptr<Object> &object);    // 错误对象判断函数
            static bool isBreak(const std::shared_ptr<Object> &object);    // break对象判断函数
            static bool isContinue(const std::shared_ptr<Object> &object); // continue对象判断函数
            static bool isReturn(const std::shared_ptr<Object> &object);   // return对象判断函数
            static bool isTrue(const std::shared_ptr<Object> &object);     // 对象真假判断函数

            // 对象创建函数
            static std::shared_ptr<Object> newError(const char *format, ...);                                            // 错误对象生成函数
            static std::shared_ptr<Object> newInteger(int64_t value);                                                    // 整数对象生成函数
            static std::shared_ptr<Object> newFloat(double value);                                                       // 浮点数对象生成函数
            static std::shared_ptr<Object> newBool(bool value);                                                          // 布尔对象生成函数
            static std::shared_ptr<Object> newString(const std::string &value);                                          // 字符串对象生成函数
            static std::shared_ptr<Object> newNull();                                                                    // 空值对象生成函数
            static std::shared_ptr<Object> newList(const std::vector<std::shared_ptr<Object>> &elements);                // 列表对象生成函数
            static std::shared_ptr<Object> newHash(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &pairs); // 哈希对象生成函数
            static std::shared_ptr<Object> newBreak();                                                                   // break对象生成函数
            static std::shared_ptr<Object> newContinue();                                                                // continue对象生成函数

            // 求值函数
            static std::shared_ptr<Object> eval(const std::shared_ptr<ast::Node> &node, std::shared_ptr<Environment> &env);                              // 求值函数
            static std::shared_ptr<Object> evalProgram(const std::shared_ptr<ast::Program> &program, std::shared_ptr<Environment> &env);                 // 程序求值函数
            static std::shared_ptr<Object> evalProgram(const std::list<std::shared_ptr<ast::Statement>> &statements, std::shared_ptr<Environment> &env); // 语句列表求值函数

            // 数据求值函数
            static std::shared_ptr<Object> evalInteger(const std::shared_ptr<ast::Integer> &integer);                           // 整数结点求值函数
            static std::shared_ptr<Object> evalFloat(const std::shared_ptr<ast::Float> &flt);                                   // 浮点数结点求值函数
            static std::shared_ptr<Object> evalBool(const std::shared_ptr<ast::Bool> &bl);                                      // 布尔结点求值函数
            static std::shared_ptr<Object> evalString(const std::shared_ptr<ast::String> &str);                                 // 字符串结点求值函数
            static std::shared_ptr<Object> evalNull(const std::shared_ptr<ast::Null> &null);                                    // 空值结点求值函数
            static std::shared_ptr<Object> evalList(const std::shared_ptr<ast::List> &list, std::shared_ptr<Environment> &env); // 列表结点求值函数
            static std::shared_ptr<Object> evalHash(const std::shared_ptr<ast::Hash> &hash, std::shared_ptr<Environment> &env); // 哈希结点求值函数

            // 索引求值函数
            static std::shared_ptr<Object> evalIndex(const std::shared_ptr<ast::Index> &indexNode, std::shared_ptr<Environment> &env);                                              // 索引结点求值函数
            static std::shared_ptr<Object> evalIndex(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &index);                                                    // 索引对象求值函数
            static std::shared_ptr<Object> evalListIndex(const std::shared_ptr<Object> &list, const std::shared_ptr<Object> &index);                                                // 列表索引对象求值函数
            static std::shared_ptr<Object> evalStringIndex(const std::shared_ptr<Object> &str, const std::shared_ptr<Object> &index);                                               // 字符串索引对象求值函数
            static std::shared_ptr<Object> evalHashIndex(const std::shared_ptr<Object> &hash, const std::shared_ptr<Object> &index);                                                // 哈希索引对象求值函数
            static std::shared_ptr<Object> evalIndexAssign(const std::shared_ptr<ast::Index> &indexNode, const std::shared_ptr<Object> &valObj, std::shared_ptr<Environment> &env); // 索引结点赋值表达式求值函数
            static std::shared_ptr<Object> evalIndexAssign(const std::shared_ptr<Object> &leftObj, const std::shared_ptr<Object> &indexObj, const std::shared_ptr<Object> &valObj); // 索引结点对象赋值表达式求值函数
            static std::shared_ptr<Object> evalListIndexAssign(const std::shared_ptr<Object> &list, const std::shared_ptr<Object> &index, const std::shared_ptr<Object> &val);      // 列表索引结点对象赋值表达式求值函数
            static std::shared_ptr<Object> evalHashIndexAssign(const std::shared_ptr<Object> &hash, const std::shared_ptr<Object> &index, const std::shared_ptr<Object> &val);      // 哈希索引结点对象赋值表达式求值函数

            // 属性求值函数
            static std::shared_ptr<Object> evalProperty(const std::shared_ptr<ast::Property> &propertyNode, std::shared_ptr<Environment> &env);                                              // 属性结点求值函数
            static std::shared_ptr<Object> evalProperty(const std::shared_ptr<Object> &obj, const std::string &property);                                                                    // 属性结点对象求值函数
            static std::shared_ptr<Object> evalPropertyAssign(const std::shared_ptr<ast::Property> &propertyNode, const std::shared_ptr<Object> &valObj, std::shared_ptr<Environment> &env); // 属性结点赋值表达式求值函数
            static std::shared_ptr<Object> evalPropertyAssign(const std::shared_ptr<Object> &obj, const std::string &property, const std::shared_ptr<Object> &val);                          // 属性结点对象赋值表达式求值函数

            // 语句求值函数
            static std::shared_ptr<Object> evalIdentifier(const std::shared_ptr<ast::Identifier> &ident, std::shared_ptr<Environment> &env);           // 标识符结点求值函数
            static std::shared_ptr<Object> evalAssign(const std::shared_ptr<ast::Assign> &assign, std::shared_ptr<Environment> &env);                  // 赋值表达式结点求值函数
            static std::shared_ptr<Object> evalCompoundAssign(const std::shared_ptr<ast::CompoundAssign> &cassign, std::shared_ptr<Environment> &env); // 复合赋值表达式结点求值函数
            static std::shared_ptr<Object> evalTernary(const std::shared_ptr<ast::Ternary> &ternary, std::shared_ptr<Environment> &env);               // 三元表达式结点求值函数
            static std::shared_ptr<Object> evalBlock(const std::shared_ptr<ast::Block> &block, std::shared_ptr<Environment> &env);                     // 代码块结点求值函数
            static std::shared_ptr<Object> evalIf(const std::shared_ptr<ast::If> &ifNode, std::shared_ptr<Environment> &env);                          // if语句结点求值函数
            static std::shared_ptr<Object> evalSwitch(const std::shared_ptr<ast::Switch> &switchNode, std::shared_ptr<Environment> &env);              // switch语句结点求值函数
            static std::shared_ptr<Object> evalWhile(const std::shared_ptr<ast::While> &whileNode, std::shared_ptr<Environment> &env);                 // while语句结点求值函数
            static std::shared_ptr<Object> evalFor(const std::shared_ptr<ast::For> &forNode, std::shared_ptr<Environment> &env);                       // for语句结点求值函数
            static std::shared_ptr<Object> evalBreak(const std::shared_ptr<ast::Break> &breakNode);                                                    // break语句结点求值函数
            static std::shared_ptr<Object> evalContinue(const std::shared_ptr<ast::Continue> &continueNode);                                           // continue语句结点求值函数
            static std::shared_ptr<Object> evalReturn(const std::shared_ptr<ast::Return> &returnNode, std::shared_ptr<Environment> &env);              // return语句结点求值函数

            // call函数调用结点求值函数
            static std::shared_ptr<Object> evalCall(const std::shared_ptr<ast::Call> &callNode, std::shared_ptr<Environment> &env);                                             // call结点求值函数
            static std::shared_ptr<Object> evalCall(const std::shared_ptr<Object> &obj, std::vector<std::shared_ptr<Object>> &args, std::shared_ptr<Environment> &env);         // call求值函数
            static std::shared_ptr<Object> evalCallFunction(const std::shared_ptr<Object> &obj, std::vector<std::shared_ptr<Object>> &args, std::shared_ptr<Environment> &env); // call函数调用求值函数
            static std::shared_ptr<Object> evalCallBuiltin(const std::shared_ptr<Object> &obj, std::vector<std::shared_ptr<Object>> &args);                                     // call内置函数调用求值函数
            static std::shared_ptr<Object> evalCallMethod(const std::shared_ptr<Object> &obj, std::vector<std::shared_ptr<Object>> &args);                                      // call方法调用求值函数
            static std::shared_ptr<Environment> extendFunctionEnv(const std::shared_ptr<object::Function> &funcObj, const std::vector<std::shared_ptr<Object>> &args);          // 环境扩展函数

            // in运算符求值函数
            static std::shared_ptr<Object> evalIn(const std::shared_ptr<ast::In> &in, std::shared_ptr<Environment> &env);        // in运算符结点求值函数
            static std::shared_ptr<Object> evalIn(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);    // in运算求值函数
            static std::shared_ptr<Object> evalInList(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &list); // in运算列表求值函数
            static std::shared_ptr<Object> evalInStr(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &str);   // in运算字符串求值函数
            static std::shared_ptr<Object> evalInHash(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &hash); // in运算哈希求值函数

            // fn函数求值函数
            static std::shared_ptr<Object> evalFunction(const std::shared_ptr<ast::Function> &func, std::shared_ptr<Environment> &env); // 函数结点求值函数

            // 对象类型转换函数
            static std::shared_ptr<Object> int2Float(const std::shared_ptr<Object> &integer); // 整数转浮点数函数
            static std::shared_ptr<Object> int2Bool(const std::shared_ptr<Object> &integer);  // 整数转布尔类型数函数
            static std::shared_ptr<Object> float2Int(const std::shared_ptr<Object> &flt);     // 浮点数转整数函数
            static std::shared_ptr<Object> float2Bool(const std::shared_ptr<Object> &flt);    // 浮点数转布尔类型数函数
            static std::shared_ptr<Object> bool2Int(const std::shared_ptr<Object> &bl);       // 布尔类型数转整数函数
            static std::shared_ptr<Object> bool2Float(const std::shared_ptr<Object> &bl);     // 布尔类型数转浮点数函数
            static std::shared_ptr<Object> str2Int(const std::shared_ptr<Object> &str);       // 字符串转整数函数
            static std::shared_ptr<Object> str2Float(const std::shared_ptr<Object> &str);     // 字符串转浮点数函数
            static std::shared_ptr<Object> str2Bool(const std::shared_ptr<Object> &str);      // 字符串转布尔类型数函数
            static std::shared_ptr<Object> str2List(const std::shared_ptr<Object> &str);      // 字符串转列表函数
            static std::shared_ptr<Object> null2Bool();                                       // 空值类型数转布尔类型函数
            static std::shared_ptr<Object> list2Bool(const std::shared_ptr<Object> &list);    // 列表转布尔类型数函数
            static std::shared_ptr<Object> list2Hash(const std::shared_ptr<Object> &list);    // 列表转哈希函数
            static std::shared_ptr<Object> hash2Bool(const std::shared_ptr<Object> &hash);    // 哈希转布尔类型数函数
            static std::shared_ptr<Object> hash2List(const std::shared_ptr<Object> &hash);    // 哈希转列表函数
            static std::shared_ptr<Object> any2Bool(const std::shared_ptr<Object> &any);      // 任意类型数转布尔类型数函数
            static std::shared_ptr<Object> any2Str(const std::shared_ptr<Object> &any);       // 任意类型数转字符串函数
            static std::shared_ptr<Object> any2Int(const std::shared_ptr<Object> &any);       // 任意类型数转整数函数
            static std::shared_ptr<Object> any2Float(const std::shared_ptr<Object> &any);     // 任意类型数转浮点数函数
            static std::shared_ptr<Object> any2List(const std::shared_ptr<Object> &any);      // 任意类型数转列表函数
            static std::shared_ptr<Object> any2Hash(const std::shared_ptr<Object> &any);      // 任意类型数转哈希函数

            // prefix前缀表达式求值函数
            static std::shared_ptr<Object> evalPrefix(const std::shared_ptr<ast::Prefix> &prefix, std::shared_ptr<Environment> &env);                                       // 前缀表达式求值函数
            static std::shared_ptr<Object> evalChgPrefix(const std::shared_ptr<ast::Prefix> &prefix, std::shared_ptr<Environment> &env);                                    // 自变化前缀表达式求值函数
            static std::shared_ptr<Object> evalIdentChgPrefix(const std::string &op, const std::shared_ptr<ast::Identifier> &ident, std::shared_ptr<Environment> &env);     // 标识符自变化前缀表达式求值函数
            static std::shared_ptr<Object> evalIndexChgPrefix(const std::string &op, const std::shared_ptr<ast::Index> &index, std::shared_ptr<Environment> &env);          // 索引自变化前缀表达式求值函数
            static std::shared_ptr<Object> evalPropertyChgPrefix(const std::string &op, const std::shared_ptr<ast::Property> &property, std::shared_ptr<Environment> &env); // 属性自变化前缀表达式求值函数
            static std::shared_ptr<Object> evalObjChgPrefix(const std::string &op, const std::shared_ptr<Object> &obj);                                                     // 对象自变化前缀表达式求值函数
            static std::shared_ptr<Object> evalObjExpPrefix(const std::string &op, const std::shared_ptr<Object> &right);                                                   // 表达式对象前缀求值函数
            static std::shared_ptr<Object> evalIntExpPrefix(const std::string &op, const std::shared_ptr<Object> &right);                                                   // 整数前缀表达式求值函数
            static std::shared_ptr<Object> evalFloatExpPrefix(const std::string &op, const std::shared_ptr<Object> &right);                                                 // 浮点数前缀表达式求值函数
            static std::shared_ptr<Object> evalStrExpPrefix(const std::string &op, const std::shared_ptr<Object> &right);                                                   // 字符串前缀表达式求值函数
            static std::shared_ptr<Object> evalBoolLogPrefix(const std::string &op, const std::shared_ptr<Object> &right);                                                  // 布尔类型数前缀逻辑表达式求值函数
            static std::shared_ptr<Object> evalListExpPrefix(const std::string &op, const std::shared_ptr<Object> &right);                                                  // 列表前缀表达式求值函数

            // infix中缀表达式求值函数
            static std::shared_ptr<Object> evalInfix(const std::shared_ptr<ast::Infix> &infix, std::shared_ptr<Environment> &env);                                   // 中缀表达式求值函数
            static std::shared_ptr<Object> evalInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);              // 中缀表达式求值函数
            static std::shared_ptr<Object> evalIntInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);           // 整数中缀表达式求值函数
            static std::shared_ptr<Object> evalFloatInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);         // 浮点数中缀表达式求值函数
            static std::shared_ptr<Object> evalBoolInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);          // 布尔类型数中缀表达式求值函数
            static std::shared_ptr<Object> evalStrInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);           // 字符串中缀表达式求值函数
            static std::shared_ptr<Object> evalNullInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);          // 空值中缀表达式求值函数
            static std::shared_ptr<Object> evalListInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);          // 列表中缀表达式求值函数
            static std::shared_ptr<Object> evalHashInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);          // 哈希中缀表达式求值函数
            static std::shared_ptr<Object> evalHashKeysInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);      // 哈希键列表中缀表达式求值函数
            static std::shared_ptr<Object> evalHashValuesInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);    // 哈希值列表中缀表达式求值函数
            static std::shared_ptr<Object> evalTypeInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);          // 类型对象中缀表达式求值函数
            static std::shared_ptr<Object> evalFunctionInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);      // 函数对象中缀表达式求值函数
            static std::shared_ptr<Object> evalBuiltinInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);       // 内置函数中缀表达式求值函数
            static std::shared_ptr<Object> evalBuiltinMethodInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right); // 内置方法中缀表达式求值函数
            static std::shared_ptr<Object> evalDiffTypeInfix(const std::string &op, const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right);      // 不同类型数比较函数

            // postfix后缀表达式求值函数
            static std::shared_ptr<Object> evalPostfix(const std::shared_ptr<ast::Postfix> &postfix, std::shared_ptr<Environment> &env);                                     // 后缀表达式求值函数
            static std::shared_ptr<Object> evalChgPostfix(const std::shared_ptr<ast::Postfix> &postfix, std::shared_ptr<Environment> &env);                                  // 标识符自变化后缀表达式求值函数
            static std::shared_ptr<Object> evalIdentChgPostfix(const std::string &op, const std::shared_ptr<ast::Identifier> &ident, std::shared_ptr<Environment> &env);     // 标识符自变化后缀表达式求值函数
            static std::shared_ptr<Object> evalIndexChgPostfix(const std::string &op, const std::shared_ptr<ast::Index> &index, std::shared_ptr<Environment> &env);          // 索引自变化后缀表达式求值函数
            static std::shared_ptr<Object> evalPropertyChgPostfix(const std::string &op, const std::shared_ptr<ast::Property> &property, std::shared_ptr<Environment> &env); // 属性自变化后缀表达式求值函数
            static std::shared_ptr<Object> evalObjExpPostfix(const std::string &op, const std::shared_ptr<Object> &left);                                                    // 后缀表达式求值函数
            static std::shared_ptr<Object> evalIntExpPostfix(const std::string &op, const std::shared_ptr<Object> &left);                                                    // 整数后缀表达式求值函数
            static std::shared_ptr<Object> evalFloatExpPostfix(const std::string &op, const std::shared_ptr<Object> &left);                                                  // 浮点数后缀表达式求值函数
        };
    }
}