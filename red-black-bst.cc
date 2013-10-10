/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * red-black-bst.cc
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

#include <stdlib.h>

#include "red-black-bst.h"


int compare(int a, int b)
{
  return a-b;
}

int
main (int argc, char *argv[])
{
  RedBlackBST<int, int, int (&)(int a, int b) > bst(compare);
  int i;
  RedBlackBST<int, int, int (&)(int a, int b) >::const_iterator iter;

  for (i = 0; i < 1000; i++)
    bst.put(i, i);

  bst.print(std::cout);

  std:: cout << "IsRedBlackBST: " << bst.isRedBlackBST() << std::endl;

  srandom(204);
  for (i = 0; i < 990; i++) {
    long int i = (random() * 999) / RAND_MAX;
    bst.remove(i);
  }

  bst.print(std::cout);

  std:: cout << "IsRedBlackBST: " << bst.isRedBlackBST() << std::endl;

  return 0;
}