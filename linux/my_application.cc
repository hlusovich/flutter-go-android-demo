#include "my_application.h"
#include <initializer_list>
#include <flutter_linux/flutter_linux.h>
#ifdef GDK_WINDOWING_X11
#include <gdk/gdkx.h>
#endif
#include <cstdlib>
#include "flutter/generated_plugin_registrant.h"

struct _MyApplication {
  GtkApplication parent_instance;
  char** dart_entrypoint_arguments;
};

G_DEFINE_TYPE(MyApplication, my_application, GTK_TYPE_APPLICATION)

static int getRandomNumber() {
    return rand() % 50;
}

static void method_call_cb(FlMethodChannel *channel,
                           FlMethodCall *method_call,
                           gpointer user_data)
{
  const gchar *method = fl_method_call_get_name(method_call);
  if (strcmp(method, "getBirdsList") == 0){
  g_autoptr(FlValue) res = fl_value_new_list();
  fl_value_append_take(res, fl_value_new_int(91));
  fl_value_append_take(res, fl_value_new_int(34));
  fl_value_append_take(res, fl_value_new_int(83));
  fl_value_append_take(res, fl_value_new_int(112));
  fl_value_append_take(res, fl_value_new_int(97));
  fl_value_append_take(res, fl_value_new_int(114));
  fl_value_append_take(res, fl_value_new_int(114));
  fl_value_append_take(res, fl_value_new_int(111));
  fl_value_append_take(res, fl_value_new_int(119));
  fl_value_append_take(res, fl_value_new_int(34));
  fl_value_append_take(res, fl_value_new_int(44));
  fl_value_append_take(res, fl_value_new_int(34));
  fl_value_append_take(res, fl_value_new_int(80));
  fl_value_append_take(res, fl_value_new_int(105));
  fl_value_append_take(res, fl_value_new_int(103));
  fl_value_append_take(res, fl_value_new_int(101));
  fl_value_append_take(res, fl_value_new_int(111));
  fl_value_append_take(res, fl_value_new_int(110));
  fl_value_append_take(res, fl_value_new_int(34));
  fl_value_append_take(res, fl_value_new_int(44));
  fl_value_append_take(res, fl_value_new_int(34));
  fl_value_append_take(res, fl_value_new_int(72));
  fl_value_append_take(res, fl_value_new_int(101));
  fl_value_append_take(res, fl_value_new_int(114));
  fl_value_append_take(res, fl_value_new_int(111));
  fl_value_append_take(res, fl_value_new_int(110));
  fl_value_append_take(res, fl_value_new_int(34));
  fl_value_append_take(res, fl_value_new_int(93));
  g_autoptr(FlMethodResponse) response = FL_METHOD_RESPONSE(fl_method_success_response_new(res));
  g_autoptr(GError) error = nullptr;
  fl_method_call_respond(method_call, response, &error);
    
  }

  if (strcmp(method, "getRandomNumber") == 0){
  FlValue *res = fl_value_new_int(getRandomNumber());

  g_autoptr(FlMethodResponse) response = FL_METHOD_RESPONSE(fl_method_success_response_new(res));
  g_autoptr(GError) error = nullptr;
  fl_method_call_respond(method_call, response, &error); 
  }
  if (strcmp(method, "getBirdInfo") == 0){
  FlValue* args = fl_method_call_get_args(method_call);
  FlValue* bird_it = fl_value_lookup_string(args, "bird");
  const char* bird = fl_value_get_string(bird_it);
  int value[]  = {123, 34, 98, 105, 114, 100, 84, 121, 112, 101, 34, 58, 34, 83, 112, 97, 114, 114, 111, 119, 34, 44, 34, 119, 104, 97, 116, 32, 105, 116, 32, 100, 111, 101, 115, 34, 58, 34, 108, 105, 107, 101, 115, 32, 116, 111, 32, 101, 97, 116, 32, 115, 101, 101, 100, 34, 125};

  if (strcmp(bird, "Sparrow") == 0) {
  g_autoptr(FlValue) res = fl_value_new_list();
  int n = sizeof(value);
  for (i = 0; i < n; i++) {
   fl_value_append_take(res, fl_value_new_int(value[i]));
  }
  g_autoptr(FlMethodResponse) response = FL_METHOD_RESPONSE(fl_method_success_response_new(res));
  g_autoptr(GError) error = nullptr;
  fl_method_call_respond(method_call, response, &error); 
  }
  }
}
// Implements GApplication::activate.
static void my_application_activate(GApplication* application) {
  MyApplication* self = MY_APPLICATION(application);
  GtkWindow* window =
      GTK_WINDOW(gtk_application_window_new(GTK_APPLICATION(application)));

  // Use a header bar when running in GNOME as this is the common style used
  // by applications and is the setup most users will be using (e.g. Ubuntu
  // desktop).
  // If running on X and not using GNOME then just use a traditional title bar
  // in case the window manager does more exotic layout, e.g. tiling.
  // If running on Wayland assume the header bar will work (may need changing
  // if future cases occur).
  gboolean use_header_bar = TRUE;
#ifdef GDK_WINDOWING_X11
  GdkScreen* screen = gtk_window_get_screen(window);
  if (GDK_IS_X11_SCREEN(screen)) {
    const gchar* wm_name = gdk_x11_screen_get_window_manager_name(screen);
    if (g_strcmp0(wm_name, "GNOME Shell") != 0) {
      use_header_bar = FALSE;
    }
  }
#endif
  if (use_header_bar) {
    GtkHeaderBar* header_bar = GTK_HEADER_BAR(gtk_header_bar_new());
    gtk_widget_show(GTK_WIDGET(header_bar));
    gtk_header_bar_set_title(header_bar, "gomobilefrontend");
    gtk_header_bar_set_show_close_button(header_bar, TRUE);
    gtk_window_set_titlebar(window, GTK_WIDGET(header_bar));
  } else {
    gtk_window_set_title(window, "gomobilefrontend");
  }

  gtk_window_set_default_size(window, 1280, 720);
  gtk_widget_show(GTK_WIDGET(window));

  g_autoptr(FlDartProject) project = fl_dart_project_new();
  fl_dart_project_set_dart_entrypoint_arguments(project, self->dart_entrypoint_arguments);

  FlView* view = fl_view_new(project);
  gtk_widget_show(GTK_WIDGET(view));
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(view));

  fl_register_plugins(FL_PLUGIN_REGISTRY(view));
  FlEngine *engine = fl_view_get_engine(view);

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlBinaryMessenger) messenger = fl_engine_get_binary_messenger(engine);
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(messenger,
                            "example.com/gomobileNative",  
                            FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(channel, 
                                            method_call_cb,  
                                            g_object_ref(view),
                                            g_object_unref);

  fl_method_channel_set_method_call_handler(channel, 
                            method_call_cb, g_object_ref(view), g_object_unref);

  gtk_widget_grab_focus(GTK_WIDGET(view));
  gtk_widget_grab_focus(GTK_WIDGET(view));
}

