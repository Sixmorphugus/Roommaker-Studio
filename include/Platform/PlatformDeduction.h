// Copyright Chris Sixsmith 2017. All Rights Reserved.

#if defined(_MSC_VER)
#define RMS_PLATFORM_WINDOWS // MSC only runs on windows
#define RMS_PLATFORM_STRING std::string("Windows")
#define RMS_COMPILER_VS
#if defined(RMSDLL_Export)
#define RMSDLL __declspec(dllexport)
#else
#define RMSDLL __declspec(dllimport)
#endif
#elif defined(__GNUC__)
#if defined(WIN32)
#define RMS_PLATFORM_WINDOWS
#define RMS_COMPILER_GNUC
#define RMS_PLATFORM_STRING std::string("Windows")
#endif
#if defined(__linux__)
#define RMS_PLATFORM_LINUX
#define RMS_COMPILER_GNUC
#define RMS_PLATFORM_STRING std::string("Linux")
#endif

#if defined(RMSDLL_Export)
#define RMSDLL __attribute__ ((visibility ("default")))
#else
#define RMSDLL
#endif
#else
#error "Please use either GCC or Microsoft Visual C++ (preferred) to compile this."
#endif