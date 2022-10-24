#ifndef __MAIN_H__
#define __MAIN_H__

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <atomic>

#define PATH "C:\\Users\\Gram\\Desktop\\something\\test_8000000.txt"
#define ANSWER "C:\\Users\\Gram\\Desktop\\something\\answer_8000000.txt"
/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

extern "C" int DLL_EXPORT SomeFunction();

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
