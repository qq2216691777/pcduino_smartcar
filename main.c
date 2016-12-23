#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include <time.h>
#include "key_function.h"
#include "pthread.h"

gchar *_(gchar *string)
{
    return(g_locale_to_utf8(string, -1, NULL, NULL, NULL));
}

GtkWidget *window;
GtkWidget *Image_fixedd;
GdkPixbuf *dest_pixbuf;
   GtkWidget *Imagee;
    GtkWidget *Image_frame;
/* 绘制实时图像栏 */
GdkPixbuf *src_pixbuf;
void Real_Time_Video( GtkWidget **Image_fixed )
{


    Image_frame = gtk_frame_new("实时图像");
    gtk_frame_set_shadow_type(GTK_FRAME(Image_frame), GTK_SHADOW_IN);
    gtk_frame_set_label_align(GTK_FRAME(Image_frame),0.04,0.9);
    gtk_widget_set_size_request(Image_frame, 500, 300);

    src_pixbuf = gdk_pixbuf_new_from_file("web.png", NULL);
    dest_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, 500, 300, GDK_INTERP_HYPER);

    Imagee = gtk_image_new_from_pixbuf(dest_pixbuf);
    gtk_container_add(GTK_CONTAINER(Image_frame), Imagee);

    Image_fixedd = *Image_fixed = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(*Image_fixed), Image_frame, 20, 30);
}
extern char new_image;
void   update_image( )
{
    static char temp__d=0;
    while(1)
    {

        if( new_image )
        {
            //update a new image
            gdk_threads_enter();
            gtk_container_remove(GTK_CONTAINER(Image_frame), Imagee);

            src_pixbuf = gdk_pixbuf_new_from_file("res.jpg", NULL);
            dest_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, 500, 300, GDK_INTERP_HYPER);

            Imagee = gtk_image_new_from_pixbuf(dest_pixbuf);
            gtk_container_add(GTK_CONTAINER(Image_frame), Imagee);

            Image_fixedd = gtk_fixed_new();
            gtk_fixed_put(GTK_FIXED(Image_fixedd), Image_frame, 20, 30);
            gtk_widget_show_all(Image_fixedd);
            gdk_threads_leave();
            new_image = 0;
            temp__d = 0;
        }
        if( (!temp__d)&&(!now_status.status.PCDuino) )
        {
            gdk_threads_enter();
            gtk_container_remove(GTK_CONTAINER(Image_frame), Imagee);

            src_pixbuf = gdk_pixbuf_new_from_file("web.png", NULL);
            dest_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, 500, 300, GDK_INTERP_HYPER);

            Imagee = gtk_image_new_from_pixbuf(dest_pixbuf);
            gtk_container_add(GTK_CONTAINER(Image_frame), Imagee);

            Image_fixedd = gtk_fixed_new();
            gtk_fixed_put(GTK_FIXED(Image_fixedd), Image_frame, 20, 30);
            gtk_widget_show_all(Image_fixedd);
            gdk_threads_leave();
            temp__d = 1;

        }
        usleep(10000);

    }
}

