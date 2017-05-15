#include "notifies.h"

notify_t::notify_t (const user_id id_arg, pt::ptime notify_time_arg, std::shared_ptr <event_t> notify_event_arg):
  id (id_arg), notify_time (notify_time_arg), notify_event (notify_event_arg)
{

}

notify_t::notify_t (const notify_t &rhs):
  id (rhs.id), notify_time (rhs.notify_time), notify_event (rhs.notify_event)
{

}

notify_t &notify_t::operator= (const notify_t &rhs)
{
  id = rhs.id;
  notify_time = rhs.notify_time;
  notify_event = rhs.notify_event;
  return *this;
}

bool notify_t::operator== (const notify_t &rhs) const
{
  auto left_bound = notify_time - pt::minutes (1);
  auto right_bound = notify_time + pt::minutes (1);
  auto rhs_left_bound = rhs.notify_time - pt::minutes (1);
  auto rhs_right_bound = rhs.notify_time + pt::minutes (1);

  bool equal_id = id == rhs.id;
  if (!equal_id)
    return false;
  bool equal_event = *notify_event == *(rhs.notify_event);
  if (!equal_event)
    return false;

  bool equal_time = false;
  if (notify_time == rhs.notify_time)
    equal_time = true;
  else if (notify_time < rhs.notify_time)
    equal_time = right_bound < rhs_left_bound;
  else
    equal_time = rhs_right_bound < left_bound;

  return equal_time;
}

bool notify_t::operator< (const notify_t &rhs) const
{
  return notify_time < rhs.notify_time;
}

bool notify_t::operator> (const notify_t &rhs) const
{
  return notify_time > rhs.notify_time;
}

bool notify_t::operator>= (const notify_t &rhs) const
{
  return notify_time >= rhs.notify_time;
}

bool notify_t::operator<= (const notify_t &rhs) const
{
  return notify_time <= rhs.notify_time;
}

bool notify_t::operator< (const pt::ptime &rhs) const
{
  return notify_time < rhs;
}

bool notify_t::operator<= (const pt::ptime &rhs) const
{
  return notify_time <= rhs;
}

bool notify_t::operator> (const pt::ptime &rhs) const
{
  return notify_time > rhs;
}

bool notify_t::operator>= (const pt::ptime &rhs) const
{
  return notify_time >= rhs;
}

int notify_t::switch_repeatability ()
{
  if (repeating_interval == pt::not_a_date_time)
    return -1;
  repeatable = !repeatable;
  return 0;
}

int notify_t::make_repeatable (pt::time_duration repeating_interval_arg)
{
  if (set_repeating_interval (repeating_interval_arg) < 0)
    return -1;
  repeatable = true;
  return 0;
}

int notify_t::set_repeating_interval (pt::time_duration repeating_interval_arg)
{
  if (repeating_interval_arg < pt::minutes (1))
    return -1;

  repeating_interval = repeating_interval_arg;
  return 0;
}

int notifies_t::add_notify (notify_t new_notify)
{
  auto new_notifying_event = new_notify.get_notifying_event ();
  auto notifying_event_time = new_notifying_event->get_date_time ();
  bool event_is_repeatable = new_notifying_event->is_repeatable ();
  auto new_notify_time = new_notify.get_notify_time ();

  if ((new_notify_time > notifying_event_time && !event_is_repeatable) ||
      event_is_repeatable && new_notify_time > notifying_event_time + new_notifying_event->get_repeat_interval ())
    return -1;

  notify_t this_time_notifies_left_bound (new_notify.get_user_id (),
                                          new_notify_time - pt::minutes (1),
                                          new_notify.get_notifying_event ());

  auto this_time_notifies_begin = std::lower_bound (all_notifies.begin (), all_notifies.end (), this_time_notifies_left_bound);
  auto this_time_notifies_end = this_time_notifies_begin;
  while (*this_time_notifies_end < new_notify_time + pt::minutes (1))
    {
      if (*this_time_notifies_end == new_notify)
        return -2; // This notify already exists in one minute bounds
      this_time_notifies_end++;
    }
  all_notifies.insert (std::lower_bound (this_time_notifies_begin, this_time_notifies_end, new_notify), new_notify);
  return 0;
}

int notifies_t::add_notify (user_id &id, pt::ptime notify_time, std::shared_ptr<event_t> notify_event)
{
  return add_notify (notify_t (id, notify_time, notify_event));
}

void notifies_t::clear_user_noifies (user_id &id)
{
  for (auto i = all_notifies.begin (); i != all_notifies.end (); )
    {
      if ((*i).get_user_id () == id)
        i = all_notifies.erase (i);
      else
        i++;
    }
}

int notifies_t::remove_user_one_notify (user_id &id, pt::ptime notify_time, std::shared_ptr <event_t> notify_event)
{
  notify_t notify_to_remove (id, notify_time, notify_event);
  auto this_time_notify = std::lower_bound (all_notifies.begin (), all_notifies.end (), notify_to_remove);
  while (*this_time_notify < notify_time + pt::minutes (1))
    {
      if (*this_time_notify == notify_to_remove)
        {
          all_notifies.erase (this_time_notify);
          return 0;
        }
      else
        this_time_notify++;
    }
  return -1;
}

void notifies_t::remove_user_event_notifies (user_id &id, std::shared_ptr <event_t> notify_event)
{
  for (auto i = all_notifies.begin (); i != all_notifies.end (); )
    {
      if ((*i).get_user_id () == id && (*i).get_notifying_event () == notify_event)
        i = all_notifies.erase (i);
      else
        i++;
    }
}

void notifies_t::remove_past_notifies (pt::ptime curr_time)
{
  for (auto i = all_notifies.begin (); i != all_notifies.end (); )
    {
      notify_t &curr_notify = *i;
      if (curr_notify > curr_time)
        break;
      if (curr_notify.is_repeatable () &&
          curr_notify.get_notify_time () + curr_notify.get_repeating_interval () < curr_notify.get_notifying_event ()->get_date_time ())
        {
          curr_notify.repeat_notify ();
          add_notify (curr_notify); // Check if adding new iterator doesn't do anything bad
        }
      i = all_notifies.erase (i);
    }
}
