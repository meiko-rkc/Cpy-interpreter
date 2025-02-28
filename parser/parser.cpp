#include <parser/parser.h>
#include "parser.h"
using namespace cpy::parser;
// 优先级表
const std::unordered_map<Token::Type, Parser::Precedence> Parser::precedences = {
    {Token::TOKEN_PLUS, SUM},               // '+'运算符
    {Token::TOKEN_MINUS, SUM},              // '-'运算符
    {Token::TOKEN_ASTERISK, PRODUCT},       // '*'乘法运算符
    {Token::TOKEN_SLASH, PRODUCT},          // '/'除法运算符
    {Token::TOKEN_MODULO, PRODUCT},         // '%'取模运算符
    {Token::TOKEN_TILDE, PREFIX},           // '~'按位取反运算符
    {Token::TOKEN_NOT, PREFIX},             // '!'逻辑非运算符
    {Token::TOKEN_POW, POWER},              // '**'幂运算符
    {Token::TOKEN_BWAND, LOGIC},            // '&'按位与运算符
    {Token::TOKEN_BWOR, LOGIC},             // '|'按位或运算符
    {Token::TOKEN_BWXOR, LOGIC},            // '^'按位异或运算符
    {Token::TOKEN_LSHIFT, LOGIC},           // '<<'左移运算符
    {Token::TOKEN_RSHIFT, LOGIC},           // '>>'右移运算符
    {Token::TOKEN_AND, LOGIC},              // '&&'逻辑与运算符
    {Token::TOKEN_OR, LOGIC},               // '||'逻辑或运算符
    {Token::TOKEN_LT, COMPARE},             // '<'小于运算符
    {Token::TOKEN_GT, COMPARE},             // '>'大于运算符
    {Token::TOKEN_LE, COMPARE},             // '<='小于等于运算符
    {Token::TOKEN_GE, COMPARE},             // '>='大于等于运算符
    {Token::TOKEN_EQ, COMPARE},             // '=='等于运算符
    {Token::TOKEN_NE, COMPARE},             // '!='不等于运算符
    {Token::TOKEN_ASSIGN, ASSIGN},          // '='赋值运算符
    {Token::TOKEN_PLUS_ASSIGN, ASSIGN},     // '+='赋值运算符
    {Token::TOKEN_MINUS_ASSIGN, ASSIGN},    // '-='赋值运算符
    {Token::TOKEN_ASTERISK_ASSIGN, ASSIGN}, // '*='赋值运算符
    {Token::TOKEN_POW_ASSIGN, ASSIGN},      // '**='赋值运算符
    {Token::TOKEN_SLASH_ASSIGN, ASSIGN},    // '/='赋值运算符
    {Token::TOKEN_MODULO_ASSIGN, ASSIGN},   // '%='赋值运算符
    {Token::TOKEN_BWAND_ASSIGN, ASSIGN},    // '&='赋值运算符
    {Token::TOKEN_BWOR_ASSIGN, ASSIGN},     // '|='赋值运算符
    {Token::TOKEN_BWXOR_ASSIGN, ASSIGN},    // '^='赋值运算符
    {Token::TOKEN_LSHIFT_ASSIGN, ASSIGN},   // '<<='赋值运算符
    {Token::TOKEN_RSHIFT_ASSIGN, ASSIGN},   // '>>='赋值运算符
    {Token::TOKEN_QUESTION, TERNARY},       // '?'三目运算符
    {Token::TOKEN_LBRACKET, INDEX},         // '['左中括号
    {Token::TOKEN_DOT, DOT},                // '.'点运算符
    {Token::TOKEN_IN, IN},                  // 'in'关键字
    {Token::TOKEN_LPAREN, CALL},            // '('左括号
};

// 前缀解析函数表
const std::unordered_map<Token::Type, Parser::prefixParseFn> Parser::prefixParseFns = {
    {Token::TOKEN_LPAREN, &Parser::parseGroup},          // '('左括号
    {Token::TOKEN_PLUS, &Parser::parsePrefix},           // '+'运算符
    {Token::TOKEN_MINUS, &Parser::parsePrefix},          // '-'运算符
    {Token::TOKEN_TILDE, &Parser::parsePrefix},          // '~'按位取反运算符
    {Token::TOKEN_NOT, &Parser::parsePrefix},            // '!'逻辑非运算符
    {Token::TOKEN_INC, &Parser::parsePrefix},            // '++'自增运算符
    {Token::TOKEN_DEC, &Parser::parsePrefix},            // '--'自减运算符
    {Token::TOKEN_INTEGER, &Parser::parseInteger},       // 整数
    {Token::TOKEN_FLOAT, &Parser::parseFloat},           // 浮点数
    {Token::TOKEN_TRUE, &Parser::parseBool},             // 'true'布尔值
    {Token::TOKEN_FALSE, &Parser::parseBool},            // 'false'布尔值
    {Token::TOKEN_STRING, &Parser::parseString},         // 字符串
    {Token::TOKEN_NULL, &Parser::parseNull},             // 'null'空值
    {Token::TOKEN_LBRACKET, &Parser::parseList},         // '['左中括号
    {Token::TOKEN_LBRACE, &Parser::parseHash},           // '{'左大括号
    {Token::TOKEN_IDENTIFIER, &Parser::parseIdentifier}, // 标识符
    {Token::TOKEN_FUNCTION, &Parser::parseFunction},     // 'fn'关键字
    {Token::TOKEN_IF, &Parser::parseIf},                 // 'if'关键字
    {Token::TOKEN_SWITCH, &Parser::parseSwitch},         // 'switch'关键字
    {Token::TOKEN_WHILE, &Parser::parseWhile},           // 'while'关键字
    {Token::TOKEN_FOR, &Parser::parseFor},               // 'for'关键字
};

