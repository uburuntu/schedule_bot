#ifndef SCH_BOT_H
#define SCH_BOT_H

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

    bool user_exist (user_id id) const
      {
        return users.find (id) != users.end ();
      }

  private:
    // Send answer to input message
    void send_message (const TgBot::Message::Ptr message, const std::string &text) const;
    // Send message to specific id
    void send_message (user_id id, const std::string &text) const;
    // Send message to all users
    void send_message_all (const std::string &text) const;
};

#endif // SCH_BOT_H
