#include <gtk/gtk.h>
#include "window.h"
#include "aux.h"

class CairoContext : public Context
{
public:
    CairoContext();
    ~CairoContext();

    void SetCairoContext(cairo_t *cr);

    // унаследованные от класса Context методы
    
    void Save();
    void Restore();
    void SetMask(const Point &pos, const Point &size);

	void do_drawing (Context *cr);
    void SetColor(const RGB &clr);
    void SetLineWidth(uint16_t width);

    void FillRectangle(const Point &from, const Point &to);
    void Rectangle(const Point &from, const Point &to);
    void Line(const Point &from, const Point &to);
    
    void Rules(const Point &pos);
    void Score(const Point &pos, char str[]);
    void End(const Point &pos);

private:
    cairo_t  *m_cr;
    RGB      m_color;
    uint16_t m_width;
};

class GtkPlus : public CairoContext, public Window
{
public:
    GtkPlus();
    ~GtkPlus();

    int Run(int arc, char **argv, Window *wnd, uint16_t w, uint16_t h);
    bool NotifyWindow(uint32_t type, const Point &p, uint64_t value);

    void ReDraw();

    gboolean Draw(GtkWidget *widget, cairo_t *cr);
    gboolean Allocation(GtkWidget *widget, GdkRectangle *allocation);
    gboolean ButtonPressEvent(GtkWidget *widget, GdkEventButton *event);
    gboolean KeyPressEvent(GtkWidget *widget, GdkEvent *event);

private:
    GtkWidget *m_Widget;
    Window    *m_Window;
};


int Run(int arc, char **argv, Window *wnd, uint16_t w, uint16_t h);

gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean on_size_allocate(GtkWidget *widget, GdkRectangle *allocation, gpointer user_data);
gboolean on_button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer user_data);
gboolean on_key_press_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);