GtkWidget *Remote_pc;
GtkWidget *Stm32_Dev;
GtkWidget *Remote_Dev;
/* 绘制状态信息栏 */
void Status_Video( GtkWidget **Status_fixed )
{
    GtkWidget *Status_frame;

    GtkWidget *event_box;
    GtkWidget *hseparator1;
    GtkWidget *hseparator2;

    Status_frame = gtk_frame_new("状态信息");
    *Status_fixed = gtk_fixed_new();
    hseparator1 = gtk_separator_new(FALSE);
    hseparator2 = gtk_separator_new(FALSE);

    gtk_frame_set_shadow_type(GTK_FRAME(Status_frame), GTK_SHADOW_IN);
    gtk_frame_set_label_align(GTK_FRAME(Status_frame),0.2,0.9);
    gtk_widget_set_size_request(Status_frame, 200, 320);

    event_box = gtk_box_new( TRUE,0);

    Remote_pc = gtk_label_new (NULL);
    gtk_label_set_justify (GTK_LABEL(Remote_pc),GTK_JUSTIFY_CENTER );
    gtk_label_set_markup(GTK_LABEL(Remote_pc),_("远程电脑\n<span foreground=\"#ff0000\">离线</span>"));
    gtk_widget_set_size_request(Remote_pc, 0, 0);
    gtk_box_pack_start(GTK_BOX(event_box), Remote_pc, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(event_box),hseparator1, FALSE,FALSE,0);


    Stm32_Dev = gtk_label_new (NULL);
    gtk_label_set_justify (GTK_LABEL(Stm32_Dev),GTK_JUSTIFY_CENTER );
    gtk_label_set_markup(GTK_LABEL(Stm32_Dev),_("设备终端\n<span foreground=\"#ff0000\">离线</span>"));
    gtk_widget_set_size_request(Stm32_Dev, 0, 0);
    gtk_box_pack_start(GTK_BOX(event_box), Stm32_Dev, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(event_box),hseparator2, FALSE,FALSE,0);

    Remote_Dev = gtk_label_new (NULL);
    gtk_label_set_justify (GTK_LABEL(Remote_Dev),GTK_JUSTIFY_CENTER );
    gtk_label_set_markup(GTK_LABEL(Remote_Dev),_("遥控器终端\n<span foreground=\"#ff0000\">离线</span>"));
    gtk_widget_set_size_request(Remote_Dev, 0, 0);
    gtk_box_pack_start(GTK_BOX(event_box), Remote_Dev, TRUE, TRUE, 0);


    gtk_container_add(GTK_CONTAINER(Status_frame), event_box);
    gtk_fixed_put(GTK_FIXED(*Status_fixed), Status_frame, 20, 30);

}

GtkWidget *Button_W;
GtkWidget *Button_S;
GtkWidget *Button_A;
GtkWidget *Button_D;
GtkWidget *Button_Shift;
GtkWidget *Button_Ctrl;
GtkWidget *V_scale;
GtkWidget *IP_entry;
GtkWidget *Connect_Quit;

void Control_Window( GtkWidget **Control_fixed )
{

    GtkWidget *APP_Quit;

    GtkWidget *Switch_1;
    GtkWidget *Switch_1_text;
    GtkWidget *Switch_2;
    GtkWidget *Switch_2_text;
    GtkWidget *Switch_3;
    GtkWidget *Switch_3_text;
    GtkWidget *Switch_4;
    GtkWidget *Switch_4_text;

    IP_entry = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(*Control_fixed), IP_entry, 650, 380);
    gtk_entry_set_max_length(GTK_ENTRY(IP_entry),15);
    gtk_entry_set_text(GTK_ENTRY(IP_entry),"192.168.001.100");
    gtk_entry_set_alignment(GTK_ENTRY(IP_entry), 0.5);
    gtk_entry_set_width_chars(GTK_ENTRY(IP_entry),1);
    gtk_widget_set_size_request(IP_entry, 130, -1);
    gtk_entry_set_placeholder_text(GTK_ENTRY(IP_entry),"IP Address");

    Connect_Quit = gtk_button_new_with_label("连接");
    gtk_widget_set_size_request(Connect_Quit, 100, 40);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Connect_Quit, 670, 425);

    APP_Quit = gtk_button_new_with_label("退出");
    gtk_widget_set_size_request(APP_Quit, 100, 40);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), APP_Quit, 670, 480);

/************************ 备用按钮 ***********************/
    Switch_1_text = gtk_label_new("备用:");
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Switch_1_text, 510, 385);
    Switch_1 = gtk_switch_new();
    gtk_widget_set_size_request(Switch_1, 15, 10);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Switch_1, 550, 385);
    gtk_widget_set_sensitive(Switch_1,FALSE);

    Switch_2_text = gtk_label_new("备用:");
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Switch_2_text, 510, 421);
    Switch_2 = gtk_switch_new();
    gtk_widget_set_size_request(Switch_2, 15, 10);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Switch_2, 550, 421);
    gtk_widget_set_sensitive(Switch_2,FALSE);

    Switch_3_text = gtk_label_new("备用:");
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Switch_3_text, 510, 459);
    Switch_3 = gtk_switch_new();
    gtk_widget_set_size_request(Switch_3, 15, 10);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Switch_3, 550, 459);
    gtk_widget_set_sensitive(Switch_3,FALSE);

    Switch_4_text = gtk_label_new("备用:");
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Switch_4_text, 510, 496);
    Switch_4 = gtk_switch_new();
    gtk_widget_set_size_request(Switch_4, 15, 10);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Switch_4, 550, 496);
    gtk_widget_set_sensitive(Switch_4,FALSE);

