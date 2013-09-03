/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * sort.h
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

namespace cai
{

  template<typename RandomAccessIterator>
  void TwoPQuickSort(RandomAccessIterator first, RandomAccessIterator last);

  template<typename RandomAccessIterator>
  void InsertSort(RandomAccessIterator first, RandomAccessIterator last);
}