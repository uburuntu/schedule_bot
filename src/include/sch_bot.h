#ifndef SCH_BOT_H
#define SCH_BOT_H

#include <tgbot/Bot.h>

class sch_bot : public TgBot::Bot
{
  using chat_id = int64_t;

  public:
    explicit sch_bot (const std::string &token) : TgBot::Bot (token)
      {}

    void init_commands ();

  private:
    // Send answer to input message
    void send_message (const TgBot::Message::Ptr message, const std::string &text) const;
    // Send message to specific id
    void send_message (user_id id, const std::string &text) const;
};

#endif // SCH_BOT_H
