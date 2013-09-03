/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * priority-queue.h
 * Copyright (C) 2013 Carl-Anton Ingmarsson <mail@carlanton.se>
 *
 * PriorityQueue is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * PriorityQueue is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include <vector>

namespace cai
{

template<typename T>
class PriorityQueue
{
public:
  typedef T value_type;
  typedef typename std::vector<T>::const_iterator const_iterator;

  PriorityQueue(std::size_t);

  const_iterator begin() const { return a_.begin(); }
  const_iterator end() const { return a_.end(); }

  void add(int key, const T& item);

  void change(int key, const T& item);

  T delMax();

protected:

private:
  PriorityQueue(const PriorityQueue& a);

  void exch(std::size_t i1, std::size_t i2);
  void swim(std::size_t i);
  void sink(std::size_t i);

  std::vector<ssize_t> keyToPos_;
  std::vector<size_t> posToKey_;
  std::vector<T> a_;
};

}

#endif // _PRIORITY_QUEUE_H_
