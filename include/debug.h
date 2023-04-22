#ifndef DEBUG_H
#define DEBUG_H

/*
 * The log output macros print output to the console. These macros produce
 * compiled log output only if the LOG_LEVEL defined in the makefile (or the
 * make command line) is greater or equal than the level required for that
 * type of log output.
 *
 * The format expected is the same as for printf(). For example:
 * INFO("Info %s.\n", "message")    -> INFO:    Info message.
 * WARN("Warning %s.\n", "message") -> WARNING: Warning message.
 */

#define LOG_LEVEL 20

#define LOG_LEVEL_NONE			0
#define LOG_LEVEL_ERROR			10
#define LOG_LEVEL_NOTICE		20
#define LOG_LEVEL_WARNING		30
#define LOG_LEVEL_INFO			40
#define LOG_LEVEL_VERBOSE		50

/*
 * Define Log Markers corresponding to each log level which will
 * be embedded in the format string and is expected by tf_log() to determine
 * the log level.
 */
#define LOG_MARKER_ERROR		"\xa"	/* 10 */
#define LOG_MARKER_NOTICE		"\x14"	/* 20 */
#define LOG_MARKER_WARNING		"\x1e"	/* 30 */
#define LOG_MARKER_INFO			"\x28"	/* 40 */
#define LOG_MARKER_VERBOSE		"\x32"	/* 50 */

void tf_log(const char *fmt, ...);

#define no_tf_log(fmt, ...)				\
	do {						\
		if (false) {				\
			tf_log(fmt, ##__VA_ARGS__);	\
		}					\
	} while (false)

#if LOG_LEVEL >= LOG_LEVEL_ERROR
# define ERROR(...)	tf_log(LOG_MARKER_ERROR __VA_ARGS__)
#else
# define ERROR(...)	no_tf_log(LOG_MARKER_ERROR __VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_NOTICE
# define NOTICE(...)	tf_log(LOG_MARKER_NOTICE __VA_ARGS__)
#else
# define NOTICE(...)	no_tf_log(LOG_MARKER_NOTICE __VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARNING
# define WARN(...)	tf_log(LOG_MARKER_WARNING __VA_ARGS__)
#else
# define WARN(...)	no_tf_log(LOG_MARKER_WARNING __VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
# define INFO(...)	tf_log(LOG_MARKER_INFO __VA_ARGS__)
#else
# define INFO(...)	no_tf_log(LOG_MARKER_INFO __VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_VERBOSE
# define VERBOSE(...)	tf_log(LOG_MARKER_VERBOSE __VA_ARGS__)
#else
# define VERBOSE(...)	no_tf_log(LOG_MARKER_VERBOSE __VA_ARGS__)
#endif
#endif /* DEBUG_H */
