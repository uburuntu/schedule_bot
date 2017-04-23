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
    void send_message (TgBot::Message::Ptr message, const std::string &text);
    // Send message to specific id
    void send_message (chat_id id, const std::string &text);
};

#endif // SCH_BOT_H
