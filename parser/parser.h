#pragma once
#include <lexer/lexer.h>
#include <ast/ast.h>
using namespace cpy::lexer;
using namespace cpy::ast;

namespace cpy
{
    namespace parser
    {
        class Parser
        {
        public:
            // 优先级枚举类型
            enum Precedence
            {
                LOWEST = 0,   // 最低优先级
                ASSIGN,       // = += -= *= **= /= %= &= |= ^= <<= >>=
                IN,           // in
                LOGIC,        // & | ^ << >> && ||
                TERNARY,      // ?:
                COMPARE,      // < > <= >= == !=
                SUM,          // + -
                PRODUCT,      // * / %
                PREFIX,       // -x ~x !x ++x --x
                POWER,        // **
                INDEX,        // []
                DOT = INDEX,  // .
                CALL = INDEX, // ()
            };

            /* 构造函数 */
            // 空参构造函数
            Parser();
            // 带参构造函数
            Parser(const std::shared_ptr<Lexer> &lexer);

            /* 析构函数 */
            ~Parser() = default;

            // 前缀表达式构建函数原型定义
            typedef std::shared_ptr<Expression> (Parser::*prefixParseFn)(void);

            // 中缀表达式构建函数原型定义
            typedef std::shared_ptr<Expression> (Parser::*infixParseFn)(const std::shared_ptr<Expression> &);

            // 后缀表达式构建函数原型定义
            typedef std::shared_ptr<Expression> (Parser::*postfixParseFn)(const std::shared_ptr<Expression> &);

            /* 公有成员函数 */
            void nextToken();                                              // 进行下一次的token获取函数
            bool isCurrToken(Token::Type type);                            // 判断当前token是否为type类型函数
            bool isCurrToken(const std::vector<Token::Type> &types);       // 判断当前token是否为某个type类型函数
            bool isPeekToken(Token::Type type);                            // 判断下一个token是否为type类型函数
            bool isPeekToken(const std::vector<Token::Type> &types);       // 判断下一个token是否为某个type类型函数
            bool isPeekTokenExpect(Token::Type type);                      // 判断下一个token是否为期望的type类型函数
            bool isPeekTokenExpect(const std::vector<Token::Type> &types); // 判断下一个token是否为期望的type类型函数
            void peekError(Token::Type type);                              // 错误信息传入错误列表函数
            void peekError(const std::vector<Token::Type> &types);         // 错误信息传入错误列表函数
            Precedence currTokenPrecedence();                              // 获取当前token的优先级函数
            Precedence peekTokenPrecedence();                              // 获取下一个token的优先级函数
            bool isError() const;                                          // 判断是否有错误函数
            void printErrors() const;                                      // 打印错误信息函数

            void noPrefixParseFnError(Token::Type type); // 缺乏前缀表达式解析错误输出函数
            std::list<std::string> &getErrors();         // 获取错误列表函数

            std::shared_ptr<Expression> parseExpression(Precedence precedence);            // 表达式解析函数
            std::vector<std::shared_ptr<Expression>> parseExpressionList(Token::Type end); // 表达式列表解析函数
            std::shared_ptr<Program> parseProgram();                                       // 程序解析函数
            std::shared_ptr<Statement> parseStatement();                                   // 语句解析函数
            std::shared_ptr<Statement> parseBreakStatement();                              // break语句解析函数
            std::shared_ptr<Statement> parseContinueStatement();                           // continue语句解析函数
            std::shared_ptr<Statement> parseReturnStatement();                             // return语句解析函数
            std::shared_ptr<ExpressionStatement> parseExpressionStatement();               // 表达式语句解析函数
            std::shared_ptr<Block> parseBlock();                                           // 代码块解析函数

            // prefix前缀解析函数
            std::shared_ptr<Expression> parseGroup();                            // 分组解析函数
            std::shared_ptr<Expression> parsePrefix();                           // 前缀解析函数 如：-x
            std::shared_ptr<Expression> parseInteger();                          // 整数解析函数
            std::shared_ptr<Expression> parseFloat();                            // 浮点数解析函数
            std::shared_ptr<Expression> parseBool();                             // 布尔解析函数
            std::shared_ptr<Expression> parseString();                           // 字符串解析函数
            std::shared_ptr<Expression> parseNull();                             // null解析函数
            std::shared_ptr<Expression> parseList();                             // 列表解析函数
            std::shared_ptr<Expression> parseHash();                             // 哈希解析函数
            std::shared_ptr<Expression> parseIdentifier();                       // 标识符解析函数
            std::shared_ptr<Expression> parseFunction();                         // 函数解析函数
            bool parseFunctionParameters(const std::shared_ptr<Function> &func); // 函数参数解析函数
            bool parseFunctionBody(const std::shared_ptr<Function> &func);       // 函数体解析函数
            std::shared_ptr<Expression> parseIf();                               // if解析函数
            std::shared_ptr<Expression> parseSwitch();                           // switch解析函数
            std::shared_ptr<Expression> parseWhile();                            // while解析函数
            std::shared_ptr<Expression> parseFor();                              // for解析函数

            // infix中缀解析函数
            std::shared_ptr<Expression> parseInfix(const std::shared_ptr<Expression> &left);          // 中缀表达式解析函数
            std::shared_ptr<Expression> parseAssign(const std::shared_ptr<Expression> &left);         // 赋值表达式解析函数
            std::shared_ptr<Expression> parseCompoundAssign(const std::shared_ptr<Expression> &left); // 复合赋值表达式解析函数
            std::shared_ptr<Expression> parseTernary(const std::shared_ptr<Expression> &left);        // 三元表达式解析函数
            std::shared_ptr<Expression> parseIndex(const std::shared_ptr<Expression> &left);          // 索引表达式解析函数
            std::shared_ptr<Expression> parseDot(const std::shared_ptr<Expression> &left);            // 点表达式解析函数
            std::shared_ptr<Expression> parseIn(const std::shared_ptr<Expression> &left);             // in表达式解析函数
            std::shared_ptr<Expression> parseCall(const std::shared_ptr<Expression> &left);           // 函数调用表达式解析函数

            // postfix后缀解析函数
            std::shared_ptr<Expression> parsePostfix(const std::shared_ptr<Expression> &left); // 后缀表达式解析函数

        private:
            /* 私有成员变量 */
            std::shared_ptr<Lexer> lexer;  // 词法分析器
            Token curr;                    // 当前token
            Token peek;                    // 下一个token
            std::list<std::string> errors; // 错误列表

            const static std::unordered_map<Token::Type, Precedence> precedences;         // Token优先级表
            const static std::unordered_map<Token::Type, prefixParseFn> prefixParseFns;   // 前缀解析函数表
            const static std::unordered_map<Token::Type, infixParseFn> infixParseFns;     // 中缀解析函数表
            const static std::unordered_map<Token::Type, postfixParseFn> postfixParseFns; // 后缀解析函数表
        };
    }
}
