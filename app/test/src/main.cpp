#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <catch.hpp>
#include <wchar.h>
#include "../../../app/src/Parser.h"
#include "../../../app/src/Scanner.h"

void compile(const char *file) {
    wchar_t *fileName = coco_string_create(file);
    Scanner *scanner = new Scanner(fileName);
    Parser *parser = new Parser(scanner);
    coco_string_delete(fileName);
    parser->Parse();
    if (parser->errors->count == 0) {
        std::cout << "Finished" << std::endl;
    }
    delete parser;
    delete scanner;
}

int main() {
    std::cout << "Test 0\n";
    compile("tests/data/test0.b");
    compile("tests/data/test1.b");
    compile("tests/data/test2.b");
    compile("tests/data/test3.b");
    compile("tests/data/test4.b");
}
