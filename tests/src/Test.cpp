#define GMOCK_DEBUG

#include <gtest/gtest.h>
#include "List.h"
#include "Vector.h"
#include "Sort.h"
#include "Map.h"

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	//::testing::GTEST_FLAG(filter) = "BTree_rb.Insert";
	return RUN_ALL_TESTS();
	std::getchar(); // keep console window open until Return keystroke
}

TEST(List1_ns, Insert) {
	List1_ns<int> l;
	l.push_back(1);
	l.push_start(12);
	l.insert(3, 1);
	ASSERT_EQ(l[1], 3);
	ASSERT_EQ(l.getSize(), 3);
	l[1] = 42;
	ASSERT_EQ(l[1], 42);
}

TEST(List1_ns, Delete) {
	List1_ns<int> l;
	l.push_back(1);
	l.push_start(12);
	l.insert(3, 1);
	l.pop_back();
	ASSERT_EQ(l.getSize(), 2);
	l.remove(0);
	ASSERT_EQ(l[0], 3);
	l.pop_start();
	ASSERT_EQ(l.getSize(), 0);
}

TEST(List1_ns, Min_Max) {
	List1_ns<int> l;
	l.push_back(12);
	l.push_back(1);
	l.push_back(-1);
	ASSERT_EQ(l.maximum(), 12);
	ASSERT_EQ(l.minimum(), -1);
}

TEST(List1_s, Insert) {
	List1_s<int> l;
	l.insert(1);
	l.insert(0);
	l.insert(4);
	l.insert(-1);
	l.insert(3);
	ASSERT_EQ(l[0], -1);
	ASSERT_EQ(l[l.getSize() -2], 3);
}

TEST(List1_ns, Find) {
	List1_ns<int> l;
	l.push_back(12);
	l.push_back(13);
	l.push_start(0);
	List1_ns<int>::Node* cur;
	l.find(&cur, 1);
	ASSERT_EQ(cur->data, 12);
}

TEST(List2_s, Insert) {
	List2_s<int> l;
	l.insert(1);
	l.insert(0);
	l.insert(4);
	l.insert(-1);
	l.insert(3);
	List2_s<int>::Node* n;
	l.find(&n, 1);
	ASSERT_EQ(n->data, 0);
	ASSERT_EQ(n->prev->data, -1);
	ASSERT_EQ(n->next->data, 1);
	l.find(&n, l.size - 1);
	ASSERT_EQ(n->data, 4);
	ASSERT_EQ(n->next, nullptr);
	ASSERT_EQ(n->prev->data, 3);
	ASSERT_EQ(n->prev->prev->next->data, 3);
	ASSERT_EQ(l[0], -1);
	ASSERT_EQ(l[l.size - 2], 3);
}


TEST(List2_ns, Insert) {
	List2_ns<int> l;
	l.insert(1,0); //1
	l.insert(0,1); //2
	l.push_back(4); //3
	l.push_back(-1); //4
	l.push_start(3); // 0
	List2_ns<int>::Node* n;
	l.find(&n, 2);
	ASSERT_EQ(n->data, 0);
	ASSERT_EQ(n->prev->data, 1);
	ASSERT_EQ(n->next->data, 4);
	l.find(&n, l.size - 1);
	ASSERT_EQ(n->data, -1);
	ASSERT_EQ(n->next, nullptr);
	ASSERT_EQ(n->prev->data, 4);
	ASSERT_EQ(n->prev->prev->next->data, 4);
	ASSERT_EQ(l[0], 3);
	ASSERT_EQ(l[l.size - 2], 4);
}

TEST(List2_ns, Delete) {
	List2_ns<int> l;
	l.push_back(1);
	l.push_start(12);
	l.insert(3, 1);
	l.pop_back();
	ASSERT_EQ(l.size, 2);
	l.remove(0);
	ASSERT_EQ(l[0], 3);
	l.pop_start();
	ASSERT_EQ(l.size, 0);
	l.push_back(1);
	l.push_back(0);
	l.push_back(2);
	l.push_start(11);
	List2_ns<int>::Node* n;
	l.find(&n,1);
	ASSERT_EQ(n->next->data, 0);
	l.remove(2);
	ASSERT_EQ(n->next->data, 2);
	ASSERT_EQ(n->prev->data, 11);
}

