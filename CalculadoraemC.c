#include <gtk/gtk.h>

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button[17];
}calc;

GtkWidget *box;

static void activate(GtkApplication *app, gpointer user_data){
    calc widget;

    widget.window = gtk_application_window_new(app);
    gtk_window_set_position(GTK_WINDOW(widget.window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(widget.window), "calculadora");
    gtk_window_set_default_size(GTK_WINDOW(widget.window), 200, 200);
    gtk_container_set_border_width(GTK_CONTAINER(widget.window),10);

    widget.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(widget.window), widget.grid);

    box = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(box), FALSE);

    widget.button[0] = gtk_button_new_with_label("0");
    widget.button[1] = gtk_button_new_with_label("1");
    widget.button[2] = gtk_button_new_with_label("2"); 
    widget.button[3] = gtk_button_new_with_label("3"); 
    widget.button[4] = gtk_button_new_with_label("4");
    widget.button[5] = gtk_button_new_with_label("5"); 
    widget.button[6] = gtk_button_new_with_label("6"); 
    widget.button[7] = gtk_button_new_with_label("7");
    widget.button[8] = gtk_button_new_with_label("8");
    widget.button[9] = gtk_button_new_with_label("9");
    widget.button[10] = gtk_button_new_with_label(".");
    widget.button[11] = gtk_button_new_with_label("+");
    widget.button[12] = gtk_button_new_with_label("-");
    widget.button[13] = gtk_button_new_with_label("x");
    widget.button[14] = gtk_button_new_with_label("/");
    widget.button[15] = gtk_button_new_with_label("C");
    widget.button[16] = gtk_button_new_with_label("=");

    gtk_grid_attach(GTK_GRID(widget.grid),box,0,0,4,1);

    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[15],0,1,3,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[14],3,1,1,1);

    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[7],0,2,1,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[8],1,2,1,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[9],2,2,1,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[13],3,2,1,1);

    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[4],0,3,1,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[5],1,3,1,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[6],2,3,1,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[12],3,3,1,1);

    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[1],0,4,1,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[2],1,4,1,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[3],2,4,1,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[11],3,4,1,1);

    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[0],0,5,2,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[10],2,5,1,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[16],3,5,1,1);

    gtk_widget_show_all(widget.window);
}


int main(int argc, char **argv) {
    GtkApplication *app;

    gtk_init(&argc, &argv);

    int status;
    app = gtk_application_new("org.gtk.calculator", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

return status;
}
