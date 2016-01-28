#include <stdio.h>
#include <check.h>

#include "csvparse.h"

START_TEST (test_csv_parse)
{
        CsvDescriptor csv;
        csv.delimiter = ',';
        initDescriptor(&csv);

        char * line = "a,b";
        parseCsvLine(line, sizeof(line), &csv);        

        fail_if(!csv.cells);
        fail_if(!csv.cells[0]);
        fail_if(!csv.cells[1]);
        fail_if(strcmp(csv.cells[0], "a") == -1);
        fail_if(!strcmp(csv.cells[1], "b") == -1);

        destroyDescriptor(&csv);
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