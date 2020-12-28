#ifndef system_h
#define system_h
 
#include <stdio.h>
#include "traits.h"
#include "debug.h"
#include "thread.h"

__BEGIN_API
 
class System
{
public:
    static void init(void (*main)(void *));
};

__END_API

#endif
