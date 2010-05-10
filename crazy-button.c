/* crazy-button.c  --  2005.07.14
   Egy ablak, benne egy ures nyomogombbal. Kihasznalva, hogy a nyomogomb kontener-objektum, elhelyezunk benne
   egy tablat, es annak minden mezojeben eltarolunk egy ujabb nyomogombot kozos esemenykezelovel */

#include <glib.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>

/* a tablazat sor es oszlopszama */
#define X 5
#define Y 4

/* az alkalmazas foablaka */
GtkWidget * MainWindow = NULL;
/* a kulso nyomogomb */
GtkWidget * External_Button = NULL;
/* a tabla, amely a nyomogombon belul lesz */
GtkWidget * Table = NULL;
/* a belso nyomogombok keszitenesel hasznalt mutato */
GtkWidget * Internal_Button = NULL;


void Button_Clicked (GtkWidget * button, gpointer user_data)  {
 /* ha a kulso gombra kattintottak */
 if (user_data == NULL)  {
   g_print ("big button!\n");
 }
 else  {
  g_print ("small button: %d\n", (gint)user_data);
 }
}


int main(int argc, char *argv[]) {
 gint x, y, i;
 gchar Internal_Button_Label[4];

 /* inicializaljuk a GTK -t, erre mindig szukseg van */
 gtk_init(&argc, &argv);
 /* elkeszitjuk az alkalmazas foablakat, hozzarendeljuk a szignalt, beallitjuk a tulajdonsagait */
 MainWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 g_signal_connect_swapped (G_OBJECT (MainWindow), "delete-event", G_CALLBACK (gtk_main_quit), G_OBJECT (MainWindow));
 gtk_window_set_title (GTK_WINDOW (MainWindow), "crazy-button.c");
 gtk_container_set_border_width (GTK_CONTAINER (MainWindow), 20);
 /* elkeszitjuk a kulso nyomogombot, elhelyezzuk az ablakban */
 External_Button = gtk_button_new ();
 gtk_container_add (GTK_CONTAINER (MainWindow), External_Button);
 /* elkeszitjuk a tablat, es elhelyezzuk a nyomogomb belsejeben */
 Table = gtk_table_new (X, Y, TRUE);
 gtk_container_add (GTK_CONTAINER (External_Button), Table);
 /* a kulso nyomogombhoz hozzarendeljuk az esemenyt, parametert nem adunk at */
 g_signal_connect (External_Button, "clicked", G_CALLBACK (Button_Clicked), NULL);

 /* most a belso gombokat keszitjuk el, elhelyezzuk a tablaban, es hozzarendeljuk az esemenykezelot */
 i = 0;
 for (y = 0; y < Y; y++)
  for (x = 0; x < X; x++) {
    g_sprintf (Internal_Button_Label, "%3d", ++i);
    Internal_Button = gtk_button_new_with_label (Internal_Button_Label);
    gtk_table_attach (GTK_TABLE (Table), Internal_Button, x, x+1, y, y+1, 
                     (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK | GTK_FILL), 2, 2);
    g_signal_connect (Internal_Button, "clicked", G_CALLBACK (Button_Clicked), (gint*)i);
  }
 /* megjelenitunk minden widgetet */
 gtk_widget_show_all (MainWindow);
 /* Indul az X esemenyvezerlese */
 gtk_main();
 return 0;
}
