#ifndef NOTIFIES_H
#define NOTIFIES_H

#include "user.h"
#include "event.h"
#include "utils.h"

class notify_t
{
  public:
    notify_t (const user_id &id_arg, pt::ptime notify_time_arg, std::shared_ptr <event_t> notify_event_arg);
    bool operator== (const notify_t &rhs);
    bool operator< (const notify_t &rhs);
    bool operator> (const notify_t &rhs);
    bool operator>= (const notify_t &rhs);
    bool operator<= (const notify_t &rhs);

    int switch_repeatability ();
    void repeat_notify () {if (repeatable) notify_time += repeating_interval;}
    void make_repeatable (pt::time_duration repeating_interval_arg);

    // getters
    const pt::ptime &get_notify_time () const {return notify_time;}
    const user_id &get_user_id () const {return id;}
    const pt::time_duration &get_repeating_interval () const {return repeating_interval;}
    const bool &is_repeatable () const {return repeatable;}
    const std::shared_ptr <event_t> &get_notifying_event () const {return notify_event;}

    // setters
    void set_repeating_interval (pt::time_duration repeating_interval_arg) {repeating_interval = repeating_interval_arg;}

  private:
    const user_id &id;
    pt::ptime notify_time;
    bool repeatable = false;
    pt::time_duration repeating_interval = pt::not_a_date_time;
    std::shared_ptr <event_t> notify_event;
};

class notifies_t
{
  public:
    SINGLETON_CLASS (notifies_t);

    int add_notify (user_id &id, pt::ptime notify_time, std::shared_ptr <event_t> notify_event);
    void clear_user_noifies (user_id &id);
    int remove_user_one_notify (user_id &id, pt::ptime notify_time, std::shared_ptr <event_t> notify_event);
    int remove_user_event_notifies (user_id &id, std::shared_ptr <event_t> notify_event);
    void remove_past_notifies (pt::ptime curr_time);

  private:
    notifies_t ();
    notifies_t (const notifies_t &) = delete;
    notifies_t operator= (const notifies_t &) = delete;

    std::vector <notify_t> all_notifies;
};

#endif // NOTIFIES_H
