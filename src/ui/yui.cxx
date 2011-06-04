#include "yui.h"

namespace UI{

	yDialog::yDialog(int width,int height){
		dialog = YUI::widgetFactory()->createPopupDialog();
		alignment = YUI::widgetFactory()->createMinSize(dialog,width,height);
	}
	
	YAlignment * yDialog::getElement(){
		return alignment;
	}

	YLayoutBox * yLayout::getElement(){
		return layout;
	}

	yVLayout::yVLayout(yLayout * parent ){
		layout = YUI::widgetFactory()->createVBox(parent->getElement());
	}

	yVLayout::yVLayout(yDialog * parent){
		layout = YUI::widgetFactory()->createVBox(parent->getElement());
	}

	yHLayout::yHLayout(yLayout * parent){
		layout = YUI::widgetFactory()->createHBox(parent->getElement());
	}

	yHLayout::yHLayout(yDialog * parent){
		layout = YUI::widgetFactory()->createVBox(parent->getElement());
	}

}
