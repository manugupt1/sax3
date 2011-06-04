#include "yuifactory.h"
#include "yui.h"

#include<iostream>

namespace UI{
	yDialog * YUIFactory::createDialog(int width,int height){
		return new yDialog(width,height);
	}

/*	yHLayout * YUIFactory::createHLayout(yLayout * parent){
		return new yHLayout(parent);
	}
*/
	yHLayout * YUIFactory::createHLayout(Dialog * parent){
		return new yHLayout((yDialog*)parent);
	}


}

