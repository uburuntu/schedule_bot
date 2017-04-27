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

volatile sig_atomic_t signal_got = 0;

int main (int /* argc */, char *argv[])
{
  // Signal handler
  signal (SIGINT, [] (int s) { printf ("[HIGH] Program got SIGINT signal, aborting...\n"); signal_got = s;});

  // Create and initialize bot
  sch_bot bot (API_TOKEN);
  bot.init_users ();
  bot.init_commands ();

  // Log info
  printf ("[INFO] The program '%s' started work\n", argv[0]);
  printf ("[INFO] Bot id: %d\n", bot.getApi ().getMe ()->id);
  printf ("[INFO] Bot username: %s\n", bot.getApi ().getMe ()->username.c_str ());

  // Run loop to handle messages
  try
    {
      TgBot::TgLongPoll long_poll (bot);

      printf ("[LOW] Long poll started\n");
      while (!signal_got)
        {
          long_poll.start ();
          bot.notify_all ();
        }
    }
  catch (std::exception &e)
    {
      printf ("[HIGH] Error: %s\n", e.what ());
    }

  return 0;
}
