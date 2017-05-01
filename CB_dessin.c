#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int tailleD = 2; //taille du trait dessine
int tailleE = 12; //taille du trait efface
double r = 0; //r,g,b sont les 3 couleurs a modifier
double g = 0;
double b = 0;
double a = 1; //a sert a definir la transparence de ce que l'on dessine
double r_fond = 1; 
double g_fond = 1;
double b_fond = 1; //r_fond, g_fond, b_fond sont les couleurs du fond
double a_fond = 1;
int j = 16;
int plein = 0;
int imp = 0;
GtkWidget *p_da;
static cairo_surface_t *surface = NULL;
int changed = 0;

void plus_taille()
{
  tailleD = tailleD + 1;
}
void moins_taille(void)
{
  if (tailleD > 1)
tailleD = tailleD - 1;
}
void set_r(double x)
{
  r = x;
}
void set_g(double x)
{
  g = x;
}
void set_b(double x)
{
  b = x;
}
void set_a(double x)
{
  a = x;
}
void set_j(int x)
{
  j = x;
}
void set_noir()
{
r = 0;
g = 0;
b = 0;   
}
void set_red()
{
r = 237.0/255.0;
g = 28.0/255.0;
b = 36.0/255.0;   
}
void set_jaune()
{
r = 255.0/255.0;
g = 242.0/255.0;
b = 0.0/255.0;   
}
void set_vert()
{
r = 34.0/255.0;
g = 177.0/255.0;
b = 76.0/255.0;   
}
void set_bleu()
{
r = 63.0/255.0;
g = 72.0/255.0;
b = 204.0/255.0;   
}
void set_color(double x, double y, double z, double c)
{
r = x;
g = y;
b = z;
a = c;   
}
void set_plein(int x)
{
plein = x;   
}
int get_plein()
{
return plein;
}

void SetChange();


struct {
  double coordx1;
  double coordy1;
  double coordx2;
  double coordy2;
  double coordx3;
  double coordy3;
  double coordx4;
  double coordy4;
} glob;

void SetSurface (char *path){
  surface = cairo_image_surface_create_from_png(path);
  gtk_widget_queue_draw_area (p_da, 0, 0, 2000, 2000);
}


static void
clear_surface (void)
{
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgba (cr, r_fond, g_fond, b_fond,a_fond);
  cairo_paint (cr);
			char nom[30];
      strcpy(nom, ".png.tmp");
      char nb[5];
      sprintf(nb, "%d", imp);
  	  strcat(nom, nb);
  	  cairo_surface_write_to_png(surface,nom);
  	  imp++;

  cairo_destroy (cr);
}


static gboolean
configure_event_cb (GtkWidget         *widget,
            GdkEventConfigure *event,
            gpointer           data)
{
  if (surface)
    cairo_surface_destroy (surface);

  surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
                                       CAIRO_CONTENT_COLOR,
                                       gtk_widget_get_allocated_width (widget),
                                       gtk_widget_get_allocated_height (widget));


  clear_surface ();
  (void)event;
  (void)data;

  return TRUE;
}


static gboolean
draw_cb (GtkWidget *widget,
 cairo_t   *cr,
 gpointer   data)
{
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);

  (void)widget;
  (void)data;

  return FALSE;
}


static void
draw_brush_libre (GtkWidget *widget)
{
  cairo_t *cr;


  cr = cairo_create (surface);
  cairo_set_source_rgb(cr, r, g, b);


  cairo_set_line_width(cr,tailleD);

  cairo_move_to(cr, glob.coordx3, glob.coordy3);
  cairo_line_to(cr, glob.coordx4, glob.coordy4);
  cairo_stroke_preserve (cr);
  cairo_destroy (cr);
  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}


static void
draw_brush_effacer (GtkWidget *widget)
{
  cairo_t *cr;


  cr = cairo_create (surface);
  cairo_set_source_rgb(cr, r_fond, g_fond, b_fond);


  cairo_set_line_width(cr,tailleE);

  cairo_move_to(cr, glob.coordx3, glob.coordy3);
  cairo_line_to(cr, glob.coordx4, glob.coordy4);
  cairo_stroke_preserve(cr);
  cairo_destroy (cr);
  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}



static void
draw_brush_ligne (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  cairo_set_line_width(cr,2);

  cairo_move_to(cr, glob.coordx1-10, glob.coordy1-10);
  cairo_line_to(cr, glob.coordx2-10, glob.coordy2-10);
  cairo_stroke_preserve (cr);
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}

