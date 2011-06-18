#ifndef _YUIF_H_
#define _YUIF_H_

#include "uifactory.h"
#include "yui.h"

#include<iostream>

namespace UI{
	class YUIFactory : public UIFactory {
		public:
			virtual yDialog * createDialog(int width,int height);

			virtual yHLayout * createHLayout(HLayout *parent);
			virtual yHLayout * createHLayout(VLayout *parent);
			virtual yHLayout * createHLayout(Dialog *parent);

			virtual yVLayout * createVLayout(HLayout *);
			virtual yVLayout * createVLayout(VLayout *);
			virtual yVLayout * createVLayout(Dialog *);

			virtual yLabel * createLabel(Dialog *,std::string);
			virtual yLabel * createLabel(HLayout *,std::string);
			virtual yLabel * createLabel(VLayout *,std::string);

			virtual yPushButton * createPushButton(Dialog *,std::string);
			virtual yPushButton * createPushButton(HLayout *,std::string);
			virtual yPushButton * createPushButton(VLayout *,std::string);


			virtual yImage * createImage(Dialog * parent,std::string text);
			virtual yImage * createImage(HLayout * parent,std::string text);
			virtual yImage * createImage(VLayout * parent,std::string text);
			
			virtual yComboBox * createComboBox(Dialog * parent,std::string text);
			virtual yComboBox * createComboBox(HLayout * parent,std::string text);
			virtual yComboBox * createComboBox(VLayout * parent,std::string text);
			
			virtual yMultiSelectionBox * createMultiSelectionBox(Dialog * parent,std::string text);
			virtual yMultiSelectionBox * createMultiSelectionBox(HLayout * parent,std::string text);
			virtual yMultiSelectionBox * createMultiSelectionBox(VLayout * parent,std::string text);
	};	
}

#endif
