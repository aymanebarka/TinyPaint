# include <gtk-3.0/gtk/gtk.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <gdk/gdk.h>
# include <math.h>
# include "CB_dessin.h"
# include "loadnsave.h"
# include "converter.h"
# include "filters.h"

//****************************FONCTION POUR CALLBACK BUTTON********************
void popup(GtkWidget *widget)
{
  GdkRGBA color;
  int res;
  GtkColorChooserDialog *dialog;
  double r, g, b, a;

  color.red = 1;
  color.green = 1;
  color.blue = 1;
  color.alpha = 1;

  dialog = GTK_COLOR_CHOOSER_DIALOG
    (gtk_color_chooser_dialog_new("color chooser", NULL));

  gtk_color_chooser_set_use_alpha(GTK_COLOR_CHOOSER(dialog), TRUE);

  gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(dialog), &color);

  res = gtk_dialog_run(GTK_DIALOG(dialog));

  if (res == GTK_RESPONSE_OK) {
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(dialog), &color);
    r = color.red;
    g = color.green;
    b = color.blue;
    a = color.alpha;
    set_color(r, g, b, a);
  }

  gtk_widget_destroy(GTK_WIDGET(dialog));
  (void) widget;
}

void actualiser (GtkWidget *widget)
{
  cairo_t *cr;
  cr = cairo_create (surface);
  cairo_set_source_rgba(cr, r, g, b, a);
  double x,y,radius,a,b;
  x = 0;
  y = 0;
  a = 0;
  b = 0;
  radius = (a*a)+(b*b);
  cairo_arc(cr,x-6,y-6,sqrt(radius)-6,0,0);
  cairo_stroke_preserve (cr);
  cairo_surface_write_to_png(surface,".png.tmp");
  cairo_destroy (cr);

  gtk_widget_queue_draw_area (widget, 0, 0, 2000, 2000);
}

void newfile(GtkButton *button, GtkWidget *window)
{
  if (PopupNew(window) == 1) {
    clear_surface();
    SetNewFile();
    actualiser(window);
  }
  (void) button;
}

void togrey(GtkWidget *widget)
{
	char nom[30];
	char nom2[30];
	strcpy(nom, ".png.tmp");
	strcpy(nom2, ".png.tmp");
	char nb[5];
	char nb2[5];
	sprintf(nb, "%d", imp-1);
	sprintf(nb2, "%d", imp);
	strcat(nom, nb);
	strcat(nom2, nb2);

	GError **error = NULL;
  GdkPixbuf *Im = gdk_pixbuf_new_from_file(nom, error);
  to_grey(Im);
  gdk_pixbuf_save(Im, nom2, "png", error, NULL);
  SetSurface(nom2);
  SetChange();
	imp++;
	(void) widget;
}
void negativ(GtkWidget *widget)
{
	char nom[30];
	char nom2[30];
	strcpy(nom, ".png.tmp");
	strcpy(nom2, ".png.tmp");
	char nb[5];
	char nb2[5];
	sprintf(nb, "%d", imp-1);
	sprintf(nb2, "%d", imp);
	strcat(nom, nb);
	strcat(nom2, nb2);

	GError **error = NULL;
  GdkPixbuf *Im = gdk_pixbuf_new_from_file(nom, error);
  negative(Im);
  gdk_pixbuf_save(Im, nom2, "png", error, NULL);
  SetSurface(nom2);
  SetChange();
	imp++;
	(void) widget;
}
void adjust(GtkWidget *widget)
{
	char nom[30];
	char nom2[30];
	strcpy(nom, ".png.tmp");
	strcpy(nom2, ".png.tmp");
	char nb[5];
	char nb2[5];
	sprintf(nb, "%d", imp-1);
	sprintf(nb2, "%d", imp);
	strcat(nom, nb);
	strcat(nom2, nb2);

  GError **error = NULL;
  GdkPixbuf *Im = gdk_pixbuf_new_from_file(nom, error);
  adjust_RGB(Im,r*255,g*255,b*255);
  gdk_pixbuf_save(Im, nom2, "png", error, NULL);
  SetSurface(nom2);
  SetChange();
	imp++;
	(void) widget;
}
void seuil(GtkWidget *widget)
{
  char nom[30];
	char nom2[30];
	strcpy(nom, ".png.tmp");
	strcpy(nom2, ".png.tmp");
	char nb[5];
	char nb2[5];
	sprintf(nb, "%d", imp-1);
	sprintf(nb2, "%d", imp);
	strcat(nom, nb);
	strcat(nom2, nb2);

  GError **error = NULL;
  GdkPixbuf *Im = gdk_pixbuf_new_from_file(nom, error);
  seuillage(Im,1, 122,0,0,0);
  gdk_pixbuf_save(Im, nom2, "png", error, NULL);
  SetSurface(nom2);
  SetChange();
	imp++;
	(void) widget;
}

