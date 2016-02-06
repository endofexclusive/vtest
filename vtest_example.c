#include <vtest.h>

int main(void)
{
        vtest_init();

        vtest(0 == 1);
        vtest(1 == 1);
        vtest("I should not fail")
        vtest(!"I should fail")

        vtest_report();
        vtest_end();

        return 0;
}

