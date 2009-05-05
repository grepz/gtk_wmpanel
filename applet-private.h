#ifndef APPLET_PRIVATE_H
#define APPLET_PRIVATE_H

#define TAIMEN_APPLET_GET_PRIVATE(obj)					\
  (G_TYPE_INSTANCE_GET_PRIVATE ((obj), TAIMEN_TYPE_APPLET, TaimenAppletPrivate))

struct _TaimenAppletPrivate
{
  gchar *name;
};


#endif /* APPLET_PRIVATE_H */
