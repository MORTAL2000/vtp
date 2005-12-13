//
// Array.h
//
// Copyright (c) 2001-2003 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//
/** \file Array.h */

#ifndef ARRAYH
#define ARRAYH

#ifdef _MSC_VER
  #pragma warning(disable: 4786)
  #pragma warning(disable: 4100)
#endif

#if WIN32 && defined(_MSC_VER) && _DEBUG
  #define CRTDBG_MAP_ALLOC
  #include <crtdbg.h>
#endif

#include <stdlib.h>	// for free()
#include <memory.h>	// for memcpy()
#include <assert.h>	// for assert()

/**
 * An Array template which automatically grows as you add or set
 * entities.
 *
 * Note that construction and destruction is not done automatically
 * if the entities are class objects.  You can provide this destruction
 * yourself by overriding the DestructItems method, but it is easier to use
 * this template for objects with simple value semantics such as basic types
 * (int, float..), structs, and pointers.  If you do create a subclass like
 * this:
\code
	class MyArray : public Array<MyObject *> {};
\endcode
 * note that you will need to provide not only a DestructItems()
 * implementation, but also a destructor.  This is because the default
 * Array destructor is not smart enough to call your DestructItems()
 * method (it will call the base DestructItems() instead, which does
 * nothing).
 *
 * A full working example is:
\code
	class MyArray : public Array<MyObject *>
	{
		virtual ~MyArray() { Empty(); free(m_Data); m_Data = NULL; m_MaxSize = 0; }
		virtual	void DestructItems(unsigned int first, unsigned int last)
		{
			for (unsigned int i = first; i <= last; i++)
				delete GetAt(i);
		}
	};
\endcode
 */
template <class E> class Array
{
public:
	Array(unsigned int size = 0);
	Array(const Array<E>&);
	virtual ~Array();

//	Accessors
	unsigned int	GetSize() const;
	unsigned int	GetMaxSize() const;
	bool		SetSize(unsigned int);
	bool		SetMaxSize(unsigned int);
	unsigned int	GetElemSize() const;
	E*			GetData() const;
	bool		IsEmpty() const;
	E&			GetAt(unsigned int i) const;
	bool		SetAt(unsigned int i, E);

//	Other operations
	Array<E>& operator=(const Array<E>&);
	E&			operator[](unsigned int i);
	const E&	operator[](unsigned int i) const;
	void		Empty();
	bool		RemoveAt(unsigned int i, int n = 1);
	int			Append(const E&);
	int			Append(const Array<E>&);
	int			Find(const E&) const;

protected:
//	Internal functions
	virtual bool	Grow(unsigned int);
	virtual	void	DestructItems(unsigned int first, unsigned int last);

//	Data members
	unsigned int	m_Size;		// number of elements added so far
	unsigned int	m_MaxSize;	// maximum number of elements we have room for
	E*				m_Data;		// data area for array
};


/**
 * Creates and initializes an empty array (array with no elements).
 *
 * \param size	number of elements data area should initially make
 *			room for (initial value of [MaxSize]).
 *			If zero, little initial space is allocated but the
 *			array will grow dynamically as space is needed.
 *
 * \sa Array::SetMaxSize Array::SetSize
 *
 * \par Example:
\code
	Array<void*> foo;		// empty array of pointers
\endcode
 *
 */
template <class E> Array<E>::Array(unsigned int size)
{
	m_Size = 0;				// empty to start
	m_MaxSize = 0;			// remember the size
	m_Data = NULL;
	if (size > 0)			// make room for <size> elements
		Grow(size);
}

/**
 * Creates and initializes an array from another (of the same type).
 *
 * \param a	An array to copy from.
 */
template <class E> Array<E>::Array(const Array<E>& a)
{
	if( this == &a )
		return;

	m_Size = 0;		// empty to start
	m_MaxSize = 0;	// remember the size
	m_Data = NULL;
	Append(a);		// copy each element from the given array
}


/**
 *	Called by the array implementation when array items are deleted.
 *	The default implementation does _not_ call the destructors for the
 *	array items. This will not work if your array elements do memory
 *	deallocation in their destructors.
 *
 *	Override this function to explicitly call the destructors properly if
 *	you need this functionality.
 *
 *	\param first	Index of first element to destroy
 *	\param last		Index of last element to destroy
 *
 * \par Example:
\code
	// Overrides DestructItems to call constructors
	inline void MyArray::DestructItems(unsigned int first, unsigned int last)
	{
		for (unsigned int i = first; i <= last; ++i)
		   delete GetAt(i);
	}
\endcode
 */
template <class E> inline void Array<E>::DestructItems(unsigned int first, unsigned int last)
{
	//VTLOG("base DestructItems, %d %d\n", start, nitems);
}


/**
 *	Destructor for array class.
 */
template <class E> inline Array<E>::~Array()
{
	//VTLOG("~Array, size %d, max %d\n", m_Size, m_MaxSize);
	Empty();
	free(m_Data);
	m_Data = NULL;
	m_MaxSize = 0;
}

