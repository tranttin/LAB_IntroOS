#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void copy_file(const char *source, const char *destination) {
    FILE *src_file = fopen(source, "rb");
    if (src_file == NULL) {
        g_print("Could not open source file.\n");
        return;
    }

    FILE *dest_file = fopen(destination, "wb");
    if (dest_file == NULL) {
        g_print("Could not open destination file.\n");
        fclose(src_file);
        return;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);

    g_print("File copied successfully.\n");
}
void on_copy_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const char *source = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const char *destination = gtk_entry_get_text(GTK_ENTRY(entries[1]));

    if (strlen(source) == 0 || strlen(destination) == 0) {
        g_print("Please select both source and destination files.\n");
        return;
    }

    copy_file(source, destination);
}

void on_open_source_button_clicked(GtkWidget *widget, gpointer entry) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Select Source File",
                                         NULL,
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         "_Open", GTK_RESPONSE_ACCEPT,
                                         NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        gtk_entry_set_text(GTK_ENTRY(entry), filename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void on_save_destination_button_clicked(GtkWidget *widget, gpointer entry) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Select Destination File",
                                         NULL,
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         "_Save", GTK_RESPONSE_ACCEPT,
                                         NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        gtk_entry_set_text(GTK_ENTRY(entry), filename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *source_entry, *destination_entry;
    GtkWidget *open_source_button, *save_destination_button, *copy_button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "File Copy");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    source_entry = gtk_entry_new();
    destination_entry = gtk_entry_new();

    open_source_button = gtk_button_new_with_label("Select Source");
    save_destination_button = gtk_button_new_with_label("Select Destination");
    copy_button = gtk_button_new_with_label("Copy File");

    GtkWidget *entries[2] = {source_entry, destination_entry};

    g_signal_connect(open_source_button, "clicked", G_CALLBACK(on_open_source_button_clicked), source_entry);
    g_signal_connect(save_destination_button, "clicked", G_CALLBACK(on_save_destination_button_clicked), destination_entry);
    g_signal_connect(copy_button, "clicked", G_CALLBACK(on_copy_button_clicked), entries);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Source File:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), source_entry, 1, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), open_source_button, 3, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Destination File:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), destination_entry, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), save_destination_button, 3, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), copy_button, 1, 2, 2, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
