/**
 * Facilities to threadify a function in C language
 *
 * @author Roberto Sosa Cano
 */
#ifndef __THREADIFY_H__
#define __THREADIFY_H__

#include <pthread.h>

#define THREAD_START_0(func) \
{ \
	void *__thread_func(void *args) { \
		func(); \
		pthread_exit(NULL); \
	};\
	pthread_t __thread_id; \
	pthread_create(&__thread_id, NULL, __thread_func, NULL); \
	pthread_detach(__thread_id); \
}
#define THREAD_START_1(func, p1) \
{ \
	struct __thread_args { \
		typeof(p1) _p1; \
	} *__args = (struct __thread_args*)malloc(sizeof *__args); \
	__args->_p1 = p1; \
	void *__thread_func(void *args) { \
		struct __thread_args *__args = (struct __thread_args*)args; \
		typeof(p1) _p1 = __args->_p1; \
		free(args); \
		func(_p1); \
		pthread_exit(NULL); \
	};\
	pthread_t __thread_id; \
	pthread_create(&__thread_id, NULL, __thread_func, __args); \
	pthread_detach(__thread_id); \
}
#define THREAD_START_2(func, p1, p2) \
{ \
	struct __thread_args { \
		typeof(p1) _p1; \
		typeof(p2) _p2; \
	} *__args = (struct __thread_args*)malloc(sizeof *__args); \
	__args->_p1 = p1; \
	__args->_p2 = p2; \
	void *__thread_func(void *args) { \
		struct __thread_args *__args = (struct __thread_args*)args; \
		typeof(p1) _p1 = __args->_p1; \
		typeof(p2) _p2 = __args->_p2; \
		free(args); \
		func(_p1, _p2); \
		pthread_exit(NULL); \
	};\
	pthread_t __thread_id; \
	pthread_create(&__thread_id, NULL, __thread_func, __args); \
	pthread_detach(__thread_id); \
}
#define THREAD_START_3(func, p1, p2, p3) \
{ \
	struct __thread_args { \
		typeof(p1) _p1; \
		typeof(p2) _p2; \
		typeof(p3) _p3; \
	} *__args = (struct __thread_args*)malloc(sizeof *__args); \
	__args->_p1 = p1; \
	__args->_p2 = p2; \
	__args->_p3 = p3; \
	void *__thread_func(void *args) { \
		struct __thread_args *__args = (struct __thread_args*)args; \
		typeof(p1) _p1 = __args->_p1; \
		typeof(p2) _p2 = __args->_p2; \
		typeof(p3) _p3 = __args->_p3; \
		free(args); \
		func(_p1, _p2, _p3); \
		pthread_exit(NULL); \
	};\
	pthread_t __thread_id; \
	pthread_create(&__thread_id, NULL, __thread_func, __args); \
	pthread_detach(__thread_id); \
}

#define THREAD_CONCATENATE(arg1, arg2)  THREAD_CONCATENATE_(arg1, arg2)
#define THREAD_CONCATENATE_(arg1, arg2)  arg1##arg2
#define THREAD_COUNT_PARAMS(...) THREAD_COUNT_PARAMS_(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define THREAD_COUNT_PARAMS_(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define THREAD_START(function, ...) THREAD_CONCATENATE(THREAD_START_, THREAD_COUNT_PARAMS(__VA_ARGS__))(function, __VA_ARGS__)

#endif
