#ifndef UTILS_H
#define UTILS_H

template<typename T>
static void fix_unused (const T &) {}

static void do_nothing () {}

static void switch_bool (bool &a)
{
  a = !a;
}

#endif // UTILS_H
