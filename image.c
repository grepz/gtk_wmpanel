#include "image.h"
#include "image-private.h"

#include "tools.h"

static void taimen_image_init ();
static void taimen_image_class_init ();
static void taimen_image_get_property (GObject *object, guint property_id,
				       GValue *value, GParamSpec *pspec);
static void taimen_image_set_property (GObject *object, guint property_id,
				       const GValue *value, GParamSpec   *pspec);

enum {
  PROP_TAIMEN_IMAGE_0,

  PROP_TAIMEN_IMAGE_IMAGEPATH,
  PROP_TAIMEN_IMAGE_SCALABLE,
  //If image name is default, then set it according to iconpath name
  PROP_TAIMEN_IMAGE_NAME,
  PROP_TAIMEN_IMAGE_XSIZE,
  PROP_TAIMEN_IMAGE_YSIZE
};

GType
taimen_image_get_type (void)
{
  static GType taimen_image_type_id = 0;
  if (G_UNLIKELY (taimen_image_type_id == 0)) {
    static const GTypeInfo g_define_type_info = {
      sizeof (TaimenImageClass),
      (GBaseInitFunc) NULL,
      (GBaseFinalizeFunc) NULL,
      (GClassInitFunc) taimen_image_class_init,
      (GClassFinalizeFunc) NULL,
      NULL,
      sizeof (TaimenImage),
      0,
      (GInstanceInitFunc) taimen_image_init
    };

    taimen_image_type_id = g_type_register_static (GTK_TYPE_IMAGE,
						   "TaimenImage",
						   &g_define_type_info,
						   0);
  }
  return taimen_image_type_id;
}

static void
taimen_image_init (TaimenImage *self)
{
  TaimenImagePrivate *priv;

  self->priv = priv = TAIMEN_IMAGE_GET_PRIVATE (self);
}

