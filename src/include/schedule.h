#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <unordered_map>

#include "include/event.h"
#include "include/notifies.h"

class schedule_interface
{
  public:
    virtual ~schedule_interface () {}

    // Initialize events from file or by other logic
    virtual void init_schedule () = 0;

    virtual void update_schedule () = 0;
};

class schedule_tsphere : public schedule_interface
{
  public:
    schedule_tsphere () {}

    virtual void init_schedule () {}
    virtual void update_schedule () {}

  private:
    std::vector<event_ptr> all_exercises;
};

class schedule_mechmath : public schedule_interface
{
  public:
    schedule_mechmath () {}

    virtual void init_schedule () {}
    virtual void update_schedule () {}

  private:
    std::vector<event_ptr> all_exercises;
};

#endif // SCHEDULE_H
