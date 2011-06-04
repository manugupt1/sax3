#include "yuifactory.h"
#include "yui.h"

#include<iostream>

namespace UI{
	yDialog * YUIFactory::createDialog(int width,int height){
		return new yDialog(width,height);
	}

}

