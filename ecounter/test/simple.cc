#include <gtest/gtest.h>
#include <ecounter/ec.h>

EC_INST_DEF(test, 4, 10);

TEST(ecounter, simple) {
    EC_INST_INIT(test);

    uint32_t d;

    d = 0x1234;
    ec_inst_record(EC_INST(test), &d);

    d = 0x1235;
    ec_inst_record(EC_INST(test), &d);

    d = 0x1236;
    ec_inst_record(EC_INST(test), &d);
}
