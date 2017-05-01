//converter.c

# include <gtk-3.0/gtk/gtk.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <err.h>

enum format{PNG, JPEG, BMP, GIF, TIFF};

struct ConvData {
  GtkWidget *window, *ConvWindow;
  GtkWidget *EntryIm, *EntrySave;
  GtkWidget *ComboOut;
  int Entry1, Entry2;
  enum format Format;
};

/****************************** Outils basiques *******************************/
/*size_t ArrayCmp (char a[], char b[], size_t count) {
	for (size_t i = 0 ; i < count ; i++)
			if (a[i] != b[i])
				return 0;
	return 1;
}
*/
/*Value returned : -1 = Error
										0 = png,
										1 = jpeg,
										2 = bmp,
										3 = gif,
										4 = tiff.
*/
/*int isCorrectImage(char *path) {
	int fd, fmt = -1;
	char png[]   = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
	char gif[]   = {0x47, 0x49, 0x46};
	char bmp[]   = {0x42, 0x4D};
	char jpg[]   = {0xFF, 0xD8};
	char tiff1[] = {0x4D, 0x4D};
	char tiff2[] = {0x49, 0x49};

	if ((fd = open(path, O_RDONLY)) == -1)
		return -1;
	else {
		char buf[8];
		if (read(fd, buf, 8) == -1) {
			return -2;
			err(1, "Reading Failed");
		}
		if (ArrayCmp(png, buf, 8) == 1)
			fmt = 0;
		else if (ArrayCmp(jpg, buf, 2) == 1)
			fmt = 1;
		else if (ArrayCmp(bmp, buf, 2) == 1)
			fmt = 2;
		else if (ArrayCmp(gif, buf, 3) == 1)
			fmt = 3;
		else if (ArrayCmp(tiff1, buf, 2) == 1 || ArrayCmp(tiff2, buf, 2) == 1)
			fmt = 4;
	}

	close(fd);
	return fmt;
}
*/
/***************************** Boites de dialogue *****************************/
/* Affiche une boîte de dialogue pour choisir une image */
char* dialog_browse(GtkWidget *window) {
	char *picturePath = NULL;
  GtkWidget *chooser = 	gtk_file_chooser_dialog_new("Pick a picture",
															GTK_WINDOW(window),
															GTK_FILE_CHOOSER_ACTION_OPEN,
															"_Cancel",
															GTK_RESPONSE_CANCEL,
															"_Open",
															GTK_RESPONSE_ACCEPT,
															NULL);

	// Lancement de l'explorateur
  switch (gtk_dialog_run(GTK_DIALOG(chooser))) {
  	case GTK_RESPONSE_ACCEPT:	//OPEN pushed
			picturePath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
      break;
    default: //CANCEL pushed
			picturePath = NULL;
			break;
   }

	// Destruction de la boîte de dialogue
  gtk_widget_destroy(chooser);
	return picturePath;
}


/* Affiche une boîte de dialogue pour choisir le chemin de la sauvegarde */
/*char* dialog_box_save(GtkWidget *window) {
	char *picturePath;
  GtkWidget *chooser = 	gtk_file_chooser_dialog_new("Save as..",
									 			GTK_WINDOW(window),
												GTK_FILE_CHOOSER_ACTION_SAVE,
												"_Cancel",
												GTK_RESPONSE_CANCEL,
												"_Save",
												GTK_RESPONSE_ACCEPT,
												NULL);

	gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER(chooser),
																		"Untitled document");

	// Lancement de l'explorateur
  switch (gtk_dialog_run(GTK_DIALOG(chooser))) {
  	//L'utilisateur clique LOAD
    case GTK_RESPONSE_ACCEPT:
			picturePath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
      break;
    // L'utilisateur clique CANCEL
    default:
			picturePath = NULL;
			break;
   }

	// Destruction de la boîte de dialogue
  gtk_widget_destroy(chooser);
	return picturePath;
}*/

/*Callback qui permet de retourner à la fenêtre principal */
void gtk_main_display(GtkButton *button, struct ConvData *d) {
	gtk_widget_destroy(d->ConvWindow);
	(void)button;
}




/******************************** Callbacks ***********************************/
void gtk_GetPathImage(GtkButton *button, struct ConvData *d) {
	char *PathImage = dialog_browse(d->ConvWindow);
	if (isCorrectImage(PathImage) == -1) {
		gtk_entry_set_text (GTK_ENTRY(d->EntryIm), "INVALID IMAGE");
		d->Entry1 = -1;
	}
	else {
		gtk_entry_set_text (GTK_ENTRY(d->EntryIm), PathImage);
		d->Entry1 = 0;
	}
	(void)button;
}