static void
draw_brush_los (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x1,y1,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx1;
      y1 = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx1;
      y1 = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx2;
      y1 = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx2;
      y1 = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_move_to(cr, x1 + width/2, y1);
  cairo_line_to(cr, x1 + width, y1 + height/2);
  cairo_line_to(cr, x1 + width/2, y1 + height);
  cairo_line_to(cr, x1, y1 + height/2);
  cairo_line_to(cr, x1 + width/2, y1);
  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}


static void
draw_brush_etoile4 (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x1,y1,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx1;
      y1 = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx1;
      y1 = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx2;
      y1 = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx2;
      y1 = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_move_to(cr, x1, y1 + height/2);
  cairo_line_to(cr, x1 + (4 * width)/10, y1 + (4 * height)/10);
  cairo_line_to(cr, x1 + width/2,y1);
  cairo_line_to(cr, x1 + (6 * width)/10, y1 + (4 * height)/10);
  cairo_line_to(cr, x1 + width, y1 + height/2);
  cairo_line_to(cr, x1 + (6 * width)/10, y1 + (6 * height)/10);
  cairo_line_to(cr, x1 + width/2,y1 + height);
  cairo_line_to(cr, x1 + (4 * width)/10, y1 + (6 * height)/10);
  cairo_line_to(cr,  x1, y1 + height/2);
  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}



static void
draw_brush_etoile5 (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x1,y1,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx1;
      y1 = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx1;
      y1 = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx2;
      y1 = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx2;
      y1 = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_move_to(cr, x1, y1 + (4 *height)/10);
  cairo_line_to(cr, x1 + (4 * width)/10, y1 + (4 * height)/10);
  cairo_line_to(cr, x1 + width/2,y1);
  cairo_line_to(cr, x1 + (6 * width)/10, y1 + (4 * height)/10);
  cairo_line_to(cr, x1 + width , y1 + (4 * height)/10);
  cairo_line_to(cr, x1 + (7 * width)/10, y1 + (6 * height)/10);
  cairo_line_to(cr, x1 + (8 * width)/10, y1 + height);
  cairo_line_to(cr, x1 + width/2,y1 + (15 * height)/20);
  cairo_line_to(cr, x1 + (2 * width)/10,y1 + height);
  cairo_line_to(cr, x1 + (3 * width)/10, y1 + (6 * height)/10);
  cairo_line_to(cr, x1, y1 + (4 *height)/10);
  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}



static void
draw_brush_etoile6 (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x1,y1,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx1;
      y1 = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx1;
      y1 = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx2;
      y1 = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx2;
      y1 = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_move_to(cr, x1, y1 + (5 *height)/20);
  cairo_line_to(cr, x1 + (3 * width)/10, y1 + (5 * height)/20);
  cairo_line_to(cr, x1 + (5 * width)/10, y1);
  cairo_line_to(cr, x1 + (7 * width)/10, y1 + (5 * height)/20);
  cairo_line_to(cr, x1 + (10 * width)/10, y1 + (5 * height)/20);
  cairo_line_to(cr, x1 + (9 * width)/10, y1 + (5 * height)/10);
  cairo_line_to(cr, x1 + (10 * width)/10, y1 + (15 * height)/20);
  cairo_line_to(cr, x1 + (7 * width)/10, y1 + (15 * height)/20);
  cairo_line_to(cr, x1 + (5 * width)/10, y1 + (10 * height)/10);
  cairo_line_to(cr, x1 + (3 * width)/10, y1 + (15 * height)/20);
  cairo_line_to(cr, x1 , y1 + (15 * height)/20);
  cairo_line_to(cr, x1 + (1 * width)/10, y1 + (5 * height)/10);
  cairo_line_to(cr, x1 , y1 + (5 * height)/20);
  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}


static void
draw_brush_penta (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x1,y1,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx1;
      y1 = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx1;
      y1 = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx2;
      y1 = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx2;
      y1 = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_move_to(cr, x1, y1 + (4 *height)/10);
  cairo_line_to(cr, x1 + (5 * width)/10, y1);
  cairo_line_to(cr, x1 + (10 * width)/10, y1 + (4 * height)/10);
  cairo_line_to(cr, x1 + (8 * width)/10, y1 + (10 * height)/10);
  cairo_line_to(cr, x1 + (2 * width)/10, y1 + (10 * height)/10);
  cairo_line_to(cr, x1 , y1 + (4 * height)/10);

  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}


