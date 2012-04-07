
#ifndef _STARTMENU_H
#define _STARTMENU_H

#include "libwiigui/gui.h"

#define MAX_LINES 12

class GuiStartmenu : public GuiWindow
{
	public:
		GuiStartmenu();
	//	~GuiStartmenu();
		void CreateGuiStartmenu(int choice_menu, vector<const char*> name);
		void DestroyGuiStartmenu(int menu);
		void DestroyGuiStartmenu(int from, int to);
		bool CheckMenu();
		void Update(GuiTrigger * t);
		
		int get_menu;
		int get_line;
		
	protected:
		
		int lines[3];
		GuiImageData * menu[3];
		GuiImageData * menu_top[3];
		GuiImageData * menuChoice[3];

		GuiImage * menuImg[3];
		GuiImage * menu_topImg[3];
		GuiImage * menuBtnImgOver[3][MAX_LINES];

		GuiButton * menuBtn[3][MAX_LINES];
		GuiText * menuBtnTxt[3][MAX_LINES];

		GuiButton * backBtn;

		GuiTrigger * trigA;
		GuiTrigger * trigB;
};

#endif
