#include "user.h"
#include "event.h"

int user_t::add_own_event (event_t new_own_event)
{
  for (auto i = user_own_events.begin (); i != user_own_events.end (); i++)
    {
      if (**i == new_own_event)
        return -1; // Event already exists
      if (new_own_event < **i)
        {
          user_own_events.insert (i, std::unique_ptr<event_t> (new event_t (new_own_event)));
          return 0;
        }
    }
  return -2;
}

int user_t::add_notify_to_own_event (pt::ptime new_own_notify, event_t event)
{
  for (auto &i: user_own_events)
    {
      if (*i == event)
        {
          return i->add_notify (new_own_notify);
        }
    }
  return -2; // There is no such event
}

void user_t::remove_own_event (event_t own_event_to_remove)
{
  for (auto i = user_own_events.begin (); i != user_own_events.end (); i++)
    {
      if (**i == own_event_to_remove)
        {
          user_own_events.erase (i);
          return;
        }
    }
}

void user_t::remove_notify_from_event (pt::ptime notify_to_remove,  event_t event)
{
  for (auto &i: user_own_events)
    {
      if (*i == event)
        {
          i->remove_notify (notify_to_remove);
          return;
        }
    }
}

void user_t::remove_past_events (pt::ptime curr_time)
{
  for (auto i = user_own_events.begin (); i != user_own_events.end (); i++)
    {
      if (*i->get_date_time () < curr_time)
        user_own_events.erase (i);
      else
        return;
    }
}

std::vector<std::string> user_t::get_all_own_events_in_strings ()
{
  std::vector <std::string> ret;
  for (auto &i: user_own_events)
    ret.push_back (i.event_to_string);
  return ret;
}
