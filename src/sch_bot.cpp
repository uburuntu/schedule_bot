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
    users.add_user (id);

    std::string start_answer = "Привет, красавчик! Ты попал к лучшему боту в Телеграме."
                               + sbot::empty_line
                               + "Вызови /help для помощи.";

    send_message (message_in, start_answer);
  };

  auto help_handle = [this] (TgBot::Message::Ptr message_in)
  {
    std::string help_answer = "Этот бот предназначен для оповещения о парах, об их аудиториях или других событий в вашей жизни, которые нельзя пропустить."
                              + sbot::empty_line
                              + "Бот находится в стадии активной разработки, о найденных багах пишите: @rm_bk, @Aenglsmith или @crazyvaskya.";

    send_message (message_in, help_answer);
  };

  auto debug_handle = [this] (TgBot::Message::Ptr message_in)
  {
    if (!users.is_admin (message_in->chat->id))
      return;

    users.get_all_users ()[message_in->chat->id].switch_debug ();
    send_message (message_in, "Debug mode enabled. You will be notified about some serious shit.");
  };

  auto kill_handle = [this] (TgBot::Message::Ptr message_in)
  {
    if (!users.is_admin (message_in->chat->id))
      return;

    static int kill_count = 0;
    if (kill_count++ > 1)
      {
        send_message_admins (message_in->chat->username + " killed me :(\n\nRestart server now.");
        raise (SIGINT);
      }
  };

  auto all_handle = [this] (TgBot::Message::Ptr message_in)
  {
    send_message_all (message_in->chat->username + ":\n" + message_in->text);
  };

  auto flood_handle = [this] (TgBot::Message::Ptr message_in)
  {
    send_message_all (message_in->chat->username + " started the /flood testing. Aaaaaa!\n");

    static const int n_flood = 20;

    for (int i = 0; i < n_flood; i++)
      {
        send_message_all (std::to_string (i + 1) + " from " + std::to_string (n_flood) + sbot::empty_line + StringTools::generateRandomString (30));
      }
  };

  auto unknown_command_handle = [this] (TgBot::Message::Ptr message_in)
  {
    send_message (message_in, "Дедушка не понимает тебя");
  };

  auto any_message_handle = [this] (TgBot::Message::Ptr message_in)
  {
    rep.print (rep::message_in, "User (name = %s, id = %ld) wrote '%s'",
               message_in->chat->username.c_str (),
               message_in->chat->id,
               message_in->text.c_str());

    if (StringTools::startsWith (message_in->text, "/"))
      return;

    send_message (message_in, "Your message is: " + message_in->text);
  };

  getEvents ().onAnyMessage (any_message_handle);
  getEvents ().onUnknownCommand (unknown_command_handle);

  getEvents ().onCommand ("start", start_handle);
  getEvents ().onCommand ("help", help_handle);
  getEvents ().onCommand ("debug", debug_handle);
  getEvents ().onCommand ("kill", kill_handle);
  getEvents ().onCommand ("all", all_handle);
  getEvents ().onCommand ("flood", flood_handle);
}

void sch_bot::init_users ()
{
  // Developer's id as admins
  users.add_admin (sbot::r_id);
  users.add_admin (sbot::a_id);
  users.add_admin (sbot::v_id);

  // TODO: implement users import / export
}

void sch_bot::send_message (user_id id, const std::string &text) const
{
  rep.print (rep::message_out, "[To id = %ld] \n\"\n%s\n\"", id, text.c_str ());

  getApi ().sendMessage (id, text);
}

void sch_bot::send_message (const TgBot::Message::Ptr message, const std::string &text) const
{
  send_message (message->chat->id, text);
}

void sch_bot::send_message_all (const std::string &text)
{
  for (const auto &user_it : users.get_all_users ())
    {
      user_id id = user_it.second.get_id ();
      send_message (id, "[Global Message]" + sbot::empty_line + text);
    }
}

void sch_bot::send_message_admins (const std::string &text)
{
  for (const auto &user_it : users.get_admins ())
    {
      user_id id = user_it;
      send_message (id, "[Admin Report]" + sbot::empty_line + text);
    }
}

void sch_bot::notify_all ()
{
  pt::ptime time = sbot::curr_time ();
  for (const auto &notify_it : notifies.get_all_notifies ())
    {
      if (notify_it > time)
        break;
      notify_user (notify_it);
    }

  for (auto &i : users.get_all_users ())
    {
      user_t &user = std::get<1> (i);
      user.remove_past_events (time);
    }

  notifies.remove_past_notifies (time);
}

void sch_bot::notify_user (const notify_t &notify)
{
  // TODO: implement user events getter and notifying
  pt::ptime time = sbot::curr_time ();

  std::string message = sbot::program + "notify.\nCurrent time: " + pt::to_simple_string (time)
                        + sbot::empty_line
                        + notify.get_notifying_event ()->event_to_string ();

  send_message (notify.get_user_id (), message);
}
