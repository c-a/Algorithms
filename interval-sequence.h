/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 8 -*-  */
/*
 * interval-sequence.h
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

#ifndef _INTERVAL_SEQUENCE_H_
#define _INTERVAL_SEQUENCE_H_

#include <istream>

namespace cai
{

class IntervalSequence
{
public:
  struct Interval
  {
    int start;
    int end;

    Interval(int s, int e) : start(s), end(e) {};

    bool intersects(Interval& interval) {
      return (end >= interval.start && interval.end >= start);
    }
  };

  typedef std::list<Interval>::const_iterator const_iterator;

  IntervalSequence();
  IntervalSequence(std::istream is);

  void add(int start, int end);

  const_iterator begin() { return intervals_.begin(); }
  const_iterator end() { return intervals_.end(); }

private:
  std::list<Interval> intervals_;
};

};

#endif // _INTERVAL_SEQUENCE_H_

