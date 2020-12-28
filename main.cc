#include "window.h"
#include "SO/thread.h"
#include "SO/system.h"
#include "main_class.h"

__USING_API 

int main(void)
{ 
    System::init(&Main::run); 
} 
