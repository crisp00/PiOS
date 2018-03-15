#include "headers/tests.hh"
#include "hal/headers/pmm.hh"
#include "hal/headers/heap.hh"

struct test_pmm1{
    uint32_t nums[600];
}typedef test_pmm1_t;

struct test_pmm2{
    uint32_t nums[250];
}typedef test_pmm2_t;

static char tmp[100];
int test_pmm(){
    test_pmm1_t *test1 = kmalloc<test_pmm1_t>();
    test_pmm1_t *test2 = kmalloc<test_pmm1_t>();
    test1->nums[599] = 0xffffffffffffffff;
    test2->nums[0] = 100;
    

    test_pmm2_t *test3 = kmalloc<test_pmm2_t>();
    test_pmm2_t *test4 = kmalloc<test_pmm2_t>();
    test3->nums[249] = 0xffffffffffffffff;
    test4->nums[0] = 100;

    if( (int)test1 == (int)test2 ||
        (int)test3 == (int)test4){
        //pmm yielded twice the same bytes, that's a problem
        log("Address equality test FAIL");
        return TEST_FAIL_PMM;
    }
    if( test1->nums[599] != -1 ||
        test2->nums[0] != 100 ||
        test3->nums[249] != -1 ||
        test4->nums[0] != 100)
    {
        //The contents have changed, something is wrong
        log("Value detention test FAIL:\n");
        log(itoa(test1->nums[599], tmp, 10));
        log(" ");
        log(itoa(test2->nums[0], tmp, 10));
        log(" ");
        log(itoa(test3->nums[249], tmp, 10));
        log(" ");
        log(itoa(test4->nums[0], tmp, 10));
        log("\n");
        return TEST_FAIL_PMM;
    }
    if((int)test3 - (int)test2 > HEAP_BLOCK_SPACE_LENGTH){
        //3rd object should be in the same block as the 1st
        log("Block equality test FAIL:\n");
        log(" ");
        log(itoa((int)test2, tmp, 10));
        log(" ");
        log(itoa((int)test3, tmp, 10));
        log("\n");
        return TEST_FAIL_PMM;
    }
    if((int)test4 - (int)test1 > HEAP_BLOCK_SPACE_LENGTH){
        //4th object should be in the same block as the 2nd
        log("Block equality test FAIL:\n");
        log(" ");
        log(itoa((int)test1, tmp, 10));
        log(" ");
        log(itoa((int)test4, tmp, 10));
        log("\n");
        return TEST_FAIL_PMM;
    }
        bool x = pmm::bitmap_get(69);
    pmm::bitmap_put(69, !x);
    if(pmm::bitmap_get(69) != x) {
        log("pmm PASS 1\n");
    }
    pmm::bitmap_put(69, x);
    if(pmm::bitmap_get(69) == x) {
        log("pmm PASS 2\n");
    }
        // log("Running tests: ");
    // int tests = test();
    // if(tests == 0){
    //     log("All tests succeded\n");
    // }else{
    //     log("Some tests failed\n");
    // }


    // int *test_heap = kmalloc<int>();
    // *test_heap = 71;
    // log("Test heap: 0x");
    // log(itoa((uint32_t)test_heap, tmp, 16));
    // log("\n");
    // test_heap = kmalloc<int>();
    // *test_heap = 71;
    // log("Test heap: 0x");
    // log(itoa((uint32_t)test_heap, tmp, 16));
    // log("\n");
    // test_heap = kmalloc<int>();
    // *test_heap = 71;
    // log("Test heap: 0x");
    // log(itoa((uint32_t)test_heap, tmp, 16));
    // log("\n");
    // test_heap = kmalloc<int>();
    // *test_heap = 71;
    // log("Test heap: 0x");
    // log(itoa((uint32_t)test_heap, tmp, 16));
    // log("\n");
    // test_heap = kmalloc<int>();
    // *test_heap = 71;
    // log("Test heap: 0x");
    // log(itoa((uint32_t)test_heap, tmp, 16));
    // log("\n");


    // log("Accessing uninitialized page");
    // int *test = (int *)0xb0300000;
    // // vmm::alloc_page((uint32_t)test);
    // *test = 69;
    // log(itoa(*test, tmp, 10));
    // log("\n\n\n");

    // asm("int $14");
    return 0;
}

int test(){
    int fail = 0;
    fail = fail | test_pmm();
    return fail;
}

template <typename type> static type *kmalloc(){
    log("kmalloc()-> type size: ");
    log(itoa(sizeof(type), tmp, 10));
    log("\n");
    return (type *)heap::mem_alloc(sizeof(type));
}