static void
taimen_image_class_init (TaimenImageClass *klass)
{
  GObjectClass *g_object_class;

  g_object_class = G_OBJECT_CLASS(klass);

  g_type_class_add_private (klass, sizeof (TaimenImagePrivate));

  g_object_class->set_property = taimen_image_set_property;
  g_object_class->get_property = taimen_image_get_property;

  g_object_class_install_property (g_object_class, PROP_TAIMEN_IMAGE_NAME,
				   g_param_spec_string ("image-name",
							"",
							"",      /* description */
							"Image", /* default */
							G_PARAM_READWRITE
							| G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (
				   g_object_class, PROP_TAIMEN_IMAGE_IMAGEPATH,
				   g_param_spec_string ("image-path",
							"",
							"",      /* description */
							"image", /* default */
							G_PARAM_READWRITE));

  g_object_class_install_property (g_object_class, PROP_TAIMEN_IMAGE_XSIZE,
				   g_param_spec_uint ("xsize",
						      "",
						      "",
						      1,          /* minimum */
						      G_MAXINT32, /* maximum */
						      1,          /* default */
						      G_PARAM_READWRITE));

  g_object_class_install_property (g_object_class, PROP_TAIMEN_IMAGE_YSIZE,
				   g_param_spec_uint ("ysize",
						      "",
						      "",
						      1,          /* minimum */
						      G_MAXINT32, /* maximum */
						      1,          /* default */
						      G_PARAM_READWRITE));
}

static void
taimen_image_get_property (GObject    *object,
			   guint       property_id,
			   GValue     *value,
			   GParamSpec *pspec)
{
  TaimenImage *self = TAIMEN_IMAGE (object);
  //	TaimenImagePrivate *priv = TAIMEN_IMAGE_GET_PRIVATE (self);

  switch (property_id) {
  case PROP_TAIMEN_IMAGE_IMAGEPATH:
    g_value_set_string (value, self->priv->imagepath);
    taimen_debug ("%s: Getting image image path: %s", G_STRFUNC, self->priv->imagepath);
    break;
  case PROP_TAIMEN_IMAGE_SCALABLE:
    break;
  case PROP_TAIMEN_IMAGE_NAME:
    g_value_set_string (value, self->priv->name);
    taimen_debug ("%s: Setting image name: %s", G_STRFUNC, self->priv->name);
    break;
  case PROP_TAIMEN_IMAGE_XSIZE:
    g_value_set_uint (value, self->priv->xsize);
    break;
  case PROP_TAIMEN_IMAGE_YSIZE:
    g_value_set_uint (value, self->priv->ysize);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    break;
  }
}

static void
taimen_image_set_property (GObject      *object,
			   guint         property_id,
			   const GValue *value,
			   GParamSpec   *pspec)
{
  TaimenImage *self = TAIMEN_IMAGE (object);

  switch (property_id) {
  case PROP_TAIMEN_IMAGE_IMAGEPATH:
    g_free (self->priv->imagepath);
    self->priv->imagepath = g_value_dup_string (value);
    taimen_debug ("%s: image image path set to: %s", G_STRFUNC, self->priv->imagepath);
    break;
  case PROP_TAIMEN_IMAGE_SCALABLE:
    break;
  case PROP_TAIMEN_IMAGE_NAME:
    g_free (self->priv->name);
    self->priv->name = g_value_dup_string (value);
    taimen_debug ("%s: image name set to: %s", G_STRFUNC, self->priv->name);
    break;
  case PROP_TAIMEN_IMAGE_XSIZE:
    self->priv->xsize = g_value_get_uint (value);
    break;
  case PROP_TAIMEN_IMAGE_YSIZE:
    self->priv->ysize = g_value_get_uint (value);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    break;
  }
}

static gboolean
taimen_image_imagepath_callback (TaimenImage *image,
				 GParamSpec *pspec,
				 gpointer __attribute__((unused)) user_data)
{
  gchar *imagepath;
  guint xsize, ysize;

  g_object_get (G_OBJECT (image),
		"xsize", &xsize,
		"ysize", &ysize,
		NULL);

  /*
   * imagepath must be defined to some reasonable value? Also is
   * there any other way to get GValue without g_object_get
   */
  g_object_get (G_OBJECT (image), "image-path", &imagepath, NULL);

  if (!pixbuf_file_to_gtk_image_scale (GTK_IMAGE (image), imagepath, xsize, ysize)) {
    taimen_debug ("Pixbuf creation failed with file %s", imagepath);
    g_free (imagepath);
    return FALSE;
  }

  g_free (imagepath);

  return TRUE;
}

GtkWidget*
taimen_image_new (const char *img_path, guint xsize, guint ysize)
{
  GtkWidget *image;

  // FIXME: Property already checking ysize and xsize
  g_return_val_if_fail (((ysize > 0) && (xsize > 0) && img_path), NULL);

  image = g_object_new (TAIMEN_TYPE_IMAGE,
			"image-path", img_path,
			"image-name", "test",
			"xsize", xsize,
			"ysize", ysize,
			NULL);

  if (!pixbuf_file_to_gtk_image_scale (GTK_IMAGE (image),
				       img_path, xsize, ysize)) {
    taimen_debug ("Pixbuf creation failed with file %s", img_path);
    return NULL;
  }

  g_signal_connect (G_OBJECT(image),
		    "notify::image-path",
		    (GCallback) taimen_image_imagepath_callback,
		    NULL);
  return image;
}

gboolean
pixbuf_file_to_gtk_image_scale (GtkImage *image,
				const char *filepath,
				guint xscale, guint yscale)
{
  GdkPixbuf *pixbuf;

  pixbuf = gdk_pixbuf_new_from_file_at_scale (filepath,
					      xscale, yscale, TRUE, NULL);

  if (pixbuf) {
    taimen_debug ("Setting GtkImage pixbuf from file %s", filepath);
    gtk_image_set_from_pixbuf (image, pixbuf);
  } else {
    taimen_debug ("Pixbuf creation failed with file %s", filepath);
    return FALSE;
  }

  return TRUE;
}
