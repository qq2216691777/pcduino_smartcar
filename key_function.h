#ifndef _KEY_FUNCTION_H__
#define _KEY_FUNCTION_H__
#include <gtk/gtk.h>


void APP_Quit_clicked(GtkWidget *widget, gpointer label);
void Connect_Quit_clicked(GtkWidget *widget, gpointer label);


void key_value(GtkWidget *widget, GdkEventKey *event, gpointer data);

#endif // _KEY_FUNCTION_H__
