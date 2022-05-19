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

#define order_num 10

typedef struct Exchange Exchange;

struct Exchange {
	// =2
	int length;
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
	
	int length = 2;
	Order** orders = (Order**) malloc(sizeof(Order*) * length);
	Trader** traders = malloc(sizeof(Trader*) * length);

	for (int i = 0; i < length; i++){
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

	Exchange* exchange = malloc(sizeof(Exchange));
	exchange->length = length;
	exchange->orders = orders;
	exchange->traders = traders;
	exchange->product = product;

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

static int setup_orders(void **state) {
	Order** orders = (Order**) malloc(sizeof(Order*) * order_num);
	Trader* trader = create_trader(69, 420, NULL, NULL);
	trader->inventory = malloc(sizeof(InventoryData*));
	trader->inventory[0] = create_inventory_data("MELK");

	for (int i = 0; i < order_num/2; i++)
		orders[i] = create_order("MELK", trader, i, 1, 10, i + 1);

	for (int i = order_num/2; i < order_num; i++)
		orders[i] = create_order("MELK", trader, i, 0, 10, i + 1);

	*state = (void*)orders;
	return 0;
}

static int destroy_orders(void **state){
	Order** orders = (Order**) *state;
	for (int i = 0; i< order_num; i++){free(orders[i]);} 
	free(orders);
	return 0;
}

static void test_priority_queue_max(void **state) {
	Order** orders = (Order**) *state; 

	Node** pq = (Node**) malloc(sizeof (Node*));
	*(pq) = NULL;

	for (int i = 0; i < order_num; i++)
		priority_max_queue_push(pq, orders[i]);

	Node* node = *pq;
	// should be sorted from most to least
	int i = 10;
	while (node != NULL){
		assert_true(i == ((Order*) node->data)->price);
		node = node->next;
		i--;
	}
}

static void test_priority_queue_min(void **state) {
	Order** orders = (Order**) *state; 

	Node** pq = (Node**) malloc(sizeof (Node*));
	*(pq) = NULL;

	for (int i = 0; i < order_num; i++)
		priority_min_queue_push(pq, orders[i]);

	Node* node = *pq;
	int i = 1;
	while (node != NULL){
		assert_true(i == ((Order*) node->data)->price);
		node = node->next;
		i++;
	}
}

static void test_set_up_valid_orders_buy(void** state){
	Order** orders = (Order**) *state; 
	Product* product = create_product("MELK");

	for (int i = 0; i < order_num; i++)
		priority_max_queue_push(product->queue, orders[i]);

	//orders 0 should be a buy order that costs 1 there is only 1 order inside sell that will sell the product for 1
	// so there should only be 1 match in valid orders
	Node* valid_orders = setup_valid_orders(orders[0], product);

	assert_true(NULL == peek(&valid_orders));
}

static void test_set_up_valid_orders_sell(void** state){
	Order** orders = (Order**) *state; 
	Product* product = create_product("MELK");

	for (int i = 0; i < order_num; i++)
		priority_max_queue_push(product->queue, orders[i]);

	//orders 0 should be a sell order that costs 0 there are order_num/2 orders
	// the orders should be of price order_num/2 (5) going down to 1. it starts with 5
	Node* valid_orders = setup_valid_orders(orders[order_num/2 -1], product);
	Node* node = valid_orders;

	int i = 5;
	while (node != NULL){
		Order* order = (Order*) pop(&node);
		assert_int_equal(i, order->price);
		i--;
	}
}

static void test_set_up_valid_orders_none(void** state){
	Order** orders = (Order**) *state; 
	Product* product = create_product("MELK");

	// because the product has no orders inside of it's queue. the order should now be in the queue 
	setup_valid_orders(orders[0], product);
	Order* added_order = (Order*) (*product->queue)->data;

	assert_true(added_order == orders[0]);
}

static void test_perfect_trade(void** state){
    Exchange* exchange = (Exchange*) *state;
	Order* new_order = exchange->orders[0];
	Order* existing_order = exchange->orders[1];

	Trader* trader = exchange->traders[0];
	Trader* other_trader = exchange->traders[1];

	Product* product = exchange->product;

	int fees_collected = place_order(product, new_order);

	assert_int_equal(fees_collected, 1L);
	
	// the fees collected should be deducted from the trader placing the order
	assert_int_equal(trader->inventory[0]->total_balance, 99);
	assert_int_equal(other_trader->inventory[0]->total_balance, -100);

	assert_true(trader->inventory[0]->total_quantity == -1L);
	assert_true(other_trader->inventory[0]->total_quantity == 1L);

	// the old order was removed from it, and the new order should not have been placed
	assert_true(NULL == (*product->queue));
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

static void test_no_valid_orders(void** state){
    Exchange* exchange = (Exchange*) *state;
	Order* new_order = exchange->orders[0];
	new_order->price = 1000;
	Order* existing_order = exchange->orders[1];
	Product* product = exchange->product;

	int fees_collected = place_order(product, new_order);

	assert_true(fees_collected == 0L);
	
	// the new order wasnt added to it
	assert_true(new_order == (*product->queue)->data);
	assert_true(existing_order == (*product->queue)->next->data);
}

static void test_remove_from_container(void** state){
    Exchange* exchange = (Exchange*) *state;
	Order* new_order = exchange->orders[0];
	new_order->buy = 1;
	Order* existing_order = exchange->orders[1];
	Product* product = exchange->product;
	Order* another_order = exchange->orders[1];

	int fees_collected = place_order(product, new_order);
	place_order(product, another_order);

	assert_true(fees_collected == 0L);
	Order* container = (Order*) (*product->queue)->data;

	// checking that none of the orders were placed into the queue
	assert_true(NULL == find_data(*product->queue, existing_order));
	assert_true(NULL == find_data(*product->queue, new_order));
	assert_true(NULL == find_data(*product->queue, another_order));
	assert_true(container->type == CONTAINER);

	// check the container to see if it contains the orders in a queue, first inserted is at the head, latest inserted at the end
	assert_true(existing_order == container->queue->data);
	assert_true(new_order == container->queue->next->data);
	assert_true(another_order == container->queue->next->next->data);
	assert_int_equal(container->quantity, 3);
	assert_int_equal(container->num_of_orders, 3);

	remove_from_container(product, &container, another_order);

	// again check that the order is maintained
	assert_true(new_order == container->queue->data);
	assert_true(existing_order == container->queue->next->data);
	// the place where the data was should now be null
	assert_true(NULL == container->queue->next->next);
	assert_int_equal(container->quantity, 2);
	assert_int_equal(container->num_of_orders, 2);

	// the pointer from the container should now be the final order
	remove_from_container(product, &container, existing_order);
	// where the container used to be, should be the new order
	assert_true((*product->queue)->data == new_order);
	assert_true(( (Order*) (*product->queue)->data)->type != CONTAINER);
	assert_true(( (Order*) (*product->queue)->data)->type == SIMPLE);
	// the container pointer should have been replaced with the order that was last in the container
	assert_true(container == new_order);
	assert_int_equal(new_order->num_of_orders, 1);
	
	// the new order wasnt added to it
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

	puts("\n=======================TESTING PRIORITY QUEUE========================\n");
    const struct CMUnitTest priority_queue_tests[] = {
        cmocka_unit_test_setup_teardown(test_priority_queue_max, setup_orders, destroy_orders),
        cmocka_unit_test_setup_teardown(test_priority_queue_min, setup_orders, destroy_orders),
        cmocka_unit_test_setup_teardown(test_set_up_valid_orders_buy, setup_orders, destroy_orders),
        cmocka_unit_test_setup_teardown(test_set_up_valid_orders_sell, setup_orders, destroy_orders),
        cmocka_unit_test_setup_teardown(test_set_up_valid_orders_none, setup_orders, destroy_orders),
        // cmocka_unit_test_setup_teardown(test_set_up_valid_orders_none, setup_exchange, destroy_exchange),
    };
    
	failed_tests += cmocka_run_group_tests(priority_queue_tests, NULL, NULL);

	puts("\n====================TESTING PROCESSING TRADERS======================\n");

	const struct CMUnitTest trading_tests[] = {
        cmocka_unit_test_setup_teardown(test_perfect_trade, setup_exchange, destroy_exchange),
        cmocka_unit_test_setup_teardown(test_leftover_existing_trades, setup_exchange, destroy_exchange),
        cmocka_unit_test_setup_teardown(test_leftover_new_trades, setup_exchange, destroy_exchange),
        cmocka_unit_test_setup_teardown(test_creating_containers, setup_exchange, destroy_exchange),
        cmocka_unit_test_setup_teardown(test_no_valid_orders, setup_exchange, destroy_exchange),
    };

	failed_tests += cmocka_run_group_tests(trading_tests, NULL, NULL);

	puts("\n====================TESTING CONTAINERS======================\n");

	const struct CMUnitTest container_tests[] = {
        cmocka_unit_test_setup_teardown(test_remove_from_container, setup_exchange, destroy_exchange),
        cmocka_unit_test_setup_teardown(test_amending_internals, setup_exchange, destroy_exchange),
    };

	failed_tests += cmocka_run_group_tests(container_tests, NULL, NULL);

	return failed_tests;
}