// 中缀解析函数表
const std::unordered_map<Token::Type, Parser::infixParseFn> Parser::infixParseFns = {
    {Token::TOKEN_PLUS, &Parser::parseInfix},                     // '+'运算符
    {Token::TOKEN_MINUS, &Parser::parseInfix},                    // '-'运算符
    {Token::TOKEN_ASTERISK, &Parser::parseInfix},                 // '*'运算符
    {Token::TOKEN_SLASH, &Parser::parseInfix},                    // '/'运算符
    {Token::TOKEN_MODULO, &Parser::parseInfix},                   // '%'取模运算符
    {Token::TOKEN_POW, &Parser::parseInfix},                      // '**'幂运算符
    {Token::TOKEN_BWAND, &Parser::parseInfix},                    // '&'按位与运算符
    {Token::TOKEN_BWOR, &Parser::parseInfix},                     // '|'按位或运算符
    {Token::TOKEN_BWXOR, &Parser::parseInfix},                    // '^'按位异或运算符
    {Token::TOKEN_LSHIFT, &Parser::parseInfix},                   // '<<'左移运算符
    {Token::TOKEN_RSHIFT, &Parser::parseInfix},                   // '>>'右移运算符
    {Token::TOKEN_AND, &Parser::parseInfix},                      // '&&'逻辑与运算符
    {Token::TOKEN_OR, &Parser::parseInfix},                       // '||'逻辑或运算符
    {Token::TOKEN_LT, &Parser::parseInfix},                       // '<'小于运算符
    {Token::TOKEN_GT, &Parser::parseInfix},                       // '>'大于运算符
    {Token::TOKEN_LE, &Parser::parseInfix},                       // '<='小于等于运算符
    {Token::TOKEN_GE, &Parser::parseInfix},                       // '>='大于等于运算符
    {Token::TOKEN_EQ, &Parser::parseInfix},                       // '=='等于运算符
    {Token::TOKEN_NE, &Parser::parseInfix},                       // '!='不等于运算符
    {Token::TOKEN_ASSIGN, &Parser::parseAssign},                  // '='赋值运算符
    {Token::TOKEN_PLUS_ASSIGN, &Parser::parseCompoundAssign},     // '+='赋值运算符
    {Token::TOKEN_MINUS_ASSIGN, &Parser::parseCompoundAssign},    // '-='赋值运算符
    {Token::TOKEN_ASTERISK_ASSIGN, &Parser::parseCompoundAssign}, // '*='赋值运算符
    {Token::TOKEN_POW_ASSIGN, &Parser::parseCompoundAssign},      // '**='赋值运算符
    {Token::TOKEN_SLASH_ASSIGN, &Parser::parseCompoundAssign},    // '/='赋值运算符
    {Token::TOKEN_MODULO_ASSIGN, &Parser::parseCompoundAssign},   // '%='赋值运算符
    {Token::TOKEN_BWAND_ASSIGN, &Parser::parseCompoundAssign},    // '&='赋值运算符
    {Token::TOKEN_BWOR_ASSIGN, &Parser::parseCompoundAssign},     // '|='赋值运算符
    {Token::TOKEN_BWXOR_ASSIGN, &Parser::parseCompoundAssign},    // '^='赋值运算符
    {Token::TOKEN_LSHIFT_ASSIGN, &Parser::parseCompoundAssign},   // '<<='赋值运算符
    {Token::TOKEN_RSHIFT_ASSIGN, &Parser::parseCompoundAssign},   // '>>='赋值运算符
    {Token::TOKEN_QUESTION, &Parser::parseTernary},               // '?'三元表达式
    {Token::TOKEN_LBRACKET, &Parser::parseIndex},                 // '['左中括号
    {Token::TOKEN_DOT, &Parser::parseDot},                        // '.'点运算符
    {Token::TOKEN_IN, &Parser::parseIn},                          // 'in'关键字
    {Token::TOKEN_LPAREN, &Parser::parseCall},                    // '('左括号
};

// 后缀解析函数表
const std::unordered_map<Token::Type, Parser::postfixParseFn> Parser::postfixParseFns = {
    {Token::TOKEN_INC, &Parser::parsePostfix}, // '++'后缀自增运算符
    {Token::TOKEN_DEC, &Parser::parsePostfix}, // '--'后缀自减运算符
};

// 空参构造函数
Parser::Parser()
{
}

// 带参构造函数
Parser::Parser(const std::shared_ptr<Lexer> &lexer)
{
    /* 初始化词法分析器 */
    // 分别初始化当前token和下一个token
    this->lexer = lexer;
    nextToken();
    nextToken();
}

// 进行下一次的token获取函数
void Parser::nextToken()
{
    curr = peek;
    peek = lexer->nextToken();
}

// 判断当前token是否为type类型函数
bool Parser::isCurrToken(Token::Type type)
{
    return curr.getType() == type;
}

// 判断当前token是否为某个type类型函数
bool Parser::isCurrToken(const std::vector<Token::Type> &types)
{
    for (auto type : types)
    {
        if (curr.getType() == type)
            return true;
    }
    return false;
}

