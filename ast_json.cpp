#include <iostream>
#include <parser/parser.h>
using namespace cpy::lexer;
using namespace cpy::parser;

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 0;
    if (strcmp(argv[1], "-h") == 0)
    {
        printf("usage: ./ast -i <input_file> -o <output_file>\n");
        printf("function: generate ast from code\n");
        return 0;
    }
    else if (strcmp(argv[1], "-i") == 0)
    {
        if (argc < 4)
        {
            printf("usage: ./ast -i <input_file> -o <output_file>\n");
            return 0;
        }
        else if (argv[3] == "-o")
        {
            std::string input_file = argv[2];
            std::string output_file = argv[4];
            std::shared_ptr<Lexer> lexer(new Lexer(input_file));
            std::shared_ptr<Parser> parser(new Parser(lexer));
            auto program = parser->parseProgram();
            Value json = program->getJson();
            std::fstream astOut(output_file, std::ios::out);
            astOut << json;
            astOut.close();
            return 0;
        }
        else
        {
            printf("unknown option %s\n", argv[3]);
            return 0;
        }
    }
    else
    {
        printf("unknown option %s\n", argv[1]);
        return 0;
    }
}