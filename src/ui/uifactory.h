#ifndef _UIF_H_
#define _UIF_H_

#include<iostream>
#include "ui.h"

namespace UI{
	class UIFactory {
		public:
			virtual Dialog * createDialog(int,int) = 0;
	};	
}

#endif
