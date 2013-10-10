/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * list.cc
 * Copyright (C) 2013 Carl-Anton Ingmarsson <c-a@boxen>
 *
 * Algorithms is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Algorithms is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#include "list.h"

namespace cai
{

template<typename ValueType>
struct List<ValueType>::Node
{
  Node(const value_type& v, Node* n, Node* p) : value(v), next(n), prev(p) {};

  value_type value;
  Node* next;
  Node* prev;
};

template<typename ValueType>
void
List<ValueType>::prepend(const value_type& value) {
  Node* n = new Node(value, start_, 0);
  if (start_ != 0)
    start_->prev = n;
  else
    end_ = n;

  start_ = n;
}

template<typename ValueType>
void
List<ValueType>::append(const value_type& value) {
  Node* n = new Node(value, 0, end_);
  if (end_ != 0)
    end_->next = n;
  else
    start_ = n;

  end_ = n;
}

template<typename ValueType>
typename List<ValueType>::iterator
List<ValueType>::insert(iterator position, const value_type& value) {
  if (position.node_ == 0) {
    append(value);
    position.node_ = end_;
  }
  else if (position.node_->prev == 0) {
    prepend(value);
    position.node_ = end_;
  }
  else {
    Node *n = new Node(value, position.node_, position.node_->prev);

    position.node_->prev->next = n;
    position.node_->prev = n;
    position.node_ = n;
  }

  return position;
}

template<typename ValueType>
typename List<ValueType>::Node*
List<ValueType>::findMiddle(Node* n) {
  Node *slow, *fast;

  slow = fast = n;
  while (fast->next) { 
    slow = slow->next;
    if (fast->next->next == 0) {
      break;
    }
    fast = fast->next->next;
  }

  return slow;
}

template<typename ValueType>
typename List<ValueType>::Node* List<ValueType>::merge(Node* l1, Node* l2) {
  Node *head, *tail;

  #define APPEND(l) do { \
    tail->next = l; \
    l->prev = tail; \
    tail = l; \
    l = l->next; \
  } while (0)

  if (l1->value <= l2->value) {
    head = l1;
    tail = l1;
    l1 = l1->next;
  }
  else {
    head = l2;
    tail = l2;
    l2 = l2->next;
  }

  while (l1 != 0 || l2 != 0) {
    if (l1 != 0 && l2 != 0) {
      if (l1->value <= l2->value)
        APPEND(l1);
      else
        APPEND(l2);
    }
    else if (l1 != 0)
      APPEND(l1);
    else
      APPEND(l2);
  }

  head->prev = 0;
  tail->next = 0;

  return head;
}

template<typename ValueType>
typename List<ValueType>::Node*
List<ValueType>::sort(Node* list) {
  if (!list)
    return 0;

  if (list->next == 0)
    return list;

  Node* middle = findMiddle(list);
  middle->prev->next = 0;

  return(merge(sort(list), sort(middle)));
}

template<typename ValueType>
class List<ValueType>::ListIterator :
  std::iterator<std::forward_iterator_tag, ValueType>
{
public:
    ListIterator() : node_(0) {};

  ValueType& operator*() {
    return node_->value;
  }

  bool operator!=(const ListIterator& rhs) const {
    return node_ != rhs.node_;
  }

  ListIterator& operator++() {
    node_ = node_->next;
    return *this;
  }

private:
  friend class List;

  Node* node_;

  ListIterator(Node* const node) : node_(node) {};
};

template<typename ValueType>
class List<ValueType>::ConstListIterator :
  std::iterator<std::forward_iterator_tag, ValueType>
{
public:
  ConstListIterator() : node_(0) {};

  ConstListIterator(const ListIterator& iter) : node_(iter.node_) {};

  const ValueType& operator*() const {
    return node_->value;
  }

  bool operator!=(const ConstListIterator& rhs) const {
    return node_ != rhs.node_;
  }

  ConstListIterator& operator++() {
    node_ = node_->next;
    return *this;
  }

private:
  friend class List;

  const Node* node_;

  ConstListIterator(Node* const node) : node_(node) {};
};

};

int main(int argc, char* argv[])
{
  int i;
  cai::List<int> l;
  cai::List<int>::iterator iter;
  cai::List<int>::const_iterator citer;

  for (i = 0; i < 10; i++)
    l.append(i);

#if 0
  for (iter = l.begin(); iter != l.end(); ++iter) {
    std::cout << *iter << std::endl;
  }
#endif

  l.insert(l.begin(), 20);
  l.insert(l.end(), -20);

  for (i = 0, iter = l.begin(); iter != l.end(); ++i, ++iter) {
    if (i == 5)
      iter = l.insert(iter, 100);
  }

#if 0
  for (citer = l.begin(); citer != l.end(); ++citer) {
    std::cout << *citer << std::endl;
  }
#endif

  l.sort();
  for (citer = l.begin(); citer != l.end(); ++citer) {
    std::cout << *citer << std::endl;
  }

  return 0;
}