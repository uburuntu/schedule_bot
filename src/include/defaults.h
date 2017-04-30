#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <string>
#include <stdint.h>

typedef int64_t user_id;

namespace sbot
{
  static const std::string program = "Schedule Bot";
  static const std::string version = "0.0.3";

  static const std::string prefix_dir = "./sbot/";
  static const std::string build_date = __DATE__;
  static const std::string build_time = __TIME__;

  static const std::string empty_line = "\n\n";

  static const user_id r_id = 28006241;
  static const user_id a_id = 3191519;
  static const user_id v_id = 173546332;
}

#endif // DEFAULTS_H
