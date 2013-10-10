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

  void prepend(const value_type& value);
  void append(const value_type& value);

  iterator insert(iterator position, const value_type& value);

  void sort() {
    start_ = sort(start_);
  }

protected:

private:
  struct Node;

  static Node* sort(Node* list);
  static Node* findMiddle(Node* n);
  
  static Node* merge(Node* l1, Node* l2);

  Node* start_;
  Node* end_;
};


}

#endif // _LIST_H_

