/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * sort.cc
 *
 * Copyright (C) 2013 - Carl-Anton Ingmarsson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

#include <iterator>
#include <iostream>

#include "sort.h"

namespace cai
{

template<typename RandomAccessIterator>
void
InsertSort(RandomAccessIterator first, RandomAccessIterator last) {
  typedef std::iterator_traits<RandomAccessIterator> traits;

  if (first == last)
    return;

  for (RandomAccessIterator i = first + 1; i != last; ++i) {
    typename traits::value_type v = *i;

    RandomAccessIterator j = i;
    while (j > first && j[-1] > v) {
      j[0] = j[-1];
      j--;
    }
    j[0] = v;
  }
}

template<typename T>
static inline void
Swap(T& a, T& b)
{
  T v = a;
  a = b;
  b = v;
}

template<typename RandomAccessIterator>
static inline RandomAccessIterator
MedianOfThree(RandomAccessIterator first, RandomAccessIterator last) {
  typedef std::iterator_traits<RandomAccessIterator> traits;
  typename traits::difference_type mid;

  mid = (last - first) / 2;

  /* Puts smallest vallue first, biggest value in the middle and the
   middle value last */
  if (last[-1] < first[0])
    Swap(last[-1], first[0]);
  if (first[mid] < first[0])
    Swap(first[mid], first[0]);
  if (last[-1] < first[mid])
    Swap(last[-1], first[mid]);

  return first + mid;
}

template<typename RandomAccessIterator>
static inline RandomAccessIterator
TwoWayPartition(RandomAccessIterator first, RandomAccessIterator last) {
  RandomAccessIterator l, r;

  l = first; r = last-2;
  while (true) {
    while (*(++l) < last[-1]);
    while (*(--r) > last[-1]);

    if (l >= r)
      break;

    Swap(*l, *r);
  }

  Swap(*l, last[-1]);

  return l;
}

template<typename RandomAccessIterator>
void TwoPQuickSort(RandomAccessIterator first, RandomAccessIterator last) {

  RandomAccessIterator m, p;

  /* Use insertion sort for size smaller than or equal to seven */
  if ((last - first) <= 7) {
    InsertSort(first, last);
    return;
  }

  m = MedianOfThree(first, last);
  /* Put median last and biggest value next last as a sentinel */
  Swap(last[-1], last[-2]);
  Swap(*m, last[-1]);

  p = TwoWayPartition(first, last);

  TwoPQuickSort(first, p);
  TwoPQuickSort(p+1, last);
}

template<typename RandomAccessIterator>
static inline void
ThreeWayPartition(RandomAccessIterator first, RandomAccessIterator last,
                  RandomAccessIterator& lt, RandomAccessIterator& rt) {
  RandomAccessIterator i;

  lt = first+1; i = first + 2; rt = last - 1;
  while (i < rt) {
    if (*i < *lt)
      Swap(*i++, *lt++);
    else if (*i > *lt)
      Swap(*i, *(--rt));
    else
      ++i;
  }
}

template<typename RandomAccessIterator>
void ThreePQuickSort(RandomAccessIterator first, RandomAccessIterator last) {

  RandomAccessIterator m, lt, rt;

  /* Use insertion sort for size smaller than or equal to seven */
  if ((last - first) <= 3) {
    InsertSort(first, last);
    return;
  }

  m = MedianOfThree(first, last);

  Swap(first[1], *m);
  ThreeWayPartition(first, last, lt, rt);

  ThreePQuickSort(first, lt);
  ThreePQuickSort(rt, last);
}

}

int
main(int argc, char* argv[]) {
  char str[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaa";

  cai::ThreePQuickSort(str, str + strlen(str));

  std::cout << str << std::endl;

  return 0;
}