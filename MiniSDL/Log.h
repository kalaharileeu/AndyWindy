
#pragma once

#if defined( ANDROID )
#  include <android/log.h>
#  define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "NDKApp", __VA_ARGS__))
#else
#  include <stdio.h>
#  define LOGI(...) printf("App: "); printf(__VA_ARGS__); printf("\n");
#endif

/*
You have correctly used cout for debug output and cerr for error log. One thing to note
though is that eventually the output of your program might become quite verbose and annoying.
When that happens, it would be a pain to have to go hunting down for cout calls through
your code. You can make you life easier in the future if you replace the raw cout/cerr
calls with a simple wrapping macro that can be later disabled or changed if output becomes too verbose:

#define LOG_COMMENT(msg) do { std::cout << msg << "\n"; } while (0)
#define LOG_ERROR(msg)   do { std::cerr << "ERROR: " << msg << "\n"; } while (0)
*/
