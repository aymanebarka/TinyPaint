# include <gtk-3.0/gtk/gtk.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <err.h>

/*********************************************************************************
			INSTRUCTION ROTATION ET MIROIR

ROTATION GAUCHE --> pixbuff = gdk_pixbuf_rotate_simple(pixbuff, 90);

ROTATION DROITE --> pixbuff = gdk_pixbuf_rotate_simple(pixbuff, 270);

MIROIR VERTICALE --> pixbuff = gdk_pixbuf_flip(pixbuff, FALSE);

MIROIR HORIZONTALE --> pixbuff = gdk_pixbuf_flip(pixbuff, TRUE);

********************************************************************************/

void to_grey(GdkPixbuf *pb)
{
  int width, height, rowstride, n_channels;
  int i, j;
  guchar *pixels, *p, grey_p;
  

  n_channels = gdk_pixbuf_get_n_channels (pb);

  g_assert (gdk_pixbuf_get_colorspace (pb) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pb) == 8);
  //g_assert (gdk_pixbuf_get_has_alpha (pb));
  //g_assert (n_channels == 4);

  width = gdk_pixbuf_get_width (pb);
  height = gdk_pixbuf_get_height (pb);

  rowstride = gdk_pixbuf_get_rowstride (pb);
  pixels = gdk_pixbuf_get_pixels (pb);

  for(i = 0; i < height; i++)
  {
    for(j = 0; j < width; j++)
    {
      p = pixels + i * rowstride + j * n_channels;
      grey_p = 0.3*p[0] + 0.59*p[1] + 0.11*p[2];
      p[0] = grey_p;
      p[1] = grey_p;
      p[2] = grey_p; 
    }
  }
}


void negative(GdkPixbuf *pb)
{
  int width, height, rowstride, n_channels;
  int i, j;
  guchar *pixels, *p;


  n_channels = gdk_pixbuf_get_n_channels (pb);

  //g_assert (gdk_pixbuf_get_colorspace (pb) == GDK_COLORSPACE_RGB);
  //g_assert (gdk_pixbuf_get_bits_per_sample (pb) == 8);
  //g_assert (gdk_pixbuf_get_has_alpha (pb));
  //g_assert (n_channels == 4);

  width = gdk_pixbuf_get_width (pb);
  height = gdk_pixbuf_get_height (pb);

  rowstride = gdk_pixbuf_get_rowstride (pb);
  pixels = gdk_pixbuf_get_pixels (pb);

  for(i = 0; i < height ; i++)
  {
    for(j = 0; j < width; j++)
    {
      p = pixels + i * rowstride + j * n_channels;
      p[0] = 255 - p[0];
      p[1] = 255 - p[1];
      p[2] = 255 - p[2];
    }
  }
}


void adjust_RGB(GdkPixbuf *pb, guchar red, guchar green, guchar blue)
{
  int width, height, rowstride, n_channels;
  int i, j;
  guchar *pixels, *p;


  n_channels = gdk_pixbuf_get_n_channels (pb);

  g_assert (gdk_pixbuf_get_colorspace (pb) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pb) == 8);
  //g_assert (gdk_pixbuf_get_has_alpha (pb));
  //g_assert (n_channels == 4);

  width = gdk_pixbuf_get_width (pb);
  height = gdk_pixbuf_get_height (pb);

  rowstride = gdk_pixbuf_get_rowstride (pb);
  pixels = gdk_pixbuf_get_pixels (pb);

  for(i = 0; i < height; i++)
  {
    for(j = 0; j < width; j++)
    {
      p = pixels + i * rowstride + j * n_channels;
      if(p[0] - blue - green < 0)
        p[0] = 0;
      else
        p[0] = p[0] - blue - green;
      if(p[1] - red - blue < 0)
        p[1] = 0;
      else
        p[1] = p[1] - red - blue;
      if(p[2] - red - green < 0)
        p[2] = 0;
      else
        p[2] = p[2] - red - green;
    }
  }
}

void seuillage(GdkPixbuf *pb, int grey, guchar seuil_grey, guchar seuil_r, guchar seuil_g, guchar seuil_b)
{
  int width, height, rowstride, n_channels;
  int i, j;
  guchar *pixels, *p;


  n_channels = gdk_pixbuf_get_n_channels (pb);

  g_assert (gdk_pixbuf_get_colorspace (pb) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pb) == 8);
	//g_assert (gdk_pixbuf_get_has_alpha (pb));
	//g_assert (n_channels == 4);

  width = gdk_pixbuf_get_width (pb);
  height = gdk_pixbuf_get_height (pb);

  rowstride = gdk_pixbuf_get_rowstride (pb);
  pixels = gdk_pixbuf_get_pixels (pb);

  if(grey)
  {
    for(i = 0; i < height; i++)
    {
      for(j = 0; j < width; j++)
      {
        p = pixels + i * rowstride + j * n_channels;
        if(p[0] < seuil_grey)
	{
          p[0] = 0;
          p[1] = 0;
          p[2] = 0;
	}
	else
	{
	  p[0] = 255;
          p[1] = 255;
          p[2] = 255;
	}
      }
    }
  }
  else
  {
    for(i = 0; i < height; i++)
    {
      for(j = 0; j < width; j++)
      {
        p = pixels + i * rowstride + j * n_channels;
        if(p[0] < seuil_r)
        {
          p[0] = 0;
	}
	else
	{
	  p[0] = 255;
	}

	if(p[1] < seuil_g)
	{
          p[1] = 0;
	}
	else
	{
	  p[1] = 255;
	}

	if(p[2] < seuil_b)
	{
          p[2] = 0;
	}
	else
	{
	  p[2] = 255;
	}
      }
    }
  }
}

