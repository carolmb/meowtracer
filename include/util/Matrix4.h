#ifndef __MATRIX__
#define __MATRIX__

class Matrix4 {
private:
	typedef double number; 

	number[4][4] values;
public:
	number operator [](int i) const { return values[i]; }
    number & operator [](int i) { return values[i]; }
};

#endif