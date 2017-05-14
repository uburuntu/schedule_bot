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

void user_t::remove_past_events (pt::ptime curr_time)
{
  for (auto i = user_own_events.begin (); i != user_own_events.end (); )
    {
      if ((*i)->get_date_time () < curr_time)
        {
          if ((*i)->is_repeatable ())
            {
              (*i)->repeat_event ();
              event_t tmp_event = **i;
              i = user_own_events.erase (i); // TODO: check if there are no problems with iterators
              add_own_event (tmp_event);
            }
          else
            i = user_own_events.erase (i);
        }
      else
        return;
    }
}

std::vector<std::string> user_t::get_all_own_events_in_strings ()
{
  std::vector <std::string> ret;
  for (auto &i: user_own_events)
    ret.push_back (i->event_to_string ());
  return ret;
}

void users_t::add_user (user_id id)
{
  if (!user_exist (id))
    {
      users.emplace (id, id);
    }
}

void users_t::add_admin (user_id id)
{
  add_user (id);
  admins.insert (id);
}

bool users_t::user_exist (user_id id) const
{
  return users.find (id) != users.end ();
}

bool users_t::is_admin (user_id id) const
{
  return admins.find (id) != admins.end ();
}
