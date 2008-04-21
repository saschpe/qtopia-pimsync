#ifndef FUNAMBOL_BASE_H
#define FUNAMBOL_BASE_H

#ifdef WIN32
// nothing for now
#else // WIN32

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BOOL int
#ifndef TRUE
#   define TRUE 1
#endif
#ifndef FALSE
#   define FALSE 0
#endif

#ifdef USE_WCHAR
#    undef WCHAR
#    include <wchar.h>
#    include <wctype.h>
#    define WCHAR wchar_t
#    define WCHAR_PRINTF "s"
#    define TEXT(_x) L##_x
#else
/* map WCHAR and its functions back to standard functions */
#    undef WCHAR
#    define WCHAR char
#    define WCHAR_PRINTF "s"
#    define TEXT(_x) _x
#    define wsprintf sprintf
#    define _wfopen fopen
#    define wprintf printf
#    define fwprintf fprintf
#    define wsprintf sprintf
#    define swprintf snprintf
#    define snwprintf snprintf
#    define wcscpy strcpy
#    define wcsncpy strncpy
#    define wcsncmp strncmp
#    define wcslen strlen
#    define wcstol strtol
#    define wcstoul strtoul
#    define wcsstr strstr
#    define wcscmp strcmp
#    define wcstok strtok
#    define wmemmove memmove
#    define wmemcpy memcpy
#    define wmemcmp memcmp
#    define wmemset memset
#    define wcschr strchr
#    define wcsrchr strrchr
#    define wcscat strcat
#    define wcsncat strncat
#    define _wtoi atoi
#    define wcstod strtod
#    define wcsicmp strcasecmp
#    define _wcsicmp strcasecmp
#    define _stricmp strcasecmp
#endif

#endif // WIN32

#endif // FUNAMBOL_BASE_H

