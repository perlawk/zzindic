This zigzag.c is derived from zigzag.f.  Which is from TTR of R pacakge.

I use f2c to translate from fortran to C without any problem.
Just rename of machine generated variable to a more human-like name.
The function is call zigzag, the header file zigzag.h is added.
It is not very conformity with some other software's output. Like the 
foxtrader result. But still usable.

The algorithm of the zigzag is not very clear, if someone study it well and sketch a flow chart then, it's very appreciated.

The test.c is just a driver to call the library and test with some market data.  The test.c remove some header and extract the date, high, low.
Since the zigzag function use only the high, low and length of the array.
Other parameters are documented in the source code, just try and error to see 
its meaning.

I tested under my favorite archlinux. Other unix-like system may be work since it uses only the ANSI C functions.
Any feedback are welcome!

Enjoy!
			Perlawk, 2013-06-14
