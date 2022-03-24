#include <stdio.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include <unistd.h>

int g_number = 0;

#define MAX_COUNT 100

pthread_t t1, t2;

GtkApplicationWindow *window;
GtkButton *l_btn, *m_btn, *r_btn;
GtkLabel *label;

void counter1(void *args) {
    int i = 0;
    while (i < MAX_COUNT) {
        if (g_number == MAX_COUNT / 2) {
            pthread_join(t2, NULL);
        }
        g_number++;
        printf("hi,i am pthread 1, my g_number is [%d]\n", g_number);
        usleep(1000 * 100);
        i++;
    }
}

void counter2(void *args) {
    int j = 0;
    char text[64];
    while (j < MAX_COUNT) {
        g_number++;
        sprintf(text, "hi,i am pthread 2, my g_number is [%d]", g_number);
        gtk_label_set_label(label, text);
        usleep(1000 * 100);
        j++;
    }

    gtk_widget_set_sensitive(GTK_WIDGET(l_btn), TRUE);

}

void multi_thread() {
//    pthread_create(&t1, NULL, counter1, NULL);
    int res = pthread_create(&t2, NULL, counter2, NULL);
}

void on_l_btn_click() {
    gtk_label_set_label(label, "The matrix has you...");
    gtk_widget_set_sensitive(GTK_WIDGET(l_btn), FALSE);

    multi_thread();
}

void on_r_btn_click() {
    if (pthread_cancel(t2) == 0) {
        gtk_widget_set_sensitive(GTK_WIDGET(l_btn), TRUE);
        gtk_label_set_label(label, "");

        g_print("Thread canceled!\n");
    }
}

void on_activate(GtkApplication *app) {
    GtkBuilder *builder;
    builder = gtk_builder_new_from_file("./resource/window.ui");

    window = GTK_APPLICATION_WINDOW(gtk_builder_get_object(builder, "window"));
    l_btn = GTK_BUTTON(gtk_builder_get_object(builder, "l_btn"));
    m_btn = GTK_BUTTON(gtk_builder_get_object(builder, "m_btn"));
    r_btn = GTK_BUTTON(gtk_builder_get_object(builder, "r_btn"));
    label = GTK_LABEL(gtk_builder_get_object(builder, "label"));

    gtk_application_add_window(app, GTK_WINDOW(window));

    g_signal_connect(l_btn, "clicked", G_CALLBACK(on_l_btn_click), NULL);
    g_signal_connect_swapped(m_btn, "clicked", G_CALLBACK(gtk_window_close), window);
    g_signal_connect(r_btn, "clicked", G_CALLBACK(on_r_btn_click), NULL);

    gtk_window_present(GTK_WINDOW(window));

    g_object_unref(builder);
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("com.example.GtkApplication",
                                              G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