// 判断下一个token是否为type类型函数
bool Parser::isPeekToken(Token::Type type)
{
    return peek.getType() == type;
}

// 判断下一个token是否为某个type类型函数
bool Parser::isPeekToken(const std::vector<Token::Type> &types)
{
    for (auto type : types)
    {
        if (peek.getType() == type)
            return true;
    }
    return false;
}

// 判断下一个token是否为期望的type类型函数
bool Parser::isPeekTokenExpect(Token::Type type)
{
    // 如果是期待的类型，则进行下一次token获取
    if (isPeekToken(type))
    {
        nextToken();
        return true;
    }
    // 否则，输出错误信息
    else
    {
        peekError(type);
        return false;
    }
}

// 判断下一个token是否为期望的某个type类型函数
bool Parser::isPeekTokenExpect(const std::vector<Token::Type> &types)
{
    if (isPeekToken(types))
    {
        nextToken();
        return true;
    }
    peekError(types);
    return false;
}

// 错误信息传入错误列表函数
void Parser::peekError(Token::Type type)
{
    // 构建错误信息字符串流并传入到错误列表中
    std::stringstream ss;
    ss << "(" << curr.getLine() << "," << curr.getColumn() << ") expectedd next token to be " << type << ",got " << peek.getType() << " instead";
    errors.emplace_back(ss.str());
}

// 错误信息传入错误列表函数
void Parser::peekError(const std::vector<Token::Type> &types)
{
    // 构建错误信息字符串流并传入到错误列表中
    std::stringstream ss;
    ss << "expected next token to be one of ";
    int64_t max = types.size() - 1;
    for (int64_t i = 0; i < max; i++)
        ss << types[i] << ",";
    if (max >= 0)
        ss << types[max] << ",got" << peek.getType() << " instead";
    errors.emplace_back(ss.str());
}

// 获取当前token的优先级函数
Parser::Precedence Parser::currTokenPrecedence()
{
    // 获取当前token的类型
    Token::Type type = curr.getType();
    /* 判断当前token的类型是否在优先级表中 */
    // 如果在，则返回对应的优先级
    if (precedences.find(type) != precedences.end())
        return precedences.at(type);
    // 如果不在，则返回最低优先级
    return LOWEST;
}

// 获取下一个token的优先级函数
Parser::Precedence Parser::peekTokenPrecedence()
{
    // 获取当前token的类型
    Token::Type type = peek.getType();
    /* 判断当前token的类型是否在优先级表中 */
    // 如果在，则返回对应的优先级
    if (precedences.find(type) != precedences.end())
        return precedences.at(type);
    // 如果不在，则返回最低优先级
    return LOWEST;
}

// 判断是否有错误函数
bool Parser::isError() const
{
    return !errors.empty();
}

// 输出错误信息函数
void Parser::printErrors() const
{
    for (std::list<std::string>::const_iterator it = errors.begin(); it != errors.end(); it++)
        std::cout << *it << std::endl;
}

// 缺乏前缀表达式解析错误输出函数
void Parser::noPrefixParseFnError(Token::Type type)
{
    // 构建前缀表达式错误信息字符串流并传入到错误列表中
    std::stringstream ss;
    ss << "no prefix parse function for " << type;
    errors.emplace_back(ss.str());
}

// 获取错误信息列表函数
std::list<std::string> &Parser::getErrors()
{
    return errors;
}

// 表达式解析函数
std::shared_ptr<Expression> Parser::parseExpression(Precedence precedence)
{
    // 检查前缀解析函数表中是否有当前token的类型对应的前缀解析函数
    if (prefixParseFns.find(curr.getType()) == prefixParseFns.end())
    {
        // 输出错误信息
        noPrefixParseFnError(curr.getType());
        return nullptr;
    }
    // 调用前缀解析函数
    std::shared_ptr<Expression> exp = (this->*prefixParseFns.at(curr.getType()))();
    // 循环判断是下一个token是否为分号';'并且其优先级是否大于precedence的优先级
    while (!isPeekToken(Token::TOKEN_SEMICOLON) && precedence < peekTokenPrecedence())
    {
        // 如果中缀解析函数表中没有下一个token类型对应的中缀解析函数，则返回当前表达式节点
        if (infixParseFns.find(peek.getType()) == infixParseFns.end())
            return exp;
        // 进行下一次token获取
        nextToken();
        // 调用中缀解析函数
        exp = (this->*infixParseFns.at(curr.getType()))(exp);
    }
    // 如果后缀解析函数表中没有下一个token类型对应的后缀解析函数，则返回当前表达式节点
    if (postfixParseFns.find(peek.getType()) == postfixParseFns.end())
        return exp;
    // 进行下一次token获取
    nextToken();
    // 调用后缀解析函数
    exp = (this->*postfixParseFns.at(curr.getType()))(exp);
    return exp;
}

// 列表表达式解析函数
std::vector<std::shared_ptr<Expression>> Parser::parseExpressionList(Token::Type end)
{
    // 初始化元素列表
    std::vector<std::shared_ptr<Expression>> listExpr;
    // 如果下一个token是end类型
    if (isPeekToken(end))
    {
        // 跳过结束token，并返回空列表
        nextToken();
        return listExpr;
    }
    // 跳过左括号token，并解析第一个表达式
    nextToken();
    listExpr.emplace_back(parseExpression(LOWEST));
    // 循环解析剩余的表达式
    while (isPeekToken(Token::TOKEN_COMMA))
    {
        // 跳至逗号token
        nextToken();
        // 跳过逗号token
        nextToken();
        // 解析表达式
        listExpr.emplace_back(parseExpression(LOWEST));
    }
    // 如果下一个token不是end类型，则输出错误信息并返回空列表
    if (!isPeekTokenExpect(end))
    {
        // 跳过结束token
        nextToken();
        return std::vector<std::shared_ptr<Expression>>();
    }
    // 返回元素列表
    return listExpr;
}

