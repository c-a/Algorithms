/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * list.h
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

#ifndef _LIST_H_
#define _LIST_H_

#include <iterator>

namespace cai
{

template<typename ValueType>
class List
{
private:
  struct Node;
  class ListIterator;
  class ConstListIterator;

public:
  typedef ValueType value_type;
  typedef ListIterator iterator;
  typedef ConstListIterator const_iterator;

  List() : start_(0), end_(0) {};

  iterator begin() {
    return iterator(start_);
  }

  iterator end() {
    return iterator(0);
  }

  const_iterator begin() const {
    return const_iterator(start_);
  }

  const_iterator end() const {
    return const_iterator(0);
  }

  void prepend(const value_type& value) {
    Node* n = new Node(value, start_, 0);
    if (start_ != 0)
      start_->prev = n;
    else
      end_ = n;

    start_ = n;
  }

  void append(const value_type& value) {
    Node* n = new Node(value, 0, end_);
    if (end_ != 0)
      end_->next = n;
    else
      start_ = n;

    end_ = n;
  }

  iterator insert(iterator position, const value_type& value) {
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

  void sort() {
    start_ = sort(start_);
  }

protected:

private:

  static Node* sort(Node* list) {
    if (!list)
      return 0;

    if (list->next == 0)
      return list;

    Node* middle = findMiddle(list);
    middle->prev->next = 0;

    return(merge(sort(list), sort(middle)));
  }

  static Node* findMiddle(Node* n) {
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

  static Node* merge(Node* l1, Node* l2) {
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

  struct Node
  {
    Node(const value_type& v, Node* n, Node* p) : value(v), next(n), prev(p) {};

    value_type value;
    Node* next;
    Node* prev;
  };

  class ListIterator :
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

  class ConstListIterator :
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

  friend ListIterator;
  friend ConstListIterator;
  
  Node* start_;
  Node* end_;
};


}

#endif // _LIST_H_

