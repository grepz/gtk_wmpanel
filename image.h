#ifndef TAIMEN_IMAGE_H
#define TAIMEN_IMAGE_H

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define TAIMEN_TYPE_IMAGE (taimen_image_get_type())

#define TAIMEN_IMAGE(obj)						\
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TAIMEN_TYPE_IMAGE, TaimenImage))

#define TAIMEN_IMAGE_CLASS(klass)					\
  (G_TYPE_CHECK_CLASS_CAST(klass, TAIMEN_TYPE_IMAGE, TaimenImageClass))

#define TAIMEN_IS_IMAGE(obj)					\
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TAIMEN_TYPE_IMAGE))

#define TAIMEN_IS_IMAGE_CLASS(klass)			\
  (G_TYPE_CHECK_CLASS_TYPE((klass), TAIMEN_TYPE_IMAGE))

#define TAIMEN_IMAGE_GET_CLASS(obj)					\
  (G_TYPE_GET_CLASS((obj), TAIMEN_TYPE_IMAGE, TaimenImageClass))

typedef struct _TaimenImage TaimenImage;
typedef struct _TaimenImageClass TaimenImageClass;
typedef struct _TaimenImagePrivate TaimenImagePrivate;

struct _TaimenImage
{
  GtkImage image;
  /* We include pointer to private structure to minimize amount of
   * code, but later throw this away to use proper GET_PRIVATE macro
   */
  TaimenImagePrivate *priv;
};

struct _TaimenImageClass
{
  GtkImageClass image_class;
};

GType taimen_image_get_type (void);
GtkWidget* taimen_image_new (const char *img_path, guint xsize, guint ysize);
gboolean pixbuf_file_to_gtk_image_scale (GtkImage *image, const char *filepath, guint xscale, guint yscale);

G_END_DECLS

#endif /* TAIMEN_IMAGE_H */
