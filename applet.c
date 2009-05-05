#include "applet.h"
#include "applet-private.h"

static void taimen_applet_init (TaimenApplet *self);
static void taimen_applet_class_init (TaimenAppletClass *klass);
static void taimen_applet_get_property (GObject *object, guint property_id,
					GValue *value, GParamSpec *pspec);
static void taimen_applet_set_property (GObject *object, guint property_id,
					const GValue *value, GParamSpec *pspec);

enum {
  PROP_TAIMEN_APPLET_0,

  PROP_TAIMEN_APPLET_NAME,
};

GType
taimen_applet_get_type (void)
{
  static GType taimen_applet_type_id = 0;
  if (G_UNLIKELY (taimen_applet_type_id == 0)) {
    static const GTypeInfo g_define_type_info = {
      sizeof (TaimenAppletClass),
      (GBaseInitFunc) NULL,
      (GBaseFinalizeFunc) NULL,
      (GClassInitFunc) taimen_applet_class_init,
      (GClassFinalizeFunc) NULL,
      NULL,
      sizeof (TaimenApplet),
      0,
      (GInstanceInitFunc) taimen_applet_init
    };

    taimen_applet_type_id = g_type_register_static (GTK_TYPE_EVENT_BOX,
						    "TaimenApplet",
						    &g_define_type_info,
						    0);
  }
  return taimen_applet_type_id;
}

static void
taimen_applet_init (TaimenApplet *self)
{
  TaimenAppletPrivate *priv;

  self->priv = priv = TAIMEN_APPLET_GET_PRIVATE (self);
}

static void
taimen_applet_class_init (TaimenAppletClass *klass)
{
  GObjectClass *g_object_class;

  g_object_class = G_OBJECT_CLASS(klass);

  g_type_class_add_private (klass, sizeof(TaimenAppletPrivate));

  g_object_class->set_property = taimen_applet_set_property;
  g_object_class->get_property = taimen_applet_get_property;

}

static void
taimen_applet_set_property (GObject      *object,
			    guint         property_id,
			    const GValue *value,
			    GParamSpec   *pspec)
{
  //	GtkTaimenApplet *self = GTK_TAIMEN_APPLET (object);
}

static void
taimen_applet_get_property (GObject    *object,
			    guint       property_id,
			    GValue     *value,
			    GParamSpec *pspec)
{
  //	GtkTaimenApplet *self = GTK_TAIMEN_APPLET (object);
}

gboolean
taimen_applet_set_image (TaimenApplet *applet,
			 TaimenImage *image)
{
  g_return_val_if_fail (applet != NULL
			|| image != NULL, FALSE);
  g_return_val_if_fail (TAIMEN_IS_APPLET (applet)
			&& TAIMEN_IS_IMAGE(image), FALSE);

  // TODO: Cache, not delete, we have mostly 2 images and slow
  // gradient color change, but in some cases we may have more
  if (applet->image)
    // XXX: g_free ?
    g_object_unref (applet->image);

  applet->image = image;
  gtk_container_add (GTK_CONTAINER (applet), GTK_WIDGET (image));

  return TRUE;
}

// TODO: implement
void
taimen_applet_rem_callback (TaimenApplet *applet, gchar *event,
			    void (*callfunc) ())
{
  g_return_if_fail (TAIMEN_IS_APPLET (applet));
}

/**
 * gtk_taimen_applet_new
 * @imgpath: Path to image to display (png file)
 * @xscale: scale image over x
 * @yscale: scale image over y
 * @events: events, sets #GdkEventMask mask, if eq 0, widget sets
 * default event masks: GDK_BUTTON_PRESS_MASK, GDK_BUTTON_MOTION_MASK
 *
 * Creates #GtkTaimenApplet, which is child of #GtkEventBox and
 * includes #GtkTaimenImage.
 * #GtkEventBox is for handling events like button press, key press,
 * mouse click, cursor motion etc.
 * #GtkTaimenImage hold scalable image.
 * Implements replacement for button on panel
 *
 * Return value: #GtkTaimenApplet
 **/
GtkWidget*
taimen_applet_new (gchar *imgpath, gint xscale, gint yscale, gint events)
{
  TaimenApplet *applet;
  GtkWidget *image;

  g_return_val_if_fail(imgpath != NULL, NULL);

  applet = g_object_new (TAIMEN_TYPE_APPLET, NULL);
  image = taimen_image_new (imgpath, xscale, yscale);
  taimen_applet_set_image (applet, TAIMEN_IMAGE (image));

  if (!events) {
    //		gtk_widget_set_events (GTK_WIDGET(applet),
    //							   GDK_BUTTON_PRESS_MASK |
    //							   GDK_BUTTON_MOTION_MASK);
    g_object_set (G_OBJECT (applet), "events",
		  GDK_BUTTON_PRESS_MASK | GDK_BUTTON_MOTION_MASK,
		  NULL);
  }

  return GTK_WIDGET (applet);
}
