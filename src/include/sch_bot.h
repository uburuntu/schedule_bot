#ifndef SCH_BOT_H
#define SCH_BOT_H

#include <set>

#include "boost/date_time/posix_time/posix_time.hpp"

#include <tgbot/Bot.h>

#include "defaults.h"
#include "event.h"
#include "report_system.h"
#include "user.h"

class sch_bot : public TgBot::Bot
{
  public:
    explicit sch_bot (const std::string &token) : TgBot::Bot (token)
    {}

    void init_commands ();
    void init_users ();

    // Send answer to input message
    void send_message (const TgBot::Message::Ptr message, const std::string &text) const;
    // Send message to specific id
    void send_message (user_id id, const std::string &text) const;
    // Send message to all users
    void send_message_all (const std::string &text) const;
    // Send message to all admins
    void send_message_admins (const std::string &text) const;

    // Notify methods
    void notify_all ();
    void notify_user (user_t &user);

    // Users methods
    void add_user (user_id id);
    void add_admin (user_id id);
    bool user_exist (user_id id) const;
    bool is_admin (user_id id) const;

    rep_ptr rep;
    void set_report_system (rep_ptr &rep_in)
    {
      rep = rep_in;
    }

  private:
    std::map<user_id, user_t> users;
    std::set<user_id> admins;
};

#endif // SCH_BOT_H