/**
 * Enlarge the array to accomodate <i>growto</i> elements. If the array
 * can already hold this many elements, nothing is done. Otherwise,
 * the data area of the array is enlarged (reallocating if necessary)
 * so that <i>growto</i> contiguous elements can be stored.
 *
 * \param growto	Number of elements the array should be able to
 *					hold after it has grown
 *
 * \return True if array was successfully grown, else false.
 *
 * \sa Array::SetData Array::SetMaxSize
 */
template <class E> bool Array<E>::Grow(unsigned int growto)
{
	int	n = growto - m_MaxSize;
	E*		old_data;

	if (n >= 0)
	{
		if (m_Data == NULL)					// make new data area?
		{
//			assert(m_Size == 0);
			m_Data = (E*) malloc(sizeof(E) * growto);
			if (m_Data == NULL)				// could not enlarge?
//				ERROR(("Array::Grow: out of memory"), false);
				return false;
		}
		else
		{
			if (growto < 12) growto = 12;	// minimum growth
			old_data = m_Data;
			m_Data = (E*) malloc(sizeof(E) * (growto));
			memcpy(m_Data, old_data, sizeof(E) * m_Size);
			free(old_data);
			if (m_Data == NULL)
//				ERROR(("Array::Grow: out of memory"), false);
				return false;
		}
		m_MaxSize = growto;					// remember new size
	}
	return true;
}

template <class E> inline E* Array<E>::GetData() const
{
	return m_Data;
}

/**
 * If the array is user-managed, MaxSize establishes the
 * maximum number of elements that can be stored. If the array
 * is dynamically managed by the system, setting the maximum size
 * enlarges its data area to accomodate the required number of elements.
 *
 * \param s	Current maximum size of array (number of elements its
 *			data area can hold)
 *
 * \return bool, true if maximum size successfully changed, else false.
 *
 * \sa Array::SetData Array::SetSize Array::GetElemSize Array::Grow
 */
template <class E> bool Array<E>::SetMaxSize(unsigned int s)
{
	if (s > m_MaxSize)			// enlarge array
		return Grow(s);			// if we can
	return true;
}

template <class E> inline unsigned int	Array<E>::GetMaxSize() const
	{ return m_MaxSize; }

template <class E> inline unsigned int	Array<E>::GetElemSize() const
	{ return sizeof(E); }

/**
 * Set the current array size. If the array is dynamically managed,
 * it will be enlarged to accomodate the new size. If not,
 * the array size cannot be set beyond the current maximum size.
 * When the array size is enlarged, we should call constructors
 * for the new empty elements. We don't do that yet.
 *
 * \param s		Current number of elements contained in array
 *
 * \return bool	True if size successfully changed, else false.
 *
 * \sa Array::SetData Array::Grow Array::SetMaxSize
 *
 * \par Examples:
\code
	Array<RGBi> cols(256);	  // room for 256 colors
	int ncols = cols.GetSize();	// will be zero
	ncols = cols.GetMaxSize();	// will be 256
	cols.SetSize(ncols);		// calls 256 Color4 constructors NOT
\endcode
 *
 */
template <class E> bool inline Array<E>::SetSize(unsigned int s)
{
	assert(s >= 0);
	if (s > m_MaxSize)
		if (!Grow(s))
			return false;
	m_Size = s;
	return true;
}

template <class E> inline unsigned int Array<E>::GetSize() const
	{ return m_Size; }

/**
 *	Sets the i'th element of the array to the given value.
 *	The number of bytes copied is determined by the element size
 *	of the array specified at initialization time.
 *	If the array is not large enough, it is extended to become
 *	1 1/2 times its current size.
 *
 * \param i		Index of new element (0 based)
 * \param val	Value of the new element.
 *
 * \return int index of element added or -1 if out of memory
 *
 * \par Examples:
\code
	Array<RGBi> cols(16);			// room for 16 colors
	cols.SetAt(0, RGBi(1,1,1));		// first color white
	cols.SetAt(15, RGBi(1,0,0));	// last color red
									// makes Colors 1-14, too
	cols.SetAt(17, RGBi(0,1,1));	// causes array growth
\endcode
 */
template <class E> bool Array<E>::SetAt(unsigned int i, E val)
{
	if (i >= m_MaxSize)			// need to extend array?
	   {
		unsigned int n = m_MaxSize;
		n += (n >> 1);			// grow to 1 1/2 times current size
		if (n <= i) n = i + 1;	// unless user wants more
		if (!Grow(n))			// extend failure
			return false;
	   }
	m_Data[i] = val;
	if (i >= m_Size)			// enlarge array size if at end
		m_Size = i + 1;
	return true;
}

/**
 *	Gets the i'th element of the array.
 *
 * \param i	0 based index of element to get. Like C++ arrays,
 *			these arrays do not check the range of the index so your
 *			program will crash if you supply a number less than zero
 *			or greater than the array size as an index.
 *
 * \return element accessed
 */
