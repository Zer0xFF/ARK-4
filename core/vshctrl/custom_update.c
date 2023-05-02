/*
 * This file is part of PRO CFW.

 * PRO CFW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * PRO CFW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PRO CFW. If not, see <http://www.gnu.org/licenses/ .
 */

#include <pspsdk.h>
#include <pspsysmem_kernel.h>
#include <pspkernel.h>
#include <psputilsforkernel.h>
#include <pspsysevent.h>
#include <pspiofilemgr.h>
#include <pspctrl.h>
#include <stdio.h>
#include <string.h>
#include "systemctrl.h"
#include "systemctrl_se.h"
#include "globals.h"
#include "macros.h"

extern ARKConfig* ark_config;
extern int psp_model;

char server[64];

void load_server_file(){
	char path[ARK_PATH_SIZE];
	strcpy(path, ark_config->arkpath);
	strcat(path, "UPDATER.TXT");

	memset(server, 0, sizeof(server));
	
	int fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
	sceIoRead(fd, server, sizeof(server)-1);
	sceIoClose(fd);
}

void patch_update_plugin_module(SceModule *mod_)
{

	if (server[0] == 0) return;

	int version;
	int i;
	u32 text_addr, text_size;
	SceModule2 *mod = (SceModule2*)mod_;

	text_addr = mod->text_addr;
	text_size = mod->text_size;
	// ImageVersion
	// If it's lower than the one in updatelist.txt then the FW will update
	version = sctrlHENGetMinorVersion(); // ARK's full version number

	_sw((version >> 16) | 0x3C050000, text_addr + 0x000082A4);
	_sw((version & 0xFFFF) | 0x34A40000, text_addr + 0x000082AC);

	//beql -> beq
	_sw( 0x10400002, text_addr + 0x000082A0);

	// substitute all /UPDATE with /ARK_FW
	/*
	for(i = 0; i < text_size;) {
		u32 addr = text_addr + i;

		if(0 == strncmp((char *)addr, "/UPDATE", 7)) {
			memcpy((char *)addr, "/ARK_FW", 7);
			i += 7;
		} else {
			i++;
		}
	}
	*/
}

void patch_SceUpdateDL_Library(u32 text_addr)
{
	char *p;
	if (server[0] == 0) return;

	if(NULL == sceKernelFindModuleByName("update_plugin_module")) {
		return;
	}

	p = (char*)(text_addr + 0x000032BC);
	_sw(NOP, text_addr + 0x00002044);
	_sw(NOP, text_addr + 0x00002054);
	_sw(NOP, text_addr + 0x00002080);
	_sw(NOP, text_addr + 0x0000209C);

	sprintf(p, "%s/%s?", server, (psp_model==PSP_GO)? "psp-updatelist-go.txt":"psp-updatelist.txt");
}
