#ifndef REPORT_SYSTEM_H
#define REPORT_SYSTEM_H

#include <fstream>
#include <memory>
#include <sys/stat.h>
#include "defaults.h"
#include "utils.h"

class report_system
{
  public:
    SINGLETON_CLASS (report_system);

    enum log_type
    {
      info,
      message_in,
      message_out,
      warning,
      error,

      count
    };

    void print (const log_type &type, const char *format, ...);

    static void print (const char *format, FILE *stream = stdout);
    static void print_error (const char *format);

    static const char *enum_to_string (const log_type &type);

  private:
    report_system ()
    {
      mkdir (sbot::prefix_dir.c_str (), S_IRWXU | S_IRWXG | S_IRWXO);

      for (int type = (int) info; type < (int) count; type++)
        {
          // TODO: realize checks
          log_files[type].open (sbot::prefix_dir + enum_to_string ((log_type) type) + ".log", std::ios_base::out | std::ios_base::app);
        }
    }
    report_system (const report_system &) = delete;
    report_system operator= (const report_system &) = delete;

    ~report_system ()
    {
      std::string time = pt::to_simple_string (sbot::curr_time ());
      for (int type = (int) info; type < (int) count; type++)
        {
          log_files[type] << "[END] [" + time + "] Total " << enum_to_string ((log_type) type) << ": " << log_count[type] << sbot::empty_line;
          log_files[type].close ();
        }
    }

    char buf[sbot::buf_size] = {};

    long long int log_count[log_type::count] = {};
    std::fstream log_files[log_type::count];
};

using rep = report_system;
using rep_ptr = std::shared_ptr<report_system>;

#endif // REPORT_SYSTEM_H
