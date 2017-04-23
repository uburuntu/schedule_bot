#include <tgbot/Api.h>
#include <tgbot/EventBroadcaster.h>
#include <tgbot/types/Message.h>

#include "sch_bot.h"
#include "include/utils.h"

void sch_bot::init_commands ()
{
  auto start_handle = [this] (TgBot::Message::Ptr message)
  {
    getApi ().sendMessage (message->chat->id, "Приветик, красавчик! Ты попал к лучшему боту в Телеграме.\n\nВызови /help для помощи.");
  };

  auto help_handle = [this] (TgBot::Message::Ptr message)
  {
    std::string help_answer = std::string ("Этот бот предназначен для оповещения о парах, об их аудиториях или других событий в вашей жизни, которые нельзя пропустить.\n\n") +
                              std::string ("Бот находится в стадии активной разработки, о найденных багах пишите: @rm_bk, @Aenglsmith или @crazyvaskya.");

    getApi ().sendMessage (message->chat->id, help_answer);
  };

  auto debug_handle = [this] (TgBot::Message::Ptr message)
  {
    fix_unused (message);
    do_nothing ();
    abort (); // kek
  };

  auto any_message_handle = [this] (TgBot::Message::Ptr message)
  {
    printf ("User %s wrote %s\n\n", message->chat->username.c_str (), message->text.c_str());

    if (StringTools::startsWith (message->text, "/start")
        || StringTools::startsWith (message->text, "/help")
        || StringTools::startsWith (message->text, "/debug"))
      {
        return;
      }

    getApi().sendMessage (message->chat->id, "Your message is: " + message->text);
  };

  getEvents ().onCommand ("start", start_handle);
  getEvents ().onCommand ("help", help_handle);
  getEvents ().onCommand ("debug", debug_handle);

  getEvents ().onAnyMessage (any_message_handle);
}
