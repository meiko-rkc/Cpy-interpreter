#pragma once
#include <cmath>
#include <string>
#include <iostream>
#include <unordered_map>
#include <evaluator/evaluator.h>
// 一级命名空间 namespace pi
namespace cpy
{
    // 二级命名空间 namespace evaluator
    namespace evaluator
    {
        // 定义数学类
        class Math
        {
        public:
            /* 构造函数 */
            // 空参构造函数
            Math() {};

            /* 析构函数 */
            ~Math() = default;

            // 整数类
            class Integer
            {
            public:
                /* 构造函数 */
                // 空参构造函数
                Integer() {};

                /* 析构函数 */
                ~Integer() = default;

                // 整数前缀表达式计算函数指针
                typedef int64_t (*intExpPrefixFn)(int64_t);

                // 整数中缀表达式计算函数指针
                typedef int64_t (*intExpInfixFn)(int64_t, int64_t);

                // 整数中缀逻辑运算函数指针
                typedef bool (*intCmpInfixFn)(int64_t, int64_t);

                // 整数后缀表达式计算函数指针
                typedef int64_t (*intExpPostfixFn)(int64_t);

                /* 公有成员函数 */
                /* 整数前缀表达式计算函数 */
                // 数学运算函数
                static int64_t plus(int64_t right);  // 正数 '+'
                static int64_t minus(int64_t right); // 负数 '-'

                // 位运算函数
                static int64_t bwnot(int64_t right); // 按位非 '~'

                // 自变化算术运算函数
                static int64_t inc(int64_t right); // 自增 '++'
                static int64_t dec(int64_t right); // 自减 '--'

                // 前缀表达式计算函数
                static int64_t evalIntExpPrefix(const std::string &op, int64_t right); // 前缀表达式求值函数

                // 运算符有效性判断函数
                static bool isValidExpPrefixOp(const std::string &op); // 前缀表达式运算符有效性判断函数

                /* 整数中缀表达式计算函数 */
                // 数学运算函数
                static int64_t add(int64_t left, int64_t right); // 加法 '+'
                static int64_t sub(int64_t left, int64_t right); // 减法 '-'
                static int64_t mul(int64_t left, int64_t right); // 乘法 '*'
                static int64_t div(int64_t left, int64_t right); // 除法 '/'
                static int64_t mod(int64_t left, int64_t right); // 取模 '%'
                static int64_t pow(int64_t left, int64_t right); // 幂运算 '**'

                // 位运算函数
                static int64_t bwand(int64_t left, int64_t right);  // 按位与 '&'
                static int64_t bwor(int64_t left, int64_t right);   // 按位或 '|'
                static int64_t bwxor(int64_t left, int64_t right);  // 按位异或 '^'
                static int64_t lshift(int64_t left, int64_t right); // 左移 '<<'
                static int64_t rshift(int64_t left, int64_t right); // 右移 '>>'

                // 比较运算函数
                static bool lt(int64_t left, int64_t right); // 小于 '<'
                static bool gt(int64_t left, int64_t right); // 大于 '>'
                static bool le(int64_t left, int64_t right); // 小于等于 '<='
                static bool ge(int64_t left, int64_t right); // 大于等于 '>='
                static bool eq(int64_t left, int64_t right); // 等于 '=='
                static bool ne(int64_t left, int64_t right); // 不等于 '!='

                // 整数中缀表达式计算函数
                static int64_t evalIntExpInfix(const std::string &op, int64_t left, int64_t right); // 中缀表达式求值函数
                static bool evalIntCmpInfix(const std::string &op, int64_t left, int64_t right);    // 中缀比较表达式求值函数

                // 运算符有效性判断函数
                static bool isValidInfixOp(const std::string &op);    // 中缀运算符有效性判断函数
                static bool isValidExpInfixOp(const std::string &op); // 中缀表达式运算符有效性判断函数
                static bool isValidCmpInfixOp(const std::string &op); // 中缀逻辑运算符有效性判断函数

                /* 整数后缀表达式计算函数 */
                static int64_t evalIntExpPostfix(const std::string &op, int64_t right); // 后缀表达式求值函数

                // 运算符有效性判断函数
                static bool isValidExpPostfixOp(const std::string &op); // 后缀表达式运算符有效性判断函数

            private:
                /* 私有静态成员变量 */
                const static std::unordered_map<std::string, intExpPrefixFn> intExpPrefixFns;   // 整数前缀表达式运算符函数映射表
                const static std::unordered_map<std::string, intExpInfixFn> intExpInfixFns;     // 整数中缀表达式运算符函数映射表
                const static std::unordered_map<std::string, intCmpInfixFn> intCmpInfixFns;     // 整数中缀比较运算符函数映射表
                const static std::unordered_map<std::string, intExpPostfixFn> intExpPostfixFns; // 整数后缀表达式运算符函数映射表
            };

