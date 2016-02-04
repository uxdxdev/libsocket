
#ifndef socket_EXPORT_H
#define socket_EXPORT_H

#ifdef SOCKET_STATIC_DEFINE
#  define socket_EXPORT
#  define SOCKET_NO_EXPORT
#else
#  ifndef socket_EXPORT
#    ifdef socket_EXPORTS
        /* We are building this library */
#      define socket_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define socket_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef SOCKET_NO_EXPORT
#    define SOCKET_NO_EXPORT 
#  endif
#endif

#ifndef SOCKET_DEPRECATED
#  define SOCKET_DEPRECATED 
#endif

#ifndef SOCKET_DEPRECATED_EXPORT
#  define SOCKET_DEPRECATED_EXPORT socket_EXPORT SOCKET_DEPRECATED
#endif

#ifndef SOCKET_DEPRECATED_NO_EXPORT
#  define SOCKET_DEPRECATED_NO_EXPORT SOCKET_NO_EXPORT SOCKET_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define SOCKET_NO_DEPRECATED
#endif

#endif
