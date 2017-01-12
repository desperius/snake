#ifndef _SNK_MENU_H_
#define _SNK_MENU_H_

#include "snkState.h"

class snkMenu : public snkState
{
public:
   snkMenu() = default;
   virtual ~snkMenu() = default;

   void Init(snkField& buf, int w, int h);
   State Update(int key) override;

private:
   void Refresh() override;
   void CreateItem(const char* text, int size, int row);

private:
   State mActive {State::START};
};

#endif /* _SNK_MENU_H_ */
