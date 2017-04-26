#ifndef USER_H
#define USER_H

#include "defaults.h"

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

    bool debug_mode = false;

private:
    user_id id = 0;
};

#endif // USER_H