void tricroissant(guchar tab[], int tab_size)
{
  int i=0;
  int tmp=0;
  int j=0;

  for(i = 0; i < tab_size; i++)
    {
      for(j = 1; j < tab_size; j++)
        {
          if(tab[i] < tab[j])
            {
              tmp = tab[i];
              tab[i] = tab[j];
              tab[j] = tmp;
              j--;
            }
        }
    }
  tmp = tab[0];
  for(i = 0; i < tab_size; i++)
    tab[i] = tab[i+1];
  tab[tab_size-1] = tmp;
}

void median(GdkPixbuf *pb)
{
  int width, height, rowstride, n_channels;
  int i, j, k;
  guchar *pixels, *p;


  n_channels = gdk_pixbuf_get_n_channels (pb);

  //g_assert (gdk_pixbuf_get_colorspace (pb) == GDK_COLORSPACE_RGB);
  //g_assert (gdk_pixbuf_get_bits_per_sample (pb) == 8);
  //g_assert (gdk_pixbuf_get_has_alpha (pb));
  //g_assert (n_channels == 3);

  width = gdk_pixbuf_get_width (pb);
  height = gdk_pixbuf_get_height (pb);

  rowstride = gdk_pixbuf_get_rowstride (pb);
  pixels = gdk_pixbuf_get_pixels (pb);

  guchar val_r[9];
  guchar val_g[9];
  guchar val_b[9];

  for(i = 1; i < height - 1; i++)
  {
    for(j = 1; j < width - 1; j++)
    {
      for(k = 0; k < 9; k++)
      {
        p = pixels + (i + ((k / 3) - 1)) * rowstride + (j + ((k % 3) - 1)) * n_channels;
        val_r[k] = p[0];
        val_g[k] = p[1];
        val_b[k] = p[2];
      }

      tricroissant(val_r, 9);
      tricroissant(val_g, 9);
      tricroissant(val_b, 9);

      p = pixels + i * rowstride + j * n_channels;
      p[0] = val_r[5];
      p[1] = val_g[5];
      p[2] = val_b[5];

      if(i%2 == 1)
        j++;
    }
  }
}

void artistique(GdkPixbuf *pb)
{
  int width, height, rowstride, n_channels;
  int i, j, k;
  guchar *pixels, *p;


  n_channels = gdk_pixbuf_get_n_channels (pb);

  //g_assert (gdk_pixbuf_get_colorspace (pb) == GDK_COLORSPACE_RGB);
  //g_assert (gdk_pixbuf_get_bits_per_sample (pb) == 8);
  //g_assert (gdk_pixbuf_get_has_alpha (pb));
  //g_assert (n_channels == 3);

  width = gdk_pixbuf_get_width (pb);
  height = gdk_pixbuf_get_height (pb);

  rowstride = gdk_pixbuf_get_rowstride (pb);
  pixels = gdk_pixbuf_get_pixels (pb);

  guchar val_r[9];
  guchar val_g[9];
  guchar val_b[9];

  for(i = 1; i < height - 1; i++)
  {
    for(j = 1; j < width - 1; j++)
    {
      for(k = 0; k < 9; k++)
      {
        p = pixels + (i + ((k / 3) - 1)) * rowstride + (j + ((k % 3) - 1)) * n_channels;
        val_r[k] = p[0];
        val_g[k] = p[1];
        val_b[k] = p[2];
      }

      tricroissant(val_r, 9);
      tricroissant(val_g, 9);
      tricroissant(val_b, 9);

      p = pixels + i * rowstride + j * n_channels;
      p[0] = val_r[5];
      p[1] = val_g[5];
      p[2] = val_b[5];
    }
  }
}

/*
int main(int argc, char *argv[])
{
  GtkWidget *pWindow;
  //GtkWidget *pVBox /, pVBox2/;
  GtkWidget *pImage;
  //GtkWidget *pSaveBtn, *pQuitBtn;

        //Init de GTK
  gtk_init(&argc, &argv);

        //Setting de la window
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(pWindow), "GtkImage");

        // Chargement d'une image a partir d'un fichier
  pImage = gtk_image_new_from_file("png.png");
  if (pImage == NULL)
                return 0;
  g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);   
  
 	 //pixbuf
  GdkPixbuf *pb = gtk_image_get_pixbuf(GTK_IMAGE(pImage));
 
  if(atoi(argv[1]) == 0)
    to_grey(pb);
  else if(atoi(argv[1]) == 1)
    adjust_RGB(pb, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));   
  else if(atoi(argv[1]) == 2)
    negative(pb);
  else if(atoi(argv[1]) == 3)
    seuillage(pb, 0, 120, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));  
  */
/*
  pb = gdk_pixbuf_flip (pb, true);
  
  gtk_container_add(GTK_CONTAINER(pWindow), pImage);  

  gtk_widget_show_all(pWindow);

  gtk_main();
  
  return EXIT_SUCCESS;
}
*/
