
#include "main.h"
#include "prompts.h"
#include "prompt_startmenu2.h"

/*** Extern variables ***/
extern GuiWindow * mainWindow;

/*** Extern functions ***/
extern void ResumeGui();
extern void HaltGui();

int width;

void CheckAppsMenu(PopUpMenu *Parent)
{
	int choice = -1;
	PopUpMenu *AppsMenu = new PopUpMenu(Parent->GetWidth()+screenwidth/2-width/2-15, Parent->GetTop()+5);

 //   Applications Apps(Settings.AppPath);
	int count = vechomebrew_list_category[0].size();

	if (count > 0)
	{
		for (int i = 0; i < count; i++)
			AppsMenu->AddItem(vechomebrew_list_category[0][i].name.c_str());

		AppsMenu->Finish();

		mainWindow->Append(AppsMenu);

debug("a");

		while (choice == -1)
		{
			usleep(100);
/*
			if (shutdown)
				Sys_Shutdown();
			else if (reset)
				Sys_Reboot();
*/
			choice = AppsMenu->GetChoice();
		}
	}

	delete AppsMenu;

	if (choice >= 0)
	{
		debug(vechomebrew_list_category[0][choice].name.c_str());
	}
}

int CheckStartMenu()
{
	int menu = 0;
/*	GuiImageData *taskbarImgData = Resources::GetImageData(bar_png, bar_png_size);
	GuiImage *taskbarImg = new GuiImage(taskbarImgData);

	width = taskbarImg->GetWidth();
//	height = taskbarImg->GetHeight();

	PopUpMenu *StartMenu = new PopUpMenu(screenwidth/2-width/2-2, 105);
	StartMenu->AddItem(tr("Apps"), cancel_active_png, cancel_active_png_size, true);
	StartMenu->AddItem(tr("Channels"), cancel_active_png, cancel_active_png_size, true);
	StartMenu->AddItem(tr("URL List"), cancel_active_png, cancel_active_png_size, true);
	StartMenu->AddItem(tr("BootMii"), cancel_active_png, cancel_active_png_size);
//	if(Settings.ShowFormatter)
        StartMenu->AddItem(tr("Formatter"), cancel_active_png, cancel_active_png_size);
	StartMenu->AddItem(tr("Settings"), cancel_active_png, cancel_active_png_size);
	StartMenu->AddItem(tr("FTP Server"), cancel_active_png, cancel_active_png_size);
	StartMenu->AddItem(tr("Reload"), cancel_active_png, cancel_active_png_size);
    StartMenu->AddItem(tr("Restart"), cancel_active_png, cancel_active_png_size);
    StartMenu->AddItem(tr("Exit"), cancel_active_png, cancel_active_png_size);

	StartMenu->Finish();

//	int menuWidth = StartMenu->GetWidth();

//	SetState(STATE_DISABLED);
//	MainWindow::Instance()->SetState(STATE_DISABLED);
//	MainWindow::Instance()->Append(StartMenu);

	mainWindow->SetState(STATE_DISABLED);
	mainWindow->Append(StartMenu);
	
	int choice = -1;
	while (choice == -1)
	{
		usleep(100);
*//*
		if (shutdown)
			Sys_Shutdown();
		else if (reset)
			Sys_Reboot();
*/
/*		choice = StartMenu->GetChoice();

	//	if(choice >= FORMATTER && !Settings.ShowFormatter)
    //        choice++;

		if (choice == APPS)
		{
			CheckAppsMenu(StartMenu);
			choice = -1;
		}
		else if (choice == CHANNELS)
		{
		//	CheckChannelsMenu(StartMenu);
			choice = -1;
		}
		else if (choice == URLS)
		{
		//	OpenLinksMenu(StartMenu);
			choice = -1;
		}
	}

	HaltGui();
	delete StartMenu;

//	SetState(STATE_DEFAULT);
//	MainWindow::Instance()->SetState(STATE_DEFAULT);
	mainWindow->SetState(STATE_DEFAULT);
	ResumeGui();
	
//	startBtn->ResetState();

*//*
	if (choice == SETTINGS)
	{
		menu = MENU_SETTINGS;
	}
	else if (choice == FTPSERVER)
	{
		menu = MENU_FTP;
	}
	else if (choice == BOOTMII)
	{
	    int res = WindowPrompt(tr("Do you want to start BootMii?"), 0, tr("Yes"), tr("No"));
	    if(res)
	    {
            ExitApp();
            if(IOS_ReloadIOS(254) < 0)
                ShowError(tr("You do not have BootMii installed!"));
	    }
	}
    else if (choice == FORMATTER)
    {
        choice = -1;

        MainWindow::Instance()->SetState(STATE_DISABLED);
        MainWindow::Instance()->SetDim(true);
        SetTriggerUpdate(false);
        PartitionFormatterGui * PartFormatter = new PartitionFormatterGui();
        PartFormatter->SetAlignment(ALIGN_CENTRE, ALIGN_MIDDLE);
        MainWindow::Instance()->Append(PartFormatter);
        PartFormatter->MainUpdate();
        delete PartFormatter;
        MainWindow::Instance()->SetDim(false);
        MainWindow::Instance()->SetState(STATE_DEFAULT);
        SetTriggerUpdate(true);
	}
	else if (choice == RELOAD)
	{
		if (WindowPrompt(tr("Do you want to remount the devices?"), 0, tr("Yes"), tr("Cancel")))
		{
            StartProgress(tr("Remounting all devices."), AUTO_THROBBER);
            ShowProgress(0, 1, tr("Please wait..."));
			DeviceHandler::Instance()->UnMountAll();
			DeviceHandler::Instance()->MountAll();
			StopProgress();
		}
	}
	else if (choice == RESTART)
	{
		if (WindowPrompt(tr("Do you want to reboot WiiXplorer?"), 0, tr("Yes"), tr("Cancel")))
		{
			RebootApp();
		}
	}
	else if (choice == EXIT)
	{
		if (WindowPrompt(tr("Do you want to exit WiiXplorer?"), 0, tr("Yes"), tr("Cancel")))
		{
			menu = MENU_EXIT;
		}
	}
*/
/*


	HaltGui();
	delete taskbarImg;
	Resources::Remove(taskbarImgData);
	ResumeGui();
*/
	return menu;
}


int startmenu2Prompt()
{
	int menu = CheckStartMenu();
	return menu;	
}