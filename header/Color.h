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
	/*! An alias for the floating point representation of color components (32bit per color channel).
	 *
	 * Each color channel goes from 0.0f (darkness) to 1.0f (full color brightness).
	 * For example, bright red is (1,0,0), white is (1,1,1), magenta is (1,0,1) etc.
	 */
	typedef float component_t;

	/*! Represents a triplet of Red, Green, Blue (RGB) values. 
	 */	
	class Color 
	{
	public: 
		// members
		component_t r, //! The red color channel (component)
		            g, //! The green color channel (component)
					b; //! The blue color channel (component)
		
		// member functions
		
		/*! This operator returns the index-th component of the image.
		 * 
         *	For speed, no bounds for index values are checked.
		 *
		 *  \param index is the index of the component to obtain. Values should be 0, 1 or 2. 
		 *
		 *  \return a reference to the respective color component.
		 */
		component_t & operator [] (size_t index)
		{
			return *(&r + index);
		}
		
		/*! Addition operator.
		 *
		 *  Adds a color to the current one and returns the result.
		 *
		 *  \param right is the right Color operand of the + sign. 
		 *  
		 *  \return the resulting color after the component-wise addition of the two colors.
		 */
		Color operator + (Color & right)
		{
			Color left;
			left.r = r + right.r;
			left.g = g + right.g;
			left.b = b + right.b;
			return left;
		}

		// constructors
		
		/*! Parameterized constructor.
		 *
		 * \param r is the red component of the color.
		 * \param g is the green component of the color.
		 * \param b is the blue component of the color.
		 */  
		Color(component_t r, component_t g, component_t b) : r(r), g(g), b(b) {}
		
		/*! Default constructor.
		 *
		 *  All components set to zero, i.e. a black color.
		 */
		Color() : r(0), g(0), b(0) {}
	};
}

#endif _COLOR