void artist(GtkWidget *widget)
{
  char nom[30];
	char nom2[30];
	strcpy(nom, ".png.tmp");
	strcpy(nom2, ".png.tmp");
	char nb[5];
	char nb2[5];
	sprintf(nb, "%d", imp-1);
	sprintf(nb2, "%d", imp);
	strcat(nom, nb);
	strcat(nom2, nb2);

  GError **error = NULL;
  GdkPixbuf *Im = gdk_pixbuf_new_from_file(nom, error);
  artistique(Im);
  gdk_pixbuf_save(Im, nom2, "png", error, NULL);
  SetSurface(nom2);
  SetChange();
	imp++;
	(void) widget;
}

void medi(GtkWidget *widget)
{
  char nom[30];
	char nom2[30];
	strcpy(nom, ".png.tmp");
	strcpy(nom2, ".png.tmp");
	char nb[5];
	char nb2[5];
	sprintf(nb, "%d", imp-1);
	sprintf(nb2, "%d", imp);
	strcat(nom, nb);
	strcat(nom2, nb2);

  GError **error = NULL;
  GdkPixbuf *Im = gdk_pixbuf_new_from_file(nom, error);
  median(Im);
  gdk_pixbuf_save(Im, nom2, "png", error, NULL);
  SetSurface(nom2);
  SetChange();
	imp++;
	(void) widget;
}

void rotiD(GtkWidget *widget)
{
  char nom[30];
	char nom2[30];
	strcpy(nom, ".png.tmp");
	strcpy(nom2, ".png.tmp");
	char nb[5];
	char nb2[5];
	sprintf(nb, "%d", imp-1);
	sprintf(nb2, "%d", imp);
	strcat(nom, nb);
	strcat(nom2, nb2);

  GError **error = NULL;
  GdkPixbuf *Im = gdk_pixbuf_new_from_file(nom, error);
  Im = gdk_pixbuf_rotate_simple(Im,270);
  gdk_pixbuf_save(Im, nom2, "png", error, NULL);
  SetSurface(nom2);
  SetChange();
	imp++;
	(void) widget;
}

void rotiG(GtkWidget *widget)
{
  char nom[30];
	char nom2[30];
	strcpy(nom, ".png.tmp");
	strcpy(nom2, ".png.tmp");
	char nb[5];
	char nb2[5];
	sprintf(nb, "%d", imp-1);
	sprintf(nb2, "%d", imp);
	strcat(nom, nb);
	strcat(nom2, nb2);

  GError **error = NULL;
  GdkPixbuf *Im = gdk_pixbuf_new_from_file(nom, error);
  Im = gdk_pixbuf_rotate_simple(Im,90);
  gdk_pixbuf_save(Im, nom2, "png", error, NULL);
  SetSurface(nom2);
  SetChange();
	imp++;
	(void) widget;
}

void mirH(GtkWidget *widget)
{
  char nom[30];
	char nom2[30];
	strcpy(nom, ".png.tmp");
	strcpy(nom2, ".png.tmp");
	char nb[5];
	char nb2[5];
	sprintf(nb, "%d", imp-1);
	sprintf(nb2, "%d", imp);
	strcat(nom, nb);
	strcat(nom2, nb2);

  GError **error = NULL;
  GdkPixbuf *Im = gdk_pixbuf_new_from_file(nom, error);
  Im = gdk_pixbuf_flip(Im,TRUE);
  gdk_pixbuf_save(Im, nom2, "png", error, NULL);
  SetSurface(nom2);
  SetChange();
	imp++;
	(void) widget;
}

