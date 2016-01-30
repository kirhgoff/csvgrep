#include <stdio.h>
#include <check.h>

#include "error.h"
#include "csvparse.h"
#include "expparse.h"
#include "stack.h"

void check(char * actual, char ** expected) {
  const int length = sizeof(expected) / sizeof(expected[0]);

  CsvDescriptor csv;
  csv.delimiter = ',';
  initDescriptor(&csv);

  parseCsvLine(actual, sizeof(actual), &csv);

  fail_if(!csv.cells);
  for (int i = 0; i < length; i++) {
    fail_if(strcmp(csv.cells[i], expected[i]) == -1);
  }
  destroyDescriptor(&csv);
}

START_TEST (test_csv_parse) {
  check("", (char * []) {""});
  check(",", (char * []) {"", ""});

  check("a", (char * []) {"a"});
  check("a,b", (char * []) {"a", "b"});
  check("abc,bde", (char * []) {"abc", "bde"});
  check("a,b,c", (char * []) {"a", "b", "c"});

  check("abc,,bde", (char * []) {"abc", "", "bde"});

  check("a , b", (char * []) {"a ", " b"});
}
END_TEST

START_TEST(test_expparse_node) {
  ExpressionNode * a1 = createNode(TERMINAL, "a");
  ExpressionNode * a2 = createNode(TERMINAL, "a");
  ExpressionNode * c = createNode(TERMINAL, "c");

  fail_if(!a1);
  fail_if(!a2);
  fail_if(!c);

  fail_if(!equals(a1, a2));
  fail_if(!equals(a2, a1));
  fail_if(equals(a1, NULL));
  fail_if(equals(NULL, a2));
  fail_if(equals(c, a2));

  destroyNode(a1);
  destroyNode(a2);
  destroyNode(c);
}
END_TEST

/*
START_TEST(test_stack) {
  ExpressionNode * a = createNode(TERMINAL, "a");
  ExpressionNode * b = createNode(TERMINAL, "b");
  ExpressionNode * c = createNode(TERMINAL, "c");

  Stack * stack = createStack();
  fail_if(pop(stack) != NULL);
  fail_if(size(stack) != 0);

  push(stack, a);
  push(stack, b);

  fail_if(size(stack) != 2);
  fail_if(!equals(pop(stack), b));
  fail_if(size(stack) != 1);
  fail_if(!equals(pop(stack), a));
  fail_if(size(stack) != 0);
  fail_if(pop(stack) != NULL);

  push(stack, c);
  fail_if(size(stack) != 1);
  fail_if(!equals(pop(stack), c));

  destroyNode(a);
  destroyNode(b);
  destroyNode(c);

  destroyStack(stack);
}
END_TEST
*/

Suite* str_suite (void) {
  TCase *tcase = tcase_create("case");
  tcase_add_test(tcase, test_csv_parse);
  tcase_add_test(tcase, test_expparse_node);
  //tcase_add_test(tcase, test_stack);

  Suite *suite = suite_create("csvparse");
  suite_add_tcase(suite, tcase);
  return suite;
}

int main (int argc, char *argv[]) {
  int number_failed;
  Suite *suite = str_suite();
  SRunner *runner = srunner_create(suite);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed;
}
