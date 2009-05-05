#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <gtk/gtkmain.h>
#include <gtk/gtkwindow.h>
#include <gtk/gtkhbox.h>
#include <gtk/gtkvbox.h>
#include <gtk/gtkframe.h>

#include <gdk/gdkx.h>

#include <X11/Xatom.h>

#include "panel.h"
#include "panel-private.h"

#include "image.h"
#include "applet.h"
#include "menu-applet.h"

#include "tools.h"

#define TAIMEN_PANEL_WIDTH 25
#define GTK_TAIMEN_PANEL_ORIENT_CONTROL		\
  (gtk_taimen_panel_orient_control_get_type ())

/* Panel properties */
enum {
  PROP_TAIMEN_PANEL_0,

  PROP_TAIMEN_PANEL_NAME,
  PROP_TAIMEN_PANEL_ORIENT,
  PROP_TAIMEN_PANEL_WIDTH,
  PROP_TAIMEN_PANEL_HEIGHT,
  PROP_TAIMEN_PANEL_TRANSP,
  PROP_TAIMEN_PANEL_SCREEN_MAX_WIDTH,
  PROP_TAIMEN_PANEL_SCREEN_MAX_HEIGHT
};

static gpointer gtk_taimen_panel_parent_class = NULL;

static void gtk_taimen_panel_class_init (GtkTaimenPanelClass *klass);
static void gtk_taimen_panel_init (GtkTaimenPanel *self);
//static void gtk_taimen_panel_realize (GtkWidget *widget);
static GType gtk_taimen_panel_orient_control_get_type (void);

static void
gtk_taimen_panel_set_property (GObject      *object,
			       guint         property_id,
			       const GValue *value,
			       GParamSpec   *pspec)
{
  GtkTaimenPanel *self = GTK_TAIMEN_PANEL (object);

  switch (property_id) {
  case PROP_TAIMEN_PANEL_NAME:
    g_free (self->name);
    self->name = g_value_dup_string (value);
    taimen_debug ("panel name set to: %s", self->name);
    break;
  case PROP_TAIMEN_PANEL_ORIENT:
    self->priv->orient = g_value_get_enum(value);
    taimen_debug ("panel orientation set to: %d", self->priv->orient);
    break;
  case PROP_TAIMEN_PANEL_WIDTH:
    self->width = g_value_get_int(value);
    taimen_debug ("panel width set to: %d", self->width);
    break;
  case PROP_TAIMEN_PANEL_HEIGHT:
    self->height = g_value_get_int(value);
    taimen_debug ("panel height set to: %d", self->height);
    break;
  case PROP_TAIMEN_PANEL_TRANSP:
    self->priv->transparent = g_value_get_boolean(value);
    taimen_debug ("panel transparency set to: %d", self->priv->transparent);
    break;
  case PROP_TAIMEN_PANEL_SCREEN_MAX_WIDTH:
    self->priv->max_width = g_value_get_int (value);
    taimen_debug ("panel screen maximum width set to: %d",
		  self->priv->max_width);
    break;
  case PROP_TAIMEN_PANEL_SCREEN_MAX_HEIGHT:
    self->priv->max_width = g_value_get_int (value);
    taimen_debug ("panel screen maximum height set to: %d",
		  self->priv->max_height);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    break;
  }
}

static void
gtk_taimen_panel_get_property (GObject    *object,
			       guint       property_id,
			       GValue     *value,
			       GParamSpec *pspec)
{
  GtkTaimenPanel *self = GTK_TAIMEN_PANEL (object);

  switch (property_id) {
  case PROP_TAIMEN_PANEL_NAME:
    g_value_set_string (value, self->name);
    break;
  case PROP_TAIMEN_PANEL_ORIENT:
    g_value_set_enum(value, self->priv->orient);
    taimen_debug ("getting panel orientation: %d", self->priv->orient);
    break;
  case PROP_TAIMEN_PANEL_WIDTH:
    g_value_set_int(value, self->width);
    taimen_debug ("getting panel width: %d", self->width);
    break;
  case PROP_TAIMEN_PANEL_HEIGHT:
    g_value_set_int(value, self->height);
    taimen_debug ("getting panel height: %d", self->height);
    break;
  case PROP_TAIMEN_PANEL_TRANSP:
    g_value_set_boolean(value, self->priv->transparent);
    taimen_debug ("getting panel transparency: %d",
		  self->priv->transparent);
    break;
  case PROP_TAIMEN_PANEL_SCREEN_MAX_WIDTH:
    g_value_set_int (value, self->priv->max_width);
    taimen_debug ("getting panel screen maximum width: %d",
		  self->priv->max_width);
    break;
  case PROP_TAIMEN_PANEL_SCREEN_MAX_HEIGHT:
    g_value_set_int (value, self->priv->max_height);
    taimen_debug ("getting panel screen maximum height: %d",
		  self->priv->max_height);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    break;
  }
}

