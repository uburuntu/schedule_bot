/*
 * Copyright (c) 2015 Oleg Morozenkov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <signal.h>
#include <exception>

#include <tgbot/tgbot.h>
#include "sch_bot.h"
#include "token.h"

static bool sigintGot = false;

int main ()
{
  sch_bot bot (API_TOKEN);

  bot.getEvents().onCommand ("start", [&bot] (TgBot::Message::Ptr message)
  {
    bot.getApi().sendMessage (message->chat->id, "Hi!");
  });

  bot.getEvents().onAnyMessage ([&bot] (TgBot::Message::Ptr message)
  {
    printf ("User wrote %s\n", message->text.c_str());

    if (StringTools::startsWith (message->text, "/start"))
      {
        return;
      }

    bot.getApi().sendMessage (message->chat->id, "Your message is: " + message->text);
  });

  signal (SIGINT, [] (int) { printf ("SIGINT got, aborting...\n"); sigintGot = true;});

  try
    {
      printf ("Bot username: %s\n", bot.getApi().getMe()->username.c_str());

      TgBot::TgLongPoll longPoll (bot);

      while (!sigintGot)
        {
          printf ("Long poll started\n");
          longPoll.start();
        }
    }
  catch (std::exception &e)
    {
      printf ("error: %s\n", e.what());
    }

  return 0;
}
