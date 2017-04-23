#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"

#define MAX_USER_NOTE_SIZE 256
#define MAX_DEFAULT_NOTE_SIZE 512

enum EVENT_TYPE
{
  EVENT_TYPE_LECTURE,
  EVENT_TYPE_SEMINAR,
  EVENT_TYPE_SPEC_LECTURE,
  EVENT_TYPE_SPEC_SEMINAR,
  EVENT_TYPE_STUDENT_COUNCIL,
  EVENT_TYPE_OTHER
};

class event_class
{
  public:
    event_class (boost::posix_time::ptime date_time_arg, std::string &name_arg, EVENT_TYPE etype_arg);
    ~event_class ();
    event_class (const event_class &rhs);
    event_class &operator= (const event_class &rhs);

    // getters
    const boost::gregorian::date get_date () const {return event_date_time.date ();}
    const boost::posix_time::time_duration get_time () const {return event_date_time.time_of_day ();}
    const boost::gregorian::date::day_of_week_type get_weekday() const;
    const std::string &get_name () const {return name;}
    const std::vector<boost::posix_time::ptime> &get_notify () const {return notify_vector;}
    const std::string &get_default_note () const {return default_note;}
    const std::string &get_user_note () const {return user_note;}

    // setters
    void change_type (EVENT_TYPE new_etype) {etype = new_etype;}
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
    EVENT_TYPE etype;
    std::vector<boost::posix_time::ptime> notify_vector;
    std::string place;
    std::string default_note;
    std::string user_note;
};

#endif // EVENT_H
