#include "gtest/gtest.h"
#include "Node.hpp"

namespace {
  TEST(NodePointers, Initial) {
    Node* x = new Node();

    EXPECT_TRUE(x->get_up() == x);
    EXPECT_TRUE(x->get_right() == x);
    EXPECT_TRUE(x->get_left() == x);
    EXPECT_TRUE(x->get_down() == x);
  }

  TEST(NodePush, DownOneNode) {
    Node* first = new Node();
    Node *x = new Node();

    x->push_down(first);

    EXPECT_TRUE(x->get_up() == first);
    EXPECT_TRUE(x->get_down() == first);
    EXPECT_TRUE(first->get_up() == x);
    EXPECT_TRUE(first->get_down() == x);
    EXPECT_TRUE(x->get_up()->get_up() == x);

  }

  TEST(NodePush, UpOneNode) {
    Node* first = new Node();
    Node *x = new Node();

    x->push_up(first);

    EXPECT_TRUE(x->get_up() == first);
    EXPECT_TRUE(x->get_down() == first);
    EXPECT_TRUE(first->get_up() == x);
    EXPECT_TRUE(first->get_down() == x);
    EXPECT_TRUE(x->get_up()->get_up() == x);
  }

  TEST(NodePush, UpTwoNodes) {
    Node* first = new Node();
    Node* second = new Node();
    Node *x = new Node();

    x->push_up(first);
    x->push_up(second);

    EXPECT_TRUE(x->get_up() == second);
    EXPECT_TRUE(x->get_down() == first);
    EXPECT_TRUE(x->get_down()->get_down() == second);
    EXPECT_TRUE(x->get_up()->get_up() == first);
    EXPECT_TRUE(x->get_down()->get_down()->get_down() == x);
  }
}
