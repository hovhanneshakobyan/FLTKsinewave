#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include <math.h>
#include <time.h>

#define GRAPH_MAX 101
#define T 0.1 // Sampling time

struct GRAPH
{
double x[GRAPH_MAX+1];
double x1[GRAPH_MAX+1];
double x2[GRAPH_MAX+1];

int n;
};

static struct GRAPH Graph;

class GRAPHBOX : public Fl_Box
{
    void draw()
{
// redraw background

Fl_Box::draw();

fl_color(fl_rgb_color(0, 0, 0));
fl_line(x(), y()+h()/2, x()+w(), y()+h()/2);
fl_line(x(), y(), x(), y()+h());

// redraw graph
// sine function
int n;
for (n=0; n<Graph.n; n++)
{
int xk = x() + 5*(n + 1);
int yk = y() + h()/2 - 100*Graph.x[n];

fl_color(fl_rgb_color(127, 0, 0));
fl_begin_polygon();
fl_arc(xk, yk, 2, 0, 360);

fl_end_polygon();

fl_color(fl_rgb_color(0, 0, 0));
fl_begin_line();
fl_circle(xk, yk, 2);
fl_end_line();
}
// equation
int p;
for (p=0; p<Graph.n; p++)
{
int xk = x() + 5*(p + 1);
int yk = y() + h()/2 - 100*Graph.x1[p];

fl_color(fl_rgb_color(0, 127, 0));
fl_begin_polygon();
fl_arc(xk, yk, 2, 0, 360);

fl_end_polygon();

fl_color(fl_rgb_color(0, 0, 0));
fl_begin_line();
fl_circle(xk, yk, 2);
fl_end_line();
}

fl_font(FL_COURIER, 16);
char str[256],str1[256];
n = Graph.n-1;
sprintf(str, "sin(%2d)=% 1.4lf", n, Graph.x[n]);
sprintf(str1, "x(%2d)=% 1.4lf", n, Graph.x1[n]);
fl_color(fl_rgb_color(127, 0, 0));
fl_draw(str, x()+w()/2, y()+h()-20);
fl_color(fl_rgb_color(0, 127, 0));
fl_draw(str1, x()+w()/2, y()+h()-40);
    }

public:
GRAPHBOX(int x, int y, int w, int h, const char *l=0) : Fl_Box(x, y, w, h, l)
{
box(FL_FLAT_BOX);
color(fl_rgb_color(127, 127, 127));
    }
};

static bool RUNNING = true;

static void WAIT(double time)
{
int cnt = clock();
int ticks = (int) (time*CLOCKS_PER_SEC);
while (true)
{
if (clock() > (cnt + ticks))
return;
else
{
// workaround for Fl::wait(0.0) which does not return RUNNING
RUNNING = Fl::check();
}
}
}

int main(void)
{
Fl_Window window(550, 400, "Graph");
GRAPHBOX graphbox(10, 10, window.w()-20, window.h()-20);
window.show();

Graph.x1[0] = 0.0;
Graph.x2[0] = 0.0;

Graph.n = 0;

while (RUNNING)
{
if (Graph.n < GRAPH_MAX)
{
Graph.x[Graph.n] = sin(4* Graph.n * T);
Graph.x1[Graph.n+1] = Graph.x1[Graph.n]+ T* Graph.x2[Graph.n];
//Graph.x2[Graph.n+1] = Graph.x2[Graph.n]- T* (Graph.x1[Graph.n+1]+2*Graph.x2[Graph.n])+ T* Graph.x[Graph.n];
Graph.n++;
graphbox.redraw();
WAIT(0.05);
}
else
{
// done graph
RUNNING = Fl::wait();
}
}
return EXIT_SUCCESS;
}
