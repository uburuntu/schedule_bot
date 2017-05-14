#include "notifies.h"

notify_t::notify_t (const user_id &id_arg, pt::ptime notify_time_arg, std::shared_ptr <event_t> notify_event_arg):
  id (id_arg), notify_time (notify_time_arg), notify_event (notify_event_arg)
{

}

// TODO: think about one minutes bounds
bool notify_t::operator== (const notify_t &rhs)
{
  auto left_bound = notify_time - pt::minutes (1);
  auto right_bound = notify_time + pt::minutes (1);
  auto rhs_left_bound = rhs.notify_time - pt::minutes (1);
  auto rhs_right_bound = rhs.notify_time + pt::minutes (1);
  bool equal_id_event = id == rhs.id && *notify_event == *(rhs.notify_event);
  if (!equal_id_event)
    return false;
  bool equal_time = false;
  if (notify_time == rhs.notify_time)
    equal_time = true;
  else if (notify_time < rhs.notify_time)
    equal_time = right_bound < rhs_left_bound;
  else
    equal_time = rhs_right_bound < left_bound;

  return equal_id_event && equal_time;
}

bool notify_t::operator< (const notify_t &rhs)
{
  return notify_time < rhs.notify_time;
}

bool notify_t::operator> (const notify_t &rhs)
{
  return notify_time > rhs.notify_time;
}

bool notify_t::operator>= (const notify_t &rhs)
{
  return notify_time >= rhs.notify_time;
}

bool notify_t::operator<= (const notify_t &rhs)
{
  return notify_time <= rhs.notify_time;
}

int notify_t::switch_repeatability ()
{
  if (repeating_interval == pt::not_a_date_time)
    return -1;
  repeatable = !repeatable;
  return 0;
}

void notify_t::make_repeatable (pt::time_duration repeating_interval_arg)
{
  set_repeating_interval (repeating_interval_arg);
  repeatable = true;
}

// TODO: think about one minutes bounds
int notifies_t::add_notify (user_id &id, pt::ptime notify_time, std::shared_ptr<event_t> notify_event)
{

}

void notifies_t::clear_user_noifies (user_id &id)
{

}

// TODO: think about one minutes bounds
int notifies_t::remove_user_one_notify (user_id &id, pt::ptime notify_time, std::shared_ptr <event_t> notify_event)
{

}

int notifies_t::remove_user_event_notifies (user_id &id, std::shared_ptr <event_t> notify_event)
{

}

void notifies_t::remove_past_notifies (pt::ptime curr_time)
{

}
