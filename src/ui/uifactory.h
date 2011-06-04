#ifndef _UIF_H_
#define _UIF_H_

#include<iostream>
#include "ui.h"

namespace UI{
	class UIFactory {
		public:
			virtual Dialog * createDialog(int,int) = 0;

			virtual HLayout * createHLayout(Dialog *) = 0;
//			virtual HLayout * createHLayout(Layout *) = 0;
	};	
}

#endif
