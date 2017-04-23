#include <tgbot/Api.h>
#include <tgbot/EventBroadcaster.h>
#include <tgbot/types/Message.h>

#include "include/sch_bot.h"
#include "include/utils.h"

void sch_bot::init_commands ()
{
  auto start_handle = [this] (TgBot::Message::Ptr message_in)
  {
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
    fix_unused (message_in);
    do_nothing ();
  };

  auto kill_handle = [this] (TgBot::Message::Ptr message_in)
  {
    send_message (message_in, "You killed me :(\nRestart server now.");
    abort ();
  };

  auto any_message_handle = [this] (TgBot::Message::Ptr message_in)
  {
    printf ("User %s wrote %s\n\n", message_in->chat->username.c_str (), message_in->text.c_str());

    if (StringTools::startsWith (message_in->text, "/start")
        || StringTools::startsWith (message_in->text, "/help")
        || StringTools::startsWith (message_in->text, "/debug"))
      {
        return;
      }

    send_message (message_in, "Your message is: " + message_in->text);
  };

  getEvents ().onCommand ("start", start_handle);
  getEvents ().onCommand ("help", help_handle);
  getEvents ().onCommand ("debug", debug_handle);
  getEvents ().onCommand ("kill", kill_handle);

  getEvents ().onAnyMessage (any_message_handle);
}

void sch_bot::send_message (TgBot::Message::Ptr message, const std::string &text)
{
  getApi ().sendMessage (message->chat->id, text);
}

void sch_bot::send_message (chat_id id, const std::string &text)
{
  getApi ().sendMessage (id, text);
}
