This library provides a lo-overhead version of libc, which both expands and restricts functionality under Windows and Linux to a certain subset of Posix library calls.
It also performs other serious optimizations, especially under Windows, which reduces the resulting executable size dramatically.

LoLibC replaces all the standard headers. You are not expected to use any other compiler supported header files. We target CLang and Microsoft Visual Studio 2010 currently.

All externally supported libc functions are contained within within the header lolibc.h. Simply include this file in your project to get full support.
Do not include any other standard headers. To this end, dummy headers are provided.

Additionally, the library forces UTF-8 support, even though Windows does not have any direct support for it.

The library is intented to be used with the Milan framework. 

***** HOW LIBRARY WORKS *****
This is a standard libc with posix extensions.  It is designed to work in Windows as well as Linux.  It is kept up to the latest specs Cx11, for example.
Currently it compiles under Visual Studio 2010 on Windows and under CLang on Linux platforms.

Under Windows the c library defaults to MSVCRT.DLL, which is not an up-to-date implementation, however, this library does not support all features of the latest standard,
only as many as possible, while keeping the goal of the library intact, which is to produce the smallest, 0-dependency C++ library.

The library includes an additional namespace, called: lolibc.  lolibc contains useful helper classes for managing containers and smart pointers.

These smart pointers and containers enable the derived classes to maintain a global reference count on each managed memory object.  There are essentially several types
of classes (here is the heierarchy:)

lolibc::ref_base			 - base to the ref<T> smart pointer and contains a pointer to object's virtual destructor
lolibc::ref<T>				 - thin wrapper to provide buffer for 
lolibc::object				 - base class, providing a common basis for all objects
	lolibc::reference_type   - reference type objects, like strings, which can pass objects.  These classes contain shared pointers.
	lolibc::value_type<T>    - base value type class.  Integral types are copied.  T must be an integral type.


Another useful feature of lolibc are those OS specific helper DLL functions:

lolibc::dll - Windows DLL helper classes.
lolibc::so - Linux Shared Object helpers

So, instead of defining Windows Headers, lolibc defines dll classes where all the definitions are within.  Therefore lolibc forces
the programmer to NOT use OS specific MACROS which can (and often do) interfere with libc and stl functionality.