TEST(List2_ns, Min_Max) {
	List2_ns<int> l;
	l.push_back(12);
	l.push_back(1);
	l.push_back(-1);
	ASSERT_EQ(l.maximum(), 12);
	ASSERT_EQ(l.minimum(), -1);
}

TEST(List2_s, Min_Max) {
	List2_s<int> l;
	l.insert(12);
	l.insert(1);
	l.insert(-1);
	ASSERT_EQ(l.maximum(), 12);
	ASSERT_EQ(l.minimum(), -1);
}

TEST(List2_s, Find) {
	List2_s<int> l;
	l.insert(1);
	l.insert(0);
	l.insert(11);
	l.insert(0);
	l.insert(-1);
	l.insert(2);
	List2_s<int>::Node* n;
	l.find(&n, 0);
	ASSERT_EQ(n->data, -1);
	ASSERT_EQ(n->next->data, 0);
	l.find(&n, 3);
	ASSERT_EQ(n->data, 1);
	ASSERT_EQ(n->prev->data, 0);
	ASSERT_EQ(n->next->data, 2);
	ASSERT_EQ(n->next->next->data, 11);
	ASSERT_EQ(n->next->next->next, nullptr);

}

TEST(Vector, Size) {
	Vector_ns<int> v;
	ASSERT_EQ(v.getSize(), 0);
	Vector_ns<int> vc(10);
	ASSERT_EQ(vc.getSize(), 10);
}

TEST(Vector, Insert) {
	Vector_ns<int> v;
	ASSERT_EQ(v.insert(10, 2), BOUNDS);
	ASSERT_EQ(v.insert(10, 0), SUCCESS);
	ASSERT_EQ(v.getSize(), 1);
	v.push_back(11);
	v.push_start(2);
	for (int i = 3; i < 10; i++)
		v.push_back(i);
	ASSERT_EQ(v.getSize(), 10);
	ASSERT_EQ(v[9], 9);
	ASSERT_EQ(v[0], 2);
	v.push_back(10);
	v.push_start(12);
	ASSERT_EQ(v[0], 12);
}


TEST(Vector, Remove) {
	Vector_ns<int> v(3);
	v[2] = 2;
	v.remove(0);
	ASSERT_EQ(v.getSize(), 2);
	v.pop_back();
	ASSERT_EQ(v[0], 0);
	v.push_back(12);
	v.pop_start();
	ASSERT_EQ(v[0], 12);
	ASSERT_EQ(v.remove(2), BOUNDS);
	v.remove(0);
	ASSERT_EQ(v.remove(0), BOUNDS);
}

TEST(Vector, Remove_Insert) {
	Vector_ns<int> v(1);
	v.pop_back();
	ASSERT_EQ(v.getSize(), 0);
	ASSERT_EQ(v.insert(2, 2), BOUNDS);
	ASSERT_EQ(v.pop_back(), BOUNDS);
	ASSERT_EQ(v.pop_start(), BOUNDS);
	v.push_start(1);
	ASSERT_EQ(v.getSize(), 1);
	ASSERT_EQ(v[0], 1);
}

TEST(Vector, Max_Min) {
	Vector_ns<int> v;
	v.push_back(1);
	ASSERT_EQ(v.maximum(), 1);
	ASSERT_EQ(v.minimum(), 1);
	v.insert(10, 0);
	ASSERT_EQ(v.maximum(), 10);
	ASSERT_EQ(v.minimum(), 1);
	v.push_start(12);
	v.push_back(3);
	v.insert(0, 2);
	ASSERT_EQ(v.maximum(), 12);
	ASSERT_EQ(v.minimum(), 0);
}

class Sorting : public ::testing::Test {
protected:
	void SetUp()
	{
		l_int.push_back(12);
		l_int.push_back(-2);
		l_int.push_back(3);
		l_int.push_back(13);
		l_int.push_back(4);
		l_int.push_back(0);
		l_int.push_back(7);
	}
	List1_ns<int> l_int;
};

TEST_F(Sorting, Bubble) {
	Bubble a;
	a.sort(l_int);
	ASSERT_EQ(l_int[0], -2);
	ASSERT_EQ(l_int[1], 0);
	ASSERT_EQ(l_int[2], 3);
	ASSERT_EQ(l_int[3], 4);
	ASSERT_EQ(l_int[4], 7);
	ASSERT_EQ(l_int[5], 12);
	ASSERT_EQ(l_int[6], 13);
}

