#include <stdarg.h>
#include <stdio.h>

#include "report_system.h"
#include "utils.h"

void report_system::print (const report_system::log_type &type, const char *format, ...)
{
  log_count[type]++;
  std::string time = pt::to_simple_string (sbot::curr_time ());

  printf ("[%s] [%s] ", enum_to_string (type), time.c_str ());
  //log_files[type] << "[" << enum_to_string (type) << "] " << "[" << time << "] ";

  va_list args;
  va_start (args, format);

  vprintf (format, args);
  //log_files[type] << args;

  va_end (args);

  printf ("\n");
  //log_files[type] << std::endl;
}

void report_system::print (const char *format, ...)
{
  va_list args;
  va_start (args, format);
  vprintf (format, args);
  va_end (args);
}

void report_system::print (FILE *stream, const char *format, ...)
{
  va_list args;
  va_start (args, format);
  vfprintf (stream, format, args);
  va_end (args);
}

const char *report_system::enum_to_string (const report_system::log_type &type)
{
  switch (type)
    {
    case info:
      return "INFO";

    case message:
      return "MESSAGE";

    case warning:
      return "WARNING";

    case error:
      return "ERROR";
    }
  return "INVALID";
}
