#ifndef USER_H
#define USER_H

#include "boost/date_time/posix_time/posix_time.hpp"

#include <set>
#include <map>

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
    void remove_own_event (event_t own_event_to_remove);
    void remove_past_events (pt::ptime curr_time);
    std::shared_ptr<event_t> find_event (event_t event);

    std::vector<std::string> get_all_own_events_in_strings ();

  private:
    bool debug_mode = false;
    user_id id = 0;
    std::vector <std::shared_ptr <event_t>> user_own_events;
};

class users_t
{
  public:
    void add_user (user_id id);
    void add_admin (user_id id);

    bool user_exist (user_id id) const;
    bool is_admin (user_id id) const;

    // TODO: Refactor to const and implement users functions
    std::map<user_id, user_t> &get_all_users () { return users;}
    std::set<user_id> &get_admins () { return admins;}

  private:
    // TODO: Refactor containers
    std::map<user_id, user_t> users;
    std::set<user_id> admins;
};

#endif // USER_H
