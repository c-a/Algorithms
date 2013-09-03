/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * priority-queue.cc
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

#include <iostream>
#include <stdexcept>

#include <stdlib.h>

#include "priority-queue.h"

namespace cai
{

template<typename T>
void
PriorityQueue<T>::exch(std::size_t i1, std::size_t i2)
{
  size_t key1 = posToKey_[i1];
  size_t key2 = posToKey_[i2];

  keyToPos_[key1] = i2;
  keyToPos_[key2] = i1;

  posToKey_[i1] = key2;
  posToKey_[i2] = key1;
}

template<typename T>
void
PriorityQueue<T>::swim(std::size_t i)
{
  std::size_t p;

  p = i/2 + (i%2 - 1);
  while (i > 0 && a_[posToKey_[p]] < a_[posToKey_[i]])
  {
    exch(i, p);
    i = p;
    p = i/2 + (i%2 - 1);
  }
}

template<typename T>
void
PriorityQueue<T>::sink(std::size_t i)
{
  while (2*i + 1 < posToKey_.size())
  {
    std::size_t c = 2*i + 1;
    if ((c+1) < posToKey_.size() && a_[posToKey_[c]] < a_[posToKey_[c+1]])
      c++;
    if (a_[posToKey_[c]] < a_[posToKey_[i]]) break;

    exch(i, c);
    i = c;
  }
}

template<typename T>
PriorityQueue<T>::PriorityQueue(std::size_t size)
{
  keyToPos_.resize(size, -1);
  posToKey_.reserve(size);
  a_.resize(size, 0);
}

template<typename T>
void
PriorityQueue<T>::add(int key, const T& item)
{
  keyToPos_[key] = posToKey_.size();
  posToKey_.push_back(key);
  a_[key] = item;

  swim(posToKey_.size()-1);
}

template<typename T>
void
PriorityQueue<T>::change(int key, const T& item)
{
  std::size_t pos = keyToPos_[key];
  if (item < a_[key]) {
    a_[key] = item;
    sink(pos);
  }
  else if (item > a_[key]) {
    a_[key] = item;
    swim(pos);
  }
}

template<typename T>
T
PriorityQueue<T>::delMax()
{
  if (posToKey_.size() == 0) throw std::runtime_error("Empty");

  size_t max = posToKey_[0];
  posToKey_[0] = posToKey_.back();
  posToKey_.pop_back();
  sink(0);

  return a_[max];
}

}

int
main (int argc, char *argv[])
{
  cai::PriorityQueue<int> q(1000);

  for (int i = 0; i < 1000; i++)
    q.add(i, i);

  q.change(0, 1001);
  q.change(999, -1);

  for (int i = 0; i < 1000; i++)
    std::cout << q.delMax() << std::endl;

  return 0;
}
