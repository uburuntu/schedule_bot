#ifndef USER_H
#define USER_H

#include "defaults.h"
#include "utils.h"

class user
{
public:
    user () = default;
    user (user_id id) : id (id)
      {}
    ~user () = default;

    user_id get_id () const
      {
        return id;
      }

    void switch_debug () { switch_bool (debug_mode);}

private:
    bool debug_mode = false;
    user_id id = 0;
};

#endif // USER_H
