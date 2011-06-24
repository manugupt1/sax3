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

	yComboBox * YUIFactory::createComboBox(Dialog * parent,std::string text){
		return new yComboBox((yDialog*)parent,text);
	}
	yComboBox * YUIFactory::createComboBox(HLayout * parent,std::string text){
		return new yComboBox((yHLayout*)parent,text);
	}
	yComboBox * YUIFactory::createComboBox(VLayout * parent,std::string text){
		return new yComboBox((yVLayout*)parent,text);
	}

	yMultiSelectionBox * YUIFactory::createMultiSelectionBox(Dialog * parent,std::string text){
		return new yMultiSelectionBox((yDialog*)parent,text);
	}
	yMultiSelectionBox * YUIFactory::createMultiSelectionBox(HLayout * parent,std::string text){
		return new yMultiSelectionBox((yHLayout*)parent,text);
	}
	yMultiSelectionBox * YUIFactory::createMultiSelectionBox(VLayout * parent,std::string text){
		return new yMultiSelectionBox((yVLayout*)parent,text);
	}
	
	yTable * YUIFactory::createTable(Dialog *parent,std::string t1,std::string t2,std::string t3){
		return new yTable((yDialog*)parent,t1,t2,t3);
	}
	yTable * YUIFactory::createTable(HLayout *parent,std::string t1,std::string t2,std::string t3){
		return new yTable((yHLayout*)parent,t1,t2,t3);
	}
	yTable * YUIFactory::createTable(VLayout *parent,std::string t1,std::string t2,std::string t3){
		return new yTable((yVLayout*)parent,t1,t2,t3);
	}
}
