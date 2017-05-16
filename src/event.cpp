#include "event.h"

event_t::event_t (pt::ptime date_time_arg, std::string &name_arg, event_type etype_arg)
  : event_date_time (date_time_arg), name (name_arg), etype (etype_arg)
{

}

event_t::~event_t ()
{
  event_date_time = pt::not_a_date_time;
  name.clear ();
  default_note.clear ();
  user_note.clear ();
}

//should be copying everywhere
event_t::event_t (const event_t &rhs)
  : event_date_time (rhs.event_date_time), name (rhs.name),
    etype (rhs.etype), place (rhs.place),
    default_note (rhs.default_note), user_note (rhs.user_note)
{

}

//should be copying everywhere
event_t &event_t::operator= (const event_t &rhs)
{
  event_date_time = rhs.event_date_time;
  name = rhs.name;
  etype = rhs.etype;
  place = rhs.place;
  default_note = rhs.default_note;
  user_note = rhs.user_note;
  return *this;
}

bool event_t::operator== (const event_t &rhs) const
{
  return name == rhs.name &&
         event_date_time == rhs.event_date_time &&
         etype == rhs.etype;
}

bool event_t::operator< (const event_t &rhs) const
{
  return event_date_time < rhs.event_date_time;
}

bool event_t::operator> (const event_t &rhs) const
{
  return event_date_time > rhs.event_date_time;
}

const boost::gregorian::date::day_of_week_type event_t::get_weekday () const
{
  return event_date_time.date ().day_of_week ();
}

int event_t::set_repeat_interval (pt::time_duration repeat_interval_arg)
{
  if (repeat_interval_arg < pt::minutes (1))
    return -1;
  repeat_interval = repeat_interval_arg;
  return 0;
}

const char *event_t::enum_to_string (const event_t::event_type &type)
{
  switch (type)
    {
      case lecture:
        return "Lecture";

      case seminar:
        return "Seminar";

      case spec_lecture:
        return "Special Lecture";

      case spec_seminar:
        return "Special Seminar";

      case other:
        return "Other";

      case COUNT:
        {}
    }

  return "INVALID";
}

int event_t::add_user_note (std::string &added_user_note)
{
  if (added_user_note.size () + user_note.size () > MAX_USER_NOTE_SIZE)
    return -1;
  std::string t (" ");
  user_note += t + added_user_note;
  return 0;
}

int event_t::add_default_note (std::string &added_default_note)
{
  if (added_default_note.size () + default_note.size () > MAX_DEFAULT_NOTE_SIZE)
    return -1;
  std::string t (" ");
  default_note += t + added_default_note;
  return 0;
}

int event_t::rewrite_user_note (std::string &new_user_note)
{
  if (new_user_note.size () > MAX_USER_NOTE_SIZE)
    return -1;
  user_note = std::move (new_user_note);
  return 0;
}

int event_t::rewrite_default_note (std::string &new_default_note)
{
  if (new_default_note.size () > MAX_DEFAULT_NOTE_SIZE)
    return -1;
  default_note = std::move (new_default_note);
  return 0;
}

std::string event_t::event_to_string ()
{
  static const std::string endl = "\n";
  std::string ret = name + endl;
  ret += pt::to_simple_string (event_date_time) + endl;
  ret += enum_to_string (etype) + endl;
  if (!default_note.empty ())
    ret += "Note:\n" + default_note + endl;
  if (!user_note.empty ())
    ret += "User's note:\n" + user_note + endl;

  return ret;
}

int event_t::make_repeatable (pt::time_duration repeat_interval_arg)
{
  if (set_repeat_interval (repeat_interval_arg) < 0)
    return -1;
  repeatable = true;
  return 0;
}

int event_t::switch_repeatability ()
{
  if (repeat_interval == pt::not_a_date_time)
    return -1;
  repeatable = !repeatable;
  return 0;
}

bool event_t::is_empty () const // maybe not neccecary
{
  return event_date_time == pt::not_a_date_time
         && place.empty ()
         && name.empty ()
         && user_note.empty ()
         && default_note.empty ();
}

/// FUNCTIONS BELOW ARE DEBUG FUNCTIONS AND RECOMMENDED TO BE DELETED FOR RELEASE !!!
#ifdef BOT_DEBUG_EDITION
inline void print_type (event_t::event_type type)
{
  printf ("Event type: %s\n", event_t::enum_to_string (type));
}

void event_t::print_event () // That is temorary debug function
{
  printf ("\n===================================\n");
  printf ("Event name: %s\n", name.data ());
  printf ("Event date and time: %s\n", pt::to_iso_extended_string (event_date_time).data());
  printf ("Event place: %s\n", place.data ());
  printf ("Notifies:\n");
  for (auto i : notify_vector)
    printf ("  Notify: %s\n", pt::to_iso_extended_string (i).data());
  print_type (etype);
  printf ("User note :\n  %s\n", user_note.data ());
  printf ("Default note :\n  %s\n", default_note.data ());
  printf ("===================================\n");
}

void event_test_function ()
{
  std::string ts ("2002-01-20 23:59:59.000");
  std::string name_1 ("event_name_1");
  std::string name_2 ("event_name_2");
  auto pt_1 = pt::time_from_string (ts);
  pt::ptime pt_2 (boost::gregorian::date (2010, boost::gregorian::Apr, 10),
                                 pt::hours (14) + pt::minutes (15));
  event_t event_1 (pt_1, name_1, event_t::lecture);
  event_t event_2 (pt_2, name_2, event_t::seminar);


  std::string tsn1 ("2001-01-20 23:59:59.000");
  auto ptn_1 = pt::time_from_string (tsn1);
  std::string tsn2 ("2001-04-20 13:02:11.000");
  auto ptn_2 = pt::time_from_string (tsn2);
  std::string tsn3 ("2001-03-20 20:59:59.000");
  auto ptn_3 = pt::time_from_string (tsn3);
  event_1.add_notify (ptn_2);
  event_1.print_event ();
  event_1.add_notify (ptn_1);
  event_1.print_event ();
  event_1.add_notify (ptn_3);
  event_1.print_event ();
  event_1.remove_notify (ptn_3);

  event_1.add_user_note (tsn1);
  event_1.add_user_note (tsn2);
  event_2.rewrite_user_note (tsn3);

  event_1.print_event ();
  std::string plc ("new place");
  event_2.set_place (plc);
  event_2.print_event ();

  event_1.clear_notify ();
  event_1.print_event ();
}
#endif
