#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"

#define MAX_USER_NOTE_SIZE 256
#define MAX_DEFAULT_NOTE_SIZE 512

class event_t
{
  public:
    enum event_type
      {
        lecture,
        seminar,
        spec_lecture,
        spec_seminar,
        other,

        COUNT
      };

    event_t (boost::posix_time::ptime date_time_arg, std::string &name_arg, event_type etype_arg);
    ~event_t ();
    event_t (const event_t &rhs);
    event_t &operator= (const event_t &rhs);

    // getters
    const boost::gregorian::date get_date () const {return event_date_time.date ();}
    const boost::posix_time::time_duration get_time () const {return event_date_time.time_of_day ();}
    const boost::gregorian::date::day_of_week_type get_weekday() const;
    const std::string &get_name () const {return name;}
    const std::vector<boost::posix_time::ptime> &get_notify () const {return notify_vector;}
    const std::string &get_default_note () const {return default_note;}
    const std::string &get_user_note () const {return user_note;}

    // setters
    void change_type (event_type new_etype) {etype = new_etype;}
    void set_place (std::string &new_place) {place = std::move (new_place);}

    // other
    int add_user_note (std::string &added_user_note);
    int add_default_note (std::string &added_default_note);
    int rewrite_user_note (std::string &new_user_note);
    int rewrite_default_note (std::string &new_default_note);
    void clear_user_note () {user_note.clear ();}
    void clear_default_note () {default_note.clear ();}
    void add_notify (boost::posix_time::ptime new_notify);
    void remove_notify (boost::posix_time::ptime notify_to_remove);
    void clear_notify () {notify_vector.clear ();}

    bool is_empty (); // maybe not neccecary

  private:
    boost::posix_time::ptime event_date_time;
    std::string name;
    event_type etype;
    std::vector<boost::posix_time::ptime> notify_vector;
    std::string place;
    std::string default_note;
    std::string user_note;
};

#endif // EVENT_H
