#ifndef PANEL_PRIVATE_H
#define PANEL_PRIVATE_H

#define GTK_TAIMEN_PANEL_GET_PRIVATE(obj)				\
  (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GTK_TYPE_TAIMEN_PANEL, GtkTaimenPanelPrivate))

struct _GtkTaimenPanelPrivate
{
  gboolean transparent;
  /* Reserved for real transparency */
  gboolean alpha_channel;

  gint max_height;
  gint max_width;

  gchar *name;
  GtkTaimenPanelOrient orient;
};

#endif /* PANEL_PRIVATE_H */
