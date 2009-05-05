#ifndef PANEL_H
#define PANEL_H

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define DEFAULT_PANEL_SIZE -1
#define DEFAULT_PANEL_X    -1
#define DEFAULT_PANEL_Y    -1

#define PANEL_IS_HORIZONTAL(panel)					\
  ((panel)->orient == GTK_TAIMEN_PANEL_ORIENT_TOP || (panel)->orient == GTK_TAIMEN_PANEL_ORIENT_DOWN)

#define TAIMEN_GET_SCREEN_WIDTH(widget)					\
  gdk_screen_get_width (gtk_window_get_screen (GTK_WINDOW (widget)))
#define TAIMEN_GET_SCREEN_HEIGHT(widget)				\
  gdk_screen_get_height (gtk_window_get_screen (GTK_WINDOW (widget)))

/* GObj specific macroses */
#define GTK_TYPE_TAIMEN_PANEL (gtk_taimen_panel_get_type())

#define GTK_TAIMEN_PANEL(obj)						\
  (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_TAIMEN_PANEL, GtkTaimenPanel))

#define GTK_TAIMEN_PANEL_CLASS(klass)					\
  (G_TYPE_CHECK_CLASS_CAST(klass, GTK_TYPE_TAIMEN_PANEL, GtkTaimenPanelClass))

#define GTK_IS_TAIMEN_PANEL(obj)				\
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_TAIMEN_PANEL))

#define GTK_IS_TAIMEN_PANEL_CLASS(klass)			\
  (G_TYPE_CHECK_CLASS_TYPE((klass), GTK_TYPE_TAIMEN_PANEL))

#define GTK_TAIMEN_PANEL_GET_CLASS(obj)					\
  (G_TYPE_GET_CLASS((obj), GTK_TYPE_TAIMEN_PANEL, GtkTaimenPanelClass))

typedef enum _GtkTaimenPanelOrient GtkTaimenPanelOrient;
enum _GtkTaimenPanelOrient
  {
    GTK_TAIMEN_PANEL_ORIENT_TOP = 1,
    GTK_TAIMEN_PANEL_ORIENT_BOTTOM,
    GTK_TAIMEN_PANEL_ORIENT_RIGHT,
    GTK_TAIMEN_PANEL_ORIENT_LEFT
  };

typedef struct _GtkTaimenPanel GtkTaimenPanel;
typedef struct _GtkTaimenPanelClass GtkTaimenPanelClass;
typedef struct _GtkTaimenPanelPrivate GtkTaimenPanelPrivate;

// TODO: Applets container

struct _GtkTaimenPanel
{
  GtkWindow window;

  /* private */
  GtkTaimenPanelPrivate *priv;

  /* Outer frame */
  GtkWidget *frame;
  /* VBox or HBox, decision is made upon panel orientation, Here we
   * pack all applets */
  GtkWidget *box;
  guint x, y, height, width;

  Pixmap bg_pixmap;
  gboolean hidden;
  gboolean transparent;
  gchar *name;
};

struct _GtkTaimenPanelClass
{
  GtkWindowClass window_class;
};

GType gtk_taimen_panel_get_type (void);
GtkWidget * gtk_taimen_panel_new (GtkTaimenPanelOrient orient, gdouble transp);
gboolean gtk_taimen_panel_switch_hide (GtkTaimenPanel *panel);
gboolean gtk_taimen_panel_set_orient (GtkTaimenPanel *panel, GtkTaimenPanelOrient orient);

G_END_DECLS

#endif /* PANEL_H */