template <class E> inline E& Array<E>::GetAt(unsigned int i) const
	{ return m_Data[i]; }

template <class E> inline const E& Array<E>::operator[](unsigned int i) const
	{ return m_Data[i]; }

template <class E> inline E& Array<E>::operator[](unsigned int i)
	{ return m_Data[i]; }

/**
 * Compares each element of the array to the input element and
 * returns the index of the first one that matches. Comparison
 * of elements is done using operator== (which must be defined
 * for your element class if you want to use Find).
 *
 * \param
 *	<elem>	value of the element to match
 *
 * \return int
 *	index of matching array element or -1 if not found
 *
 * \sa Array::SetAt
 *
 * \par Examples:
\code
	Array<int> foo;		 // define integer array
	foo.Append(5);		 // first element is 5
	foo.Append(6);		 // second element is 5
	int t = foo.Find(7);  // returns -1
	t = foo.Find(6);	  // returns 1
\endcode
 *
 */
template <class E> int Array<E>::Find(const E& elem) const
{
	const E* p = m_Data;

	for (unsigned int i = 0; i < m_Size; ++i)	// look for matching element
		if (*p++ == elem)
			return i;					// found it
	return -1;
}

/**
 * Appends one element onto the end of the array.
 * If the array is dynamically managed, it is enlarged
 * to accomodate another element if necessary.
 *
 * \param
 *	<v>	 value of the new element
 *
 * \return void*
 *	-> element added (within array) or NULL if out of memory
 *
 * \sa Array::SetAt Array::SetSize Array::RemoveAt
 *
 * \par Examples:
\code
	Array<float>	vals;
	vals.Append(1.0f);	  // first element
	vals.Append(2.0f);	  // second element
	vals.SetAt(5, 6.0f);  // sixth element
	vals.Append(7.0f);	  // seventh element
\endcode
 */
template <class E> int inline Array<E>::Append(const E& v)
{
	int	index = m_Size;

	if (!SetAt(index, v))
		return -1;
	return index;
}

/**
 *	Removes the i'th element of the array. The following
 *	elements are shuffled up to eliminate the unused space.
 *
 * \param	i	Index of element to remove (0 based)
 * \param	n	Number of elements to remove (default 1)
 *
 * \return bool True if element was successfully removed, else false.
 *
 * \sa Array::Append Array::SetAt Array::SetSize
 *
 * \par Examples:
\code
	Array<int16> zot(8); // room for 8 shorts
	zot.SetSize(8);		 // now has 8 zeros
	zot[1] = 1;			 // second element
	zot[2] = 2;			 // third element
	zot.RemoveAt(0);	 // remove first element
	zot.RemoveAt(-1);	 // returns false
\endcode
 */
template <class E> bool Array<E>::RemoveAt(unsigned int i, int n)
{
	E*	elem;
	int	shuffle;

	if ((i < 0) || (i >= m_Size))		// element out of range?
		return false;
	if (n == 0) n = 1;					// default is one element
	shuffle = m_Size - (i + n);			// number to shuffle up
	elem = m_Data + i;
	memcpy(elem, elem + n, sizeof(E) * shuffle);
	m_Size -= n;
	return true;
}

/**
 * Concatenates the contents of the source array into the destination array.
 * The destination array is enlarged if possible. When an object array
 * is appended, the objects are multiply referenced (not duplicated).
 *
 * \param <src>	Source array containing elements to be appended
 *
 * \return index of last element successfully added or -1 on error
 *
 * \sa Array::Append Array::SetAt
 *
 * \par Examples:
\code
	int	zap[3] = { 1, 2, 3 };
	Array<int> zip(3, &zap);	// user managed
	Array<int> zot;				// dynamic
	zot.Append(zip);			// adds 1 2 3
	zot.Append(zip);			// adds 1 2 3 again
\endcode
 */
template <class E> int Array<E>::Append(const Array<E>& src)
{
	int	n = m_Size + src.m_Size;

	if (!Grow(n))
		return -1;
	for (unsigned int i = 0; i < src.m_Size; ++i)
		m_Data[m_Size + i] = src.m_Data[i];
	m_MaxSize = n;
	m_Size += src.m_Size;
	return n - 1;
}

/**
 * Removes the elements in the array but not the array data area.
 * An array is considered empty if it has no elements.
 *
 * \sa Array::SetSize Array::IsEmpty
 */
template <class E> void Array<E>::Empty()
{
	//VTLOG("Empty, size %d\n", m_Size);
	if (m_Size > 0)
		DestructItems(0, m_Size - 1);
	m_Size = 0;
}

/**
 * Determines whether an array has elements or not
 *
 * \return True if array contains no elements, else false.
 *
 * \sa Array::SetSize Array::Empty
 */
template <class E> inline bool Array<E>::IsEmpty() const
	{ return m_Size == 0; }

#endif
