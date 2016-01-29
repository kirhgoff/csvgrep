#include <stdio.h>
#include <check.h>

#include "csvparse.h"

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

Suite* str_suite (void) {
        Suite *suite = suite_create("csvparse");
        TCase *tcase = tcase_create("case");
        tcase_add_test(tcase, test_csv_parse);
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