/* Gobj type creator */
GType
gtk_taimen_panel_get_type (void)
{
  static GType gtk_taimen_panel_type_id = 0;
  if (G_UNLIKELY (gtk_taimen_panel_type_id == 0)) {
    static const GTypeInfo g_define_type_info = {
      sizeof (GtkTaimenPanelClass),
      (GBaseInitFunc) NULL,
      (GBaseFinalizeFunc) NULL,
      (GClassInitFunc) gtk_taimen_panel_class_init,
      (GClassFinalizeFunc) NULL,
      NULL,
      sizeof (GtkTaimenPanel),
      0,
      (GInstanceInitFunc) gtk_taimen_panel_init
    };

    gtk_taimen_panel_type_id =
      g_type_register_static (GTK_TYPE_WINDOW, "GtkTaimenPanel",
			      &g_define_type_info, 0);
  }
  return gtk_taimen_panel_type_id;
}

static void
gtk_taimen_panel_init (GtkTaimenPanel *self)
{
  GtkTaimenPanelPrivate *priv;

  self->priv = priv = GTK_TAIMEN_PANEL_GET_PRIVATE (self);

  self->priv->max_height = TAIMEN_GET_SCREEN_HEIGHT(self);
  self->priv->max_width  = TAIMEN_GET_SCREEN_WIDTH(self);
}

