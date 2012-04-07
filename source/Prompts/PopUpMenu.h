/***************************************************************************
 * Copyright (C) 2010
 * by Dimok
 *
 * Copyright (C) 2010
 * by dude
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you
 * must not claim that you wrote the original software. If you use
 * this software in a product, an acknowledgment in the product
 * documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and
 * must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 *
 * PopUpMenu.h
 *
 * for WiiXplorer 2010
 ***************************************************************************/

 #ifndef __POPUPMENU_H_
 #define __POPUPMENU_H_

#include <vector>

#include <gctypes.h>
#include <unistd.h>

#include "libwiigui/gui.h"
#include "Memory/Resources.h"

enum
{
	UP,
	DOWN
};

typedef struct
{
	GuiButton* Button;
	GuiText* ButtonTxt;
	GuiText* ButtonTxtOver;
	GuiImage* ButtonMenuSelect;
	GuiImage* ExpandImg;
	GuiImage* IconImg;
	GuiImageData* Icon;
//	bool SubMenu;
} Items;

class PopUpMenu : public GuiWindow
{
	public:
		PopUpMenu(int x, int y);
		~PopUpMenu();
		int GetChoice();
		int GetWidth() { return width; }
		int GetHeight() { return height; }
		void AddItem(const char *text, const u8 *icon = NULL, u32 iconsize = 0, bool submenu = false);
		void Finish();
        void Update(GuiTrigger * t);
	private:
		void OnClick(GuiElement *sender);
		void OnScrollUp(GuiElement *sender, int pointer, POINT p);
		void OnScrollDown(GuiElement *sender, int pointer, POINT p);
		void Scroll(int direction);

		std::vector<Items> Item;

		int choice;
		int maxTxtWidth;
		int width;
		int height;

		u32 xpos;
		u32 ypos;
		u32 scrollIndex;
		u32 ScrollState;

		bool hasIcons;
		bool hasSubmenus;

		GuiImage * PopUpMenuUpperImg;
		GuiImage * PopUpMenuMiddleImg;
		GuiImage * PopUpMenuLowerImg;
		GuiImage * PopUpMenuScrollUpImg;
		GuiImage * PopUpMenuScrollDownImg;

		GuiImageData * PopUpMenuUpper;
		GuiImageData * PopUpMenuMiddle;
		GuiImageData * PopUpMenuLower;
		GuiImageData * PopUpMenuSelect;
		GuiImageData * PopUpMenuScrollUp;
		GuiImageData * PopUpMenuScrollDown;
		GuiImageData * PopUpMenuExpand;

		GuiSound * PopUpMenuClick;

		GuiButton * NoBtn;
		GuiButton * HomeBtn;
		GuiButton * ScrollUpBtn;
		GuiButton * ScrollDownBtn;

		SimpleGuiTrigger * trigA;
		GuiTrigger * trigAHeld;
		GuiTrigger * trigB;
		GuiTrigger * trigUp;
		GuiTrigger * trigDown;
		GuiTrigger * trigHome;
};

#endif
