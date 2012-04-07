
#ifndef _PROMPTS_H_
#define _PROMPTS_H_

#include "main.h"

#include <string>
using namespace std;

string AddApp(const char *AppName);
string checkUpdatePrompt();
string eraseCategory();
string MoveApp(int moveAppNr);
void MoveCategory(int moveCategoryNr, string &Kategorie1, bool &vor, string &Kategorie2);

bool eraseDir(const char *AppName);
bool RemoveApp(const char *AppName);
bool MetaEdit(string dir);

int AppInfo(const char *title, string dir, u8* icon);
int ChoiceAppInfo(vector<homebrew_list> list, int i);
int devicePrompt();
int endPrompt();
int menuPrompt();
int sortPrompt();
int startmenuPrompt(int &CategoryNr, int &AppNr);
int startmenu2Prompt();
int systemPrompt();
int viewPrompt();
int WindowPrompt(const char *title, const char *msg, const char *btn1Label, const char *btn2Label = NULL);

void debug(const char *msg);
void infoPrompt();
void OnScreenCodeboard(char * var, u16 maxlen);
void OnScreenKeyboard(char * var, u16 maxlen, bool br);
void revtext(const char *msg);
void updatePrompt(string rev);

// Themes download
string checkThemesPrompt();
void themeDownload(string themename);

// Fonts download
string checkFontsPrompt();
void fontDownload(string font);

// Languages download
string checkLanguagesPrompt();
void languageDownload(string language);

#endif