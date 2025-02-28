#include <iostream>
#include <lexer/lexer.h>
using namespace std;
using namespace cpy::lexer;
int main(int argc, char *argv[])
{
    if (argc < 2)
        return 0;
    if (strcmp(argv[1], "-h") == 0)
    {
        printf("usage: ./lexer -i <input_file> -o <output_file>\n");
        printf("function: generate tokens from code\n");
        return 0;
    }
    else if (strcmp(argv[1], "-i") == 0)
    {
        if (argc < 4)
        {
            printf("usage: ./lexer -i <input_file> -o <output_file>\n");
            return 0;
        }
        else if (argv[3] == "-o")
        {
            std::string input_file = argv[2];
            std::string output_file = argv[4];
            Lexer lexer(input_file);
            Value tokens;
            while (true)
            {
                Token token = lexer.nextToken();
                token.show();
                tokens.append(token.getJson());
                if (token.getType() == Token::TOKEN_EOF)
                    break;
            }
            Value root;
            root["tokens"] = tokens;
            fstream fout(output_file, ios::out);
            fout << root;
            fout.close();
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