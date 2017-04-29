#ifndef UTILS_H
#define UTILS_H

#include "boost/date_time/posix_time/posix_time.hpp"

namespace pt = boost::posix_time;

namespace sbot
{
  template<typename T>
  static void fix_unused (const T &) {}

  static void do_nothing () {}

  static void switch_bool (bool &a)
  {
    a = !a;
  }

  static pt::ptime curr_time ()
  {
    return pt::second_clock::local_time ();
  }
}

#endif // UTILS_H
