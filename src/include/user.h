#ifndef USER_H
#define USER_H

#include "defaults.h"

class user
{
public:
    user ()
      {}
    user (user_id id) : id (id)
      {}

    bool debug_mode = false;

private:
    user_id id;
};

#endif // USER_H
