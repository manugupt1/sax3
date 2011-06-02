#ifndef _UI_H_
#define _UI_H_

#include<string>

namespace UI{

  class HLayout;
  class VLayout;
  class Dialog;
  class PushButton;
  class Label;
  class VSpacing;
  class HSpacing;
  class Image;

  class Dialog{
  public:
    Dialog();
    virtual Dialog * createDialog(int, int) = 0;
    virtual void Event() = 0;
  };

  class VSpacing{
  public:
    virtual void createVSpacing(Dialog *,int dim) = 0;
    virtual void createVSpacing(VLayout *,int dim) = 0;
    virtual void createVSpacing(HLayout *,int dim) = 0;
  };

  class HSpacing{
  public:
    virtual void createHSpacing(Dialog *,int dim) = 0;
    virtual void createHSpacing(VLayout *,int dim) = 0;
    virtual void createHSpacing(HLayout *,int dim) = 0;

  };

  class VLayout{
  public:
    virtual void createVLayout(Dialog *) = 0;
    virtual void createVLayout(VLayout *) = 0;
    virtual void createVLayout(HLayout *) = 0;
  };

  class HLayout{
  public:
    virtual void createHLayout(Dialog *) = 0;
    virtual void createHLayout(VLayout *) = 0;
    virtual void createHLayout(HLayout *) = 0;
  };
  
  class Label{
  public:
    virtual void createLabel(VLayout * parent,string text)=0;
    virtual void createLabel(HLayout * parent,string text)=0;
  };

  class PushButton{
  public:
    virtual void createButton(VLayout * parent,string text)=0;
    virtual void createButton(HLayout * parent,string text)=0;
  };

  class Image{
  public:
    virtual void createImage(VLayout * parent,string path)=0;
    virtual void createImage(HLayout * parent,string path)=0;
    virtual void size(int width,int height);
  };

}

#endif
