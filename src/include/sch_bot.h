#ifndef SCH_BOT_H
#define SCH_BOT_H

#include <set>

#include <tgbot/Bot.h>

#include "user.h"
#include "defaults.h"

class sch_bot : public TgBot::Bot
{
  public:
    explicit sch_bot (const std::string &token) : TgBot::Bot (token)
      {}

    void init_commands ();
    void init_users ();

    std::map<user_id, user> users;
    std::set<user_id> admins;
    void add_user (user_id id);
    void add_admin (user_id id);
    bool user_exist (user_id id) const;
    bool is_admin (user_id id) const;

  private:
    // Send answer to input message
    void send_message (const TgBot::Message::Ptr message, const std::string &text) const;
    // Send message to specific id
    void send_message (user_id id, const std::string &text) const;
    // Send message to all users
    void send_message_all (const std::string &text) const;
    // Send message to all users except one
    void send_message_all (user_id id, const std::string &text) const;
    // Send message to all admins
    void send_message_admins (const std::string &text) const;
};

#endif // SCH_BOT_H
