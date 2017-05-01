#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include "CB_dessin.c"



static void clear_surface (void);
void plus_taille();
void moins_taille(void);
void set_r(double x);
void set_g(double x);
void set_b(double x);
void set_a(double x);
void set_j(int x);
void set_color(double x, double y, double z, double c);
void set_plein(int x);
int get_plein();

static gboolean
configure_event_cb (GtkWidget         *widget,
            GdkEventConfigure *event,
            gpointer           data);

void SetSurface (char *path);

static gboolean draw_cb (GtkWidget *widget, cairo_t   *cr, gpointer   data);

static void
draw_brush_libre (GtkWidget *widget);

static void
draw_brush_effacer (GtkWidget *widget);

static void
draw_brush_ligne (GtkWidget *widget);

static void
draw_brush_rec (GtkWidget *widget);

static void
draw_brush_cercle (GtkWidget *widget);

static gboolean clicked(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data);

static gboolean released(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data);

static gboolean
motion_notify_event_cb (GtkWidget      *widget,
                GdkEventMotion *event,
                gpointer        data);
