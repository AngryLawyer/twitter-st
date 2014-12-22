#include "seatest.h"
#include "window.h"

void test_no_wrapping() {
    char *s = "Hello world!";
    char buffer[255];
    short max_width = 320;
    short text_size = 4;
    short last_position = 0;
    //Hello World! won't wrap as it's only 36 pixels wide!
    assert_true(tokenize_multiline(buffer, s, max_width, text_size, &last_position));
    assert_string_equal(s, buffer);
    assert_false(tokenize_multiline(buffer, s, max_width, text_size, &last_position));
}

void test_linebreak() {
    char *s = "Hello\nworld!";
    char buffer[255];
    short max_width = 320;
    short text_size = 4;
    short last_position = 0;
    //Wrap on the line break
    assert_true(tokenize_multiline(buffer, s, max_width, text_size, &last_position));
    assert_string_equal("Hello", buffer);
    assert_true(tokenize_multiline(buffer, s, max_width, text_size, &last_position));
    assert_string_equal("world!", buffer);
}

void test_find_line_break() {
    char *s = "Hello hello world!";
    char buffer[255];
    short max_width = 14 * 4;
    short text_size = 4;
    short last_position = 0;
    //Wrap on the nearest space to 14 characters
    assert_true(tokenize_multiline(buffer, s, max_width, text_size, &last_position));
    assert_string_equal("Hello hello", buffer);
    assert_true(tokenize_multiline(buffer, s, max_width, text_size, &last_position));
    assert_string_equal("world!", buffer);
}

void test_fixture_string_wrapping( void ) {
    test_fixture_start();
    run_test(test_no_wrapping);
    run_test(test_linebreak);
    run_test(test_find_line_break);
    test_fixture_end();
}

void all_tests( void ) {
    test_fixture_string_wrapping();
}

short main(short int argc, char *argv[]) {
    run_tests(all_tests);
    getchar();
}
