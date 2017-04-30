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
{
  event_date_time = rhs.event_date_time;
  name = rhs.name;
  etype = rhs.etype;
  notify_vector = rhs.notify_vector;
  place = rhs.place;
  default_note = rhs.default_note;
  user_note = rhs.user_note;
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

const boost::gregorian::date::day_of_week_type event_t::get_weekday () const
{
  return event_date_time.date ().day_of_week ();
}

void event_t::add_notify (pt::ptime new_notify)
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

bool event_t::is_empty () // maybe not neccecary
{
  return event_date_time == pt::not_a_date_time
         && notify_vector.empty ()
         && place.empty ()
         && name.empty ()
         && user_note.empty ()
         && default_note.empty ();
}
