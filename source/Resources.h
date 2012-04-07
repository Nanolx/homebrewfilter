/***************************************************************************
 * Copyright (C) 2009
 * by Dimok & r-win
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
 * Resources.h
 *
 * for WiiXplorer 2009
 ***************************************************************************/

#ifndef _RESOURCES_H
#define _RESOURCES_H

#define UNUSED	__attribute__((unused))

#include <gccore.h>

#include "libwiigui/gui.h"
#include "filelist.h"

#include <map>

class Resources
{
	public:
		static Resources *Instance();
		static void DestroyInstance();
        //! Only images/sounds that are compiled into the app go here
		static GuiImageData *GetImageData(const u8 *img, u32 imgSize);
		static GuiSound *GetSound(const u8 *snd, s32 sndSize);

		static void Remove(GuiImageData *img);
		static void Remove(GuiSound *snd);
	private:
		GuiImageData *InternalGetImageData(const u8 *img, u32 imgSize);
		GuiSound *InternalGetSound(const u8 *snd, s32 sndSize);
		void InternalRemoveImageData(GuiImageData *img);
		void InternalRemoveSound(GuiSound *snd);

		~Resources();

		static Resources *instance;

		std::map<const u8 *, GuiImageData *> images;
		std::map<const u8 *, GuiSound *> sounds;

		std::map<GuiImageData *, int> imageCount;
		std::map<GuiSound *, int> soundCount;
};

#endif //_RESOURCES_H
