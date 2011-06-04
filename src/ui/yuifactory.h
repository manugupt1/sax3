#ifndef _YUIF_H_
#define _YUIF_H_

#include "uifactory.h"
#include "yui.h"

#include<iostream>

namespace UI{
	class YUIFactory : public UIFactory {
		public:
			virtual yDialog * createDialog(int width,int height);

	//		virtual yHLayout * createHLayout(yLayout * parent);
			virtual yHLayout * createHLayout(Dialog * parent);

	};	
}

#endif
