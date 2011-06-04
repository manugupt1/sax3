#include "yui.h"

namespace UI{

	yDialog::yDialog(int width,int height){
		dialog = YUI::widgetFactory()->createPopupDialog();
		alignment = YUI::widgetFactory()->createMinSize(dialog,width,height);
	}
	
	YAlignment * yDialog::getElement(){
		return alignment;
	}

}
