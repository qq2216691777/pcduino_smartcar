#include "gtk/gtk.h"
#include "key_function.h"
#include "pthread.h"
#include "net.h"
//鼠标离开按钮时触发leave信号  
//    g_signal_connect(GTK_OBJECT(button),"leave",G_CALLBACK(button_leave),NULL);  
//鼠标按下按钮时触发pressed信号  
//    g_signal_connect(GTK_OBJECT(button),"pressed",G_CALLBACK(button_pressed),NULL);  
//鼠标松开是触发clicked信号  
//    g_signal_connect(GTK_OBJECT(button),"clicked",G_CALLBACK(button_clicked),NULL);

pthread_t Net_p_id;

void APP_Quit_clicked(GtkWidget *widget, gpointer label)
{
    gtk_widget_set_sensitive(widget,FALSE);
    gtk_main_quit();

}
extern GtkWidget *IP_entry;
extern GtkWidget *V_scale;
extern GtkWidget *window;
void Connect_Quit_clicked(GtkWidget *widget, gpointer label)
{
    char *get_buff;
    if( 0==now_status.net.Status )
    {
        gtk_widget_set_sensitive(widget,FALSE);

        get_buff = gtk_entry_get_text(GTK_ENTRY(IP_entry));
        now_status.net.Status = 0;
        pthread_create( &Net_p_id, NULL, &Pthread_Net, get_buff );
        while( now_status.net.Status == 0)
            usleep(10000);

        if(0!=pthread_kill(Net_p_id,0))
        {
            //连接失败
            gtk_widget_set_sensitive(widget,TRUE);
            return ;
        }
        gtk_button_set_label (GTK_BUTTON(widget),"断开");

        gtk_widget_set_sensitive(widget,TRUE);
        g_signal_connect(window, "key-press-event", G_CALLBACK(key_value), NULL);
    }
    else if( 0!=now_status.net.Status )
    {
        gtk_widget_set_sensitive(widget,FALSE);

        gtk_button_set_label (GTK_BUTTON(widget),"连接");

        now_status.net.Status = 0;
        now_status.status.PCDuino = 0;
        now_status.status.Device = 0;
        gtk_widget_set_sensitive(widget,TRUE);
        pthread_cancel(Net_p_id);
    }
}

void Button_W_pressed(GtkWidget *widget, gpointer label)
{

}

void Button_W_leave(GtkWidget *widget, gpointer label)
{



}

void Button_S_pressed(GtkWidget *widget, gpointer label)
{

}

void Button_S_leave(GtkWidget *widget, gpointer label)
{


}

void Button_A_pressed(GtkWidget *widget, gpointer label)
{

}

void Button_A_leave(GtkWidget *widget, gpointer label)
{

}


void Button_D_pressed(GtkWidget *widget, gpointer label)
{

}

void Button_D_leave(GtkWidget *widget, gpointer label)
{

}
extern int w_key_time;
extern int s_key_time;
extern int a_key_time;
extern int d_key_time;
extern int q_key_time;
extern int e_key_time;
void key_value(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    char *key_value;
    key_value = gdk_keyval_name(event->keyval);
    if( key_value[1] >10 )
    {
        if( 'T' == key_value[0] )
        {
            printf("Tab\r\n");
        }
        else if( 'C' == key_value[0] )
        {
            if('a' == key_value[1])
                printf("Cap\r\n");
            else
                gtk_range_set_value(GTK_RANGE(V_scale),now_status.speed.Rate-20);
        }
        else if( 'S' == key_value[0] )
        {
            gtk_range_set_value(GTK_RANGE(V_scale),now_status.speed.Rate+20);
        }


    }
    else if( 'w' == key_value[0] || 'W' == key_value[0] )
    {
        w_key_time = 1;
    }
    else if( 's' == key_value[0] || 'S' == key_value[0] )
    {
        if( !s_key_time )
            s_key_time = 8;
        else
            s_key_time = 1;
    }
    else if( 'a' == key_value[0] || 'A' == key_value[0] )
    {
        if( !a_key_time )
            a_key_time = 8;
        else
            a_key_time = 1;
    }
    else if( 'd' == key_value[0] || 'D' == key_value[0] )
    {
        if( !d_key_time )
            d_key_time = 8;
        else
            d_key_time = 1;
    }
    else if( 'q' == key_value[0] || 'Q' == key_value[0] )
    {
        if( !q_key_time )
            q_key_time = 8;
        else
            q_key_time = 1;
    }
    else if( 'e' == key_value[0] || 'E' == key_value[0] )
    {
        if( !e_key_time )
            e_key_time = 8;
        else
            e_key_time = 1;
    }

}







