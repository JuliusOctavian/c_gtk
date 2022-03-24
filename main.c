#include <gtk/gtk.h>

void on_activate(GtkApplication *app) {
    GtkWidget *window,*button, *label;
    GtkBox *box;

    window = gtk_application_window_new(app);

    box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 30));
    gtk_box_set_homogeneous(box, TRUE);

    button = gtk_button_new_with_label("Click");
    label = gtk_label_new("");

    gtk_box_append(box, button);gtk_box_append(box, label);
    gtk_window_set_child(GTK_WINDOW(window), GTK_WIDGET(box));

    gtk_widget_show(window);
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("com.example.GtkApplication",
                                              G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