TEST_F(Sorting, Selection) {
	Selection a;
	a.sort(l_int);
	ASSERT_EQ(l_int[0], -2);
	ASSERT_EQ(l_int[1], 0);
	ASSERT_EQ(l_int[2], 3);
	ASSERT_EQ(l_int[3], 4);
	ASSERT_EQ(l_int[4], 7);
	ASSERT_EQ(l_int[5], 12);
	ASSERT_EQ(l_int[6], 13);
}

TEST_F(Sorting, Insertion) {
	Insertion a;
	a.sort(l_int);
	ASSERT_EQ(l_int[0], -2);
	ASSERT_EQ(l_int[1], 0);
	ASSERT_EQ(l_int[2], 3);
	ASSERT_EQ(l_int[3], 4);
	ASSERT_EQ(l_int[4], 7);
	ASSERT_EQ(l_int[5], 12);
	ASSERT_EQ(l_int[6], 13);
}

TEST(BTree_mb, Insert) {
	BTree_mb<int, int> t;
	t.insert(5, 4);
	t.insert(2, 1);
	t.insert(12, 2);
	t.insert(7, 3);
	t.insert(3, 5);
	ASSERT_EQ(t.getNodeCount(), 5);
	ASSERT_EQ(t[2], 12);
	ASSERT_EQ(t[5], 3);
}

TEST(BTree_mb, Remove) {
	BTree_mb<int, int> t;
	ASSERT_EQ(t.remove(7), EMPTY);
	t.insert(1, 20);
	t.remove(20);
	ASSERT_EQ(t.remove(20), EMPTY);
	t.insert(1, 20);
	t.insert(2, 21);
	t.insert(3, 8);
	t.insert(4, 7);
	t.insert(5, 15);
	t.insert(6, 4);
	t.insert(5, 14);
	t.insert(5, 16);
	ASSERT_EQ(t.remove(12), NOT_FOUND);
	t.remove(21);
	ASSERT_EQ(t.getNodeCount(), 7);
	ASSERT_EQ(t[20], 1);
	t.remove(7);
	t.remove(8);
	ASSERT_EQ(t.getNodeCount(), 5);
	ASSERT_EQ(t[4], 6);
}

TEST(BTree_mb, Remove_String_Value) {
	BTree_mb<std::string, int> t;
	t.insert("first", 20);
	t.insert("second", 21);
	t.insert("third", 8);
	t.insert("fourth", 7);
	t.remove(21);
	ASSERT_EQ(t.getNodeCount(), 3);
	ASSERT_STREQ(t[20].c_str(), "first");
	t.remove(7);
	t.remove(8);
	ASSERT_EQ(t.getNodeCount(), 1);
}

TEST(BTree_mb, Remove_String_Value_Key) {
	BTree_mb<std::string, std::string> t;
	t.insert("first", "Melon");
	t.insert("second", "Apple");
	t.insert("third", "Berry");
	t.insert("fourth", "Orange");
	t.remove("Berry");
	ASSERT_EQ(t.getNodeCount(), 3);
	ASSERT_STREQ(t["Apple"].c_str(), "second");
	t.remove("Melon");
	t.remove("Apple");
	ASSERT_EQ(t.getNodeCount(), 1);
}

TEST(BTree_mb, Max_Min) {
	BTree_mb<int, int> t;
	t.insert(1, 20);
	t.insert(2, 21);
	t.insert(3, 8);
	t.insert(4, 7);
	ASSERT_EQ(t.minimum(), 1);
	ASSERT_EQ(t.maximum(), 4);
}

TEST(BTree_mb, Max_Min_String) {
	BTree_mb<std::string, int> t;
	t.insert("Orange", 20);
	t.insert("Lemon", 21);
	t.insert("Melon", 8);
	t.insert("Pear", 7);
	t.insert("Apple", 12);
	ASSERT_EQ(t.minimum(), "Apple");
	ASSERT_EQ(t.maximum(), "Pear");
}