// 程序解析函数
std::shared_ptr<Program> Parser::parseProgram()
{
    // 构建程序根节点
    std::shared_ptr<Program> program(new Program());
    // 循环直到当前token为EOF为止
    while (curr.getType() != Token::TOKEN_EOF)
    {
        // 解析语句
        std::shared_ptr<Statement> stmt = parseStatement();
        // 如果stmt不为空，则将stmt加入到程序根节点的语句列表中
        if (stmt != nullptr)
            program->statements.emplace_back(stmt);
        // 进行下一次token获取
        nextToken();
    }
    // 返回程序根节点
    return program;
}

// 语句解析函数
std::shared_ptr<Statement> Parser::parseStatement()
{
    // 匹配语句类型
    switch (curr.getType())
    {
    case Token::TOKEN_BREAK:
        // break语句解析
        return parseBreakStatement();
    case Token::TOKEN_CONTINUE:
        // continue语句解析
        return parseContinueStatement();
    case Token::TOKEN_RETURN:
        // return语句解析
        return parseReturnStatement();
    default:
        // 表达式语句解析
        return parseExpressionStatement();
    }
}

// break语句解析函数
std::shared_ptr<Statement> Parser::parseBreakStatement()
{
    // 创建break语句结点
    std::shared_ptr<Break> stmt(new Break());
    // 设置当前break结点的token
    stmt->token = curr;
    // 跳过分号
    while (isPeekToken(Token::TOKEN_SEMICOLON))
        nextToken();
    // 返回break语句结点
    return stmt;
}

// continue语句解析函数
std::shared_ptr<Statement> Parser::parseContinueStatement()
{
    // 创建continue语句结点
    std::shared_ptr<Continue> stmt(new Continue());
    // 设置当前continue结点的token
    stmt->token = curr;
    // 跳过分号
    while (isPeekToken(Token::TOKEN_SEMICOLON))
        nextToken();
    // 返回continue语句结点
    return stmt;
}

std::shared_ptr<Statement> Parser::parseReturnStatement()
{
    // 创建return语句结点
    std::shared_ptr<Return> stmt(new Return());
    // 设置当前return结点的token
    stmt->token = curr;
    // 如果为隐式返回，则设置返回值为空值
    // 如果return下一个token为分号或者发生换行，则设置返回值为空值
    if (isPeekToken(Token::TOKEN_SEMICOLON) || curr.getLine() < peek.getLine())
    {
        // 创建空值结点
        std::shared_ptr<Null> null(new Null());
        // 设置空值结点的token
        null->token = Token(Token::TOKEN_NULL, "null", curr.getLine(), curr.getColumn());
        // 设置return语句的返回值
        stmt->value = null;
    }
    // 否则解析表达式
    else
    {
        // 跳至return下一个token
        nextToken();
        // 解析表达式
        stmt->value = parseExpression(LOWEST);
    }
    // 跳过分号
    while (isPeekToken(Token::TOKEN_SEMICOLON))
        nextToken();
    // 返回return语句结点
    return stmt;
}

// 表达式语句解析函数
std::shared_ptr<ExpressionStatement> Parser::parseExpressionStatement()
{
    // 创建表达式语句结点
    std::shared_ptr<ExpressionStatement> stmt(new ExpressionStatement());
    // 设置当前表达式语句的token
    stmt->token = curr;
    // 解析表达式
    stmt->expr = parseExpression(LOWEST);
    // 跳过分号
    while (isPeekToken(Token::TOKEN_SEMICOLON))
        nextToken();
    // 返回表达式语句结点
    return stmt;
}

// 代码块解析函数
std::shared_ptr<Block> Parser::parseBlock()
{
    // 创建代码块
    std::shared_ptr<Block> block(new Block());
    // 跳过左大括号
    block->token = curr;
    nextToken();
    // 循环解析语句，直到遇到右大括号
    while (!isCurrToken(Token::TOKEN_RBRACE))
    {
        // 如果继续遇到左大括号，则递归解析代码块
        if (isCurrToken(Token::TOKEN_LBRACE))
        {
            std::shared_ptr<Block> nextBlock = parseBlock();
            block->appendBlock(nextBlock);
        }
        // 解析语句
        std::shared_ptr<Statement> stmt = parseStatement();
        // 如果解析成功，则添加到代码块中
        if (stmt)
            block->statements.emplace_back(stmt);
        // 跳至下一个语句起始token
        nextToken();
    }
    // 返回代码块结点
    return block;
}

// 分组解析函数
std::shared_ptr<Expression> Parser::parseGroup()
{
    // 当前token为'('时，进行下一次token获取
    nextToken();
    // 解析表达式
    std::shared_ptr<Expression> exp = parseExpression(LOWEST);
    // 如果下一个token不是')'，则返回nullptr
    if (!isPeekTokenExpect(Token::TOKEN_RPAREN))
        return nullptr;
    // 返回表达式
    return exp;
}

