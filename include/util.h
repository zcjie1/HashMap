#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#define NEW(type) (type *)malloc(sizeof(type))
#define APPLY(task, ...) task(__VA_ARGS__)

#endif