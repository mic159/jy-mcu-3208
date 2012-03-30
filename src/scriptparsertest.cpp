#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cstring>
#include <stdint.h>
#include "scriptparser.h"
#include "commands.h"

class ScriptParserTest : public CppUnit::TestFixture {
private:
    CPPUNIT_TEST_SUITE(ScriptParserTest);
    CPPUNIT_TEST(test_no_args);
    CPPUNIT_TEST(test_1_arg);
    CPPUNIT_TEST_SUITE_END();

    void parse(const char* text, const uint8_t* expected, int length) {
        uint8_t script[100];
        ScriptParser parser(script);
        do {
            parser.parse(*text);
        } while (*(text++) != '\0');
        CPPUNIT_ASSERT(ScriptParser::IGNORE != parser.state);
        CPPUNIT_ASSERT_EQUAL(0, std::memcmp(script, expected, length));
    }

public:
    void test_no_args() {
        uint8_t e1[] = { CODE_END };
        parse("end", e1, sizeof(e1));
    }

    void test_1_arg() {
        uint8_t e1[] = { CODE_HSCROLL, 5, 'h', 'e', 'l', 'l', 'o' };
        parse("hscroll hello", e1, sizeof(e1));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ScriptParserTest);
