#include "yuifactory.h"
#include "yui.h"

#include<iostream>

namespace UI{
	yDialog * YUIFactory::createDialog(int width,int height){
		return new yDialog(width,height);
	}

	yHLayout * YUIFactory::createHLayout(Layout * parent){
		return new yHLayout((yDialog*)parent);
	}

	yHLayout * YUIFactory::createHLayout(Dialog * parent){
		return new yHLayout((yDialog*)parent);
	}

	yLabel * YUIFactory::createLabel(Dialog * parent,std::string text){
		return new yLabel((yDialog*)parent,text);
	}
	yLabel * YUIFactory::createLabel(Layout * parent,std::string text){
		return new yLabel((yLayout*)parent,text);
	}

	yPushButton * YUIFactory::createPushButton(Dialog * parent,std::string text){
		return new yPushButton((yDialog*)parent,text);
	}
	
	yImage * YUIFactory::createImage(Dialog * parent,std::string path){
		return new yImage((yDialog*)parent,path);
	}


}
