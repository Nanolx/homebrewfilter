
#include <unistd.h>

#include "libwiigui/gui.h"
#include "main.h"

/*** Extern variables ***/
extern GuiWindow * mainWindow;

/*** Extern functions ***/
extern void ResumeGui();
extern void HaltGui();

/****************************************************************************
 * WindowPrompt
 *
 * Displays a prompt window to user, with information, an error message, or
 * presenting a user with a choice
 ***************************************************************************/
int viewPrompt()
{
	bool stop = false;
	int device = -1;

	GuiWindow promptWindow(144,64);
	promptWindow.SetAlignment(ALIGN_CENTRE, ALIGN_TOP);
	promptWindow.SetPosition(0, 280);
	if(Options.apps == 5)
		promptWindow.SetPosition(0, 307);
	GuiTrigger trigA;
	GuiTrigger trigB;
	trigA.SetSimpleTrigger(-1, WPAD_BUTTON_A | WPAD_CLASSIC_BUTTON_A, PAD_BUTTON_A);
	trigB.SetButtonOnlyTrigger(-1, WPAD_BUTTON_B | WPAD_CLASSIC_BUTTON_B, PAD_BUTTON_B);

	// Hintergrund
	GuiImageData dialogBox(Theme.choice);
	GuiImage dialogBoxImg(&dialogBox);

	// button data
	GuiImageData normal_BtnImgData(Theme.normal_inactive);
	GuiImageData normal_BtnImgDataOver(Theme.normal_active);
	GuiImageData grid_BtnImgData(Theme.grid_inactive);
	GuiImageData grid_BtnImgDataOver(Theme.grid_active);
	GuiImageData pc_BtnImgData(Theme.pc_inactive);
	GuiImageData pc_BtnImgDataOver(Theme.pc_active);

	// button
	GuiImage normal_BtnImg(&normal_BtnImgData);
	GuiImage grid_BtnImg(&grid_BtnImgData);
	GuiImage pc_BtnImg(&pc_BtnImgData);

	// button over
	GuiImage normal_BtnImgOver(&normal_BtnImgDataOver);
	GuiImage grid_BtnImgOver(&grid_BtnImgDataOver);
	GuiImage pc_BtnImgOver(&pc_BtnImgDataOver);
	
	GuiButton normal_Btn(normal_BtnImgData.GetWidth(), normal_BtnImgData.GetHeight());
	normal_Btn.SetAlignment(ALIGN_LEFT, ALIGN_MIDDLE);
	normal_Btn.SetPosition(8, 0);
	normal_Btn.SetImage(&normal_BtnImg);
	normal_Btn.SetImageOver(&normal_BtnImgOver);
	normal_Btn.SetTrigger(&trigA);
	
	GuiButton grid_Btn(grid_BtnImgData.GetWidth(), grid_BtnImgData.GetHeight());
	grid_Btn.SetAlignment(ALIGN_CENTRE, ALIGN_MIDDLE);
	grid_Btn.SetPosition(0, 0);
	grid_Btn.SetImage(&grid_BtnImg);
	grid_Btn.SetImageOver(&grid_BtnImgOver);
	grid_Btn.SetTrigger(&trigA);
	
	GuiButton pc_Btn(pc_BtnImgData.GetWidth(), pc_BtnImgData.GetHeight());
	pc_Btn.SetAlignment(ALIGN_RIGHT, ALIGN_MIDDLE);
	pc_Btn.SetPosition(-8, 0);
	pc_Btn.SetImage(&pc_BtnImg);
	pc_Btn.SetImageOver(&pc_BtnImgOver);
	pc_Btn.SetTrigger(&trigA);

	GuiButton back(0, 0);
	back.SetTrigger(&trigB);

	promptWindow.Append(&dialogBoxImg);
	promptWindow.Append(&normal_Btn);
	promptWindow.Append(&grid_Btn);
	promptWindow.Append(&pc_Btn);
	promptWindow.Append(&back);

	HaltGui();
	mainWindow->SetState(STATE_DISABLED2);
	mainWindow->Append(&promptWindow);
	mainWindow->ChangeFocus(&promptWindow);
	ResumeGui();

	while(!stop)
	{
		usleep(100);

		if(normal_Btn.GetState() == STATE_CLICKED)
		{
			device = 0;
			stop = true;
		}
		
		if(grid_Btn.GetState() == STATE_CLICKED)
		{
			device = 1;
			stop = true;
		}
		
		if(pc_Btn.GetState() == STATE_CLICKED)
		{
			device = 2;
			stop = true;
		}
		
		if(back.GetState() == STATE_CLICKED)
			stop = true;
	}

	HaltGui();
	mainWindow->Remove(&promptWindow);
	mainWindow->SetState(STATE_DEFAULT);
	ResumeGui();
	
	return device;
}

