//filters.h
# include "filters.c"

void to_grey(GdkPixbuf *pb);
void negative(GdkPixbuf *pb);
void adjust_RGB(GdkPixbuf *pb, guchar red, guchar green, guchar blue);
void seuillage(GdkPixbuf *pb, int grey, guchar seuil_grey, guchar seuil_r, guchar seuil_g, guchar seuil_b);
void median(GdkPixbuf *pb);
void artistique(GdkPixbuf *pb);