TEST(BTree_mb, Height) {
	BTree_mb<int, int> t;
	t.insert(6, 6);
	t.insert(9, 9);
	t.insert(4, 4);
	t.insert(3, 3);
	t.insert(5, 5);
	ASSERT_EQ(t.getHeight(t.head->left), 2);
	ASSERT_EQ(t.getHeight(t.head->right), 1);
	t.insert(5, 11);
	t.insert(5, 14);
	ASSERT_EQ(t.getHeight(t.head->right), 3);
	t.insert(5, 15);
	t.insert(5, 13);
	ASSERT_EQ(t.getHeight(t.head->right), 4);
	t.insert(5, 2);
	ASSERT_EQ(t.getHeight(t.head->left), 3);
}

TEST(BTree_mb, Balancing) {
	BTree_mb<int, int> t;
	t.insert(6, 6);
	t.insert(2, 2);
	t.insert(4, 4);
	t.insert(3, 3);
	t.insert(5, 5);
	t.insert(1, 1);
	t.balanceTree();
	ASSERT_EQ(t.isTreeBalanced(), true);
	BTree_mb<int, int> t1;
	ASSERT_EQ(t1.balanceTree(), EMPTY);
	ASSERT_EQ(t1.isTreeBalanced(), false);
}

//checking correctness of insertion and structure of tree: left, right, parent nodes have to be correct
TEST(BTree_rb, Insert) {
	//right right
	BTree_rb<int, int> t1;
	t1.insert(10, 10);
	t1.insert(20, 20);
	t1.insert(30, 30);
	t1.insert(15, 15);
	ASSERT_EQ(t1.head->color, t1.black);
	ASSERT_EQ(t1.head->index, 20);
	ASSERT_EQ(t1.isTreeBalanced(), true);
	//left left
	BTree_rb<int, int> t2;
	t2.insert(30, 30);
	t2.insert(20, 20);
	t2.insert(10, 10);
	ASSERT_EQ(t2.head->color, t2.black);
	ASSERT_EQ(t2.head->index, 20);
	ASSERT_EQ(t2.head->left->index, 10);
	ASSERT_EQ(t2.isTreeBalanced(), true);
	//left right
	BTree_rb<int, int> t3;
	t3.insert(30, 30);
	t3.insert(20, 20);
	t3.insert(25, 25);
	ASSERT_EQ(t3.head->color, t3.black);
	ASSERT_EQ(t3.head->index, 25);
	ASSERT_EQ(t3.head->left->index, 20);
	ASSERT_EQ(t3.isTreeBalanced(), true);
	//right left
	BTree_rb<int, int> t4;
	t4.insert(20, 20);
	t4.insert(30, 30);
	t4.insert(25, 25);
	ASSERT_EQ(t4.head->color, t4.black);
	ASSERT_EQ(t4.head->index, 25);
	ASSERT_EQ(t4.head->right->index, 30);
	ASSERT_EQ(t4.head->right->color, t4.red);
	ASSERT_EQ(t4.isTreeBalanced(), true);
	//real example
	BTree_rb<int, int> t5;
	//black
	t5.insert(47, 47);
	//red
	t5.insert(32, 32);
	//red
	t5.insert(71, 71);
	//recoloring: all black instead of this
	t5.insert(93, 93);
	//red
	t5.insert(65, 65);
	//recoloring
	t5.insert(82, 82);
	//left right rotation
	t5.insert(87, 87);
	ASSERT_EQ(t5.count, 7);
	ASSERT_EQ(t5.head->right->color, t5.red);
	ASSERT_EQ(t5.head->right->right->value, 87);
	//another real example
	BTree_rb<int, int> t6;
	t6.insert(2, 2);
	t6.insert(1, 1);
	t6.insert(4, 4);
	t6.insert(5, 5);
	t6.insert(9, 9);
	t6.insert(3, 3);
	t6.insert(6, 6);
	t6.insert(7, 7);
	ASSERT_EQ(t6.count, 8);
	ASSERT_EQ(t6.head->right->color, t6.red);
	ASSERT_EQ(t6.head->right->right->color, t6.black);
	ASSERT_EQ(t6.head->right->right->left->color, t6.red);
	ASSERT_EQ(t6.head->right->right->left->value, 6);
	ASSERT_EQ(t6.head->right->right->value, 7);
	ASSERT_EQ(t6.head->right->left->value, 4);
	ASSERT_EQ(t6.head->right->left->color, t6.black);
	ASSERT_EQ(t6.head->left->value, 1);
	ASSERT_EQ(t6.head->right->left->left->color, t6.red);
	ASSERT_EQ(t6.head->right->left->left->value, 3);
}