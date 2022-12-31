#ifndef GFX_LOG_H
#define GFX_LOG_H

#include <cstdio>

#define GFX_LOG(level, fmt, ...) fprintf(stderr,  "[%s, %s, %d][" level "]: " fmt "\n", \
	__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define GFX_LOGI(fmt, ...) GFX_LOG("INFO", fmt, __VA_ARGS__)

#define DEBUG 0
#if DEBUG
#define GFX_LOGD(fmt, ...) GFX_LOG("DEBUG", fmt, __VA_ARGS__)
#else
#define GFX_LOGD(fmt, ...) (void)(fmt)
#endif
#define GFX_LOGW(fmt, ...) GFX_LOG("WARNING", fmt, __VA_ARGS__)

#define GFX_LOGE(fmt, ...) GFX_LOG("EORROR", fmt, __VA_ARGS__)

#define GFX_CHK_RETURN(condition, val, ...) \
	do { \
		if (condition) { \
			__VA_ARGS__; \
			return val; \
		} \
	} while (0)

#define GFX_CHK_RETURN_NOT_VALUE(condition, ...) \
	do { \
		if (condition) { \
			__VA_ARGS__; \
			return; \
		} \
	} while (0)

#endif
