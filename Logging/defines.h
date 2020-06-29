#pragma once
#ifdef LOGGING_EXPORTS
#define API_LOGGER __declspec(dllexport)
#else
#define API_LOGGER __declspec(dllimport)
#endif

#if defined(_DEBUG)
#define LOGGING_DEBUG
#endif