// Implements GApplication::local_command_line.
static gboolean my_application_local_command_line(GApplication* application, gchar*** arguments, int* exit_status) {
  MyApplication* self = MY_APPLICATION(application);
  // Strip out the first argument as it is the binary name.
  self->dart_entrypoint_arguments = g_strdupv(*arguments + 1);

  g_autoptr(GError) error = nullptr;
  if (!g_application_register(application, nullptr, &error)) {
     g_warning("Failed to register: %s", error->message);
     *exit_status = 1;
     return TRUE;
  }

  g_application_activate(application);
  *exit_status = 0;

  return TRUE;
}

// Implements GObject::dispose.
static void my_application_dispose(GObject* object) {
  MyApplication* self = MY_APPLICATION(object);
  g_clear_pointer(&self->dart_entrypoint_arguments, g_strfreev);
  G_OBJECT_CLASS(my_application_parent_class)->dispose(object);
}

static void my_application_class_init(MyApplicationClass* klass) {
  G_APPLICATION_CLASS(klass)->activate = my_application_activate;
  G_APPLICATION_CLASS(klass)->local_command_line = my_application_local_command_line;
  G_OBJECT_CLASS(klass)->dispose = my_application_dispose;
}

static void my_application_init(MyApplication* self) {}

MyApplication* my_application_new() {
  return MY_APPLICATION(g_object_new(my_application_get_type(),
                                     "application-id", APPLICATION_ID,
                                     "flags", G_APPLICATION_NON_UNIQUE,
                                     nullptr));
}
