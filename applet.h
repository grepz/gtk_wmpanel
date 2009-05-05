#ifndef APPLET_H
#define APPLET_H

#include <glib-object.h>
#include <gtk/gtk.h>

#include "image.h"

#define TAIMEN_TYPE_APPLET (taimen_applet_get_type())

#define TAIMEN_APPLET(obj)						\
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TAIMEN_TYPE_APPLET, TaimenApplet))

#define TAIMEN_APPLET_CLASS(klass)					\
  (G_TYPE_CHECK_CLASS_CAST(klass, TAIMEN_TYPE_APPLET, TaimenAppletClass))

#define TAIMEN_IS_APPLET(obj)					\
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TAIMEN_TYPE_APPLET))

#define TAIMEN_IS_APPLET_CLASS(klass)				\
  (G_TYPE_CHECK_CLASS_TYPE((klass), TAIMEN_TYPE_APPLET))

#define TAIMEN_APPLET_GET_CLASS(obj)					\
  (G_TYPE_GET_CLASS((obj), TAIMEN_TYPE_APPLET, TaimenAppletClass))

typedef struct _TaimenApplet TaimenApplet;
typedef struct _TaimenAppletClass TaimenAppletClass;
typedef struct _TaimenAppletPrivate TaimenAppletPrivate;

struct _TaimenApplet
{
  GtkEventBox evbox;
  TaimenImage *image;
  TaimenAppletPrivate *priv;
};

struct _TaimenAppletClass
{
  GtkEventBoxClass evbox_class;
};

GtkWidget* taimen_applet_new (gchar *imgpath, gint xscale, gint yscale, gint events);
gboolean taimen_applet_set_image (TaimenApplet *applet, TaimenImage *image);
GType taimen_applet_get_type (void);
void taimen_applet_add_callback (TaimenApplet *applet, gchar *event, void (*callfunc) (void));

#endif
