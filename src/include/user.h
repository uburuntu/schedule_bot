#ifndef USER_H
#define USER_H

#include "boost/date_time/posix_time/posix_time.hpp"

#include "defaults.h"
#include "utils.h"

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

private:
    bool debug_mode = false;
    user_id id = 0;
};

#endif // USER_H