// 前缀表达式解析函数
std::shared_ptr<Expression> Parser::parsePrefix()
{
    // 构建前缀表达式节点
    std::shared_ptr<Prefix> exp(new Prefix());
    // 设置前缀表达式节点的token和对应运算符
    exp->token = curr;
    exp->op = curr.getLiteral();
    // 进行下一次token获取
    nextToken();
    // 设置前缀表达式节点的右操作数，在解析操作数时优先级设为PREFIX
    exp->right = parseExpression(PREFIX);
    return exp;
}

// 整数解析函数
std::shared_ptr<Expression> Parser::parseInteger()
{
    // 构建整数节点
    std::shared_ptr<Integer> integer(new Integer());
    // 设置整数节点的token和值
    integer->token = curr;
    integer->value = std::stoll(curr.getLiteral());
    // 返回整数节点
    return integer;
}

// 浮点数解析函数
std::shared_ptr<Expression> Parser::parseFloat()
{
    // 构建浮点数节点
    std::shared_ptr<Float> flt(new Float());
    // 设置浮点数节点的token和值
    flt->token = curr;
    flt->value = std::stod(curr.getLiteral());
    // 返回浮点数节点
    return flt;
}

// 布尔值解析函数
std::shared_ptr<Expression> Parser::parseBool()
{
    // 构建布尔值节点
    std::shared_ptr<Bool> bl(new Bool());
    // 设置布尔值节点的token和值
    bl->token = curr;
    bl->value = isCurrToken(Token::TOKEN_TRUE);
    // 返回布尔值节点
    return bl;
}

// 字符串解析函数
std::shared_ptr<Expression> Parser::parseString()
{
    // 构建字符串节点
    std::shared_ptr<ast::String> str(new ast::String());
    // 设置字符串节点的token和值
    str->token = curr;
    str->value = curr.getLiteral();
    // 返回字符串节点
    return str;
}

// 空值解析函数
std::shared_ptr<Expression> Parser::parseNull()
{
    // 构建空值节点
    std::shared_ptr<Null> null(new Null());
    // 设置空值节点的token
    null->token = curr;
    while (isPeekToken(Token::TOKEN_SEMICOLON))
        nextToken();
    // 返回空值节点
    return null;
}

// 列表解析函数
std::shared_ptr<Expression> Parser::parseList()
{
    // 构建列表节点
    std::shared_ptr<List> listNode(new List());
    // 设置列表节点的token，并解析表达式列表(解析到右中括号为止)
    listNode->token = curr;
    listNode->elements = parseExpressionList(Token::TOKEN_RBRACKET);
    // 返回列表节点
    return listNode;
}

// 哈希表解析函数
std::shared_ptr<Expression> Parser::parseHash()
{
    // 构建哈希表节点
    std::shared_ptr<Hash> hashNode(new Hash());
    // 设置哈希表节点的token
    hashNode->token = curr;
    // 循环解析键值对，直到遇到右大括号为止
    while (!isPeekToken(Token::TOKEN_RBRACE))
    {
        // 跳过左括号token或者跳至新表达式起始token
        nextToken();
        // 解析键
        std::shared_ptr<Expression> key = parseExpression(LOWEST);
        // 如果下一个token不是冒号，则报错
        if (!isPeekTokenExpect(Token::TOKEN_COLON))
            return nullptr;
        // 跳过冒号token
        nextToken();
        // 解析值
        std::shared_ptr<Expression> value = parseExpression(LOWEST);
        // 将键值对添加到哈希表中
        hashNode->pairs[key] = value;
        // 如果下一个token不是逗号
        if (isPeekToken(Token::TOKEN_COMMA))
            nextToken();
        else if (isPeekToken(Token::TOKEN_RBRACE))
            break;
        else
        {
            // 语法错误,并返回nullptr
            peekError({Token::TOKEN_COMMA, Token::TOKEN_RBRACE});
            return nullptr;
        }
    }
    // 跳至右大括号token
    nextToken();
    // 返回哈希表结点
    return hashNode;
}

// 标识符解析函数
std::shared_ptr<Expression> Parser::parseIdentifier()
{
    // 构建标识符节点
    std::shared_ptr<Identifier> identifier(new Identifier());
    // 设置标识符节点的token和字符串值
    identifier->token = curr;
    identifier->value = curr.getLiteral();
    // 返回标识符节点
    return identifier;
}

// 函数解析函数
std::shared_ptr<Expression> Parser::parseFunction()
{
    // 构建函数节点
    std::shared_ptr<Function> func(new Function());
    // 设置函数节点的token
    func->token = curr;
    // 如果下一个token不是标识符则报错并返回nullptr，否则跳至标识符并设置函数名
    if (!isPeekTokenExpect(Token::TOKEN_IDENTIFIER))
        return nullptr;
    func->value = curr.getLiteral();
    // 如果下一个token不是左括号则报错并返回nullptr，否则跳至左括号
    if (!isPeekTokenExpect(Token::TOKEN_LPAREN))
        return nullptr;
    // 解析函数参数
    // 如果解析函数参数失败则报错并返回nullptr
    if (!parseFunctionParameters(func))
        return nullptr;
    // 如果下一个token不是左大括号则报错并返回nullptr，否则跳至左大括号
    if (!isPeekTokenExpect(Token::TOKEN_LBRACE))
        return nullptr;
    // 解析函数体
    // 如果解析函数体失败则报错并返回nullptr
    if (!parseFunctionBody(func))
        return nullptr;
    // 返回函数节点
    return func;
}

