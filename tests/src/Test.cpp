#define GMOCK_DEBUG

#include <gtest/gtest.h>
#include "List.h"
#include "Vector.h"
#include "Sort.h"
#include "Map.h"

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
//	::testing::GTEST_FLAG(filter) = "Vector_cns.Insert";
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


TEST(Bubble, List1_ns) {
	List1_ns<int> l;
	l.push_back(12);
	l.push_back(-2);
	l.push_back(3);
	l.push_back(13);
	l.push_back(4);
	l.push_back(0);
	l.push_back(7);
	Bubble a;
	a.sort(l);
	ASSERT_EQ(l[0], -2);
	ASSERT_EQ(l[1], 0);
	ASSERT_EQ(l[2], 3);
	ASSERT_EQ(l[3], 4);
	ASSERT_EQ(l[4], 7);
	ASSERT_EQ(l[5], 12);
	ASSERT_EQ(l[6], 13);
}

TEST(BTree_nb, insert) {
	BTree_nb<int> t;
	t.insert(12, 4);
	t.insert(12, 1);
	t.insert(12, 2);
	t.insert(12, 3);
	t.insert(12, 5);
}