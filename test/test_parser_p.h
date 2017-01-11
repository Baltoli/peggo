#ifndef TEST_PARSER_P_H
#define TEST_PARSER_P_H

#include <stdlib.h>

#include "test_parser.h"

void empty_success(void **state);

void terminal_success(void **state);
void terminal_failure(void **state);

void non_terminal_success(void **state);
void non_terminal_failure(void **state);

void sequence_success(void **state);
void sequence_failure(void **state);
void sequence_first(void **state);
void sequence_second(void **state);

void choice_first(void **state);
void choice_second(void **state);
void choice_longer(void **state);
void choice_failure(void **state);

void zero_or_more_zero(void **state);
void zero_or_more_one(void **state);
void zero_or_more_many(void **state);

void one_or_more_one(void **state);
void one_or_more_many(void **state);
void one_or_more_failure(void **state);

#endif
