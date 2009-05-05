#ifndef MENU_APPLET_H
#define MENU_APPLET_H

#include "applet.h"

#define TAIMEN_TYPE_MENU_APPLET (taimen_menu_applet_get_type())

#define TAIMEN_MENU_APPLET(obj)						\
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TAIMEN_TYPE_MENU_APPLET, TaimenMenuApplet))

#define TAIMEN_MENU_APPLET_CLASS(klass)					\
  (G_TYPE_CHECK_CLASS_CAST(klass, TAIMEN_TYPE_MENU_APPLET, TaimenMenuAppletClass))

#define TAIMEN_IS_MENU_APPLET(obj)				\
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TAIMEN_TYPE_MENU_APPLET))

#define TAIMEN_IS_MENU_APPLET_CLASS(klass)			\
  (G_TYPE_CHECK_CLASS_TYPE((klass), TAIMEN_TYPE_MENU_APPLET))

#define TAIMEN_MENU_APPLET_GET_CLASS(obj)				\
  (G_TYPE_GET_CLASS((obj), TAIMEN_TYPE_MENU_APPLET, TaimenMenuAppletClass))


typedef struct _TaimenMenuApplet TaimenMenuApplet;
typedef struct _TaimenMenuAppletClass TaimenMenuAppletClass;
// typedef struct _GtkTaimenMenuAppletPrivate GtkTaimenMenuAppletPrivate;

struct _TaimenMenuApplet
{
  TaimenApplet applet;

  // GtkTaimenAppletPrivate *priv;
};

struct _TaimenMenuAppletClass
{
  TaimenAppletClass applet_class;
};


GType taimen_menu_applet_get_type (void);
GtkWidget *taimen_menu_applet_new ();

#endif /* MENU_APPLET_H */
