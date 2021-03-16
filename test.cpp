#include "pch.h"
#include "RB-Tree.h"

using namespace std;

RB_Tree<int, int> global_tree;

TEST(Test_RB_Tree, InitCase) {
	ASSERT_ANY_THROW(global_tree.create_bft_ierator()); // tree is empty
}

TEST(Test_RB_Tree, InsertCase) {
	int value = 1; // for simplicity, the value will always be the same
	// Only the key will change
	int keys_in_out[] = { 50,25,66,13,40,55,100 };
	for (size_t i = 0; i < 7; i++) {
		global_tree.Insert(keys_in_out[i], value);
	}
	List <int> keys_in_tree = *global_tree.Get_keys();
	for (size_t i = 0; i < 7; i++) {
		ASSERT_EQ(keys_in_out[i], keys_in_tree[i]);
	}
}

TEST(Test_RB_Tree, FindCase) {
	ASSERT_EQ(1, global_tree.Find(66)); // value in the tree is always equal to one
	ASSERT_EQ(1,global_tree.Find(100));
}

TEST(Test_RB_Tree, RemoveCase) {

	// example of deleting a red node
	int value = 1;
	global_tree.Remove(40);
	int keys_in_out_after_remove[] = { 50,25,66,13,55,100 };
	List <int> keys_in_tree = *global_tree.Get_keys();
	for (size_t i = 0; i < 6; i++) {
		ASSERT_EQ(keys_in_out_after_remove[i], keys_in_tree[i]); 
	}
	keys_in_tree.~List();


	// example of deleting black node with big rotate and no children
	int new_key = 40;
	global_tree.Insert(new_key, value);
	new_key = 30;
	global_tree.Insert(new_key, value);
	global_tree.Remove(13); 
	keys_in_tree = *global_tree.Get_keys();
	int keys_in_out_after_remove2[] = { 50,30,66,25,40,55,100 };
	for (size_t i = 0; i < 7; i++) {
		ASSERT_EQ(keys_in_out_after_remove2[i], keys_in_tree[i]);
	}
	keys_in_tree.~List();


	// example of deleting black node with 2 children
	global_tree.Remove(66);
	int keys_in_out_after_remove3[] = { 50,30,55,25,40,100 }; 
	keys_in_tree = *global_tree.Get_keys();
	for (size_t i = 0; i < 6; i++) {
		ASSERT_EQ(keys_in_out_after_remove3[i], keys_in_tree[i]);
	}
	keys_in_tree.~List();

	// example of deleting black node with 1 children
	global_tree.Remove(55);
	int keys_in_out_after_remove4[] = { 50,30,100,25,40 };
	keys_in_tree = *global_tree.Get_keys();
	for (size_t i = 0; i < 5; i++) {
		ASSERT_EQ(keys_in_out_after_remove4[i], keys_in_tree[i]);
	}
	keys_in_tree.~List();
}


TEST(Test_RB_Tree, ExceptionCase) {
	ASSERT_ANY_THROW(global_tree.Find(-1));
	ASSERT_ANY_THROW(global_tree.Remove(31));
	global_tree.~RB_Tree();
	ASSERT_ANY_THROW(global_tree.Get_values());
}