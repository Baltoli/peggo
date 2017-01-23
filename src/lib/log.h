#ifndef LOG_H
#define LOG_H

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

/**
 * Logs a message to `stderr`, then exits the program with a nonzero return
 * code.
 *
 * \param message The message to log
 */
void fatal_error(char *message);

/**
 * Log a message to `stderr` at the given level. If the level is less than \ref
 * DEBUG_LEVEL as defined at compile time, then the message will not be logged.
 *
 * \param level The debug level at which to log this message
 * \param message The message to log
 */
void log_level(unsigned int level, char *message);

#endif
