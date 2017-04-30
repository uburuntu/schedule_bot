#ifndef REPORT_SYSTEM_H
#define REPORT_SYSTEM_H

#include <fstream>
#include <memory>
#include <sys/stat.h>
#include "defaults.h"

class report_system
{
  public:
    report_system ()
    {
      mkdir (sbot::prefix_dir.c_str (), S_IRWXU | S_IRWXG | S_IRWXO);
      for (int type = (int) info; type < (int) count; type++)
        {
          // TODO: realize checks
          //log_files[type].open (sbot::prefix_dir + enum_to_string ((log_type) type) + ".log", std::ios_base::out | std::ios_base::app);
        }
    }
    ~report_system ()
    {
      for (int type = (int) info; type < (int) count; type++)
        {
          //log_files[type] << "[END] Total " << enum_to_string ((log_type) type) << ": " << log_count[type];
          //log_files[type].close ();
        }
    }

    enum log_type
    {
      info,
      message,
      warning,
      error,

      count = error
    };

    void print (const log_type &type, const char *format, ...);

    static void print (const char *format, ...);
    static void print (FILE *stream, const char *format, ...);

    static const char *enum_to_string (const log_type &type);

  private:
    long long int log_count[log_type::count] = {};
    //std::fstream log_files[log_type::count];
};

using rep = report_system;
using rep_ptr = std::shared_ptr<report_system>;

#endif // REPORT_SYSTEM_H
