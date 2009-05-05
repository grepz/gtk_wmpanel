#ifndef TOOLS_H
#define TOOLS_H

#include <stddef.h>

#include <glib-object.h>
#include <gtk/gtk.h>

/* Various macros magic, casting, structure member casting, ... */

#define TAIMEN_GOBJ_PRINT_TYPE (widget)					\
  g_print ("%s", g_type_name(((GTypeClass*)((GTypeInstance*)widget)->g_class)->g_type))

#define container_of(ptr, type, member) ({			\
      const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
      (type *)( (char *)__mptr - offsetof(type,member) );})

void exec_arg (const gchar *exec_str);

#ifdef DEBUG
#define taimen_debug(_fmt, ...) g_debug("(%s): " _fmt, G_STRFUNC, ##__VA_ARGS__)
#else
#define taimen_debug(_fmt, ...)
#endif

#endif
