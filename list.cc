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

int main(int argc, char* argv[])
{
  int i;
  cai::List<int> l;
  cai::List<int>::iterator iter;
  cai::List<int>::const_iterator citer;

  for (i = 0; i < 10000; i++)
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