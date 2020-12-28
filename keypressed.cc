#include "keypressed.h"

Key KeyPressed::_key = L_KEY;
bool KeyPressed::_handled = false;

Key KeyPressed::GetKey(){
    return _key;
}
 
void KeyPressed::SetKey(Key key){
    _key = key;
}

bool KeyPressed::GetHandled(){
	return _handled;
}
void KeyPressed::SetHandled(bool handled){
	_handled = handled;
}
