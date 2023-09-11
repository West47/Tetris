#include <assert.h>
#include "GUI.h"
#include <iostream>


CairoContext::CairoContext()
{
    m_width = 1;
}

CairoContext::~CairoContext()
{
}

void CairoContext::SetCairoContext(cairo_t *cr)
{
    m_cr = cr;
}

void CairoContext::Save()
{
    cairo_save(m_cr);
}

void CairoContext::Restore()
{
    cairo_restore(m_cr);
}

void CairoContext::SetMask(const Point &pos, const Point &size)
{
    cairo_translate(m_cr, pos.GetX(), pos.GetY());
    cairo_rectangle(m_cr, 0, 0, size.GetX(), size.GetY());
    cairo_clip(m_cr);
}

void CairoContext::SetColor(const RGB &clr)
{
    m_color = clr;
}

void CairoContext::SetLineWidth(uint16_t width)
{
    m_width = width;
}

void CairoContext::FillRectangle(const Point &from, const Point &to)
{
	cairo_set_source_rgb(m_cr, m_color.GetRed(), m_color.GetGreen(), m_color.GetBlue());
	cairo_set_line_width (m_cr, m_width);
	cairo_rectangle(m_cr, from.GetX(), from.GetY(), to.GetX(), to.GetY());
    cairo_fill(m_cr);
}

void CairoContext::Rectangle(const Point &from, const Point &to)
{
	cairo_set_source_rgb(m_cr, m_color.GetRed(), m_color.GetGreen(), m_color.GetBlue());
	cairo_set_line_width (m_cr, m_width);
	cairo_rectangle(m_cr, from.GetX(), from.GetY(), to.GetX(), to.GetY());
    cairo_stroke(m_cr);
}

void CairoContext::Line(const Point &from, const Point &to)
{
	cairo_set_source_rgb(m_cr, m_color.GetRed(), m_color.GetGreen(), m_color.GetBlue());
	cairo_set_line_width (m_cr, m_width);
    cairo_move_to(m_cr, from.GetX(), from.GetY());
    cairo_line_to(m_cr, to.GetX(), to.GetY());
    cairo_stroke(m_cr);
}

void CairoContext::End(const Point &pos)
{
				  cairo_set_source_rgb(m_cr,m_color.GetRed(),m_color.GetGreen(),m_color.GetBlue());
	cairo_set_font_size(m_cr, m_width);
	cairo_move_to(m_cr,pos.GetX()-20, pos.GetY()+125);
	cairo_show_text(m_cr,"G A M E");
	cairo_move_to(m_cr,pos.GetX()+525, pos.GetY()+125);
	cairo_show_text(m_cr,"O V E R");
}

void CairoContext::do_drawing (Context *cr)
{
	
}

void CairoContext::Score(const Point &pos, char str[])
{
	cairo_set_source_rgb(m_cr, m_color.GetRed(), m_color.GetGreen(), m_color.GetBlue());
	cairo_set_font_size(m_cr, m_width);
	cairo_move_to(m_cr, pos.GetX()+10, pos.GetY());
	cairo_show_text(m_cr, str);
}

void CairoContext::Rules(const Point &pos)
{
	cairo_set_source_rgb(m_cr,m_color.GetRed(),m_color.GetGreen(),m_color.GetBlue());
	cairo_set_font_size(m_cr, m_width);
	cairo_move_to(m_cr,pos.GetX()+450, pos.GetY());
	cairo_show_text(m_cr,"CONTROL:");
	cairo_move_to(m_cr,pos.GetX()+450, pos.GetY()+25);
	cairo_show_text(m_cr,"A - LEFT");
	cairo_move_to(m_cr,pos.GetX()+450, pos.GetY()+40);
	cairo_show_text(m_cr,"S - DOWN");
	cairo_move_to(m_cr,pos.GetX()+450, pos.GetY()+55);
	cairo_show_text(m_cr,"D - RIGHT");
	cairo_move_to(m_cr,pos.GetX()+550, pos.GetY()+25);
	cairo_show_text(m_cr,"Q - TURN LEFT");
	cairo_move_to(m_cr,pos.GetX()+550, pos.GetY()+40);
	cairo_show_text(m_cr,"E - TURN RIGHT");
	cairo_move_to(m_cr,pos.GetX()+10, pos.GetY());
	cairo_show_text(m_cr,"OPTIONS");
	cairo_move_to(m_cr,pos.GetX()+10, pos.GetY()+20);
	cairo_show_text(m_cr,"1 - START/CONTINUE");
	cairo_move_to(m_cr,pos.GetX()+10, pos.GetY()+35);
	cairo_show_text(m_cr,"2 - PAUSE");
	cairo_move_to(m_cr,pos.GetX()+10, pos.GetY()+50);
	cairo_show_text(m_cr,"3 - TIMER ON");	
	cairo_move_to(m_cr,pos.GetX()+10, pos.GetY()+65);
	cairo_show_text(m_cr,"0 - NEW GAME");
	cairo_move_to(m_cr,pos.GetX()+10, pos.GetY()+90);
	cairo_show_text(m_cr,"B - CLOSE WINDOW");
}
GtkPlus::GtkPlus()
{
}