void mirV(GtkWidget *widget)
{
  char nom[30];
	char nom2[30];
	strcpy(nom, ".png.tmp");
	strcpy(nom2, ".png.tmp");
	char nb[5];
	char nb2[5];
	sprintf(nb, "%d", imp-1);
	sprintf(nb2, "%d", imp);
	strcat(nom, nb);
	strcat(nom2, nb2);

  GError **error = NULL;
  GdkPixbuf *Im = gdk_pixbuf_new_from_file(nom, error);
  Im = gdk_pixbuf_flip(Im,FALSE);
  gdk_pixbuf_save(Im, nom2, "png", error, NULL);
  SetSurface(nom2);
  SetChange();
	imp++;
	(void) widget;
}


void plus(GtkWidget *widget)
{
  plus_taille();
  (void) widget;
}
void moins(GtkWidget *widget)
{
  moins_taille();
  (void) widget;
}
/***********************  SET J / changement des modes***********************/
void set_pinceau(GtkWidget *widget)
{
  set_j(16);
  (void) widget;
}
void set_gomme(GtkWidget *widget)
{
  set_j(17);
  (void) widget;
}
void set_cercle(GtkWidget *widget)
{
  set_j(1);
  (void) widget;
}
void set_rectangle(GtkWidget *widget)
{
  set_j(3);
  (void) widget;
}
void set_ligne(GtkWidget *widget)
{
  set_j(2);
  (void) widget;
}
void set_losange(GtkWidget *widget)
{
  set_j(4);
  (void) widget;
}
void set_triangle(GtkWidget *widget)
{
  set_j(5);
  (void) widget;
}
void set_etoile4(GtkWidget *widget)
{
  set_j(6);
  (void) widget;
}
void set_etoile5(GtkWidget *widget)
{
  set_j(7);
  (void) widget;
}
void set_etoile6(GtkWidget *widget)
{
  set_j(8);
  (void) widget;
}
void set_penta(GtkWidget *widget)
{
  set_j(9);
  (void) widget;
}
void set_hexa(GtkWidget *widget)
{
  set_j(10);
  (void) widget;
}
void set_flecheg(GtkWidget *widget)
{
  set_j(11);
  (void) widget;
}
void set_fleched(GtkWidget *widget)
{
  set_j(12);
  (void) widget;
}
void set_flecheh(GtkWidget *widget)
{
  set_j(13);
  (void) widget;
}
void set_flecheb(GtkWidget *widget)
{
  set_j(14);
  (void) widget;
}
void set_trapeze(GtkWidget *widget)
{
  set_j(15);
  (void) widget;
}
void togg (GtkWidget *widget, gpointer data)
{
         if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data)))
	{
	   set_plein(1);
	}
	 else
	   set_plein(0);
	(void)widget;
}
void mode(GtkWidget *widget)
{
  if (get_plein() == 0)
set_plein(1);
  else
set_plein(0);
  (void) widget;
}
// **************** Event KeyBoard *****************************************

static gboolean keyboard(GtkWidget *widget, GdkEventKey *event,
								    		 gpointer user_data) {
				switch (event->keyval) {
					case GDK_KEY_z :
						if (event->state == 20 && imp > 1) {
							char nom[30];
							strcpy(nom, ".png.tmp");
							char nb[5];
							sprintf(nb, "%d", imp-2);
							strcat(nom, nb);
							SetSurface(nom);
							imp--;
						}
						break;
				}
	(void) user_data;
	(void) widget;
	return TRUE;
}



