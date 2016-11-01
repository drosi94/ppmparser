//------------------------------------------------------------
//
// C++ course tutorial code 
//
// G. Papaioannou, 2015
//
//-------------------------------------------------------------

#ifndef _COLOR
#define _COLOR


namespace imaging 
{
	// create an alias for the floating point representation of color components (32bit per color channel).
	// Each color channel goes from 0.0f (darkness) to 1.0f (full color brightness).
	// For example, bright red is (1,0,0), white is (1,1,1), magenta is (1,0,1) etc.
	typedef float component_t;

	class Color 
	{
	public: 
		// members
		component_t r,g,b;
		
		// member functions
		component_t & operator [] (size_t index)
		{
			return *(&r + index);
		}
		
		Color operator + (Color & right)
		{
			Color left;
			left.r = r + right.r;
			left.g = g + right.g;
			left.b = b + right.b;
			return left;
		}

		// constructors
		Color(component_t r, component_t g, component_t b) : r(r), g(g), b(b) {}
		
		Color() : r(0), g(0), b(0) {}
	};
}

#endif _COLOR