void gtk_GetPathSave(GtkButton *button, struct ConvData *d) {
	char *ext = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(
																								 d->ComboOut)),
			 *path = dialog_box_save(d->ConvWindow);
	if (path == NULL) {
		d->Entry2 = -1;
		return;
	}
	char *result = malloc(strlen(ext)+strlen(path)+1);

  strcpy(result, path);
	strcat(result, ext);
	gtk_entry_set_text (GTK_ENTRY(d->EntrySave), result);

	d->Entry2 = 0;
	(void)button;
}

void gtk_OK(GtkButton *button, struct ConvData *d) {
	GError **error = NULL;
	GtkWidget *MessageBox;

	//Vérifie que les deux entry soit remplis
	if (d->Entry1 == 0 && d->Entry2 == 0) {
		GdkPixbuf *Im = gdk_pixbuf_new_from_file(gtk_entry_get_text(
										GTK_ENTRY(d->EntryIm)),
										error);
		if (Im == NULL) { //Lance un message d'erreur si Im n'est pas chargée
    	MessageBox = gtk_message_dialog_new(GTK_WINDOW(d->ConvWindow),
										GTK_DIALOG_DESTROY_WITH_PARENT,
										GTK_MESSAGE_ERROR,
										GTK_BUTTONS_CLOSE,
										"An error has occured opening your image.\nYour image may be deteriorated.");
			gtk_dialog_run(GTK_DIALOG(MessageBox));
			gtk_widget_destroy(MessageBox);
			gtk_main_display(NULL, d);
			return;
		}
		else {
			char *ext = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(
																														d->ComboOut));
			gboolean b = gdk_pixbuf_save(Im,
										gtk_entry_get_text(GTK_ENTRY(d->EntrySave)),
										ext+1,
										error,
										NULL);
			if (b) {
				MessageBox = gtk_message_dialog_new(GTK_WINDOW(d->ConvWindow),
										GTK_DIALOG_DESTROY_WITH_PARENT,
										GTK_MESSAGE_INFO,
										GTK_BUTTONS_CLOSE,
										"Your image was saved successfully");
				gtk_dialog_run(GTK_DIALOG(MessageBox));
				gtk_widget_destroy(MessageBox);
			}
			else {
				MessageBox = gtk_message_dialog_new(GTK_WINDOW(d->ConvWindow),
										GTK_DIALOG_DESTROY_WITH_PARENT,
										GTK_MESSAGE_ERROR,
										GTK_BUTTONS_CLOSE,
										"An error has occured saving the image");
				gtk_dialog_run(GTK_DIALOG(MessageBox));
				gtk_widget_destroy(MessageBox);
			}
			gtk_main_display(NULL, d);
			return;
		}
	}
	else {
		MessageBox = gtk_message_dialog_new(GTK_WINDOW(d->ConvWindow),
										GTK_DIALOG_DESTROY_WITH_PARENT,
										GTK_MESSAGE_ERROR,
										GTK_BUTTONS_CLOSE,
										"Some fields are not completed.");
		gtk_dialog_run(GTK_DIALOG(MessageBox));
		gtk_widget_destroy(MessageBox);
	}
	(void)button;
}
/**************************** Fenêtre convertisseur ***************************/
void InitConvertWindow(struct ConvData *d) {
	GError **error = NULL;
	// Declaration des widgets
	GtkWidget *grid;
  GtkWidget *BtnOk, *BtnQuit, *BtnDial, *BtnSaveDial;
	GtkWidget *LabIm, *LabTo, *LabSave;

	/* Creation et initialisation de la fenetre secondaire convert*/
	d->ConvWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 	gtk_window_set_default_size(GTK_WINDOW(d->ConvWindow), 300, 350);
	gtk_window_set_title(GTK_WINDOW(d->ConvWindow), "Converter");
 	gtk_container_set_border_width(GTK_CONTAINER(d->ConvWindow), 10);
 	gtk_window_set_position(GTK_WINDOW(d->ConvWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable (GTK_WINDOW(d->ConvWindow), FALSE);
	gtk_window_set_icon(GTK_WINDOW(d->ConvWindow),
									gdk_pixbuf_new_from_file("Images/ConvertIco.png", error));
	d->Entry1 = -1;
	d->Entry2 = -1;

	/* Création de la table de positionnement */
  grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(d->ConvWindow), grid);
	gtk_grid_set_row_spacing (GTK_GRID (grid), 20);

	/*Création des widgets invisibles */
	GtkWidget *Inv1 = gtk_label_new(" ");
	GtkWidget *Inv2 = gtk_label_new(" ");
	GtkWidget *Inv3 = gtk_label_new(" ");

	/*Creation des buttons*/
  BtnOk = gtk_button_new_with_label("Ok");
  BtnQuit = gtk_button_new_with_label("Cancel");
  BtnDial = gtk_button_new_with_label("...");
  BtnSaveDial = gtk_button_new_with_label("...");

	/*Creation des label*/
	LabIm = gtk_label_new("Pick your picture:");
	LabTo = gtk_label_new("Select output format :");
	LabSave = gtk_label_new("Enter the output path :");

	/* Création de la ComboBox */
	d->ComboOut = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(d->ComboOut), NULL, ".png");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(d->ComboOut), NULL, ".jpeg");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(d->ComboOut), NULL, ".bmp");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(d->ComboOut), NULL, ".tiff");
	gtk_combo_box_set_active(GTK_COMBO_BOX(d->ComboOut), 1);

	/* Creation des Input*/
	d->EntryIm = gtk_entry_new();
	d->EntrySave = gtk_entry_new();

	/*Ajout des elements a la grid */
	gtk_grid_set_row_spacing (GTK_GRID (grid), 10);
	//Partie selection d'image
	gtk_grid_attach (GTK_GRID (grid), LabIm, 0, 0, 4, 1);
	gtk_grid_attach (GTK_GRID (grid), d->EntryIm, 0, 1, 12, 1);
	gtk_grid_attach (GTK_GRID (grid), BtnDial, 12, 1, 2, 1);
	//Saut de ligne
	gtk_grid_attach (GTK_GRID (grid), Inv1, 0, 3, 4, 1);
	//Partie extention à convertir
	gtk_grid_attach (GTK_GRID (grid), LabTo, 0, 4, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), d->ComboOut, 0, 5, 12, 1);
	//Saut de ligne
	gtk_grid_attach (GTK_GRID (grid), Inv2, 0, 6, 4, 1);
	//Partie sauvegarde
	gtk_grid_attach (GTK_GRID (grid), LabSave, 0, 7, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), d->EntrySave, 0, 8, 12, 1);
	gtk_grid_attach (GTK_GRID (grid), BtnSaveDial, 12, 8, 2, 1);
	//Saut de ligne
	gtk_grid_attach (GTK_GRID (grid), Inv3, 0, 9, 4, 1);
	// OK ou CANCEL
	gtk_grid_attach (GTK_GRID (grid), BtnQuit, 1, 10, 1, 2);
	gtk_grid_attach (GTK_GRID (grid), BtnOk, 2, 10, 11, 2);

	/* Création des signaux/événements avec leur callback */
	g_signal_connect(G_OBJECT(d->ConvWindow), "destroy",
 									 G_CALLBACK(gtk_main_display), d);
  g_signal_connect(G_OBJECT(BtnQuit), "clicked",
									 G_CALLBACK(gtk_main_display), d);
  g_signal_connect(G_OBJECT(BtnDial), "clicked",
									 G_CALLBACK(gtk_GetPathImage), d);
  g_signal_connect(G_OBJECT(BtnSaveDial), "clicked",
									 G_CALLBACK(gtk_GetPathSave), d);
  g_signal_connect(G_OBJECT(BtnOk), "clicked",
									 G_CALLBACK(gtk_OK), d);
}

