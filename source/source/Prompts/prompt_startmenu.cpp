/****************************************************************************
 * libwiigui
 *
 * Tantric 2009
 *
 * gui_keyboard.cpp
 *
 * GUI class definitions
 ***************************************************************************/

#include "libwiigui/gui.h"
#include "main.h"
#include "Prompts/prompts.h"
#include "Prompts/prompt_startmenu.h"
#include "Tools/copy_app_in_category.h"

/*** Extern variables ***/
extern GuiWindow * mainWindow;

/*** Extern functions ***/
extern void ResumeGui();
extern void HaltGui();

enum
{
	MENU_START = 0,
	MENU_CATEGORIES,
	MENU_APPS
};

/**
 * Constructor for the GuiKeyboard class.
 */
GuiStartmenu::GuiStartmenu()
{
	get_menu = 0;
	
	trigA = new GuiTrigger;
	trigA->SetSimpleTrigger(-1, WPAD_BUTTON_A | WPAD_CLASSIC_BUTTON_A, PAD_BUTTON_A);
	trigB = new GuiTrigger;
	trigB->SetButtonOnlyTrigger(-1, WPAD_BUTTON_B | WPAD_CLASSIC_BUTTON_B, PAD_BUTTON_B);

	backBtn = new GuiButton(0, 0);
	backBtn->SetTrigger(trigB);

	this->SetAlignment(ALIGN_LEFT, ALIGN_BOTTOM);
	this->SetPosition(0, -68);
	this->Append(backBtn);
}

void GuiStartmenu::CreateGuiStartmenu(int choice_menu, vector<const char*> name)
{
	lines[choice_menu] = 0;
	int x = 0;
	
	if(choice_menu > MENU_START)
		x = menuImg[MENU_START]->GetLeft() + menuImg[MENU_START]->GetWidth();
	
	if(choice_menu > MENU_CATEGORIES)
		x += menuImg[MENU_CATEGORIES]->GetLeft();
	
	int number = name.size();
	if(number > MAX_LINES)
		number = MAX_LINES;

	int fontsize = 20;
	int abstand = 12;
	int top_pos = number * (fontsize + abstand);

	menu[choice_menu] = new GuiImageData(Theme.startmenu);
	menu_top[choice_menu] = new GuiImageData(Theme.startmenu_top);
	menuChoice[choice_menu] = new GuiImageData(Theme.menu_selection);

	menuImg[choice_menu] = new GuiImage(menu[choice_menu]);
	menuImg[choice_menu]->SetScaleYpx(top_pos);
	menuImg[choice_menu]->SetPosition(x, - (top_pos /2) - menuImg[choice_menu]->GetHeight() /2);

	menu_topImg[choice_menu] = new GuiImage(menu_top[choice_menu]);
	menu_topImg[choice_menu]->SetPosition(x, - top_pos - menu_topImg[choice_menu]->GetHeight());


	int width = menuImg[choice_menu]->GetWidth();
	int maxwidth = 0;
	
	for(int i = 0; i < number; i++)
	{
		menuBtnImgOver[choice_menu][i] = new GuiImage(menuChoice[choice_menu]);
		
		menuBtnTxt[choice_menu][i] = new GuiText(name[i], fontsize, (GXColor){Theme.apps_1, Theme.apps_2, Theme.apps_3, 100});
		menuBtnTxt[choice_menu][i]->SetAlignment(ALIGN_LEFT, ALIGN_MIDDLE);
		menuBtnTxt[choice_menu][i]->SetPosition(10, abstand/4);
		if(menuBtnTxt[choice_menu][i]->GetTextWidth() +20 > maxwidth)
			maxwidth = menuBtnTxt[choice_menu][i]->GetTextWidth() +20;	
		
		menuBtn[choice_menu][i] = new GuiButton(width, fontsize + abstand);
		menuBtn[choice_menu][i]->SetPosition(x, i * (fontsize + abstand) - top_pos);
		menuBtn[choice_menu][i]->SetLabel(menuBtnTxt[choice_menu][i]);
		menuBtn[choice_menu][i]->SetImageOver(menuBtnImgOver[choice_menu][i]);
		menuBtn[choice_menu][i]->SetTrigger(trigA);
		
		this->Append(menuBtn[choice_menu][i]);
		lines[choice_menu] = i +1;
	}
	
	
	if(maxwidth > width)
	{
//	debug("größer");
		menuImg[choice_menu]->SetScaleXpx(maxwidth);
		menu_topImg[choice_menu]->SetScaleXpx(maxwidth);
		
		for(int i=0; i < number; i++)
		{
			menuBtnImgOver[choice_menu][i]->SetScaleXpx(maxwidth);
			menuBtn[choice_menu][i]->SetSize(maxwidth, fontsize + abstand);
		}
	}

	this->Append(menuImg[choice_menu]);
	this->Append(menu_topImg[choice_menu]);
}

void GuiStartmenu::DestroyGuiStartmenu(int menu)
{
	DestroyGuiStartmenu(menu, menu);
}

