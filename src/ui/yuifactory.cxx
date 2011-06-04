#include "yuifactory.h"
#include "yui.h"

#include<iostream>

namespace UI{

	yDialog * YUIFactory::createDialog(int width,int height){
		return new yDialog(width,height);
	}


	yVLayout * YUIFactory::createVLayout(HLayout * parent){
		return new yVLayout((yHLayout*)parent);
	}
	yVLayout * YUIFactory::createVLayout(VLayout * parent){
		return new yVLayout((yVLayout*)parent);
	}
	yVLayout * YUIFactory::createVLayout(Dialog * parent){
		return new yVLayout((yDialog*)parent);
	}


	yHLayout * YUIFactory::createHLayout(HLayout * parent){
		return new yHLayout((yHLayout*)parent);
	}
	yHLayout * YUIFactory::createHLayout(VLayout * parent){
		return new yHLayout((yVLayout*)parent);
	}
	yHLayout * YUIFactory::createHLayout(Dialog * parent){
		return new yHLayout((yDialog*)parent);
	}

	yLabel * YUIFactory::createLabel(Dialog * parent,std::string text){
		return new yLabel((yDialog*)parent,text);
	}
	yLabel * YUIFactory::createLabel(HLayout * parent,std::string text){
		return new yLabel((yHLayout*)parent,text);
	}
	yLabel * YUIFactory::createLabel(VLayout * parent,std::string text){
		return new yLabel((yVLayout*)parent,text);
	}


	yPushButton * YUIFactory::createPushButton(Dialog * parent,std::string text){
		return new yPushButton((yDialog*)parent,text);
	}
	yPushButton * YUIFactory::createPushButton(HLayout * parent,std::string text){
		return new yPushButton((yHLayout*)parent,text);
	}
	yPushButton * YUIFactory::createPushButton(VLayout * parent,std::string text){
		return new yPushButton((yVLayout*)parent,text);
	}
	
	yImage * YUIFactory::createImage(Dialog * parent,std::string path){
		return new yImage((yDialog*)parent,path);
	}
	yImage * YUIFactory::createImage(HLayout * parent,std::string path){
		return new yImage((yHLayout*)parent,path);
	}
	yImage * YUIFactory::createImage(VLayout * parent,std::string path){
		return new yImage((yVLayout*)parent,path);
	}

}