// 函数参数解析函数
bool Parser::parseFunctionParameters(const std::shared_ptr<Function> &func)
{
    // 循环解析函数参数，直到遇到右括号为止
    while (!isPeekToken(Token::TOKEN_RPAREN))
    {
        // 跳过左括号token或者跳过逗号token
        nextToken();
        // 如果当前token不是标识符则直接返回false
        if (!isCurrToken(Token::TOKEN_IDENTIFIER))
        {
            // 语法错误，并返回false
            peekError(Token::TOKEN_IDENTIFIER);
            return false;
        }
        // 创建标识符结点，设置token和字符串值并添加到函数参数列表中
        std::shared_ptr<Identifier> ident(new Identifier());
        ident->token = curr;
        ident->value = curr.getLiteral();
        func->parameters.emplace_back(ident);
        /* 处理默认参数 */
        // 如果下一个token是赋值号，则跳至赋值号
        if (isPeekToken(Token::TOKEN_ASSIGN))
        {
            // 跳至赋值号
            nextToken();
            // 跳至赋值号后紧跟着的token
            nextToken();
            // 将默认参数赋值结果添加到函数默认参数列表中
            func->defaults[ident->value] = parseExpression(LOWEST);
        }
        // 保证默认参数位置在参数列表的最后
        else if (!func->defaults.empty())
        {
            // 语法错误，并返回false
            peekError(Token::TOKEN_ASSIGN);
            return false;
        }
        /* 逗号处理 */
        // 如果下一个token是逗号，则跳至逗号并继续循环
        if (isPeekToken(Token::TOKEN_COMMA))
            nextToken();
        // 如果下一个token是右括号或者EOF则跳出循环
        else if (isPeekToken({Token::TOKEN_RPAREN, Token::TOKEN_EOF}))
            break;
        else
        {
            // 语法错误，并返回false
            peekError({Token::TOKEN_COMMA, Token::TOKEN_RPAREN});
            return false;
        }
    }
    // 如果下一个token不是右括号，则报错并返回false
    return isPeekTokenExpect(Token::TOKEN_RPAREN);
}

// 函数体解析函数
bool Parser::parseFunctionBody(const std::shared_ptr<Function> &func)
{
    // 解析函数体
    func->body = parseBlock();
    // 如果函数体解析为空指针则返回false，否则返回true
    return func->body != nullptr;
}

// if解析函数
std::shared_ptr<Expression> Parser::parseIf()
{
    // 构建if节点
    std::shared_ptr<If> ifExpr(new If());
    ifExpr->token = curr;
    // 跳过if关键字token
    nextToken();
    // 创建场景结点
    std::shared_ptr<Scenario> scenario(new Scenario());
    // 解析当前场景下的条件表达式
    scenario->condition = parseExpression(Precedence::LOWEST);
    // 如果下一个token不是左大括号，则报错，否则跳至左大括号并解析语句块
    if (!isPeekTokenExpect(Token::TOKEN_LBRACE))
        return nullptr;
    scenario->body = parseBlock();
    // 将场景加入if节点
    ifExpr->scenarios.emplace_back(scenario);
    // 循环解析elif语句
    while (isPeekToken(Token::TOKEN_ELIF))
    {
        // 跳至elif关键字token
        nextToken();
        // 跳至到elif后紧跟着的token
        nextToken();
        // 创建新的场景结点
        std::shared_ptr<Scenario> nextScenario(new Scenario());
        // 解析场景条件语句
        nextScenario->condition = parseExpression(Precedence::LOWEST);
        // 如果下一个token不是左大括号则报错
        if (!isPeekTokenExpect(Token::TOKEN_LBRACE))
            return nullptr;
        // 解析场景代码块语句并添加到场景中
        nextScenario->body = parseBlock();
        // 添加场景到if结点中
        ifExpr->scenarios.emplace_back(nextScenario);
    }
    // 解析else语句
    if (isPeekToken(Token::TOKEN_ELSE))
    {
        // 跳至else关键字token
        nextToken();
        // 如果else关键字下一个token是否为左大括号则报错
        if (!isPeekTokenExpect(Token::TOKEN_LBRACE))
            return nullptr;
        // 创建新的场景结点
        std::shared_ptr<Scenario> nextScenario(new Scenario());
        // 创建一个true条件token
        std::shared_ptr<Bool> trueConditon(new Bool());
        trueConditon->token = Token(Token::TOKEN_TRUE, "true", curr.getLine(), curr.getColumn());
        trueConditon->value = true;
        // 设置场景条件为true
        nextScenario->condition = trueConditon;
        // 解析场景代码块语句并添加到场景中
        nextScenario->body = parseBlock();
        // 添加场景到if结点中
        ifExpr->scenarios.emplace_back(nextScenario);
    }
    // 返回if结点
    return ifExpr;
}

