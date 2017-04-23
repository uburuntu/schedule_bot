#include <tgbot/Api.h>
#include <tgbot/EventBroadcaster.h>
#include <tgbot/types/Message.h>

#include "sch_bot.h"
#include "utils.h"

void sch_bot::init_commands ()
{
  auto start_handle = [this] (TgBot::Message::Ptr message_in)
  {
    user_id id = message_in->chat->id;
    if (!user_exist (id))
      users.emplace (id, id);

    send_message (message_in, "Приветик, красавчик! Ты попал к лучшему боту в Телеграме.\n\nВызови /help для помощи.");
  };

  auto help_handle = [this] (TgBot::Message::Ptr message_in)
  {
    std::string help_answer = std::string ("Этот бот предназначен для оповещения о парах, об их аудиториях или других событий в вашей жизни, которые нельзя пропустить.\n\n") +
                              std::string ("Бот находится в стадии активной разработки, о найденных багах пишите: @rm_bk, @Aenglsmith или @crazyvaskya.");

    send_message (message_in, help_answer);
  };

  auto debug_handle = [this] (TgBot::Message::Ptr message_in)
  {
    switch_bool (users[message_in->chat->id].debug_mode);
    send_message (message_in, "Debug mode enabled. You will be notified about some serious shit.");
  };

  auto kill_handle = [this] (TgBot::Message::Ptr message_in)
  {
    send_message (message_in, "You killed me :(\nRestart server now.");
    abort ();
  };

  auto unknown_command_handle = [this] (TgBot::Message::Ptr message_in)
  {
    send_message (message_in, "Дедушка не понимает тебя");
  };

  auto any_message_handle = [this] (TgBot::Message::Ptr message_in)
  {
    printf ("[LOW] User %s wrote %s\n\n", message_in->chat->username.c_str (), message_in->text.c_str());

    if (StringTools::startsWith (message_in->text, "/"))
      {
        return;
      }

    send_message (message_in, "Your message is: " + message_in->text);
  };

  getEvents ().onAnyMessage (any_message_handle);

  getEvents ().onCommand ("start", start_handle);
  getEvents ().onCommand ("help", help_handle);
  getEvents ().onCommand ("debug", debug_handle);
  getEvents ().onCommand ("kill", kill_handle);
  getEvents ().onUnknownCommand (unknown_command_handle);
}

void sch_bot::send_message (const TgBot::Message::Ptr message, const std::string &text) const
{
  getApi ().sendMessage (message->chat->id, text);
}

void sch_bot::send_message (user_id id, const std::string &text) const
{
  getApi ().sendMessage (id, text);
}
