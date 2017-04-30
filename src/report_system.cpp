#include <stdarg.h>
#include <stdio.h>
#include <exception>

#include "report_system.h"
#include "utils.h"

void report_system::print (const report_system::log_type &type, const char *format, ...)
{
  size_t printed_length = 0;
  int length;
  std::string time = pt::to_simple_string (sbot::curr_time ());

  // Print string to buffer
  length =  snprintf (buf + printed_length, sbot::buf_size - printed_length, "[%s] [%s] ", enum_to_string (type), time.c_str ());
  printed_length += length;

  va_list args;
  va_start (args, format);
  length = vsnprintf (buf + printed_length, sbot::buf_size - printed_length, format, args);
  printed_length += length;
  va_end (args);

  if (length < 0)
    {
      throw std::invalid_argument ("Wrong print arguments, check format");
    }

  length =  snprintf (buf + printed_length, sbot::buf_size - printed_length, "\n");
  printed_length += length;

  if (printed_length >= sbot::buf_size)
    {
      throw std::overflow_error ("Buf size too small");
    }

  // Print buffer into streams
  log_count[type]++;

  log_files[type] << buf;

  if (type == warning || type == error)
    {
      print_error (buf);
    }
  else if (type != message_out)
    {
      print (buf);
    }
}

void report_system::print (const char *format, FILE *stream)
{
  fprintf (stream, format);
}

void report_system::print_error (const char *format)
{
  print (format, stderr);
}

const char *report_system::enum_to_string (const report_system::log_type &type)
{
  switch (type)
    {
      case info:
        return "INFO";

      case message_in:
        return "MSG_IN";

      case message_out:
        return "MSG_OUT";

      case warning:
        return "WARNING";

      case error:
        return "ERROR";

      case count:
        return "INVALID";
    }

  return "INVALID";
}
