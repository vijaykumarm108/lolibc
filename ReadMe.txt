This library provides a lo-overhead version of libc, which both expands and restricts functionality under Windows and Linux to a certain subset of Posix library calls. It also performs other serious optimizations, especially under Windows, which reduces the resulting executable size dramatically.

LoLibC replaces all the standard headers. You are not expected to use any other compiler supported header files. We target CLang and Microsoft Visual Studio 2010 currently.

All externally supported libc functions are contained within within the header lolibc.h. Simply include this file in your project to get full support. Do not include any other standard headers. To this end, dummy headers are provided.

Additionally, the library forces UTF-8 support, even though Windows does not have any direct support for it.

The library is intented to be used with the Milan framework. 

