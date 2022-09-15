#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Chart.H>
#include <math.h>

//using namespace FI;

int main ()
{
	Fl_Window win(400,500);
    	    Fl_Chart  *chart = new Fl_Chart(20, 20, win->w()-40, win->h()-40, "Chart");
    chart->bounds(-125.0, 125.0);
    for ( double t=0; t<15; t+=0.5 ) {
        double val = sin(t) * 125.0;
        static char val_str[20];
        sprintf(val_str, "%.0lf", val);
        chart->add(val, val_str, (val<0)?FL_RED:FL_GREEN);
	
	Fl_Box box(0,0,200,200,"Hey, I mean, Hello, World!");
	win.show();
	return (Fl::run());


}