static void
draw_brush_hexa (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x1,y1,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx1;
      y1 = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx1;
      y1 = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx2;
      y1 = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx2;
      y1 = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_move_to(cr, x1, y1 + (5 *height)/20);
  cairo_line_to(cr, x1 + (5 * width)/10, y1);
  cairo_line_to(cr, x1 + (10 * width)/10, y1 + (5 * height)/20);
  cairo_line_to(cr, x1 + (10 * width)/10, y1 + (15 * height)/20);
  cairo_line_to(cr, x1 + (5 * width)/10, y1 + (10 * height)/10);
  cairo_line_to(cr, x1 , y1 + (15 * height)/20);
  cairo_line_to(cr, x1 , y1 + (5 * height)/20);

  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}


static void
draw_brush_flecheG (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x1,y1,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx1;
      y1 = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx1;
      y1 = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx2;
      y1 = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx2;
      y1 = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_move_to(cr, x1, y1 + (5 *height)/10);
  cairo_line_to(cr, x1 + (10 * width)/10, y1);
  cairo_line_to(cr, x1 + (7 * width)/10, y1 +(5 * height)/10);
  cairo_line_to(cr, x1 + (10 * width)/10, y1 +(10 * height)/10);
  cairo_line_to(cr, x1 , y1 + (5 * height)/10);

  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}


static void
draw_brush_flecheD (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x1,y1,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx1;
      y1 = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx1;
      y1 = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx2;
      y1 = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx2;
      y1 = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_move_to(cr, x1, y1);
  cairo_line_to(cr, x1 + (10 * width)/10, y1 +(5 * height)/10);
  cairo_line_to(cr, x1, y1 +(10 * height)/10);
  cairo_line_to(cr, x1 + (3 * width)/10, y1 +(5 * height)/10);
  cairo_line_to(cr, x1 , y1);

  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}



static void
draw_brush_flecheH (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x1,y1,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx1;
      y1 = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx1;
      y1 = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx2;
      y1 = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx2;
      y1 = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_move_to(cr, x1 , y1 +(10 * height)/10);
  cairo_line_to(cr, x1 + (5 * width)/10, y1);
  cairo_line_to(cr, x1 + (10 * width)/10, y1 +(10 * height)/10);
  cairo_line_to(cr, x1 + (5 * width)/10, y1 +(7 * height)/10);
  cairo_line_to(cr, x1 , y1 +(10 * height)/10);

  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}



static void
draw_brush_flecheB (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x1,y1,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx1;
      y1 = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx1;
      y1 = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx2;
      y1 = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx2;
      y1 = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_move_to(cr, x1, y1);
  cairo_line_to(cr, x1 + (5 * width)/10, y1 +(3 * height)/10);
  cairo_line_to(cr, x1 + (10 * width)/10, y1);
  cairo_line_to(cr, x1 + (5 * width)/10, y1 +(10 * height)/10);
  cairo_line_to(cr, x1, y1);

  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}



static void
draw_brush_trapeze (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x1,y1,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx1;
      y1 = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx1;
      y1 = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx2;
      y1 = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx2;
      y1 = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_move_to(cr, x1 + (3 * width)/10, y1);
  cairo_line_to(cr, x1 + (7 * width)/10, y1);
  cairo_line_to(cr, x1 + (10 * width)/10, y1 + (10 * height)/10);
  cairo_line_to(cr, x1 , y1 + (10 * height)/10);
  cairo_line_to(cr, x1 + (3 * width)/10, y1);

  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}




static void
draw_brush_triangle (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x1,y1,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx1;
      y1 = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx1;
      y1 = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x1 = glob.coordx2;
      y1 = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x1 = glob.coordx2;
      y1 = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_move_to(cr, x1 + width/2, y1);
  cairo_line_to(cr, x1 + width, y1 + height);
  cairo_line_to(cr, x1, y1 + height);
  cairo_line_to(cr, x1 + width/2, y1);
  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}




static void
draw_brush_rec (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x,y,width,height;
  if (glob.coordx1 <= glob.coordx2){
    if (glob.coordy1 <= glob.coordy2){
      x = glob.coordx1;
      y = glob.coordy1;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x = glob.coordx1;
      y = glob.coordy2;
      width = glob.coordx2-glob.coordx1;
      height = glob.coordy1-glob.coordy2;
    }
  }
  else {
    if (glob.coordy1 <= glob.coordy2){
      x = glob.coordx2;
      y = glob.coordy1;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy2-glob.coordy1;
    }
    else {
      x = glob.coordx2;
      y = glob.coordy2;
      width = glob.coordx1-glob.coordx2;
      height = glob.coordy1-glob.coordy2;
    }
  }
  cairo_rectangle(cr,x,y,width,height);
  if (plein == 0){
    cairo_stroke_preserve (cr);
  }
  else {
    cairo_fill_preserve (cr);
  }
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}


