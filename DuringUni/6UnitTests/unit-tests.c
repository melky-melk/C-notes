/*
 * Copyright 2008 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../spx_common.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "cmocka.h"

#define TESTING
#include "../spx_trader.h"
#include "../spx_exchange.h"
#include "../spx_exchange.c"

typedef struct Exchange Exchange;

/*
essentially what you want to do for unit tests is in the setup tests, you create a struct that contains all of the information you need for the functions

within the functions you recieve a double void pointer to the struct or thing you created in the set up function, within the functions you test. you want to unpack that void pointer and assign it all the values you use it for so you can properly test without needing to do setup every time
*/

// typically you create a struct that would contain all the variables you need
struct Exchange {
	// each orders corresponds to a trader with the same i and start with buy = 0 for [0] and 1 for [1] quantity=1 price 100. the orders[1] is already inside the product you should manipulate the orders each time within the testing function. you want to add order[0] to the list
	Order** orders;
	// typically 2 traders trading between each other, traders[0] is the one placing the order and traders[1] is the one with a prexisting order inside 
	Trader** traders;
	// all orders will have the same product name
	Product* product;
};

static int setup_exchange(void **state) {
	char* product_name = malloc(sizeof(char) * 5);
	strcpy(product_name, "MELK");
	Order** orders = (Order**) malloc(sizeof(Order*) * length);
	Trader** traders = malloc(sizeof(Trader*) * length);

	for (int i = 0; i < 2; i++){
		Trader* trader = malloc(sizeof(Trader));
		trader->id = i;
		trader->inventory = malloc(sizeof(InventoryData*));
		trader->disconnected = 1; //so it doesnt attempt writing to the pipes
		trader->inventory[0] = create_inventory_data(product_name);
		traders[i] = trader;

		Order* order = create_order(product_name, trader, i, i, 1, 100);
		orders[i] = order;
		stack_push(&trader->inventory[0]->orders, order);
	}

	Product* product = create_product(product_name);
	priority_max_queue_push(product->queue, orders[1]);

	Exchange* exchange = {.orders = orders, .traders = traders, .product = product};

	// then typecast the exchange into the void state, so it can be passed to future unit tests
	// within other functions you unpack and typecast all values within it
	*state = (void*)exchange;
	return 0;
}

static int destroy_exchange(void **state){
	Exchange* exchange = (Exchange*) *state;
	Order** orders = exchange->orders; 
	Trader** traders = exchange->traders;
	Product* product = exchange->product;

	free(product);
	free_nodes(&traders[0]->inventory[0]->orders);
	free_nodes(&traders[1]->inventory[0]->orders);
	free(traders);
	free(orders);
	free(exchange);
	return 0;
}

static void test_leftover_existing_trades(void** state){
    Exchange* exchange = (Exchange*) *state;
	Order* new_order = exchange->orders[0];
	new_order->quantity = 50;
	Order* existing_order = exchange->orders[1];
	existing_order->quantity = 100;

	Trader* trader = exchange->traders[0];
	Trader* other_trader = exchange->traders[1];

	Product* product = exchange->product;

	int fees_collected = place_order(product, new_order);

	assert_int_equal(fees_collected, 50);
	
	assert_true(existing_order == (Order*) (*product->queue)->data);
	assert_int_equal(existing_order->quantity, 50);
	
	assert_true(other_trader->inventory[0]->total_balance == -5000L);
	assert_true(other_trader->inventory[0]->total_quantity == 50L);

	assert_true(trader->inventory[0]->total_balance == 4950L);
	assert_true(trader->inventory[0]->total_quantity == -50L);
	
	// the existing order remains because there was leftover
	assert_true(existing_order == (*product->queue)->data);
	// the new order wasnt added to it
	assert_true(NULL == (*product->queue)->next);
}