GtkPlus::~GtkPlus()
{
}

int GtkPlus::Run(int argc, char **argv, Window *wnd, uint16_t w, uint16_t h)
{
    // инициализация GTK+
	gtk_init(&argc, &argv);

	// Создаем главное окно, устанавливваем заголовок
	m_Widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	m_Window = wnd;
	gtk_window_set_title(GTK_WINDOW(m_Widget), "GUI Model");
	gtk_window_set_default_size (GTK_WINDOW(m_Widget),w,h);

	// Показываем окно
	gtk_widget_show_all(m_Widget);

	wnd->Create(this);

	// Соединяем сигналы
	g_signal_connect(G_OBJECT(m_Widget), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(m_Widget), "draw", G_CALLBACK(on_draw), this);
	g_signal_connect(G_OBJECT(m_Widget), "size-allocate", G_CALLBACK(on_size_allocate), this);
    g_signal_connect (m_Widget, "button-press-event", G_CALLBACK (on_button_press_event), this);
    g_signal_connect (m_Widget, "key-press-event", G_CALLBACK (on_key_press_event), this);

	// Приложение переходит в вечный цикл ожидания действий пользователя
	gtk_main();

	return 0;
}

bool GtkPlus::NotifyWindow(uint32_t type, const Point &p, uint64_t value)
{
    bool res = m_Window->WindowProc(type, p, value);

    if(m_Window->m_bToBeDeleted)
    {
        gtk_main_quit();
    }

    return res;
}

gboolean GtkPlus::Draw(GtkWidget *widget, cairo_t *cr)
{
    assert(m_Widget == widget);
    SetCairoContext(cr);
    m_Window->Draw(this);
    return TRUE;
}

void GtkPlus::ReDraw()
{
    gtk_widget_queue_draw(m_Widget);
}

gboolean GtkPlus::Allocation(GtkWidget *widget, GdkRectangle *allocation)
{
    assert(m_Widget == widget);
    return NotifyWindow(EVENT_WINDOWRESIZE, Point(allocation->width,allocation->height),0);
}

gboolean GtkPlus::ButtonPressEvent(GtkWidget *widget, GdkEventButton *event)
{
    assert(m_Widget == widget);

    uint32_t type;

    switch(event->button)
    {
    case GDK_BUTTON_PRIMARY:
        type = EVENT_LEFTMOUSEBUTTONCLICK;
        break;
    case GDK_BUTTON_SECONDARY:
        type = EVENT_RIGHTMOUSEBUTTONCLICK;
        break;
    default:
        type = EVENT_UNKNOWN;
    }

    return NotifyWindow(type, Point(event->x,event->y),0);
}

gboolean GtkPlus::KeyPressEvent(GtkWidget *widget, GdkEvent *event)
{
    assert(m_Widget == widget);
    /*
    uint32_t type;
    int k;
    k=getchar();
    switch (event->key.keyval)
    {
    	case 'a':
    		std::cout << "ChildWindow::OnDraw()" << 'L' <<std::endl;
    		break;
    		
    	case 's':
    		std::cout << "ChildWindow::OnDraw()" << 'D' <<std::endl;
    		break;
    	case 'd':
    		std::cout << "ChildWindow::OnDraw()" << 'R' <<std::endl;
    		break;
    }
    */
    return NotifyWindow(EVENT_KEYPRESS, Point(0,0),event->key.keyval);
}



int Run(int argc, char **argv, Window *wnd, uint16_t w, uint16_t h)
{
    GtkPlus *gui = new GtkPlus;
    int res = gui->Run(argc, argv, wnd, w, h);
    delete gui;
    return res;
}

gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    GtkPlus *gui = reinterpret_cast<GtkPlus*>(user_data);
    return gui->Draw(widget,cr);
}

gboolean on_size_allocate(GtkWidget *widget, GdkRectangle *allocation, gpointer user_data)
{
    GtkPlus *gui = reinterpret_cast<GtkPlus*>(user_data);
    return gui->Allocation(widget,allocation);
}

gboolean on_button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
    GtkPlus *gui = reinterpret_cast<GtkPlus*>(user_data);
    return gui->ButtonPressEvent(widget,event);
}

gboolean on_key_press_event(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    GtkPlus *gui = reinterpret_cast<GtkPlus*>(user_data);
    return gui->KeyPressEvent(widget,event);
}
