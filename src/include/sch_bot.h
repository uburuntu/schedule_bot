#ifndef SCH_BOT_H
#define SCH_BOT_H

#include <tgbot/Bot.h>

class sch_bot : public TgBot::Bot
{
  public:
    explicit sch_bot (const std::string &token) : TgBot::Bot (token)
      {}

    void init_commands ();
};

#endif // SCH_BOT_H
