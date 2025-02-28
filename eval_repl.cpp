#include <iostream>
#include <lexer/lexer.h>
#include <parser/parser.h>
#include <evaluator/evaluator.h>
using namespace cpy::lexer;
using namespace cpy::parser;
using namespace cpy::evaluator;

// 定义提示符
// REPL:Read-Eval-Print-Loop
const std::string PROMPT = ">> ";

int main()
{
    // 打印欢迎信息
    std::cout << "Welcome to Cpy Programming language!" << std::endl;
    // 进入REPL循环
    std::shared_ptr<Evaluator> evaluaotr(new Evaluator());
    std::shared_ptr<Environment> env(new Environment());
    while (true)
    {
        std::cout << PROMPT;
        std::string text;
        std::getline(std::cin, text);
        // 创建词法分析器
        std::shared_ptr<Lexer> lexer(new Lexer(text,Lexer::INPUT_CONTENT));
        // 创建语法分析器
        std::shared_ptr<Parser> parser(new Parser(lexer));
        // 创建抽象语法树
        std::shared_ptr<Program> program = parser->parseProgram();
        // 如果有语法错误，则打印错误信息并返回-1
        if (parser->isError())
        {
            parser->printErrors();
            system("pause");
            return -1;
        }
        // 否则进行树递归下降求值
        std::shared_ptr<Object> eval = evaluaotr->eval(program,env);
        if (eval&&(eval->getType()!=Object::OBJECT_NULL))
            eval->print();
    }
    return 0;
}