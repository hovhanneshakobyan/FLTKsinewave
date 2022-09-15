#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>


//using namespace FI;

int main ()
{
	Fl_Window wi(400,500);
    	Fl_Box box(0,0,200,200,"Hey, I mean, Hello, World!");
	wi.show();
	return (Fl::run());


}


