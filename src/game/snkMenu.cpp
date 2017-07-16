#include "snkMenu.h"

void snkMenu::Init(int w, int h)
{
   snkState::Construct(w, h);
}

State snkMenu::Update(int key)
{
   State ret = State::MENU;

   /* Change data according to pressed key */
   switch (key)
   {
      case KEY_UP:
      {
         if (mActive != State::START)
         {
            int menu_item = static_cast<int>(mActive) - 2;
            mActive = static_cast<State>(menu_item);
            Refresh();
         }

         break;
      }

      case KEY_DOWN:
      {
         if (mActive != State::EXIT)
         {
            int menu_item = static_cast<int>(mActive) + 2;
            mActive = static_cast<State>(menu_item);
            Refresh();
         }

         break;
      }

      case '\r':
      case '\n':
      {
         ret = mActive;
         break;
      }

      default:
      {
         Refresh();
         break;
      }
   }

   return ret;
}

void snkMenu::Refresh()
{
   ClearBuf();

   std::string text = "S N A K E";
   CreateItem(text.c_str(), text.length(), 0);

   /* Create frame for menu item */
   text = {(char)218, (char)196, (char)196, (char)196, (char)196, (char)196, (char)196, (char)196, (char)191};
   CreateItem(text.c_str(), text.length(), static_cast<int>(mActive) - 1);

   text = {(char)179, ' ', ' ', ' ', ' ', ' ', ' ', ' ', (char)179};
   CreateItem(text.c_str(), text.length(), static_cast<int>(mActive));

   text = {(char)192, (char)196, (char)196, (char)196, (char)196, (char)196, (char)196, (char)196, (char)217};
   CreateItem(text.c_str(), text.length(), static_cast<int>(mActive) + 1);

   /* Create menu items */
   text = "START";
   CreateItem(text.c_str(), text.length(), static_cast<int>(State::START));

   text = "ABOUT";
   CreateItem(text.c_str(), text.length(), static_cast<int>(State::ABOUT));

   text = "EXIT!";
   CreateItem(text.c_str(), text.length(), static_cast<int>(State::EXIT));

   text = "version 1.0";
   CreateItem(text.c_str(), text.length(), mH - 1);
}
