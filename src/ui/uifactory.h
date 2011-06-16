#ifndef _UIF_H_
#define _UIF_H_

#include<iostream>
#include "ui.h"

namespace UI{
	class UIFactory {
		public:
			virtual Dialog * createDialog(int,int) = 0;

			virtual HLayout * createHLayout(HLayout *)=0;
			virtual HLayout * createHLayout(VLayout *)=0;
			virtual HLayout * createHLayout(Dialog *)=0;

			virtual VLayout * createVLayout(HLayout *)=0;
			virtual VLayout * createVLayout(VLayout *)=0;
			virtual VLayout * createVLayout(Dialog *)=0;

			virtual Label * createLabel(Dialog *,std::string) = 0;
			virtual Label * createLabel(HLayout *,std::string) = 0;
			virtual Label * createLabel(VLayout *,std::string) = 0;

			virtual PushButton * createPushButton(Dialog *,std::string)=0;
			virtual PushButton * createPushButton(HLayout *,std::string)=0;
			virtual PushButton * createPushButton(VLayout *,std::string)=0;

			virtual Image * createImage(Dialog *,std::string)=0;
			virtual Image * createImage(HLayout *,std::string)=0;
			virtual Image * createImage(VLayout *,std::string)=0;

			virtual ComboBox * createComboBox(Dialog *,std::string)=0;
			virtual ComboBox * createComboBox(HLayout *,std::string)=0;
			virtual ComboBox * createComboBox(VLayout *,std::string)=0;

	};	
}

#endif
