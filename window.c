//
// Created by albert on 2022/3/25.
//
#include "window.h"

void on_switch_change(GtkSwitch *switcher) {
    g_print("switcher changed:%d.\n", gtk_switch_get_state(switcher));
}

void on_check_button_change(GtkCheckButton *button) {
    g_print("check button changed:%d.\n", gtk_check_button_get_active(button));
}

void on_scale_button_change(GtkScale *scale) {
    g_print("scale button changed:%f.\n", gtk_range_get_value(GTK_RANGE(scale)));
}

void on_spin_button_change(GtkSpinButton *button) {
    g_print("spin button changed:%f.\n", gtk_spin_button_get_value(button));
}

void on_combobox_change(GtkComboBoxText *box) {
    g_print("drop button changed:%s.\n", gtk_combo_box_text_get_active_text(box));
}

void on_entry_change(GtkEntry *entry) {
    g_print("drop button changed:%s.\n", gtk_editable_get_text(GTK_EDITABLE(entry)));
}

void on_activate(GtkApplication *app) {
    GtkBuilder *builder;
    GObject *window, *switcher, *check, *scale, *spin, *dropdown, *entry;

    builder = gtk_builder_new_from_file("./resource/window.ui");

    window = gtk_builder_get_object(builder, "window");
    switcher = gtk_builder_get_object(builder, "switcher");
    check = gtk_builder_get_object(builder, "check");
    scale = gtk_builder_get_object(builder, "scale");
    spin = gtk_builder_get_object(builder, "spin");
    dropdown = gtk_builder_get_object(builder, "dropdown");
    entry = gtk_builder_get_object(builder, "entry");

    g_signal_connect(GTK_SWITCH(switcher), "state-set", G_CALLBACK(on_switch_change), NULL);
    g_signal_connect(GTK_CHECK_BUTTON(check), "toggled", G_CALLBACK(on_check_button_change), NULL);
    g_signal_connect(GTK_SCALE(scale), "value-changed", G_CALLBACK(on_scale_button_change), NULL);
    g_signal_connect(GTK_SPIN_BUTTON(spin), "value-changed", G_CALLBACK(on_spin_button_change), NULL);
    g_signal_connect(GTK_COMBO_BOX(dropdown), "changed", G_CALLBACK(on_combobox_change), NULL);
    g_signal_connect(GTK_ENTRY(entry), "changed", G_CALLBACK(on_entry_change), NULL);


    gtk_application_add_window(app, GTK_WINDOW(window));
    gtk_window_present(GTK_WINDOW(window));

    g_object_unref(builder);
}