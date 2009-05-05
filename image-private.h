#ifndef TAIMEN_IMAGE_PRIVATE_H
#define TAIMEN_IMAGE_PRIVATE_H

#define TAIMEN_IMAGE_GET_PRIVATE(obj)					\
  (G_TYPE_INSTANCE_GET_PRIVATE ((obj), TAIMEN_TYPE_IMAGE, TaimenImagePrivate))

struct _TaimenImagePrivate
{
  gchar *imagepath;
  gchar *name;
  gboolean scalable;
  gulong sig;

  guint xsize, ysize;
};

#endif /* TAIMEN_IMAGE_PRIVATE_H */
