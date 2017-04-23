#include "include/event.h"

event_class::event_class(boost::posix_time::ptime date_time_arg, std::string &name_arg, EVENT_TYPE etype_arg)
  : event_date_time (date_time_arg), name (name_arg), etype (etype_arg)
{

}

event_class::~event_class ()
{
  event_date_time = boost::posix_time::not_a_date_time;
  name.clear ();
  notify_vector.clear ();
  default_note.clear ();
  user_note.clear ();
}
//should be copying everywhere
event_class::event_class (const event_class &rhs)
{
  event_date_time = rhs.event_date_time;
  name = rhs.name; // Not sure, check later if copy pointer or meanings
  etype = rhs.etype;
  notify_vector = rhs.notify_vector; // Not sure, check later if copy pointer or meanings
  place = rhs.place; // Not sure, check later if copy pointer or meanings
  default_note = rhs.default_note; // Not sure, check later if copy pointer or meanings
  user_note = rhs.user_note; // Not sure, check later if copy pointer or meanings
}
//should be copying everywhere
event_class &event_class::operator= (const event_class &rhs)
{
  event_date_time = rhs.event_date_time;
  name = rhs.name; // Not sure, check later if copy pointer or meanings
  etype = rhs.etype;
  notify_vector = rhs.notify_vector; // Not sure, check later if copy pointer or meanings
  place = rhs.place; // Not sure, check later if copy pointer or meanings
  default_note = rhs.default_note; // Not sure, check later if copy pointer or meanings
  user_note = rhs.user_note; // Not sure, check later if copy pointer or meanings
  return *this;
}

const boost::gregorian::date::day_of_week_type event_class::get_weekday () const
{
  return event_date_time.date ().day_of_week ();
}

void event_class::add_notify (boost::posix_time::ptime new_notify)
{
  if (!notify_vector.empty ())
    {
      for (auto i = notify_vector.begin (); i != notify_vector.end (); i++)
        {
          if (*i == new_notify)  // This one alreade exists
            return;
          if (new_notify < *i)
            {
              notify_vector.insert (i, new_notify);
              return;
            }
        }
    }
  notify_vector.push_back (new_notify);
}

void event_class::remove_notify (boost::posix_time::ptime notify_to_remove)
{
  for (auto i = notify_vector.begin (); i != notify_vector.end (); i++)
    if (*i == notify_to_remove)
      {
        notify_vector.erase (i);  // Enough to remove only one because
        return;                   // there can not be more, see add_notify
      }
}

int event_class::add_user_note (std::string &added_user_note)
{
  if (added_user_note.size () + user_note.size () > MAX_USER_NOTE_SIZE)
    return -1;
  std::string t (" ");
  user_note += t + added_user_note;
  return 0;
}

int event_class::add_default_note (std::string &added_default_note)
{
  if (added_default_note.size () + default_note.size () > MAX_DEFAULT_NOTE_SIZE)
    return -1;
  std::string t (" ");
  default_note += t + added_default_note;
  return 0;
}

int event_class::rewrite_user_note (std::string &new_user_note)
{
  if (new_user_note.size () > MAX_USER_NOTE_SIZE)
    return -1;
  user_note = std::move (new_user_note);
  return 0;
}

int event_class::rewrite_default_note (std::string &new_default_note)
{
  if (new_default_note.size () > MAX_DEFAULT_NOTE_SIZE)
    return -1;
  default_note = std::move (new_default_note);
  return 0;
}

bool event_class::is_empty () // maybe not neccecary
{
  return event_date_time == boost::posix_time::not_a_date_time && notify_vector.empty () && place.empty () &&
         name.empty () && user_note.empty () && default_note.empty ();
}
