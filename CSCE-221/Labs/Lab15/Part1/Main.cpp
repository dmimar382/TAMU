#include <iostream>
using namespace std;

class Color {
/* Public */
public:
    void cout_rgb (void) { cout << "Color Values: (" << R << ',' << G <<
        ',' << B << ')' << endl;}
    int get_R (){return R;}
    int get_G (){return G;}
    int get_B (){return B;}

    void set_R(int r){
    	if (r < 0 || r > 255)
    		throw runtime_error("the value is out of range");
    	else
    		R = r; 

    }
    void set_G(int g){
    	if (g < 0 || g > 255)
    		throw runtime_error("the value is out of range");
    	else
    		G = g; 

    }
    void set_B(int b){
    	if (b < 0 || b > 255)
    		throw runtime_error("the value is out of range");
    	else
    		B = b; 

    }
    // int R;
    // int G;
    // int B;
/* Private */
private:
	int R = 255;
    int G = 255;
    int B = 255;
};

int main()
{
	try{
	    Color color;
	    // color.R = 29;
	    // color.G = 51;
	    // color.B = 98;
	    color.cout_rgb();
	    cout << "color.R = " << color.get_R() <<endl;
	    cout << "color.G = " << color.get_G() <<endl;
	    cout << "color.B = " << color.get_B() <<endl;

	    cout << "Please enter integer values for R, G, and B: ";
	    int R, G, B;
	    cin >> R >> G >> B;
	    color.set_R(R); color.set_G(G); color.set_B(B);
	    color.cout_rgb();
	}
	catch( runtime_error& x){
		cout << x.what()<< endl;
	}
}