static void
draw_brush_cercle (GtkWidget *widget)
{
  cairo_t *cr;
  

  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x,y,radius,an,b;
  x = glob.coordx1;
  y = glob.coordy1;
  an = glob.coordx1-glob.coordx2;
  b = glob.coordy1-glob.coordy2;
  radius = (an*an)+(b*b);
  cairo_arc(cr,x-6,y-6,sqrt(radius)-6,0,360);
  if (plein == 0){
    cairo_stroke (cr);
  }
  else {
    cairo_fill (cr);
  }
  cairo_destroy (cr);
  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);

}




static gboolean clicked(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data)
{

    if (event->button == 1) {
      if (j > 15){
	glob.coordx3 = event->x;
        glob.coordy3 = event->y;
        glob.coordx4 = event->x;
        glob.coordy4 = event->y;
      }
      if (j < 17){
        glob.coordx1 = event->x;
        glob.coordy1 = event->y;
      }
    }
    else if (event->button == 2){
      j = j + 1;
      if (j > 17){
	j = 1;
      }
    }
  if (event->button == 3){
      clear_surface ();
      gtk_widget_queue_draw (widget);
  }
  (void) widget;
  (void) user_data;

  return TRUE;
}


static gboolean released(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data)
{
    if (event->button == 1) {
	if (j<16){
		glob.coordx2 = event->x;
        	glob.coordy2 = event->y;
	}	
	if (j==1){
        	draw_brush_cercle(widget);
		gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
	}
	if (j==2){
        	draw_brush_ligne(widget);
		gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
	}
	if (j==3){
        	draw_brush_rec(widget);
		gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
	}
        if (j==4){
        	draw_brush_los(widget);
	}
        if (j==5){
		draw_brush_triangle(widget);
	}
        if (j==6){
		draw_brush_etoile4(widget);
	}
        if (j==7){
		draw_brush_etoile5(widget);
	}
        if (j==8){
		draw_brush_etoile6(widget);
	}
        if (j==9){
        	draw_brush_penta(widget);
	}
        if (j==10){
		draw_brush_hexa(widget);
	}
        if (j==11){
        	draw_brush_flecheG(widget);
	}
        if (j==12){
        	draw_brush_flecheD(widget);
	}
        if (j==13){
        	draw_brush_flecheH(widget);
	}
        if (j==14){
        	draw_brush_flecheB(widget);
	}
        if (j==15){
        	draw_brush_trapeze(widget);
	}
					changed = 1;
          char nom[30];
          strcpy(nom, ".png.tmp");
          char nb[5];
          sprintf(nb, "%d", imp);
  	  strcat(nom, nb);
  	  cairo_surface_write_to_png(surface,nom);
  	  imp++;
    }

	(void) user_data;
    return TRUE;
}



static gboolean
motion_notify_event_cb (GtkWidget      *widget,
                GdkEventMotion *event,
                gpointer        data)
{

  if (surface == NULL)
    return FALSE;

  if (event->state & GDK_BUTTON1_MASK){
      glob.coordx4 = event->x;
      glob.coordy4 = event->y;
      glob.coordx2 = event->x;
      glob.coordy2 = event->y;
      if (j == 16){
        draw_brush_libre (widget);
      }
      else if (j == 17){
        draw_brush_effacer (widget);
      }
      glob.coordx3 = event->x;
      glob.coordy3 = event->y;
  }
  (void)data;

  return TRUE;
}


/*static void
close_window (void)
{
  if (surface)
    cairo_surface_destroy (surface);

  gtk_main_quit ();
}

int
main (int   argc,
      char *argv[])
{
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *da;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Drawing Area");

  g_signal_connect (window, "destroy", G_CALLBACK (close_window), NULL);

  gtk_container_set_border_width (GTK_CONTAINER (window), 8);

  frame = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
  gtk_container_add (GTK_CONTAINER (window), frame);

  da = gtk_drawing_area_new ();

  gtk_widget_set_size_request (da, 500, 500);

  gtk_container_add (GTK_CONTAINER (frame), da);


  g_signal_connect (da, "draw",
            G_CALLBACK (draw_cb), NULL);
  g_signal_connect (da,"configure-event",
            G_CALLBACK (configure_event_cb), NULL);


  g_signal_connect (da, "motion-notify-event",
            G_CALLBACK (motion_notify_event_cb), NULL);
  g_signal_connect(window, "button-press-event", 
      G_CALLBACK(clicked), NULL);
  g_signal_connect(window, "button-release-event", 
      G_CALLBACK(released), NULL);

  gtk_widget_set_events (da, gtk_widget_get_events (da)
                     | GDK_BUTTON_PRESS_MASK
                     | GDK_POINTER_MOTION_MASK
		     | GDK_BUTTON_RELEASE_MASK);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}*/