// switch结点解析函数
std::shared_ptr<Expression> Parser::parseSwitch()
{
    // 创建switch结点
    std::shared_ptr<Switch> switchExpr(new Switch());
    // 设置switch关键字token
    switchExpr->token = curr;
    // 跳过switch关键字token
    nextToken();
    // 解析switch值表达式
    switchExpr->value = parseExpression(LOWEST);
    // 如果switch值表达式计算出错则提前输出
    if (!switchExpr->value)
        return nullptr;
    // 判断下一个token是否为左大括号
    if (!isPeekTokenExpect(Token::TOKEN_LBRACE))
        return nullptr;
    // 跳过左大括号token
    nextToken();
    // 循环解析直到遇到右大括号
    while (!isCurrToken(Token::TOKEN_RBRACE))
    {
        std::shared_ptr<Case> caseNode(new Case());
        // 如果当前token为case
        if (isCurrToken(Token::TOKEN_CASE))
        {
            // 跳过case对应token
            nextToken();
            // 解析case对应的值
            caseNode->values.emplace_back(parseExpression(Precedence::LOWEST));
            // 如果解析表达式的下一个token为逗号，则继续解析下一个值
            while (isPeekToken(Token::TOKEN_COMMA))
            {
                // 跳过当前token
                nextToken();
                // 跳过逗号token
                nextToken();
                // 解析表达式继续添加到caseNode->values中
                caseNode->values.emplace_back(parseExpression(Precedence::LOWEST));
            }
        }
        // 如果当前token是default，则设置default为true
        else if (isCurrToken(Token::TOKEN_DEFAULT))
            caseNode->isDefault = true;
        // 否则发生错误报错
        else
        {
            // error
            std::stringstream ss;
            ss << "expected 'case' or 'default', got " << curr.getType() << " instead";
            errors.emplace_back(ss.str());
            return nullptr;
        }
        // 如果下一个token不是冒号，则报错
        if (!isPeekTokenExpect(Token::TOKEN_COLON))
            return nullptr;
        // 创建代码块结点并设置对应token
        std::shared_ptr<Block> body(new Block());
        body->token = curr;
        // 跳过冒号token
        nextToken();
        // 如果没遇到下一个case或default，则循环解析代码块语句
        while (!isCurrToken(Token::TOKEN_CASE) && !isCurrToken(Token::TOKEN_DEFAULT))
        {
            if (isCurrToken(Token::TOKEN_RBRACE))
                break;
            std::shared_ptr<Statement> stmt = parseStatement();
            body->statements.emplace_back(stmt);
            // 跳过分号token，即跳至下一个语句起始token
            nextToken();
        }
        // 设置case结点添加代码块结点
        caseNode->body = body;
        // 添加case结点到switch结点中
        switchExpr->cases.emplace_back(caseNode);
    }
    // 如果下一个token不是右大括号，则报错
    if (!isCurrToken(Token::TOKEN_RBRACE))
        return nullptr;
    // 返回switch结点
    return switchExpr;
}

// while结点解析函数
std::shared_ptr<Expression> Parser::parseWhile()
{
    // 创建while结点
    std::shared_ptr<While> whileExpr(new While());
    // 设置while结点的token
    whileExpr->token = curr;
    // 跳过while关键字token
    nextToken();
    // 解析while条件表达式
    whileExpr->condition = parseExpression(Precedence::LOWEST);
    // 如果下一个token不是左大括号则报错
    if (!isPeekTokenExpect(Token::TOKEN_LBRACE))
        return nullptr;
    // 解析while代码块语句并添加到while结点中
    whileExpr->body = parseBlock();
    // 返回while结点
    return whileExpr;
}

// for结点解析函数
std::shared_ptr<Expression> Parser::parseFor()
{
    // 创建for结点
    std::shared_ptr<For> forExpr(new For());
    // 设置for结点的token
    forExpr->token = curr;
    // 判断下一个token是否为左括号
    if (!isPeekTokenExpect(Token::TOKEN_LPAREN))
        return nullptr;
    // 解析for循环起始表达式
    forExpr->starters = parseExpressionList(Token::TOKEN_SEMICOLON);
    // // 如果起始表达式为空则报错
    // if (!forExpr->starter)
    //     return nullptr;
    // // 判断下一个token是否为分号，如果不为分号则报错，否则跳至分号token
    // if (!isPeekTokenExpect(Token::TOKEN_SEMICOLON))
    //     return nullptr;
    // 解析for循环条件表达式
    forExpr->conditions = parseExpressionList(Token::TOKEN_SEMICOLON);
    // // 如果条件表达式为空则报错
    // if (!forExpr->condition)
    //     return nullptr;
    // // 判断下一个token是否为分号，如果不为分号则报错，否则跳至分号token
    // if (!isPeekTokenExpect(Token::TOKEN_SEMICOLON))
    //     return nullptr;
    // 解析for循环步长表达式
    forExpr->closers = parseExpressionList(Token::TOKEN_RPAREN);
    // // 如果步长表达式为空则报错
    // if (!forExpr->closer)
    //     return nullptr;
    // // 判断下一个token是否为右括号，如果不为右括号则报错，否则跳至右括号token
    // if (!isPeekTokenExpect(Token::TOKEN_RPAREN))
    //     return nullptr;
    // 判断下一个token是否为左大括号，如果不为左大括号则报错，否则跳至左大括号token
    if (!isPeekTokenExpect(Token::TOKEN_LBRACE))
        return nullptr;
    // 解析for循环代码块语句并添加到for结点中
    forExpr->body = parseBlock();
    // 返回for结点
    return forExpr;
}

// 中缀表达式解析函数
std::shared_ptr<Expression> Parser::parseInfix(const std::shared_ptr<Expression> &left)
{
    std::shared_ptr<Infix> exp(new Infix());
    exp->token = curr;
    exp->left = left;
    exp->op = curr.getLiteral();
    Precedence precedence = currTokenPrecedence();
    nextToken();
    exp->right = parseExpression(precedence);
    return exp;
}

