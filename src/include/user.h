#ifndef USER_H
#define USER_H

#include "boost/date_time/posix_time/posix_time.hpp"

#include "defaults.h"
#include "utils.h"
class event_t;

class user_t
{
  public:
    user_t () = default;
    ~user_t () = default;
    user_t (const user_t &rhs) = default;
    user_t &operator= (const user_t &) = default;

    user_t (user_id id) : id (id)
    {
      last_notify = sbot::curr_time ();
    }
    user_id get_id () const { return id;}

    void switch_debug () { sbot::switch_bool (debug_mode);}

    pt::ptime last_notify;

    int add_own_event (event_t new_own_event);
    int add_notify_to_own_event (pt::ptime new_own_notify, event_t event);
    void remove_own_event (event_t own_event_to_remove);
    void remove_notify_from_event (pt::ptime notify_to_remove,  event_t event);
    void remove_past_events (pt::ptime curr_time);

    std::vector<std::string> get_all_own_events_in_strings ();

  private:
    bool debug_mode = false;
    user_id id = 0;
    std::vector <std::unique_ptr <event_t>> user_own_events;
};

#endif // USER_H
