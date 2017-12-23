#include <iostream>
#include <wchar.h>
#include "Scanner.h"
#include "Parser.h"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        wchar_t *fileName = coco_string_create(argv[1]);
        Scanner *scanner = new Scanner(fileName);
        Parser *parser = new Parser(scanner);
        coco_string_delete(fileName);
        parser->Parse();
        if (parser->errors->count == 0) {
            std::cout << "Finished" << std::endl;
        }
        delete parser;
        delete scanner;

    } else {
        std::cout << "No source file" << std::endl;
    }
}
