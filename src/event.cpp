#include "event.h"

event_t::event_t (pt::ptime date_time_arg, std::string &name_arg, event_type etype_arg)
  : event_date_time (date_time_arg), name (name_arg), etype (etype_arg)
{

}

event_t::~event_t ()
{
  event_date_time = pt::not_a_date_time;
  name.clear ();
  notify_vector.clear ();
  default_note.clear ();
  user_note.clear ();
}

//should be copying everywhere
event_t::event_t (const event_t &rhs)
    : event_date_time (rhs.event_date_time), name (rhs.name),
      etype (rhs.etype), notify_vector (rhs.notify_vector),
      place (rhs.place), default_note (rhs.default_note), user_note (rhs.user_note)
{

}

//should be copying everywhere
event_t &event_t::operator= (const event_t &rhs)
{
  event_date_time = rhs.event_date_time;
  name = rhs.name;
  etype = rhs.etype;
  notify_vector = rhs.notify_vector;
  place = rhs.place;
  default_note = rhs.default_note;
  user_note = rhs.user_note;
  return *this;
}

bool event_t::operator== (const event_t &rhs)
{
  return name == rhs.name &&
         event_date_time == rhs.event_date_time &&
         etype == rhs.etype;
}

bool event_t::operator< (const event_t &rhs)
{
  return event_date_time < rhs.event_date_time;
}

bool event_t::operator> (const event_t &rhs)
{
  return event_date_time > rhs.event_date_time;
}

const boost::gregorian::date::day_of_week_type event_t::get_weekday () const
{
  return event_date_time.date ().day_of_week ();
}

int event_t::add_notify (pt::ptime new_notify)
{
  auto right_edge = new_notify + boost::posix_time::minutes(1);
  auto left_edge = new_notify - boost::posix_time::minutes(1);
  if (!notify_vector.empty ())
    {
      for (auto i = notify_vector.begin (); i != notify_vector.end (); i++)
        {
          if (left_edge < *i && *i < right_edge)  // This one alreade exists
            return -1;
          if (new_notify < *i)
            {
              notify_vector.insert (i, new_notify);
              return 0;
            }
        }
    }
  notify_vector.push_back (new_notify);
}

void event_t::remove_notify (pt::ptime notify_to_remove)
{
  for (auto i = notify_vector.begin (); i != notify_vector.end (); i++)
    if (*i == notify_to_remove)
      {
        notify_vector.erase (i);  // Enough to remove only one because
        return;                   // there can not be more, see add_notify
      }
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

inline std::string type_to_string (event_t::event_type type)
{
  printf ("Event type: ");
  std::string ret;
  switch (type)
    {
    case (event_t::lecture):
      ret = "Lecture";
      break;
    case (event_t::seminar):
      ret = "Seminar";
      break;
    case (event_t::spec_lecture):
      ret = "Spec Lec";
      break;
    case (event_t::spec_seminar):
      ret = "Spec Seminar";
      break;
    case (event_t::other):
      ret = "Other";
      break;
    default:
      ret = "Unknown";
    }
}

std::string event_t::event_to_string ()
{
  std::string ret = name + "\n";
  ret += pt::to_simple_string (event_date_time) + "\n";
  ret += type_to_string (etype) + "\n";
  if (!notify_vector.empty ())
    {
      ret += "Notifies\n";
      for (auto &i: notify_vector)
        ret += pt::to_simple_string (i) + "\n";
    }
  if (!default_note.empty ())
    ret += "Note:\n" + default_note + "\n";
  if (!user_note.empty ())
    ret += "User's note:\n" + user_note + "\n";
}

bool event_t::is_empty () // maybe not neccecary
{
  return event_date_time == pt::not_a_date_time
         && notify_vector.empty ()
         && place.empty ()
         && name.empty ()
         && user_note.empty ()
         && default_note.empty ();
}



/// FUNCTIONS BELOW ARE DEBUG FUNCTIONS AND RECOMMENDED TO BE DELETED FOR RELEASE !!!
#ifdef BOT_DEBUG_EDITION
inline void print_type (event_t::event_type type)
{
  printf ("Event type: ");
  switch (type)
    {
    case (event_t::lecture):
      printf ("Lecture\n");
      break;
    case (event_t::seminar):
      printf ("Seminar\n");
      break;
    case (event_t::spec_lecture):
      printf ("Spec Lec\n");
      break;
    case (event_t::spec_seminar):
      printf ("Spec Sem\n");
      break;
    case (event_t::other):
      printf ("Other\n");
      break;
    default:
      printf ("Unknown\n");
    }
}

void event_t::print_event () // That is temorary debug function
{
  printf ("\n===================================\n");
  printf ("Event name: %s\n", name.data ());
  printf ("Event date and time: %s\n", boost::posix_time::to_iso_extended_string (event_date_time).data());
  printf ("Event place: %s\n", place.data ());
  printf ("Notifies:\n");
  for (auto i: notify_vector)
    printf ("  Notify: %s\n", boost::posix_time::to_iso_extended_string (i).data());
  print_type (etype);
  printf ("User note :\n  %s\n", user_note.data ());
  printf ("Default note :\n  %s\n", default_note.data ());
  printf ("===================================\n");
}

void event_test_function ()
{
  std::string ts("2002-01-20 23:59:59.000");
  std::string name_1 ("event_name_1");
  std::string name_2 ("event_name_2");
  auto pt_1 = boost::posix_time::time_from_string (ts);
  boost::posix_time::ptime pt_2 (boost::gregorian::date(2010, boost::gregorian::Apr, 10),
                                 boost::posix_time::hours(14) + boost::posix_time::minutes(15));
  event_t event_1 (pt_1, name_1, event_t::lecture);
  event_t event_2 (pt_2, name_2, event_t::seminar);


  std::string tsn1("2001-01-20 23:59:59.000");
  auto ptn_1 = boost::posix_time::time_from_string (tsn1);
  std::string tsn2("2001-04-20 13:02:11.000");
  auto ptn_2 = boost::posix_time::time_from_string (tsn2);
  std::string tsn3("2001-03-20 20:59:59.000");
  auto ptn_3 = boost::posix_time::time_from_string (tsn3);
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