void GuiStartmenu::DestroyGuiStartmenu(int from, int to)
{
//	HaltGui();
	for(int x = from; x >= to; x--)
	{
		if(menu[x])
			delete menu[x];
		if(menu_top[x])
			delete menu_top[x];
		if(menuChoice[x])
			delete menuChoice[x];
		if(menuImg[x])
		{
			this->Remove(menuImg[x]);
			delete menuImg[x];
		}
		if(menu_topImg[x])
		{
			this->Remove(menu_topImg[x]);
			delete menu_topImg[x];
		}
			
		for(int i = 0; i < lines[x]; i++)
		{
			if(menuBtn[x][i])
			{
				this->Remove(menuBtn[x][i]);
				delete menuBtn[x][i];
			}
			if(menuBtnTxt[x][i])
				delete menuBtnTxt[x][i];
			if(menuBtnImgOver[x][i])
				delete menuBtnImgOver[x][i];
		}
		
		if(x == MENU_START)
		{
			delete backBtn;
			delete trigA;
			delete trigB;
		}
	}
//	ResumeGui();
}


void GuiStartmenu::Update(GuiTrigger * t)
{
	if(_elements.size() == 0 /*|| (state == STATE_DISABLED && parentElement) || (state == STATE_DISABLED2 && parentElement)*/)
		return;

	for (u8 i = 0; i < _elements.size(); i++)
	{
		try	{ _elements.at(i)->Update(t); }
		catch (const std::exception& e) { }
	}

	if(backBtn->GetState() == STATE_CLICKED)
		get_menu = -1;
}

bool GuiStartmenu::CheckMenu()
{
	for(int x=0; x < 3; x++)
	{
		for(int i=0; i < lines[x]; i++)
		{
			if(menuBtn[x][i] && menuBtn[x][i]->GetState() == STATE_CLICKED)
			{
					if(WPAD_ButtonsHeld(0) & WPAD_BUTTON_A)
					{
						debug("halten");
					}
					else if(WPAD_ButtonsDown(0) & WPAD_BUTTON_A)
					{
						debug("gedrückt");
					}
				menuBtn[x][i]->ResetState();
				
				get_menu = x;
				get_line = i;
				return true;
			}
		}
	}
	return false;
}

int startmenuPrompt(int &CategoryNr, int &AppNr)
{
	int choice = 0;
	int menus = -1;
	
	vector<string>	name;
//	vector<const char*>	name;
	name.push_back("kategorien");
	name.push_back("ansicht");
	name.push_back("einstellungen");
	name.push_back("beenden");
	
	vector<const char*>	temp;
	for(int x = 0; x < (signed)name.size(); x++)
		temp.push_back(name[x].c_str());

	GuiStartmenu codeboard;
	codeboard.CreateGuiStartmenu(MENU_START, temp);
	menus = MENU_START;
//debug("a");	
	
	HaltGui();
	mainWindow->SetState(STATE_DISABLED2);
	mainWindow->Append(&codeboard);
	mainWindow->ChangeFocus(&codeboard);
	ResumeGui();
//debug("b");	
	while(codeboard.get_menu != -1 && choice == 0)
	{
		usleep(100);
		
		if(codeboard.CheckMenu())
		{
			switch (codeboard.get_menu)
			{
				// Startmenü
				case MENU_START:
				{
					if(codeboard.get_line == 0)
					{
						if(menus == MENU_CATEGORIES)
							codeboard.DestroyGuiStartmenu(MENU_CATEGORIES);
							
						temp.clear();
						for(int x = 0; x < (signed)AvailableCategory.categories.size(); x++)
							temp.push_back(AvailableCategory.categories[x].c_str());
							
						codeboard.CreateGuiStartmenu(MENU_CATEGORIES, temp);
						menus = MENU_CATEGORIES;
					}
					else
						choice = - codeboard.get_line;
						
					break;
				}
				
				// Kategoriemenü
				case MENU_CATEGORIES:
				{
					for(int i = 0; i < (signed)AvailableCategory.categories.size(); i++)
					{
						if(codeboard.get_line == i)
						{
							
							if(menus == MENU_APPS)
								codeboard.DestroyGuiStartmenu(MENU_APPS);
								
							if(i != 0)
								copy_app_in_category(i);
								
							temp.clear();
							for(int x = 0; x < (signed)vechomebrew_list_category[i].size(); x++)
								temp.push_back(vechomebrew_list_category[i][x].name.c_str());
							
							codeboard.CreateGuiStartmenu(MENU_APPS, temp);
							menus = MENU_APPS;
							CategoryNr = i;
							break;
						}
					}	
					break;
				}
					
				// Appsmenü
				case MENU_APPS:
				{
					AppNr = codeboard.get_line;
		//			choice = 1;
					
		
		
				//	debug("MENU_APPS");
					break;
				}
			}
		}
		
		if(WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
			choice = -2;
	}
	
	HaltGui();
	if(menus == MENU_APPS)
		codeboard.DestroyGuiStartmenu(MENU_APPS, MENU_START);
	
	else if(menus == MENU_CATEGORIES)
		codeboard.DestroyGuiStartmenu(MENU_CATEGORIES, MENU_START);
	
	else if(menus == MENU_START)
		codeboard.DestroyGuiStartmenu(MENU_START);
	
	mainWindow->Remove(&codeboard);
	mainWindow->SetState(STATE_DEFAULT);
	ResumeGui();
	
	return choice;
}

