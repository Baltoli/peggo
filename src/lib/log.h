#ifndef LOG_H
#define LOG_H

/**
 * Logs a message to `stderr`, then exits the program with a nonzero return
 * code.
 *
 * \param message The message to log
 */
void fatal_error(char *message);

#endif
