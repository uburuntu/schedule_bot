#ifndef SCH_BOT_H
#define SCH_BOT_H

#include <set>

#include "boost/date_time/posix_time/posix_time.hpp"

#include <tgbot/Bot.h>

#include "defaults.h"
#include "event.h"
#include "report_system.h"
#include "token.h"
#include "user.h"
#include "utils.h"

class sch_bot : public TgBot::Bot
{
  public:
    SINGLETON_CLASS (sch_bot);

    // Initialize functions
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

    report_system &rep = report_system::instance ();

  private:
    sch_bot () : TgBot::Bot (API_TOKEN)
    {
      rep.print (rep::info, "Bot id: %d", getApi ().getMe ()->id);
      rep.print (rep::info, "Bot username: %s", getApi ().getMe ()->username.c_str ());

      init_users ();
      init_commands ();
    }
    sch_bot (const sch_bot &) = delete;
    sch_bot operator= (const sch_bot &) = delete;

    std::map<user_id, user_t> users;
    std::set<user_id> admins;
};

#endif // SCH_BOT_H
