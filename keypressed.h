#ifndef keypressed_h
#define keypressed_h
#include "enum.h"

class KeyPressed{
    public:
        static Key GetKey();
        static void SetKey(Key key);
				static bool GetHandled();
				static void SetHandled(bool handled); 
    private:
        static Key _key;
				static bool _handled;
};

#endif
