/** @file */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 4
#endif

/**
 * Redirect logging to another file.
 *
 * Logs are sent to `stdout` by default, but they can be sent to any open file
 * by using this method.
 *
 * \param f The file to log to.
 */
void log_redirect(FILE *f);

/**
 * Logs a message to `stderr`, then exits the program with a nonzero return
 * code.
 *
 * \param message The message to log
 */
void fatal_error(char *message) __attribute__((noreturn));

/**
 * Log a message to `stderr` at the given level. If the level is greater than
 * \ref DEBUG_LEVEL as defined at compile time, then the message will not be
 * logged.
 *
 * \param level The debug level at which to log this message
 * \param message The message to log
 */
void log_level(unsigned int level, char *message);

/**
 * Log a message to `stderr` at log level 1.
 *
 * \param m The message to log
 */
#define log_err(m) log_level(1, m)

/**
 * Log a message to `stderr` at log level 2.
 *
 * \param m The message to log
 */
#define log_warn(m) log_level(2, m)

/**
 * Log a message to `stderr` at log level 3.
 *
 * \param m The message to log
 */
#define log_info(m) log_level(3, m)

/**
 * Log a message to `stderr` at log level 4.
 *
 * \param m The message to log
 */
#define log_debug(m) log_level(4, m)

#endif
