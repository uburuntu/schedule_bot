#include <signal.h>

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
    add_user (id);

    printf ("[HIGH] New user: %d\n", id);
    send_message (message_in, "Приветик, красавчик! Ты попал к лучшему боту в Телеграме.\n\nКаждое твоё сообщение анонимно попадает к каждому, кто зашел в бота.");
  };

  auto any_message_handle = [this] (TgBot::Message::Ptr message_in)
  {
    printf ("[LOW] User (name = %s, id = %d) wrote '%s'\n", message_in->chat->username.c_str (), message_in->chat->id, message_in->text.c_str());

    send_message_all (message_in->chat->id, message_in->text);
  };

  getEvents ().onAnyMessage (any_message_handle);
  getEvents ().onCommand ("start", start_handle);
}

void sch_bot::init_users ()
{
  // Developer's id as admins
  add_admin (sbot::r_id);

  send_message_admins ("[Admin Report] Bot started, current version: " + sbot::version);

  // TODO: implement users import / export
}

void sch_bot::add_user (user_id id)
{
  if (!user_exist (id))
    {
      users.emplace (id, id);
    }
}

void sch_bot::add_admin (user_id id)
{
  add_user (id);
  admins.insert (id);
}

bool sch_bot::user_exist (user_id id) const
{
  return users.find (id) != users.end ();
}

bool sch_bot::is_admin (user_id id) const
{
  return admins.find (id) != admins.end ();
}

void sch_bot::send_message (const TgBot::Message::Ptr message, const std::string &text) const
{
  getApi ().sendMessage (message->chat->id, text);
}

void sch_bot::send_message (user_id id, const std::string &text) const
{
  getApi ().sendMessage (id, text);
}

void sch_bot::send_message_all (const std::string &text) const
{
  for (auto &user_it : users)
    {
      send_message (user_it.second.get_id (), text);
    }
}

void sch_bot::send_message_all (user_id id, const std::string &text) const
{
  for (auto &user_it : users)
    {
      if (user_it.second.get_id () == id)
        continue;

      send_message (user_it.second.get_id (), text);
    }
}

void sch_bot::send_message_admins (const std::string &text) const
{
  for (auto &user_it : admins)
    {
      send_message (user_it, text);
    }
}
