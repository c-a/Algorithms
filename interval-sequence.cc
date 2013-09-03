/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 8 -*-  */
/*
 * interval-sequence.cc
 * Copyright (C) 2013 Carl-Anton Ingmarsson <mail@carlanton.se>
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

#include <algorithm>
#include <list>
#include <sstream>
#include <stdexcept>
#include <istream>
#include <iostream>
#include <iterator>

#include "interval-sequence.h"

namespace cai
{

IntervalSequence::IntervalSequence() :
  intervals_()
{
}

IntervalSequence::IntervalSequence(std::istream is) :
  intervals_()
{
  std::string s;

  while (std::getline(is, s))
  {
    int start, end;
    std::istringstream sstream(s);

    sstream >> start >> end;
    add(start, end);
  }
}

void
IntervalSequence::add(int start, int end)
{
  if (end <= start)
    throw std::runtime_error("Start must be less than end");

  Interval new_interval(start, end);

  // Insert at beggining
  if (intervals_.begin() == intervals_.end() ||
      end < (*intervals_.begin()).start)
  {
    intervals_.push_front(new_interval);
    return;
  }

  for (auto iter = intervals_.begin(); iter != intervals_.end(); ++iter)
  {
    // Merge with intersecting
    if (new_interval.intersects(*iter))
    {
      start = std::min(start, (*iter).start);
      end = std::max(end, (*iter).end);

      // Remove succeding 
      auto riter = iter;
      ++riter;
      while (riter != intervals_.end() && new_interval.intersects(*riter))
      {
        end = std::max(end, (*riter).end);
        riter = intervals_.erase(riter);
      }
      (*iter).start = start;
      (*iter).end = end;
      break;
    }

    // Insert interval
    else if (start > (*iter).end)
    {
      auto niter = iter;
      ++niter;

      if (niter == intervals_.end())
      {
        intervals_.push_back(new_interval);
        break;
      }
      else if (end < (*niter).start)
      {
        intervals_.insert(niter, new_interval);
        break;
      }
    }
  }
}

};

int main(int argc, char *argv[])
{
  cai::IntervalSequence is;

  is.add(0,1);
  is.add(1,3);
  is.add(4,5);

  for (auto iter = is.begin(); iter != is.end(); ++iter)
    std::cout << '(' << (*iter).start << ',' << (*iter).end << ')' << std::endl;

}