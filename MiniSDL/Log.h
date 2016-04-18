
#pragma once

#if defined( ANDROID )
#  include <android/log.h>
#  define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "NDKApp", __VA_ARGS__))
#else
#  include <stdio.h>
#  define LOGI(...) printf("NDKApp: "); printf(__VA_ARGS__); printf("\n");
#endif