static void
gtk_taimen_panel_class_init (GtkTaimenPanelClass *klass)
{
  GObjectClass *g_object_class;

  g_object_class = G_OBJECT_CLASS(klass);
  gtk_taimen_panel_parent_class = g_type_class_peek_parent (klass);

  g_type_class_add_private (klass, sizeof (GtkTaimenPanelPrivate));

  g_object_class->set_property = gtk_taimen_panel_set_property;
  g_object_class->get_property = gtk_taimen_panel_get_property;

  /* XXX: Find a way to use this */
  // g_object_class_override_property (g_object_class,
  //								  TAIMEN_PANEL_PROP_HEIGHT,
  //								  "default-height");
  // g_object_class_override_property (g_object_class,
  //								  TAIMEN_PANEL_PROP_WIDTH,
  //								  "default-width");

  /* Setting all properties */
  g_object_class_install_property(g_object_class, PROP_TAIMEN_PANEL_ORIENT,
				  g_param_spec_enum ("panel-orient", "",
						     "Panel orientation",
						     GTK_TAIMEN_PANEL_ORIENT_CONTROL, /* type */
						     GTK_TAIMEN_PANEL_ORIENT_TOP,     /* default */
						     G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property(g_object_class, PROP_TAIMEN_PANEL_NAME,
				  g_param_spec_string ("panel-name",
						       "",
						       "Global panel name", /* description */
						       "Panel",             /* default */
						       G_PARAM_READWRITE));

  g_object_class_install_property(g_object_class, PROP_TAIMEN_PANEL_TRANSP,
				  g_param_spec_boolean ("panel-transparent",
							"", "", TRUE,
							G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property(g_object_class, PROP_TAIMEN_PANEL_SCREEN_MAX_WIDTH,
				  g_param_spec_int ("screen-max-width",
						    "", "",
						    -1,         /* minimum */
						    G_MAXINT32, /* maximum */
						    -1,         /* default */
						    G_PARAM_READABLE));

  g_object_class_install_property(g_object_class, PROP_TAIMEN_PANEL_SCREEN_MAX_HEIGHT,
				  g_param_spec_int ("screen-max-height",
						    "", "", -1,
						    G_MAXINT32, -1,
						    G_PARAM_READABLE));
}

// TODO: Mention in doc:
// gtk_window_get_size
// gtk_window_get_position

GtkWidget*
gtk_taimen_panel_new (GtkTaimenPanelOrient orient, gdouble transp)
{
  GtkWidget *widget;
  gint panel_width, panel_height;

  widget = GTK_WIDGET (g_object_new (GTK_TYPE_TAIMEN_PANEL,
				     "panel-orient", orient,
				     "type-hint", GDK_WINDOW_TYPE_HINT_DOCK,
				     "accept-focus", FALSE,
				     NULL));

  g_object_set(G_OBJECT(widget),
	       "default-width", TAIMEN_GET_SCREEN_WIDTH (widget),
	       "default-height", TAIMEN_PANEL_WIDTH,
	       NULL);

  if (transp >= 0.0) {
    taimen_debug ("Transparency request of panel");
    if (gtk_widget_is_composited(widget)) {
      taimen_debug ("Panel is composited");
      g_object_set(G_OBJECT(widget),
		   "opacity", transp,
		   NULL);
    } else {
      // TODO:
      taimen_debug ("Panel is not composited");
    }
  }

  gtk_window_get_size (GTK_WINDOW (widget), &panel_width, &panel_height);
  taimen_debug ("Getting default width & height of panel: %d, %d",
		panel_width, panel_height);
  gtk_widget_set_size_request (widget, panel_width, panel_height);
  gtk_window_resize (GTK_WINDOW (widget), panel_width, panel_height);

  return widget;
}

/* Custom enum orientation type */
static GType
gtk_taimen_panel_orient_control_get_type (void)
{
  static GType orient_type = 0;
  static GEnumValue panel_orient[] = {
    {GTK_TAIMEN_PANEL_ORIENT_TOP,
     "GTK_TAIMEN_PANEL_ORIENT_TOP",    "orient-top"},
    {GTK_TAIMEN_PANEL_ORIENT_BOTTOM,
     "GTK_TAIMEN_PANEL_ORIENT_BOTTOM", "orient-bottom"},
    {GTK_TAIMEN_PANEL_ORIENT_RIGHT,
     "GTK_TAIMEN_PANEL_ORIENT_RIGHT",  "orient-right"},
    {GTK_TAIMEN_PANEL_ORIENT_LEFT,
     "GTK_TAIMEN_PANEL_ORIENT_LEFT",   "orient-left"},
    {0, NULL, NULL}
  };

  if (!orient_type) {
    orient_type =
      g_enum_register_static ("GtkTaimenPanelOrient", panel_orient);
  }
  return orient_type;
}


// TODO: Do it as reloadable private method
static void
pack_applet (GtkTaimenPanel *panel,
	     const TaimenImage *image,
	     void (*packfunc) (GtkBox    *box,
			       GtkWidget *widget,
			       gboolean   expand,
			       gboolean   fill,
			       guint      padding))
{
}

gboolean
gtk_taimen_panel_switch_hide (GtkTaimenPanel *panel)
{
  g_return_val_if_fail (panel != NULL, FALSE);
  g_return_val_if_fail (GTK_IS_TAIMEN_PANEL (panel), FALSE);
  return TRUE;
}

gboolean
gtk_taimen_panel_swith_orient (GtkTaimenPanel *panel,
			       GtkTaimenPanelOrient orient)
{
  g_return_val_if_fail (panel != NULL, FALSE);
  g_return_val_if_fail (GTK_IS_TAIMEN_PANEL (panel), FALSE);
  return TRUE;
}

/** =============================================================
 *
 ** ============================================================= **/

gboolean
configure_event(GtkWidget *w,gpointer data)
{
  GdkPixmap *pix;
  GdkBitmap *bit;
  GdkColor c = {0};

  pix=gdk_pixmap_create_from_xpm(w->window,&bit,&c,"test2.xpm");
  gdk_window_shape_combine_mask(GDK_WINDOW(w->window),bit,0,0);
  gtk_window_set_decorated(GTK_WINDOW(w),FALSE);
  return TRUE;
}

void
make_shaped_widget(GtkWidget **widget)
{
  (*widget)=gtk_window_new(GTK_WINDOW_TOPLEVEL);

  g_signal_connect(G_OBJECT(*widget),"configure_event",
		   G_CALLBACK(configure_event), NULL);
  g_signal_connect(G_OBJECT(*widget),"destroy",
		   G_CALLBACK(gtk_main_quit), NULL);

  gtk_container_add(GTK_CONTAINER(*widget), gtk_color_selection_new());
}



int main (int argc, char **argv)
{
  GtkWidget *panel;
  GtkWidget *frame;
  GtkWidget *box;
  GtkWidget *menu_applet;

  /* Set the GMemVTable to the default table. This will help track memory
   * information, which will be output by g_mem_profile(). */
  g_mem_set_vtable (glib_mem_profiler_table);
  /* Call g_mem_profile() when the application exits. */
  g_atexit (g_mem_profile);

  gtk_init(&argc, &argv);

  panel = gtk_taimen_panel_new (GTK_TAIMEN_PANEL_ORIENT_TOP, 0.8);

  //	gint sw;
  //	g_object_get(G_OBJECT(panel), "screen-max-width", &sw, NULL);
  //	g_message("width: %d", sw);
  //	gint sh;
  //	g_object_get(G_OBJECT(panel), "screen-max-height", &sh, NULL);
  //	g_message("height: %d", sh);

  //if (GTK_IS_CONTAINER (panel))
  //	g_message ("TRUE: window is a container");

  /* Add frame */
  frame = g_object_new (GTK_TYPE_FRAME,
			"shadow-type", GTK_SHADOW_ETCHED_OUT,
			NULL);

  gtk_container_add (GTK_CONTAINER (panel), frame);

  box = gtk_hbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (frame), box);

  menu_applet = taimen_menu_applet_new ("./data/menu.png");

  //	applet = gtk_taimen_applet_new ("./menu.png", 20, 20, 0);
  gtk_box_pack_start (GTK_BOX (box), GTK_WIDGET (menu_applet),
		      FALSE, FALSE, 0);

  //	GtkWidget *image;
  //	image = gtk_taimen_image_new ("./menu.png", 20, 20);
  /////	g_object_set (G_OBJECT(applet),
  /////				  "image-path", "./menu2.png",
  /////				  NULL);

  //	gtk_box_pack_start (GTK_BOX (box), GTK_WIDGET (image), FALSE, FALSE, 0);


  //	g_object_set (G_OBJECT(applet), "image-path", "boo", NULL);

  //	gtk_box_pack_start (GTK_BOX (box), applet, FALSE, FALSE, 0);
  //	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale ("./menu.png",
  //														   23, 23,
  //														   TRUE,
  //														   NULL);

  //	GtkImage *image = g_object_new (GTK_TYPE_IMAGE,
  //									NULL);
  //	if (pixbuf) {
  //		gtk_image_set_from_pixbuf (GTK_IMAGE (image), pixbuf);
  //		gtk_box_pack_start (GTK_BOX (box), GTK_WIDGET (image), FALSE, FALSE, 0);
  //	}

  gtk_widget_show_all(panel);

  gtk_main ();

  gtk_widget_destroy (panel);
  /*
    GtkWidget *window;
    GdkScreen *screen;
    GtkWidget *frame, *box;
    GtkWidget *toolbar;

    GtkToolItem *tool1, *tool2;
    GtkToolItem *sep;

    int panel_width, panel_height;

    gtk_init(&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    //	make_shaped_widget (&window);
    screen = gtk_window_get_screen (GTK_WINDOW (window));

    gtk_window_set_title(GTK_WINDOW(window), "Toolbar window");
    // Hide wm reparented windows
    gtk_window_set_type_hint (GTK_WINDOW (window),
    GDK_WINDOW_TYPE_HINT_DOCK);
    // Do not accept keyboard focus
    gtk_window_set_accept_focus (GTK_WINDOW (window), FALSE);

    // Handle window sizes
    gtk_window_set_default_size (GTK_WINDOW (window),
    gdk_screen_get_width (screen),
    DEFAULT_HEIGHT);
    gtk_window_get_size (GTK_WINDOW (window), &panel_width, &panel_height);
    gtk_widget_set_size_request (window, panel_width, panel_height);
    gtk_window_resize (GTK_WINDOW (window), panel_width, panel_height);

    frame = gtk_frame_new (NULL);
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_NONE);
    gtk_container_add (GTK_CONTAINER (window), frame);
    gtk_widget_show (frame);

    box = gtk_hbox_new (FALSE, 10);
    gtk_container_add (GTK_CONTAINER (frame), box);
    gtk_widget_show (box);

    toolbar = gtk_toolbar_new();

    gtk_toolbar_set_style (GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    gtk_toolbar_set_icon_size (GTK_TOOLBAR(toolbar), GTK_ICON_SIZE_SMALL_TOOLBAR);
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    gtk_toolbar_set_style (GTK_TOOLBAR(toolbar), GTK_SHADOW_NONE);

    gtk_container_set_border_width(GTK_CONTAINER(toolbar), 0);

    tool1 = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool1, -1);

    sep = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);

    tool2 = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool2, -1);

    gtk_box_pack_start(GTK_BOX(box), toolbar, TRUE, TRUE, 1);
    gtk_widget_show_all(toolbar);

    gtk_widget_realize (window);

    if (TITLEBAR) {
    const char *names[] = {
    "_MB_WM_STATE",
    "_MB_WM_STATE_DOCK_TITLEBAR",
    "_MB_DOCK_TITLEBAR_SHOW_ON_DESKTOP"
    };
    Atom atoms[G_N_ELEMENTS (names)];

    XInternAtoms (GDK_DISPLAY (), (char**)names,
    G_N_ELEMENTS (names), False, atoms);

    XChangeProperty (GDK_DISPLAY (),
    GDK_WINDOW_XID (window->window),
    atoms[0], XA_ATOM, 32,
    PropModeReplace,
    (unsigned char *) &atoms[1], 2);
    } else {
    Atom net_wm_strut;
    gulong struts [4] = { 0, 0, panel_height, 0 };

    gdk_error_trap_push ();
    net_wm_strut = XInternAtom (GDK_DISPLAY () , "_NET_WM_STRUT", False);
    XChangeProperty (GDK_DISPLAY (),
    GDK_WINDOW_XID (window->window),
    net_wm_strut, XA_CARDINAL, 32,
    PropModeReplace,
    (guchar *) &struts, 4);
    gdk_error_trap_pop ();
    }

    gtk_widget_show (window);

    gtk_main ();

    gtk_widget_destroy (window);
  */
  return 0;
}
