#ifndef _YUIF_H_
#define _YUIF_H_

#include "uifactory.h"
#include "yui.h"

#include<iostream>

namespace UI{
	class YUIFactory : public UIFactory {
		public:
			virtual yDialog * createDialog(int width,int height);

			virtual yHLayout * createHLayout(Layout * parent);
			virtual yHLayout * createHLayout(Dialog * parent);

			virtual yLabel * createLabel(Dialog * parent,std::string text);
			virtual yLabel * createLabel(Layout * parent,std::string text);

			virtual yPushButton * createPushButton(Dialog * parent,std::string text);
			virtual yImage * createImage(Dialog * parent,std::string text);
	};	
}

#endif