            // 浮点数类
            class Float
            {
            public:
                /* 构造函数 */
                // 空参构造函数
                Float() {};

                /* 析构函数 */
                ~Float() = default;

                // 浮点数前缀表达式计算函数指针
                typedef double (*floatExpPrefixFn)(double);

                // 浮点数中缀表达式计算函数指针
                typedef double (*floatExpInfixFn)(double, double);

                // 浮点数中缀比较运算函数指针
                typedef bool (*floatCmpInfixFn)(double, double);

                // 浮点数后缀表达式计算函数指针
                typedef double (*floatExpPostfixFn)(double);

                /* 公有成员函数 */
                /* 浮点数前缀表达式计算函数 */
                // 数学运算函数
                static double plus(double right);  // 正数 '+'
                static double minus(double right); // 负数 '-'

                // 浮点数自变化算术运算函数
                static double inc(double right); // 自增 '++'
                static double dec(double right); // 自减 '--'

                // 前缀表达式计算函数
                static double evalFloatExpPrefix(const std::string &op, double right); // 前缀表达式求值函数

                // 运算符有效性判断函数
                static bool isValidExpPrefixOp(const std::string &op); // 前缀表达式运算符有效性判断函数

                /* 浮点数中缀表达式计算函数 */
                // 数学运算函数
                static double add(double left, double right); // 加法 '+'
                static double sub(double left, double right); // 减法 '-'
                static double mul(double left, double right); // 乘法 '*'
                static double div(double left, double right); // 除法 '/'
                static double mod(double left, double right); // 取模 '%'
                static double pow(double left, double right); // 幂运算 '**'

                // 比较运算函数
                static bool lt(double left, double right); // 小于 '<'
                static bool gt(double left, double right); // 大于 '>'
                static bool le(double left, double right); // 小于等于 '<='
                static bool ge(double left, double right); // 大于等于 '>='
                static bool eq(double left, double right); // 等于 '=='
                static bool ne(double left, double right); // 不等于 '!='

                // 浮点数中缀表达式计算函数
                static double evalFloatExpInfix(const std::string &op, double left, double right); // 中缀表达式求值函数
                static bool evalFloatCmpInfix(const std::string &op, double left, double right);   // 中缀比较运算符求值函数

                // 浮点数运算符有效性判断函数
                static bool isValidInfixOp(const std::string &op);    // 中缀运算符有效性判断函数
                static bool isValidExpInfixOp(const std::string &op); // 中缀表达式运算符有效性判断函数
                static bool isValidCmpInfixOp(const std::string &op); // 中缀比较运算符有效性判断函数

                /* 浮点数后缀表达式计算函数 */
                // // 自变化算术运算函数
                // static double inc(double right);   // 自增 '++'
                // static double dec(double right);   // 自减 '--'

                // 后缀表达式计算函数
                static double evalFloatExpPostfix(const std::string &op, double right); // 后缀表达式求值函数

                // 运算符有效性判断函数
                static bool isValidExpPostfixOp(const std::string &op); // 后缀表达式运算符有效性判断函数

            private:
                /* 私有静态成员变量 */
                const static std::unordered_map<std::string, floatExpPrefixFn> floatExpPrefixFns;   // 浮点数前缀表达式运算符函数映射表
                const static std::unordered_map<std::string, floatExpInfixFn> floatExpInfixFns;     // 浮点数中缀表达式运算符函数映射表
                const static std::unordered_map<std::string, floatCmpInfixFn> floatCmpInfixFns;     // 浮点数中缀比较运算符函数映射表
                const static std::unordered_map<std::string, floatExpPostfixFn> floatExpPostfixFns; // 浮点数后缀表达式运算符函数映射表
            };

            // 布尔类
            class Bool
            {
            public:
                /* 构造函数 */
                // 空参构造函数
                Bool() {};

                /* 析构函数 */
                ~Bool() = default;

                // 字符串前缀表达式计算函数指针
                typedef bool (*boolLogPrefixFn)(bool);

                // 字符串中缀逻辑运算函数指针
                typedef bool (*boolLogInfixFn)(bool, bool);

                /* 公有成员函数 */
                /* 布尔类型前缀表达式计算函数 */
                // 逻辑运算函数
                static bool lognot(bool right); // 逻辑非 '!'

                // 布尔类型前缀表达式计算函数
                static bool evalBoolLogPrefix(const std::string &op, bool right); // 前缀逻辑表达式求值函数

                // 运算符有效性判断函数
                static bool isValidLogPrefixOp(const std::string &op); // 前缀逻辑表达式运算符有效性判断函数

                /* 布尔逻辑中缀表达式计算函数 */
                // 逻辑运算函数
                static bool logand(bool left, bool right); // 逻辑与 '&&'
                static bool logor(bool left, bool right);  // 逻辑或 '||'