/*************************** Callbacks d'affichage ****************************/
/*Callback qui permet d'afficher la fenêtre convertisseur */
void conv_display(GtkButton *button, GtkWidget *window) {
	struct ConvData *d = malloc(sizeof(struct ConvData));
	d->window = window;
	InitConvertWindow(d);
	gtk_widget_show_all(d->ConvWindow);
	(void)button;
}


/**************************** Main à supprimer ********************************/
/*int main (int argc, char *argv[]) {
	// Declaration des widgets/structs
	GtkWidget *BtnConv;
	GtkWidget *VBox;
	struct ConvData *d = malloc(sizeof(struct ConvData));

	//Init de GTK
  gtk_init(&argc, &argv);

	//Init widgets/structs
	BtnConv = gtk_button_new_with_label("Convert");
	VBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 25);

	//Setting de la window
  d->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(d->window), "GtkImage");
 	gtk_window_set_default_size(GTK_WINDOW(d->window), 100, 100);
 	gtk_window_set_position(GTK_WINDOW(d->window), GTK_WIN_POS_CENTER);

	//Gestion de la box d'affichage de la fenêtre
	gtk_box_pack_start(GTK_BOX(VBox), BtnConv, FALSE, FALSE, 10);
	gtk_container_add(GTK_CONTAINER(d->window), VBox);

	//Signal pour fermer la fenetre
	g_signal_connect(G_OBJECT(d->window), "destroy", G_CALLBACK(gtk_main_quit),
									NULL);

	//Signal pour lancer la fenêtre de convertion
	g_signal_connect(G_OBJECT(BtnConv), "clicked", G_CALLBACK(gtk_conv_display),
									d);

	//affichage principale
  gtk_widget_show_all(d->window);

	//Main loop
  gtk_main();

  return EXIT_SUCCESS;
}*/