static void test_leftover_new_trades(void** state){
    Exchange* exchange = (Exchange*) *state;
	Order* new_order = exchange->orders[0];
	new_order->quantity = 100;
	Order* existing_order = exchange->orders[1];
	existing_order->quantity = 50;

	Trader* trader = exchange->traders[0];
	Trader* other_trader = exchange->traders[1];

	Product* product = exchange->product;

	int fees_collected = place_order(product, new_order);

	assert_int_equal(fees_collected, 50);
	
	assert_true(new_order == (Order*) (*product->queue)->data);
	assert_int_equal(new_order->quantity, 50);
	
	assert_true(other_trader->inventory[0]->total_balance == -5000L);
	assert_true(other_trader->inventory[0]->total_quantity == 50L);

	assert_true(trader->inventory[0]->total_balance == 4950L);
	assert_true(trader->inventory[0]->total_quantity == -50L);

	// the order was added to it and the old should have been removed from the product
	assert_true(new_order == (*product->queue)->data);
	assert_true(NULL == (*product->queue)->next);
}

static void test_creating_containers(void** state){
    Exchange* exchange = (Exchange*) *state;
	Order* new_order = exchange->orders[0];
	new_order->buy = 1;
	Order* existing_order = exchange->orders[1];
	Product* product = exchange->product;

	int fees_collected = place_order(product, new_order);

	assert_int_equal(fees_collected, 0);
	
	Order* container = (Order*) (*product->queue)->data;
	// check that an entirely new order was made
	assert_true(existing_order != container);
	assert_true(new_order != container);
	assert_true(container->type == CONTAINER);
	// check the container to see if it contains the orders
	assert_true(existing_order == container->queue->data);
	assert_true(new_order == container->queue->next->data);
	
	assert_int_equal(container->quantity, 2);
	
	// the new order wasnt added to the product queue
	assert_true(NULL == (*product->queue)->next);
}

static void test_amending_internals(void** state){
    Exchange* exchange = (Exchange*) *state;
	Order* new_order = exchange->orders[0];
	new_order->buy = 1;
	Order* existing_order = exchange->orders[1];
	Product* product = exchange->product;

	int fees_collected = place_order(product, new_order);

	assert_true(fees_collected == 0L);
	Order* container = (Order*) (*product->queue)->data;

	assert_true(NULL == find_data(*product->queue, existing_order));
	assert_true(NULL == find_data(*product->queue, new_order));
	assert_true(container->type == CONTAINER);

	// check the container to see if it contains the orders in a queue
	assert_true(existing_order == container->queue->data);
	assert_true(new_order == container->queue->next->data);
	assert_int_equal(container->quantity, 2);
	assert_int_equal(container->num_of_orders, 2);
	assert_true(existing_order->type == INTERNAL);
	assert_true(new_order->type == INTERNAL);

	// the pointer from the container should now be the final order
	amend_order(product, existing_order, 1, 1);
	assert_true((*product->queue)->data == new_order);
	assert_true(( (Order*) (*product->queue)->data)->type != CONTAINER);
	assert_true(( (Order*) (*product->queue)->data)->type == SIMPLE);
	assert_int_equal(new_order->num_of_orders, 1);
	
	// the order that was inside should now be its own order
	assert_true((*product->queue)->next->data == existing_order);
	assert_int_equal(existing_order->quantity, 1);
	assert_int_equal(existing_order->price, 1);
	assert_true(existing_order->type != INTERNAL);
	assert_true(existing_order->type == SIMPLE);
}

int main(void) {
	int failed_tests = 0;
    
	puts("\n====================TESTING PROCESSING TRADERS======================\n");
	const struct CMUnitTest trading_tests[] = {
        cmocka_unit_test_setup_teardown(test_leftover_existing_trades, setup_exchange, destroy_exchange),
        cmocka_unit_test_setup_teardown(test_leftover_new_trades, setup_exchange, destroy_exchange),
        cmocka_unit_test_setup_teardown(test_creating_containers, setup_exchange, destroy_exchange),
    };

	failed_tests += cmocka_run_group_tests(trading_tests, NULL, NULL);

	puts("\n====================TESTING CONTAINERS======================\n");
	const struct CMUnitTest container_tests[] = {
        cmocka_unit_test_setup_teardown(test_amending_internals, setup_exchange, destroy_exchange),
    };

	failed_tests += cmocka_run_group_tests(container_tests, NULL, NULL);
	return failed_tests;
}