                // 布尔逻辑中缀表达式计算函数
                static bool evalBoolLogInfix(const std::string &op, bool left, bool right); // 中缀逻辑表达式求值函数

                // 字符串运算符有效性判断函数
                static bool isValidLogInfixOp(const std::string &op); // 中缀运算符有效性判断函数

            private:
                /* 私有静态成员变量 */
                const static std::unordered_map<std::string, boolLogPrefixFn> boolLogPrefixFns; // 布尔前缀逻辑表达式运算符函数映射表
                const static std::unordered_map<std::string, boolLogInfixFn> boolLogInfixFns;   // 布尔中缀逻辑表达式运算符函数映射表
            };

            // 字符串类
            class String
            {
            public:
                /* 构造函数 */
                // 空参构造函数
                String() {};

                /* 析构函数 */
                ~String() = default;

                // 字符串前缀表达式计算函数指针
                typedef std::string (*strExpPrefixFn)(const std::string &);

                // 字符串中缀表达式计算函数指针
                typedef std::string (*strExpInfixFn)(const std::string &, const std::string &);

                // 字符串中缀逻辑运算函数指针
                typedef bool (*strCmpInfixFn)(const std::string &, const std::string &);

                /* 公有成员函数 */
                /* 字符串前缀表达式计算函数 */
                // 数学运算函数
                static std::string plus(const std::string &right);  // 正数 '+'
                static std::string minus(const std::string &right); // 负数 '-'

                // 前缀表达式计算函数
                static std::string evalStrExpPrefix(const std::string &op, const std::string &right); // 前缀表达式求值函数

                // 运算符有效性判断函数
                static bool isValidExpPrefixOp(const std::string &op); // 前缀表达式运算符有效性判断函数

                /* 列表中缀表达式计算函数 */
                // 数学运算函数
                static std::string add(const std::string &left, const std::string &right); // 加法 '+'
                static std::string sub(const std::string &left, const std::string &right); // 减法 '-'

                // 字符串和int64_t类型乘法运算
                static std::string mul(const std::string &left, int64_t right); // 乘法 '*'

                // 比较运算函数
                static bool lt(const std::string &left, const std::string &right); // 小于 '<'
                static bool gt(const std::string &left, const std::string &right); // 大于 '>'
                static bool le(const std::string &left, const std::string &right); // 小于等于 '<='
                static bool ge(const std::string &left, const std::string &right); // 大于等于 '>='
                static bool eq(const std::string &left, const std::string &right); // 等于 '=='
                static bool ne(const std::string &left, const std::string &right); // 不等于 '!='

                // 字符串中缀表达式计算函数
                static std::string evalStrExpInfix(const std::string &op, const std::string &left, const std::string &right); // 中缀表达式求值函数
                static bool evalStrCmpInfix(const std::string &op, const std::string &left, const std::string &right);        // 中缀比较运算符求值函数

                // 字符串运算符有效性判断函数
                static bool isValidInfixOp(const std::string &op);    // 中缀运算符有效性判断函数
                static bool isValidExpInfixOp(const std::string &op); // 中缀表达式运算符有效性判断函数
                static bool isValidCmpInfixOp(const std::string &op); // 中缀比较运算符有效性判断函数

            private:
                /* 私有静态成员变量 */
                const static std::unordered_map<std::string, strExpPrefixFn> strExpPrefixFns; // 字符串前缀表达式运算符函数映射表
                const static std::unordered_map<std::string, strExpInfixFn> strExpInfixFns;   // 字符串中缀表达式运算符函数映射表
                const static std::unordered_map<std::string, strCmpInfixFn> strCmpInfixFns;   // 字符串中缀比较运算符函数映射表
            };

            // 列表类
            class List
            {
            public:
                /* 构造函数 */
                // 空参构造函数
                List() {};

                /* 析构函数 */
                ~List() = default;

                // 列表前缀表达式计算函数指针
                typedef std::vector<std::shared_ptr<Object>> (*listExpPrefixFn)(const std::vector<std::shared_ptr<Object>> &);

                // 列表中缀表达式计算函数指针
                typedef std::vector<std::shared_ptr<Object>> (*listExpInfixFn)(const std::vector<std::shared_ptr<Object>> &, const std::vector<std::shared_ptr<Object>> &);

                // 列表中缀比较运算函数指针
                typedef std::shared_ptr<Object> (*listCmpInfixFn)(const std::vector<std::shared_ptr<Object>> &, const std::vector<std::shared_ptr<Object>> &);

                /* 公有成员函数 */
                /* 列表前缀表达式计算函数 */
                // 数学运算函数
                static std::vector<std::shared_ptr<Object>> plus(const std::vector<std::shared_ptr<Object>> &right);  // 正数 '+'
                static std::vector<std::shared_ptr<Object>> minus(const std::vector<std::shared_ptr<Object>> &right); // 负数 '-'