// **************** Creation fenetre entiere *****************************************
void fenetre()
{
  // ********************************* Init widget
  GtkWidget *home;
  GtkWidget *grid;
  GtkWidget *new_file;
  GtkWidget *open;
  GtkWidget *save;
  GtkWidget *saveAs;
  GtkWidget *quit;
  GtkWidget *convert;
  GtkWidget *image = gtk_image_new_from_file("logo.jpg");
  GtkWidget *darea = gtk_drawing_area_new();
	p_da = darea;
  GtkWidget *frame;
	GError *error;

  // ************************** Home
  home = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(home), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(home), 600,400);
  gtk_window_set_title (GTK_WINDOW(home),"TinyPaint");
  gtk_window_set_icon(GTK_WINDOW(home),
									gdk_pixbuf_new_from_file("icone/pinceau.png", &error));
	grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(home),grid);

  //********************* Menu
  new_file = gtk_button_new_with_label("New file");
  open = gtk_button_new_with_label ("Open file");
  save = gtk_button_new_with_label ("Save");
  saveAs = gtk_button_new_with_label ("Save As");
  convert = gtk_button_new_with_label ("Convert");
  quit = gtk_button_new_with_label ("Quit");

  //********************** ToolBox/Palette
  GtkWidget *palette = gtk_tool_palette_new();
  GtkWidget *tool = gtk_tool_item_group_new ("ToolBox");
  GtkToolItem *ligne = gtk_tool_button_new(NULL,"Ligne");
  GtkToolItem *pinceau = gtk_tool_button_new(NULL,"Pinceau");
  GtkToolItem *cercle = gtk_tool_button_new(NULL,"Cercle");
  GtkToolItem *rectangle = gtk_tool_button_new(NULL,"Rectangle");
  GtkToolItem *gomme = gtk_tool_button_new(NULL,"Gomme");
  GtkToolItem *moins = gtk_tool_button_new(NULL,"Moins");
  GtkToolItem *plus = gtk_tool_button_new(NULL,"Plus");
  GtkToolItem *losange = gtk_tool_button_new(NULL,"Losange");
  GtkToolItem *triangle = gtk_tool_button_new(NULL,"Triangle");
  GtkToolItem *etoile4 = gtk_tool_button_new(NULL,"4*");
  GtkToolItem *etoile5 = gtk_tool_button_new(NULL,"5*");
  GtkToolItem *etoile6 = gtk_tool_button_new(NULL,"6*");
  GtkToolItem *penta = gtk_tool_button_new(NULL,"Pentagone");
  GtkToolItem *hexa = gtk_tool_button_new(NULL,"Hexagone");
  GtkToolItem *flecheg = gtk_tool_button_new(NULL,"Fleche Gauche");
  GtkToolItem *fleched = gtk_tool_button_new(NULL,"Fleche Droite");
  GtkToolItem *flecheh = gtk_tool_button_new(NULL,"Fleche Haut");
  GtkToolItem *flecheb = gtk_tool_button_new(NULL,"Fleche droite");
  GtkToolItem *trapeze = gtk_tool_button_new(NULL,"Trapeze");
  GtkWidget *plein = gtk_check_button_new_with_label("Plein");
  GtkToolItem *rotg = gtk_tool_button_new(NULL,"Rotg");
  GtkToolItem *rotd = gtk_tool_button_new(NULL,"Rotd");


  GtkWidget *pinceaulogo = gtk_image_new_from_file ("icone/pinceau.png");
  GtkWidget *lignelogo = gtk_image_new_from_file ("icone/ligne.png");
  GtkWidget *rectanglelogo = gtk_image_new_from_file ("icone/rectangle.png");
  GtkWidget *cerclelogo = gtk_image_new_from_file ("icone/cercle.png");
  GtkWidget *gommelogo = gtk_image_new_from_file ("icone/gomme.png");
  GtkWidget *losangelogo = gtk_image_new_from_file ("icone/losange.png");
  GtkWidget *trianglelogo = gtk_image_new_from_file ("icone/triangle.png");
  GtkWidget *etoile4logo = gtk_image_new_from_file ("icone/etoile4.png");
  GtkWidget *etoile5logo = gtk_image_new_from_file ("icone/etoile5.png");
  GtkWidget *etoile6logo = gtk_image_new_from_file ("icone/etoile6.png");
  GtkWidget *pentalogo = gtk_image_new_from_file ("icone/penta.png");
  GtkWidget *hexalogo = gtk_image_new_from_file ("icone/hexa.png");
  GtkWidget *flecheglogo = gtk_image_new_from_file ("icone/flecheg.png");
  GtkWidget *flechedlogo = gtk_image_new_from_file ("icone/fleched.png");
  GtkWidget *flechehlogo = gtk_image_new_from_file ("icone/flecheh.png");
  GtkWidget *flecheblogo = gtk_image_new_from_file ("icone/flecheb.png");
  GtkWidget *trapezelogo = gtk_image_new_from_file ("icone/trapeze.png");
  GtkWidget *rotdlogo = gtk_image_new_from_file ("icone/rotd.png");
  GtkWidget *rotglogo = gtk_image_new_from_file ("icone/rotg.png");



  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (ligne), lignelogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (pinceau), pinceaulogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (cercle), cerclelogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (rectangle), rectanglelogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (gomme), gommelogo);
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (moins), "zoom-out");
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (plus), "zoom-in");
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (losange), losangelogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (triangle), trianglelogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (etoile4), etoile4logo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (etoile5), etoile5logo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (etoile6), etoile6logo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (penta), pentalogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (hexa), hexalogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (flecheg), flecheglogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (fleched), flechedlogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (flecheh), flechehlogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (flecheb), flecheblogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (trapeze), trapezelogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (rotd), rotdlogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (rotg), rotglogo);


  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),rotg,1);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),rotd,2);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),moins,3);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),plus,4);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),pinceau,5);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),cercle,6);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),rectangle,7);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),gomme,8);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),ligne,9);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),losange,10);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),triangle,11);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),etoile4,12);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),etoile5,13);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),etoile6,14);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),penta,15);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),hexa,16);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),flecheg,17);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),fleched,18);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),flecheh,19);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),flecheb,20);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool),trapeze,21);

  

  gtk_container_add (GTK_CONTAINER(palette),tool);

  //**************************************************************************************
  GtkWidget *palette2 = gtk_tool_palette_new();
  GtkWidget *tool2 = gtk_tool_item_group_new ("Color");
  GtkToolItem *color = gtk_tool_button_new(NULL,"Color");
  GtkToolItem *red = gtk_tool_button_new(NULL,"red");
  GtkToolItem *noir = gtk_tool_button_new(NULL,"noir");
  GtkToolItem *bleu = gtk_tool_button_new(NULL,"bleu");
  GtkToolItem *vert = gtk_tool_button_new(NULL,"vert");
  GtkToolItem *jaune = gtk_tool_button_new(NULL,"jaune");


  GtkWidget *redlogo = gtk_image_new_from_file ("icone/red.png");
  GtkWidget *noirlogo = gtk_image_new_from_file ("icone/noir.png");
  GtkWidget *bleulogo = gtk_image_new_from_file ("icone/bleu.png");
  GtkWidget *vertlogo = gtk_image_new_from_file ("icone/vert.png");
  GtkWidget *jaunelogo = gtk_image_new_from_file ("icone/jaune.png");
  GtkWidget *colorlogo = gtk_image_new_from_file ("icone/palette.png");

  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (red), redlogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (noir), noirlogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (bleu), bleulogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (vert), vertlogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (jaune), jaunelogo);
  gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (color), colorlogo);


  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool2),noir,1);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool2),jaune,2);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool2),red,3);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool2),bleu,4);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool2),vert,5);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool2),color,6);


  gtk_container_add (GTK_CONTAINER(palette2),tool2);

  //**************************************************************************************
  GtkWidget *palette3 = gtk_tool_palette_new();
  GtkWidget *tool3 = gtk_tool_item_group_new ("Filter");
  GtkToolItem *nb = gtk_tool_button_new(NULL,"Black & White");
  GtkToolItem *teinte = gtk_tool_button_new(NULL,"Tint");
  GtkToolItem *seuillage = gtk_tool_button_new(NULL,"Thresholding");
  GtkToolItem *neg = gtk_tool_button_new(NULL,"Negative");
  GtkToolItem *artistic = gtk_tool_button_new(NULL,"Artistic");
  GtkToolItem *median = gtk_tool_button_new(NULL,"Median");
  GtkToolItem *mirh = gtk_tool_button_new(NULL,"Miroir Horizontal");
  GtkToolItem *mirv = gtk_tool_button_new(NULL,"Miroir Vertical");

  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool3),nb,1);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool3),teinte,2);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool3),seuillage,3);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool3),neg,4);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool3),artistic,5);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool3),median,6);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool3),mirh,7);
  gtk_tool_item_group_insert (GTK_TOOL_ITEM_GROUP(tool3),mirv,8);



  gtk_container_add (GTK_CONTAINER(palette3),tool3);


  //*************************** Drawing area
  frame = gtk_frame_new(NULL);
  gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_IN);
  gtk_widget_set_size_request (darea, 800, 550);
  gtk_container_add(GTK_CONTAINER(frame),darea);

  //**************** Grid Attach
  gtk_grid_attach(GTK_GRID(grid), new_file,0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid), open,1,0,1,1);
  gtk_grid_attach(GTK_GRID(grid), save,2,0,1,1);
  gtk_grid_attach(GTK_GRID(grid), saveAs,3,0,1,1);
  gtk_grid_attach(GTK_GRID(grid), convert,4,0,1,1);
  gtk_grid_attach(GTK_GRID(grid), quit,10,0,1,1);
  gtk_grid_attach(GTK_GRID(grid), image,9,7,2,2);
  gtk_grid_attach(GTK_GRID(grid), palette,0,2,1,5);
  gtk_grid_attach(GTK_GRID(grid), palette2,9,6,2,2);
  gtk_grid_attach(GTK_GRID(grid), palette3,9,2,2,6);
  gtk_grid_attach(GTK_GRID(grid), frame,1,3,8,5);
  gtk_grid_attach(GTK_GRID(grid), plein,0,7,1,1);

  //******************* Signaux de bouton
  g_signal_connect(G_OBJECT(home), "destroy",G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(quit), "clicked", G_CALLBACK(PopupQuit), NULL);
  g_signal_connect(G_OBJECT(open), "clicked", G_CALLBACK(loadImage), home);
  g_signal_connect(G_OBJECT(save), "clicked", G_CALLBACK(SaveImage), home);
  g_signal_connect(G_OBJECT(saveAs), "clicked", G_CALLBACK(gtk_save_display), home);
  g_signal_connect(G_OBJECT(convert), "clicked", G_CALLBACK(conv_display), home);
  g_signal_connect(G_OBJECT(new_file), "clicked", G_CALLBACK(newfile), home);
  g_signal_connect(G_OBJECT(pinceau), "clicked", G_CALLBACK(set_pinceau),NULL);
  g_signal_connect(G_OBJECT(gomme), "clicked", G_CALLBACK(set_gomme),NULL);
  g_signal_connect(G_OBJECT(ligne), "clicked", G_CALLBACK(set_ligne),NULL);
  g_signal_connect(G_OBJECT(rectangle), "clicked", G_CALLBACK(set_rectangle),NULL);
  g_signal_connect(G_OBJECT(cercle), "clicked", G_CALLBACK(set_cercle),NULL);
  g_signal_connect(G_OBJECT(noir), "clicked", G_CALLBACK(set_noir),NULL);
  g_signal_connect(G_OBJECT(vert), "clicked", G_CALLBACK(set_vert),NULL);
  g_signal_connect(G_OBJECT(bleu), "clicked", G_CALLBACK(set_bleu),NULL);
  g_signal_connect(G_OBJECT(red), "clicked", G_CALLBACK(set_red),NULL);
  g_signal_connect(G_OBJECT(jaune), "clicked", G_CALLBACK(set_jaune),NULL);
  g_signal_connect(G_OBJECT(moins), "clicked", G_CALLBACK(moins_taille),NULL);
  g_signal_connect(G_OBJECT(plus), "clicked", G_CALLBACK(plus_taille),NULL);
  g_signal_connect(G_OBJECT(nb), "clicked", G_CALLBACK(togrey),darea);
  g_signal_connect(G_OBJECT(teinte), "clicked", G_CALLBACK(adjust),darea);
  g_signal_connect(G_OBJECT(seuillage), "clicked", G_CALLBACK(seuil),darea);
  g_signal_connect(G_OBJECT(neg), "clicked", G_CALLBACK(negativ),darea);
  g_signal_connect(G_OBJECT(artistic), "clicked", G_CALLBACK(artist),darea);
  g_signal_connect(G_OBJECT(median), "clicked", G_CALLBACK(medi),darea);
  g_signal_connect(G_OBJECT(rotd), "clicked", G_CALLBACK(rotiD),darea);
  g_signal_connect(G_OBJECT(rotg), "clicked", G_CALLBACK(rotiG),darea);
  g_signal_connect(G_OBJECT(mirh), "clicked", G_CALLBACK(mirH),darea);
  g_signal_connect(G_OBJECT(mirv), "clicked", G_CALLBACK(mirV),darea);
  g_signal_connect(G_OBJECT(color), "clicked", G_CALLBACK(popup),NULL);
  g_signal_connect(G_OBJECT(losange), "clicked", G_CALLBACK(set_losange),NULL);
  g_signal_connect(G_OBJECT(triangle), "clicked", G_CALLBACK(set_triangle),NULL);
  g_signal_connect(G_OBJECT(etoile4), "clicked", G_CALLBACK(set_etoile4),NULL);
  g_signal_connect(G_OBJECT(etoile5), "clicked", G_CALLBACK(set_etoile5),NULL);
  g_signal_connect(G_OBJECT(etoile6), "clicked", G_CALLBACK(set_etoile6),NULL);
  g_signal_connect(G_OBJECT(penta), "clicked", G_CALLBACK(set_penta),NULL);
  g_signal_connect(G_OBJECT(hexa), "clicked", G_CALLBACK(set_hexa),NULL);
  g_signal_connect(G_OBJECT(flecheg), "clicked", G_CALLBACK(set_flecheg),NULL);
  g_signal_connect(G_OBJECT(fleched), "clicked", G_CALLBACK(set_fleched),NULL);
  g_signal_connect(G_OBJECT(flecheh), "clicked", G_CALLBACK(set_flecheh),NULL);
  g_signal_connect(G_OBJECT(flecheb), "clicked", G_CALLBACK(set_flecheb),NULL);
  g_signal_connect(G_OBJECT(trapeze), "clicked", G_CALLBACK(set_trapeze),NULL);
/******************/
  g_signal_connect(G_OBJECT(plein), "toggled", G_CALLBACK(togg),plein);

  //*****************************************************************
  g_signal_connect (darea, "draw",
      G_CALLBACK (draw_cb), NULL);
  g_signal_connect (darea,"configure-event",
      G_CALLBACK (configure_event_cb), NULL);
  g_signal_connect (darea, "motion-notify-event",
      G_CALLBACK (motion_notify_event_cb), NULL);
  g_signal_connect(darea, "button-press-event",
      G_CALLBACK(clicked), NULL);
  g_signal_connect(darea, "button-release-event",
      G_CALLBACK(released), NULL);
  g_signal_connect(home, "key-release-event",
      G_CALLBACK(keyboard), NULL);
  gtk_widget_set_events (darea, gtk_widget_get_events (darea)
      | GDK_BUTTON_PRESS_MASK
      | GDK_POINTER_MOTION_MASK
      | GDK_BUTTON_RELEASE_MASK);
  //******************************************************************


  //***************  SHOW ALL
  gtk_widget_show_all(home);
}



//* *********** Main **************

int main(int argc, char **argv)
{
  gtk_init(& argc,& argv);
  fenetre();
  gtk_main();
  return 0;
}