/************************控制按钮 **********************************/
    Button_W = gtk_button_new_with_label("W");
    gtk_widget_set_size_request(Button_W, 80, 60);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Button_W, 300, 385);

    Button_S = gtk_button_new_with_label("S");
    gtk_widget_set_size_request(Button_S, 80, 60);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Button_S, 300, 470);

    Button_A = gtk_button_new_with_label("A");
    gtk_widget_set_size_request(Button_A, 80, 60);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Button_A, 205, 425);

    Button_D = gtk_button_new_with_label("D");
    gtk_widget_set_size_request(Button_D, 80, 60);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Button_D, 395, 425);

    Button_Shift = gtk_button_new_with_label("SHIFT");
    gtk_widget_set_size_request(Button_Shift, 80, 40);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Button_Shift, 100, 440);

    Button_Ctrl = gtk_button_new_with_label("CTRL");
    gtk_widget_set_size_request(Button_Ctrl, 80, 40);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), Button_Ctrl, 100, 490);

    V_scale = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL,0, 100, 1);
    gtk_range_set_inverted(GTK_RANGE(V_scale), TRUE);
    gtk_scale_set_value_pos(GTK_SCALE(V_scale), GTK_POS_TOP);
    gtk_widget_set_size_request(V_scale, 50, 155);
    gtk_fixed_put(GTK_FIXED(*Control_fixed), V_scale, 30, 375);

    gtk_range_set_value(GTK_RANGE(V_scale),40);
    g_signal_connect(APP_Quit, "clicked", G_CALLBACK(APP_Quit_clicked), NULL);
    g_signal_connect(Connect_Quit, "clicked", G_CALLBACK(Connect_Quit_clicked), NULL);


}
int w_key_time = 0;
int s_key_time = 0;
int a_key_time = 0;
int d_key_time = 0;
int q_key_time = 0;
int e_key_time = 0;
static gboolean time_handler( GtkWidget *widget )
{
    static char last_w=0;
    static char last_s=0;
    static char last_a=0;
    static char last_d=0;
    static char last_q=0;
    static char last_e=0;
    double v_data;
    if( (0 == now_status.status.PCDuino) )
    {
        gtk_widget_set_sensitive(Button_W,FALSE);
        gtk_widget_set_sensitive(Button_S,FALSE);
        gtk_widget_set_sensitive(Button_A,FALSE);
        gtk_widget_set_sensitive(Button_D,FALSE);
        gtk_widget_set_sensitive(Button_Shift,FALSE);
        gtk_widget_set_sensitive(Button_Ctrl,FALSE);
        gtk_widget_set_sensitive(V_scale,FALSE);
        gtk_widget_set_sensitive(IP_entry,TRUE);
        gtk_label_set_markup(GTK_LABEL(Remote_pc),_("远程电脑\n<span foreground=\"#ff0000\">离线</span>"));
        gtk_label_set_markup(GTK_LABEL(Stm32_Dev),_("设备终端\n<span foreground=\"#ff0000\">离线</span>"));
        gtk_label_set_markup(GTK_LABEL(Remote_Dev),_("遥控器终端\n<span foreground=\"#ff0000\">离线</span>"));

    }
    else if( (1 == now_status.status.PCDuino) )
    {

        v_data = gtk_range_get_value(GTK_RANGE(V_scale));
        now_status.speed.Rate = (int)v_data;

        gtk_widget_set_sensitive(IP_entry,FALSE);
        gtk_label_set_markup(GTK_LABEL(Remote_pc),_("远程电脑\n<span foreground=\"#228b22\">在线</span>"));
        if( now_status.status.Device ==1 )
        {
            gtk_widget_set_sensitive(Button_W,TRUE);
            gtk_widget_set_sensitive(Button_S,TRUE);
            gtk_widget_set_sensitive(Button_A,TRUE);
            gtk_widget_set_sensitive(Button_D,TRUE);
            gtk_widget_set_sensitive(Button_Shift,TRUE);
            gtk_widget_set_sensitive(Button_Ctrl,TRUE);
            gtk_widget_set_sensitive(V_scale,TRUE);
            gtk_label_set_markup(GTK_LABEL(Stm32_Dev),_("设备终端\n<span foreground=\"#228b22\">在线</span>"));
        }
        else
        {
            gtk_label_set_markup(GTK_LABEL(Stm32_Dev),_("设备终端\n<span foreground=\"#ff0000\">离线</span>"));
        }

        if( now_status.status.Remote ==1 )
            gtk_label_set_markup(GTK_LABEL(Remote_Dev),_("遥控器终端\n<span foreground=\"#228b22\">在线</span>"));
        else
            gtk_label_set_markup(GTK_LABEL(Remote_Dev),_("遥控器终端\n<span foreground=\"#ff0000\">离线</span>"));

        if(gtk_scale_get_digits(GTK_SCALE(V_scale))>50 )
        {
            now_status.status.Remote = 1;
        }
        else
        {
            now_status.status.Remote = 0;
        }


    }

    if(w_key_time)
    {
        w_key_time --;
        if(last_w)
            now_status.speed.up = now_status.speed.Rate * 4;
        last_w = 1;
    }
    else
    {
        now_status.speed.up = 0;
        last_w = 0;
    }


    if(s_key_time)
    {
        s_key_time --;
        if(last_s)
            now_status.speed.down = now_status.speed.Rate * 4;
        last_s = 1;
    }
    else
    {
        now_status.speed.down = 0;
        last_s = 0;
    }


    if(a_key_time)
    {
        a_key_time --;
        if(last_a)
            now_status.speed.left = now_status.speed.Rate * 4;
        last_a = 1;
    }
    else
    {
        now_status.speed.left = 0;
        last_a = 0;
    }


    if(d_key_time)
    {
        d_key_time --;
        if(last_d)
            now_status.speed.right = now_status.speed.Rate * 4;
        last_d = 1;
    }
    else
    {
        now_status.speed.right = 0;
        last_d = 0;
    }

    if(q_key_time)
    {
        q_key_time --;
        if(last_q)
            now_status.speed.lRote = now_status.speed.Rate * 4;
        last_q = 1;
    }
    else
    {
        now_status.speed.lRote = 0;
        last_q = 0;
    }

    if(e_key_time)
    {
        e_key_time --;
        if(last_e)
            now_status.speed.rRote = now_status.speed.Rate * 4;
        last_e = 1;
    }
    else
    {
        now_status.speed.rRote = 0;
        last_e = 0;
    }



    return TRUE;
}