                // 前缀表达式计算函数
                static std::vector<std::shared_ptr<Object>> evalListExpPrefix(const std::string &op, const std::vector<std::shared_ptr<Object>> &right); // 前缀表达式求值函数

                // 运算符有效性判断函数
                static bool isValidExpPrefixOp(const std::string &op); // 前缀表达式运算符有效性判断函数

                /* 列表中缀表达式计算函数 */
                // 数学运算函数
                static std::vector<std::shared_ptr<Object>> add(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right); // 加法 '+'
                static std::vector<std::shared_ptr<Object>> sub(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right); // 减法 '-'

                // 列表和int64_t类型乘法运算
                static std::vector<std::shared_ptr<Object>> mul(const std::vector<std::shared_ptr<Object>> &left, int64_t right); // 乘法 '*'

                // 比较运算函数
                static std::shared_ptr<Object> lt(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right); // 小于 '<'
                static std::shared_ptr<Object> gt(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right); // 大于 '>'
                static std::shared_ptr<Object> le(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right); // 小于等于 '<='
                static std::shared_ptr<Object> ge(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right); // 大于等于 '>='
                static std::shared_ptr<Object> eq(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right); // 等于 '=='
                static std::shared_ptr<Object> ne(const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right); // 不等于 '!='

                // 列表中缀表达式计算函数
                static std::vector<std::shared_ptr<Object>> evalListExpInfix(const std::string &op, const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right); // 中缀表达式求值函数
                static std::shared_ptr<Object> evalListCmpInfix(const std::string &op, const std::vector<std::shared_ptr<Object>> &left, const std::vector<std::shared_ptr<Object>> &right);              // 中缀比较运算符求值函数

                // 列表中缀运算符有效性判断函数
                static bool isValidInfixOp(const std::string &op);    // 中缀运算符有效性判断函数
                static bool isValidExpInfixOp(const std::string &op); // 中缀表达式运算符有效性判断函数
                static bool isValidCmpInfixOp(const std::string &op); // 中缀比较运算符有效性判断函数

            private:
                /* 私有静态成员变量 */
                const static std::unordered_map<std::string, listExpPrefixFn> listExpPrefixFns; // 列表前缀表达式运算符函数映射表
                const static std::unordered_map<std::string, listExpInfixFn> listExpInfixFns;   // 列表中缀表达式运算符函数映射表
                const static std::unordered_map<std::string, listCmpInfixFn> listCmpInfixFns;   // 列表中缀比较运算符函数映射表
            };

            // 哈希类
            class Hash
            {
            public:
                /* 构造函数 */
                // 空参构造函数
                Hash() {};

                /* 析构函数 */
                ~Hash() = default;

                // 哈希表中缀表达式计算函数指针
                typedef std::unordered_map<HashKey, std::shared_ptr<HashPair>> (*hashExpInfixFn)(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &);

                // 哈希表中缀比较运算函数指针
                typedef std::shared_ptr<Object> (*hashCmpInfixFn)(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &);

                /* 公有成员函数 */
                /* 哈希表中缀表达式计算函数 */
                // 数学运算函数
                static std::unordered_map<HashKey, std::shared_ptr<HashPair>> hashInter(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &left, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &right); // 交集 '&'
                static std::unordered_map<HashKey, std::shared_ptr<HashPair>> hashUnion(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &left, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &right); // 并集 '|'

                // 比较运算函数
                static std::shared_ptr<Object> eq(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &left, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &right); // 等于 '=='
                static std::shared_ptr<Object> ne(const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &left, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &right); // 不等于 '!='

                // 哈希表中缀表达式计算函数
                static std::unordered_map<HashKey, std::shared_ptr<HashPair>> evalHashExpInfix(const std::string &op, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &left, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &right); // 中缀表达式求值函数
                static std::shared_ptr<Object> evalHashCmpInfix(const std::string &op, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &left, const std::unordered_map<HashKey, std::shared_ptr<HashPair>> &right);                                // 中缀比较运算符求值函数

                // 哈希表中缀运算符有效性判断函数
                static bool isValidInfixOp(const std::string &op);    // 中缀运算符有效性判断函数
                static bool isValidExpInfixOp(const std::string &op); // 中缀表达式运算符有效性判断函数
                static bool isValidCmpInfixOp(const std::string &op); // 中缀比较运算符有效性判断函数

            private:
                /* 私有静态成员变量 */
                const static std::unordered_map<std::string, hashExpInfixFn> hashExpInfixFns; // 哈希表中缀表达式运算符函数映射表
                const static std::unordered_map<std::string, hashCmpInfixFn> hashCmpInfixFns; // 哈希表中缀比较运算符函数映射表
            };
        };
    }
}