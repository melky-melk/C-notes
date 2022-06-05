/*
• Stack can be initialised
• Elements can be added to the stack by using the push function
• pop functionality works as intended by removing and returning the element at the top of the stack
• Stack can be deallocated
• Can retrieve the size of the stack
• Stack functions can handle null data

gcc -o unit-tests unit-tests.c libcmocka-static.a
*/

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "cmocka.h"

#include "stack.c"

static int setup_stack(void** state){
	(*state) = init_stack();

	// puts("init stack");
	// printf("stack head %p\n", *(init_stack()->head));
	return 0;
}

static int destroy_stack(void** state){
	free_stack( (Stack*) (*state));
	return 0;
}

static void test_stack_init(void** state){
	Stack* stack = (Stack*) (*state);
	assert_ptr_equal(*stack->head, NULL);
	assert_int_equal(stack->size, 0);
}

static void test_push(void** state){
	Stack* stack = (Stack*) (*state);
	Node** before = stack->head;
	
	push(stack, 69);
	assert_ptr_not_equal(*stack->head, NULL);
	assert_int_equal(stack->size, 1);
}

static void test_pop(void** state){
	Stack* stack = (Stack*) (*state);
	Node** before = stack->head;
	
	push(stack, 69);
	int popped_value = pop(stack);
	assert_int_equal(popped_value, 69);
	assert_ptr_equal(*stack->head, NULL);
	assert_int_equal(stack->size, 0);
}

static void test_empty_pop(void** state){
	Stack* stack = (Stack*) (*state);
	
	int popped_value = pop(stack);
	assert_int_equal(popped_value, -1);
	assert_ptr_equal(*stack->head, NULL);
	assert_int_equal(stack->size, 0);
}

int main(void) {
	int failed_tests = 0;
	
    const struct CMUnitTest stack_tests[] = {
        cmocka_unit_test_setup_teardown(test_stack_init, setup_stack, destroy_stack),
        cmocka_unit_test_setup_teardown(test_push, setup_stack, destroy_stack),
        cmocka_unit_test_setup_teardown(test_pop, setup_stack, destroy_stack),
        cmocka_unit_test_setup_teardown(test_empty_pop, setup_stack, destroy_stack),
    };
	failed_tests += cmocka_run_group_tests(stack_tests, NULL, NULL);

	return failed_tests;
}