// 赋值表达式解析函数
std::shared_ptr<Expression> Parser::parseAssign(const std::shared_ptr<Expression> &left)
{
    // // 检查左操作数的类型
    // switch(left->getType())
    // {
    //     // 左操作数为标识符时
    //     case Node::NODE_IDENTIFIER:
    //     {
    //         // 构建赋值表达式节点
    //         std::shared_ptr<Assign> exp(new Assign());
    //         // 设置赋值表达式节点的token和对应标识符名称
    //         exp->token=curr;
    //         exp->name=left;
    //         // 获取赋值操作的优先级
    //         Precedence precedence=currTokenPrecedence();
    //         // 进行下一次token获取
    //         nextToken();
    //         // 获取赋值表达式节点的右操作数值
    //         exp->value=parseExpression(precedence);
    //         // 返回赋值表达式节点
    //         return exp;
    //     }
    //     default:
    //         return nullptr;
    // }
    // 构建赋值表达式节点
    std::shared_ptr<Assign> exp(new Assign());
    // 设置赋值表达式节点的token和对应标识符名称
    exp->token = curr;
    exp->name = left;
    // 获取赋值操作的优先级
    Precedence precedence = currTokenPrecedence();
    // 进行下一次token获取
    nextToken();
    // 获取赋值表达式节点的右操作数值
    exp->value = parseExpression(precedence);
    // 返回赋值表达式节点
    return exp;
}

// 复合赋值表达式解析函数
std::shared_ptr<Expression> Parser::parseCompoundAssign(const std::shared_ptr<Expression> &left)
{
    // 构建复合赋值表达式节点
    std::shared_ptr<CompoundAssign> exp(new CompoundAssign());
    // 设置复合赋值表达式节点的token和对应运算符
    exp->token = curr;
    exp->op = curr.getLiteral();
    exp->left = left;
    // 获取复合赋值操作的优先级
    Precedence precedence = currTokenPrecedence();
    // 进行下一次token获取
    nextToken();
    // 获取复合赋值表达式节点的右操作数值
    exp->right = parseExpression(precedence);
    // 返回复合赋值表达式节点
    return exp;
}

// 三元表达式解析函数
std::shared_ptr<Expression> Parser::parseTernary(const std::shared_ptr<Expression> &left)
{
    std::shared_ptr<Ternary> exp(new Ternary());
    exp->token = curr;
    exp->condition = left;
    // 跳过'?'token
    nextToken();
    // 获取左表达式的优先级
    Precedence precedence = currTokenPrecedence();
    // 解析true情况下的左表达式
    exp->trueExpr = parseExpression(precedence);
    if (!isPeekTokenExpect(Token::TOKEN_COLON))
        return nullptr;
    // 跳过':'token
    nextToken();
    // 获取右表达式的优先级
    precedence = currTokenPrecedence();
    // 解析false情况下的右表达式
    exp->falseExpr = parseExpression(precedence);
    // 返回三元表达式节点
    return exp;
}

// 索引表达式解析函数
std::shared_ptr<Expression> Parser::parseIndex(const std::shared_ptr<Expression> &left)
{
    // 构建索引表达式节点
    std::shared_ptr<Index> exp(new Index());
    // 设置索引表达式节点的token和左操作数
    exp->token = curr;
    exp->left = left;
    // 跳过'['token
    nextToken();
    // 解析索引值
    exp->index = parseExpression(Precedence::LOWEST);
    // 如果下一个token不是']'则报错
    if (!isPeekTokenExpect(Token::TOKEN_RBRACKET))
        return nullptr;
    return exp;
}

// 点表达式解析函数
std::shared_ptr<Expression> Parser::parseDot(const std::shared_ptr<Expression> &left)
{
    // 创建属性节点
    std::shared_ptr<Property> exp(new Property());
    // 设置属性节点的token和对应对象
    exp->token = curr;
    exp->object = left;
    // 如果下一个token不是标识符则报错并返回nullptr
    if (!isPeekTokenExpect(Token::TOKEN_IDENTIFIER))
        return nullptr;
    // 解析属性名
    exp->property = parseIdentifier();
    // 返回属性节点
    return exp;
}

// in表达式解析函数
std::shared_ptr<Expression> Parser::parseIn(const std::shared_ptr<Expression> &left)
{
    // 构建in表达式节点
    std::shared_ptr<In> exp(new In());
    // 设置in表达式节点的token和左操作数
    exp->token = curr;
    exp->left = left;
    // 获取in操作的优先级
    Precedence precedence = currTokenPrecedence();
    // 跳过'in'token
    nextToken();
    // 获取in表达式节点的右操作数表达式
    exp->right = parseExpression(precedence);
    // 返回in表达式节点
    return exp;
}

// 函数调用表达式解析函数
std::shared_ptr<Expression> Parser::parseCall(const std::shared_ptr<Expression> &left)
{
    // 创建函数调用表达式节点
    std::shared_ptr<Call> exp(new Call());
    // 设置函数调用表达式节点的token和对应函数表达式
    exp->token = curr;
    exp->function = left;
    // 解析函数参数列表
    exp->arguments = parseExpressionList(Token::TOKEN_RPAREN);
    // 返回函数调用表达式节点
    return exp;
}

// 后缀表达式解析函数
std::shared_ptr<Expression> Parser::parsePostfix(const std::shared_ptr<Expression> &left)
{
    // 构建后缀表达式节点
    std::shared_ptr<Postfix> exp(new Postfix());
    // 设置后缀表达式节点的token和对应运算符以及左操作数
    exp->token = curr;
    exp->op = curr.getLiteral();
    exp->left = left;
    // 返回后缀表达式节点
    return exp;
}