int main( int argc, char *argv[] )
{


    GtkWidget *Control_fixed;
    GtkWidget *hbox;
    GtkWidget *Win_fixed;
    GtkWidget *Image_fixed;
    GtkWidget *Status_fixed;



    gtk_init(&argc, &argv );            //初始化整个GTK+程序
    g_thread_init(NULL);

    gdk_threads_init();

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window),"智能小车远程管理系统");
    gtk_widget_set_size_request(window, 850,580);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

    Win_fixed = gtk_fixed_new();

    hbox = gtk_box_new ( FALSE,2);
    Real_Time_Video( &Image_fixed);

    gtk_box_pack_start (GTK_BOX(hbox),Image_fixed,FALSE,TRUE,30);

    Status_Video( &Status_fixed);

    gtk_box_pack_start (GTK_BOX(hbox),Status_fixed,TRUE,TRUE,0);
    gtk_fixed_put(GTK_FIXED(Win_fixed), hbox, 0, 0);


    Control_fixed = gtk_fixed_new();

    Control_Window(&Control_fixed);

    gtk_fixed_put(GTK_FIXED(Win_fixed), Control_fixed, 0, 0);

    g_timeout_add(100, (GSourceFunc) time_handler, (gpointer)window);

    gtk_container_add(GTK_CONTAINER(window),Win_fixed);
    gtk_widget_show_all(window);
    g_signal_connect(window, "destroy",G_CALLBACK(APP_Quit_clicked),NULL);

    g_thread_new("Update_Image",(GThreadFunc)update_image, NULL);

    gtk_main();

    return 0;
}

