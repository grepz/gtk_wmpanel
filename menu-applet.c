#include "menu-applet.h"

static void taimen_menu_applet_init (TaimenMenuApplet *self);
static void taimen_menu_applet_class_init (TaimenMenuAppletClass *klass);
static void taimen_menu_applet_get_property (GObject *object, guint property_id,
					     GValue *value, GParamSpec *pspec);
static void taimen_menu_applet_set_property (GObject *object, guint property_id,
					     const GValue *value,
					     GParamSpec *pspec);

GType
taimen_menu_applet_get_type (void)
{
  static GType taimen_menu_applet_type_id = 0;
  if (G_UNLIKELY (taimen_menu_applet_type_id == 0)) {
    static const GTypeInfo g_define_type_info = {
      sizeof (TaimenMenuAppletClass),
      (GBaseInitFunc) NULL,
      (GBaseFinalizeFunc) NULL,
      (GClassInitFunc) taimen_menu_applet_class_init,
      (GClassFinalizeFunc) NULL,
      NULL,
      sizeof (TaimenMenuApplet),
      0,
      (GInstanceInitFunc) taimen_menu_applet_init
    };

    taimen_menu_applet_type_id = g_type_register_static (
							 TAIMEN_TYPE_APPLET,
							 "TaimenMenuApplet",
							 &g_define_type_info,
							 0);
  }
  return taimen_menu_applet_type_id;
}

static void
taimen_menu_applet_init (TaimenMenuApplet *self)
{
  //	GtkTaimenMenuAppletPrivate *priv;
  //	self->priv = priv = GTK_TAIMEN_MENU_APPLET_GET_PRIVATE (self);
}

static void
taimen_menu_applet_class_init (TaimenMenuAppletClass *klass)
{
  GObjectClass *g_object_class;

  g_object_class = G_OBJECT_CLASS(klass);

  //	g_type_class_add_private (klass, sizeof(GtkTaimenMenuAppletPrivate));

  g_object_class->set_property = taimen_menu_applet_set_property;
  g_object_class->get_property = taimen_menu_applet_get_property;

}

static void
taimen_menu_applet_set_property (GObject      *object,
				 guint         property_id,
				 const GValue *value,
				 GParamSpec   *pspec)
{
  //	GtkTaimenMenuApplet *self = GTK_TAIMEN_MENU_APPLET (object);
}

static void
taimen_menu_applet_get_property (GObject    *object,
				 guint       property_id,
				 GValue     *value,
				 GParamSpec *pspec)
{
  //	GtkTaimenMenuApplet *self = GTK_TAIMEN_MENU_APPLET (object);
}

static void
position_menu (GtkMenu  *menu,
               int      *x,
               int      *y,
               gboolean *push_in,
               gpointer  user_data)
{
  //        TaimenMenuApplet *applet = user_data;

  *x += 10;
  *y += 10;
  *push_in = TRUE;
}

static void test2 ()
{
  g_message("Pointer motion");
}


GtkWidget *
taimen_menu_applet_new (gchar *imgpath)
{
  TaimenMenuApplet *menu_applet;
  GtkWidget *image;

  g_return_val_if_fail(imgpath != NULL, NULL);

  menu_applet = g_object_new (TAIMEN_TYPE_MENU_APPLET,
			      "events",
			      GDK_BUTTON_PRESS_MASK | GDK_ENTER_NOTIFY,
			      NULL);

  image = taimen_image_new (imgpath, 20, 20);
  taimen_applet_set_image (TAIMEN_APPLET (menu_applet), TAIMEN_IMAGE (image));

  g_signal_connect(G_OBJECT(menu_applet),"button_press_event",
		   G_CALLBACK(gtk_main_quit), NULL);
  //	g_signal_connect (G_OBJECT (menu_applet), "button_press_event",
  //					  G_CALLBACK (test1), menu_applet);
  g_signal_connect (G_OBJECT (menu_applet), "enter_notify_event",
		    G_CALLBACK (test2), NULL);

  //	g_object_set (G_OBJECT (GTK_TAIMEN_APPLET (g_type_class_peek_parent (menu_applet))->image), "xsize", 20, "ysize", 20, NULL);

  return GTK_WIDGET (menu_applet);
}
