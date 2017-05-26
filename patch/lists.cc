// Author: Finn Hackett (Jan 2017)
/**
You can change this file by adding additional tests but don't
remove any existing tests.

To add tests, add a TEST_CASE block like this at the end of the file:
TEST_CAST("my_tests"){
  auto l = make_rlist({1,2,3});
  SECTION("section_1"){
    // assert what you want to assert
    REQUIRE(to_vector(l) == (vec{3,2,1}));
    // mess with your variables
    remove_last_element(l);
  }
  // each SECTION starts fresh - even though the previous section
  // deletes an element of l, l is recreated for section 2
  SECTION("section_2"){
    REQUIRE(to_vector(l) == (vec{3,2,1}));
  }
}
*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <initializer_list>
#include "linked_list.h"

/**
Warning: If you are new to C++, this class is a little "magical".

It manages a Node* so you don't have to clean up after yourself.
It also converts to Node*& so you can just pass it to functions you want to test and it "just works".

Examples:
// these two lines do the same thing (a or b are null)
node_manager a = nullptr;
auto b = node_manager{};

// this "just works"
insert(a, 2);
insert(a, 3);
insert(b, 4);

// wrap the result of interleave for extra convenience
auto c = node_manage{interleave(a,b)};

// this won't compile (because it makes no sense even if pointers let you do this):
b = a; // if this worked you would have two pointers to one list
*/
class node_manager{
  Node* ptr;
  void cleanup(){
    while(ptr){
      delete_last_element(ptr);
    }
  }
public:
  node_manager(Node* ptr = nullptr): ptr{ptr}{}
  operator Node*&(){
    return ptr;
  }
  node_manager(const node_manager&) = delete;
  node_manager(node_manager&& other){
    ptr = other.ptr;
    other.ptr = nullptr;
  }
  node_manager& operator=(const node_manager&) = delete;
  node_manager& operator=(node_manager&& other){
    cleanup();
    ptr = other.ptr;
    other.ptr = nullptr;
    return *this;
  }
  ~node_manager(){
    cleanup();
  }
};

using vec = std::vector<int>;

/**
This is a utility to create lists. Note: the lists it creates is in reverse order.

Example:
// l is a list with values: 3 2 1
auto l = make_rlist({1,2,3});
*/
node_manager make_rlist(const std::initializer_list<int>& elements){
  auto tmp = node_manager{};
  for(int v: elements){
    insert(tmp, v);
  }
  return tmp;
}

TEST_CASE("empty_list"){
  auto list = node_manager{};
  SECTION("do nothing"){
    // nothing
  }
  SECTION("remove_last_element"){
    delete_last_element(list);
    REQUIRE(to_vector(list) == (vec{}));
  }
  SECTION("insert_after_missing_element"){
    insert_after(list, 1, 3);
    REQUIRE(to_vector(list) == (vec{}));
  }
  SECTION("remove_missing_element"){
    remove(list, 2);
    REQUIRE(to_vector(list) == (vec{}));
  }
}

TEST_CASE("list_with_one_element"){
  auto list = make_rlist({1});
  REQUIRE(to_vector(list) == (vec{1}));
  SECTION("do_nothing"){
    // nothing
  }
  SECTION("remove_last_element"){
    delete_last_element(list);
    REQUIRE(to_vector(list) == (vec{}));
  }
  SECTION("insert_after_existing_element"){
    insert_after(list, 1, 2);
    REQUIRE(to_vector(list) == (vec{1,2}));
  }
  SECTION("insert_after_missing_element"){
    insert_after(list, 2, 3);
    REQUIRE(to_vector(list) == (vec{1}));
  }
  SECTION("remove_existing_element"){
    remove(list, 1);
    REQUIRE(to_vector(list) == (vec{}));
  }
  SECTION("remove_missing_element"){
    remove(list, 2);
    REQUIRE(to_vector(list) == (vec{1}));
  }
}

TEST_CASE("more_than_one_element"){
  auto list = make_rlist({1,2,3});
  REQUIRE(to_vector(list) == (vec{3,2,1}));
  SECTION("do nothing"){
    // nothing
  }
  SECTION("remove_last_element"){
    delete_last_element(list);
    REQUIRE(to_vector(list) == (vec{3,2}));
  }
  SECTION("insert_after_existing_element_in_middle"){
    insert_after(list, 1, 6);
    REQUIRE(to_vector(list) == (vec{3,2,6,1}));
  }
  SECTION("insert_after_existing_element at_beginning"){
    insert_after(list, 2, 6);
    REQUIRE(to_vector(list) == (vec{3,6,2,1}));
  }
  SECTION("insert_after_existing_element_at_end"){
    insert_after(list, 1, 6);
    REQUIRE(to_vector(list) == (vec{3,2,1,6}));
  }
  SECTION("insert_after_missing_element"){
    insert_after(list, 4, 3);
    REQUIRE(to_vector(list) == (vec{3,2,1}));
  }
  SECTION("remove_existing_element_at_end"){
    remove(list, 1);
    REQUIRE(to_vector(list) == (vec{3,2}));
  }
  SECTION("remove_existing_element_in_middle"){
    remove(list, 2);
    REQUIRE(to_vector(list) == (vec{3,1}));
  }
  SECTION("remove_missing_element_at_beginning"){
    remove(list, 3);
    REQUIRE(to_vector(list) == (vec{2,1}));
  }
  SECTION("remove_missing_element"){
    remove(list, 4);
    REQUIRE(to_vector(list) == (vec{3,2,1}));
  }
}

TEST_CASE("interleaving"){
  auto list1 = make_rlist({3,2,1});
  auto list2 = make_rlist({6,5,4});
  SECTION("empty_with_empty"){
    auto list3 = node_manager{interleave(nullptr, nullptr)};
    REQUIRE(to_vector(list3) == (vec{}));
  }
  SECTION("elements_with_empty"){
    auto list3 = node_manager{interleave(list1,nullptr)};
    REQUIRE(to_vector(list3) == (vec{1,2,3}));
  }
  SECTION("empty_with_elements"){
    auto list3 = node_manager{interleave(nullptr,list2)};
    REQUIRE(to_vector(list3) == (vec{4,5,6}));
  }
  SECTION("both_with_elements"){
    auto list3 = node_manager{interleave(list1,list2)};
    REQUIRE(to_vector(list3) == (vec{1,4,2,5,3,6}));
  }
}
