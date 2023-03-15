#include "common.h"
#define SUBMENU_MAX 13

extern int pwidth;
extern int xyPoint;
extern int xyPoint2;
extern SEConfig cnf;
extern char device_buf[13];
extern char umdvideo_path[256];


int is_pandora = 0;

enum {
	SUBMENU_USB_DEVICE,
	SUBMENU_USB_READONLY,
	SUBMENU_UMD_MODE,
	SUBMENU_UMD_VIDEO,
	SUBMENU_FG_COLORS,
	SUBMENU_BG_COLORS,
	SUBMENU_CONVERT_BATTERY,
	SUBMENU_SWAP_XO_BUTTONS,
	SUBMENU_ACTIVATE_FLASH_WMA,
	SUBMENU_IMPORT_CLASSIC_PLUGINS,
	SUBMENU_DELETE_HIBERNATION,
	SUBMENU_RANDOM_GAME,
	SUBMENU_RETURN_MAIN_MENU,
};

static int submenu_sel = SUBMENU_USB_DEVICE;
const char *subitem_str[SUBMENU_MAX];
int item_fcolor[SUBMENU_MAX];


int submenu_draw(void)
{
	u32 fc,bc;
	const char *msg;
	int submax_menu, subcur_menu;
	const int *pointer;	
	int xPointer;

	// ARK Version
	const char ark_version[24];
	int ver = sctrlHENGetMinorVersion();
 	int major = (ver&0xFF0000)>>16;
	int minor = (ver&0xFF00)>>8;
	int micro = (ver&0xFF);

	#ifdef DEBUG
    if (micro>0) snprintf(ark_version, sizeof(ark_version), " ARK %d.%d.%d DEBUG ", major, minor, micro);
    else snprintf(ark_version, sizeof(ark_version), " ARK %d.%d DEBUG ", major, minor);
    #else
    if (micro>0) snprintf(ark_version, sizeof(ark_version), "    ARK %d.%d.%d    ", major, minor, micro);
    else snprintf(ark_version, sizeof(ark_version), "    ARK %d.%d    ", major, minor); 
	#endif

	// check & setup video mode
	if( blit_setup() < 0) return -1;

	if(pwidth==720) {
		pointer = xyPoint;
	} else {
		pointer = xyPoint2;
	}

	// show menu list
	blit_set_color(0xffffff,0x8000ff00);
	blit_string(pointer[0], pointer[1], g_messages[MSG_PRO_VSH_MENU]);
	blit_string(pointer[0], 56, ark_version);
	fc = 0xffffff;
 
	for(submax_menu=0;submax_menu<SUBMENU_MAX;submax_menu++) {
		msg = g_messages[MSG_USB_DEVICE + submax_menu];
		switch(cnf.vsh_bg_colors) {
						// Red
						case 0: 
							bc = (submax_menu==submenu_sel) ? 0xff8080 : 0x000000ff;
							blit_set_color(fc,bc);
							break;
						// Light Red
						case 1: 
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa00000ff;
							blit_set_color(fc,bc);
							break;
						// Orange
						case 2: 
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0x0000a5ff;
							blit_set_color(fc,bc);
							break;
						// Light Orange
						case 3: 
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa000a5ff;
							blit_set_color(fc,bc);
							break;
						// Yellow
						case 4: 
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0x0000e6e6;
							blit_set_color(fc,bc);
							break;
						// Light Yellow
						case 5: 
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa000e6e6;
							blit_set_color(fc,bc);
							break;
						// Green
						case 6:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0x0000b300;
							blit_set_color(fc,bc);
						// Light Green
						case 7:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa000ff00;
							blit_set_color(fc,bc);
							break;
						// Blue
						case 8:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0x00ff0000;
							blit_set_color(fc,bc);
							break;
						// Light Blue
						case 9:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa0ff0000;
							blit_set_color(fc,bc);
							break;
						// Indigo
						case 10:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0x0082004b;
							blit_set_color(fc,bc);
							break;
						// Light Indigo
						case 11:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa082004b;
							blit_set_color(fc,bc);
							break;
						// Violet
						case 12:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0x00ee82ee;
							blit_set_color(fc,bc);
							break;
						// Light Violet
						case 13:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa0ee82ee;
							blit_set_color(fc,bc);
							break;
						// Pink 
						case 14:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0x00cbc0ff;
							blit_set_color(fc,bc);
							break;
						// Light Pink 
						case 15:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa0cbc0ff;
							blit_set_color(fc,bc);
							break;
						// Purple 
						case 16:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0x00993366;
							blit_set_color(fc,bc);
							break;
						// Light Purple 
						case 17:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa0993366;
							blit_set_color(fc,bc);
							break;
						// Teal 
						case 18:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0x00808000;
							blit_set_color(fc,bc);
							break;
						// Light Teal 
						case 19:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa0808000;
							blit_set_color(fc,bc);
							break;
						// Aqua 
						case 20:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0x00cccc00;
							blit_set_color(fc,bc);
							break;
						// Light Aqua 
						case 21:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa0cccc00;
							blit_set_color(fc,bc);
							break;
						// Grey 
						case 22:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0x00737373;
							blit_set_color(fc,bc);
							break;
						// Light Grey 
						case 23:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa0737373;
							blit_set_color(fc,bc);
							break;
						// Black 
						case 24:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0x00000000;
							blit_set_color(fc,bc);
							break;
						// Light Black 
						case 25:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xa0000000;
							blit_set_color(fc,bc);
							break;
						// White  
						case 26:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xffffffff;
							blit_set_color(fc,bc);
							break;
						// Light White  
						case 27:
							bc = (submax_menu==submenu_sel) ? 0x0000ff : 0xafffffff;
							blit_set_color(fc,bc);
							break;
						default:	
							bc = (submax_menu==submenu_sel) ? 0xff8080 : 0xa00000ff;
							blit_set_color(fc,bc);
					}

					switch(cnf.vsh_fg_colors) {
						// Red
						case 0:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x000000ff;
							blit_set_color(fc,bc);
							break;
						// Light Red
						case 1: 
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa00000ff;
							blit_set_color(fc,bc);
							break;
						// Orange
						case 2: 
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x0000a5ff;
							blit_set_color(fc,bc);
							break;
						// Light Orange
						case 3: 
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa000a5ff;
							blit_set_color(fc,bc);
							break;
						// Yellow
						case 4: 
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x0000e6e6;
							blit_set_color(fc,bc);
							break;
						// Light Yellow
						case 5: 
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa000e6e6;
							blit_set_color(fc,bc);
							break;
						// Green
						case 6:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x0000b300;
							blit_set_color(fc,bc);
						// Light Green
						case 7:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa000ff00;
							blit_set_color(fc,bc);
							break;
						// Blue
						case 8:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x00ff0000;
							blit_set_color(fc,bc);
							break;
						// Light Blue
						case 9:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa0ff0000;
							blit_set_color(fc,bc);
							break;
						// Indigo
						case 10:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x0082004b;
							blit_set_color(fc,bc);
							break;
						// Light Indigo
						case 11:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa082004b;
							blit_set_color(fc,bc);
							break;
						// Violet
						case 12:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x00ee82ee;
							blit_set_color(fc,bc);
							break;
						// Light Violet
						case 13:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa0ee82ee;
							blit_set_color(fc,bc);
							break;
						// Pink 
						case 14:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x00cbc0ff;
							blit_set_color(fc,bc);
							break;
						// Light Pink 
						case 15:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa0cbc0ff;
							blit_set_color(fc,bc);
							break;
						// Purple 
						case 16:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x00993366;
							blit_set_color(fc,bc);
							break;
						// Light Purple 
						case 17:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa0993366;
							blit_set_color(fc,bc);
							break;
						// Teal 
						case 18:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x00808000;
							blit_set_color(fc,bc);
							break;
						// Light Teal 
						case 19:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa0808000;
							blit_set_color(fc,bc);
							break;
						// Aqua 
						case 20:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x00cccc00;
							blit_set_color(fc,bc);
							break;
						// Light Aqua 
						case 21:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa0cccc00;
							blit_set_color(fc,bc);
							break;
						// Grey 
						case 22:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x00737373;
							blit_set_color(fc,bc);
							break;
						// Light Grey 
						case 23:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa0737373;
							blit_set_color(fc,bc);
							break;
						// Black 
						case 24:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0x00000000;
							blit_set_color(fc,bc);
							break;
						// Light Black 
						case 25:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xa0000000;
							blit_set_color(fc,bc);
							break;
						// White  
						case 26:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xffffffff;
							blit_set_color(fc,bc);
							break;
						// Light White  
						case 27:
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xafffffff;
							blit_set_color(fc,bc);
							break;
						default:	
							fc = (submax_menu==submenu_sel) ? 0xffffff : 0xffffffff;
							blit_set_color(fc,bc);
					}

		if(msg) {
				bc = (submax_menu==submenu_sel) ? 0xff8080 : 0x0000ff00;
			switch(submax_menu) {
				case SUBMENU_RETURN_MAIN_MENU:
					xPointer = pointer[2];
				break;
				case SUBMENU_RANDOM_GAME:
				case SUBMENU_DELETE_HIBERNATION:
					xPointer = 168;
					break;
				case SUBMENU_IMPORT_CLASSIC_PLUGINS:
				case SUBMENU_ACTIVATE_FLASH_WMA:
					xPointer = 153;
					break;
				default:
					xPointer=pointer[4];
					break;
			}



			subcur_menu = submax_menu;
			blit_string(xPointer, (pointer[5] + subcur_menu)*8, msg);
			msg = subitem_str[submax_menu];
			if (submax_menu == SUBMENU_CONVERT_BATTERY){
				if (is_pandora){
					if (is_pandora < 0) msg = "Unsupported";
					else msg = "Pandora -> Normal";
				}
				else{
					msg = "Normal -> Pandora";
				}
				blit_string(xPointer+0x80, (pointer[5] + subcur_menu)*8, msg);
			}
			else if(msg) {
				blit_string( (pointer[6] * 8) + 128, (pointer[5] + subcur_menu)*8, msg);
			}

		}

	}

	blit_set_color(0x00ffffff,0x00000000);

	return 0;
}


int submenu_setup(void)
{
	int i;
	const char *bridge;
	const char *umdvideo_disp;

	// preset
	for(i=0;i<SUBMENU_MAX;i++) {
		subitem_str[i] = NULL;
		item_fcolor[i] = RGB(255,255,255);
	}
	


//usb device
	if((cnf.usbdevice>0) && (cnf.usbdevice<5)) {
#ifdef CONFIG_639
		if(psp_fw_version == FW_639)
			scePaf_sprintf(device_buf, "%s %d", g_messages[MSG_FLASH], cnf.usbdevice-1);	
#endif

#ifdef CONFIG_635
		if(psp_fw_version == FW_635)
			scePaf_sprintf(device_buf, "%s %d", g_messages[MSG_FLASH], cnf.usbdevice-1);	
#endif

#ifdef CONFIG_620
		if (psp_fw_version == FW_620)
			scePaf_sprintf_620(device_buf, "%s %d", g_messages[MSG_FLASH], cnf.usbdevice-1);	
#endif

#if defined(CONFIG_660) || defined(CONFIG_661)
		if ((psp_fw_version == FW_660) || (psp_fw_version == FW_661))
			scePaf_sprintf_660(device_buf, "%s %d", g_messages[MSG_FLASH], cnf.usbdevice-1);	
#endif

		bridge = device_buf;
	} else {
		const char *device;

		if(cnf.usbdevice==5)
			device= g_messages[MSG_UMD_DISC];
		else
			device= g_messages[MSG_MEMORY_STICK];

		bridge = device;
	}

	umdvideo_disp = strrchr(umdvideo_path, '/');

	if(umdvideo_disp == NULL) {
		umdvideo_disp = umdvideo_path;
	} else {
		umdvideo_disp++;
	}

	subitem_str[SUBMENU_UMD_VIDEO] = umdvideo_disp;
	subitem_str[SUBMENU_USB_DEVICE] = bridge;

	switch(cnf.umdmode) {
		case MODE_NP9660:
			subitem_str[SUBMENU_UMD_MODE] = g_messages[MSG_NP9660];
			break;
		case MODE_INFERNO:
			subitem_str[SUBMENU_UMD_MODE] = g_messages[MSG_INFERNO];
			break;
		default:
			subitem_str[SUBMENU_UMD_MODE] = g_messages[MSG_INFERNO];
	}

	switch(cnf.usbdevice_rdonly) {
		case 0:
			subitem_str[SUBMENU_USB_READONLY] = g_messages[MSG_DISABLE];
			break;
		case 1:
			subitem_str[SUBMENU_USB_READONLY] = g_messages[MSG_ENABLE];
			break;
		default:
			subitem_str[SUBMENU_USB_READONLY] = g_messages[MSG_ENABLE];
	}

	switch(cnf.swap_xo) {
		case 0:
			subitem_str[SUBMENU_SWAP_XO_BUTTONS] = g_messages[MSG_DISABLE];
			break;
		case 1:
			subitem_str[SUBMENU_SWAP_XO_BUTTONS] = g_messages[MSG_ENABLE];
			break;
		default:
			subitem_str[SUBMENU_SWAP_XO_BUTTONS] = g_messages[MSG_DISABLE];
	}
	
	switch(cnf.vsh_fg_colors) {
		case FG_RED:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_RED];
			break;
		case FG_LITE_RED:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_RED];
			break;
		case FG_ORANGE:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_ORANGE];
			break;
		case FG_LITE_ORANGE:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_ORANGE];
			break;
		case FG_YELLOW:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_YELLOW];
			break;
		case FG_LITE_YELLOW:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_YELLOW];
			break;
		case FG_GREEN:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_GREEN];
			break;
		case FG_LITE_GREEN:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_GREEN];
			break;
		case FG_BLUE:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_BLUE];
			break;
		case FG_LITE_BLUE:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_BLUE];
			break;
		case FG_INDIGO:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_INDIGO];
			break;
		case FG_LITE_INDIGO:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_INDIGO];
			break;
		case FG_VIOLET:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_VIOLET];
			break;
		case FG_LITE_VIOLET:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_VIOLET];
			break;
		case FG_PINK:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_PINK];
			break;
		case FG_LITE_PINK:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_PINK];
			break;
		case FG_PURPLE:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_PURPLE];
			break;
		case FG_LITE_PURPLE:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_PURPLE];
			break;
		case FG_TEAL:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_TEAL];
			break;
		case FG_LITE_TEAL:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_TEAL];
			break;
		case FG_AQUA:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_AQUA];
			break;
		case FG_LITE_AQUA:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_AQUA];
			break;
		case FG_GREY:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_GREY];
			break;
		case FG_LITE_GREY:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_GREY];
			break;
		case FG_BLACK:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_BLACK];
			break;
		case FG_LITE_BLACK:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_BLACK];
			break;
		case FG_WHITE:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_WHITE];
			break;
		case FG_LITE_WHITE:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_WHITE];
			break;
		default:
			subitem_str[SUBMENU_FG_COLORS] = g_messages[MSG_LITE_WHITE];
	}
	switch(cnf.vsh_bg_colors) {
		case BG_RED:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_RED];
			break;
		case BG_LITE_RED:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_RED];
			break;
		case BG_ORANGE:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_ORANGE];
			break;
		case BG_LITE_ORANGE:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_ORANGE];
			break;
		case BG_YELLOW:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_YELLOW];
			break;
		case BG_LITE_YELLOW:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_YELLOW];
			break;
		case BG_GREEN:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_GREEN];
			break;
		case BG_LITE_GREEN:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_GREEN];
			break;
		case BG_BLUE:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_BLUE];
			break;
		case BG_LITE_BLUE:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_BLUE];
			break;
		case BG_INDIGO:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_INDIGO];
			break;
		case BG_LITE_INDIGO:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_INDIGO];
			break;
		case BG_VIOLET:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_VIOLET];
			break;
		case BG_LITE_VIOLET:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_VIOLET];
			break;
		case BG_PINK:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_PINK];
			break;
		case BG_LITE_PINK:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_PINK];
			break;
		case BG_PURPLE:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_PURPLE];
			break;
		case BG_LITE_PURPLE:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_PURPLE];
			break;
		case BG_TEAL:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_TEAL];
			break;
		case BG_LITE_TEAL:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_TEAL];
			break;
		case BG_AQUA:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_AQUA];
			break;
		case BG_LITE_AQUA:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_AQUA];
			break;
		case BG_GREY:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_GREY];
			break;
		case BG_LITE_GREY:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_GREY];
			break;
		case BG_BLACK:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_BLACK];
			break;
		case BG_LITE_BLACK:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_BLACK];
			break;
		case BG_WHITE:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_WHITE];
			break;
		case BG_LITE_WHITE:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_LITE_WHITE];
			break;
		default:
			subitem_str[SUBMENU_BG_COLORS] = g_messages[MSG_RED];
	}

	return 0;
}


int submenu_ctrl(u32 button_on)
{
	int direction;

	if( (button_on & PSP_CTRL_SELECT) ||
		(button_on & PSP_CTRL_HOME)) {
		submenu_sel = SUBMENU_RETURN_MAIN_MENU;
		return 1;
	}

	// change menu select
	direction = 0;

	if(button_on & PSP_CTRL_DOWN) direction++;
	if(button_on & PSP_CTRL_UP) direction--;

	submenu_sel = limit(submenu_sel+direction, 0, SUBMENU_MAX-1);

	// LEFT & RIGHT
	direction = -2;

	if(button_on & PSP_CTRL_LEFT)   direction = -1;
	if(button_on & PSP_CTRL_CROSS) direction = 0;
	if(button_on & PSP_CTRL_CIRCLE) direction = 0;
	if(button_on & PSP_CTRL_RIGHT)  direction = 1;

	if(direction <= -2)
		return 0;

	switch(submenu_sel) {
		case SUBMENU_USB_DEVICE:
			if(direction) change_usb( direction );
			break;
		case SUBMENU_USB_READONLY:
			if (direction) swap_readonly(direction);
			break;
		case SUBMENU_UMD_MODE:
			if(direction) change_umd_mode( direction );
			break;
		case SUBMENU_UMD_VIDEO:
			if(direction) {
			   	change_umd_mount_idx(direction);

				if(umdvideo_idx != 0) {
					char *umdpath;

					umdpath = umdvideolist_get(&g_umdlist, umdvideo_idx-1);

					if(umdpath != NULL) {
						strncpy(umdvideo_path, umdpath, sizeof(umdvideo_path));
						umdvideo_path[sizeof(umdvideo_path)-1] = '\0';
					} else {
						goto none;
					}
				} else {
none:
					strcpy(umdvideo_path, g_messages[MSG_NONE]);
				}
			} else {
				return 6; // Mount UMDVideo ISO flag
			}
			break;
		case SUBMENU_IMPORT_CLASSIC_PLUGINS:
			if(direction==0) {
				return 13; // Import Classic Plugins flag 
			}
			break;
		case SUBMENU_DELETE_HIBERNATION:
			if(direction==0) {
				return 10; // Delete Hibernation flag 
			}
			break;
		case SUBMENU_RANDOM_GAME:
			if(direction==0) {
				return 14; // Random Game flag 
			}
			break;
		case SUBMENU_ACTIVATE_FLASH_WMA:
			if(direction==0) {
				return 11; // Activate Flash/WMA flag 
			}
			break;
		case SUBMENU_SWAP_XO_BUTTONS:
			if(direction) { swap_xo( direction ); } // Swap X/O Buttons flag  
			else if (direction==0 && cnf.swap_xo == 1 ) return 12;
			break;
		case SUBMENU_CONVERT_BATTERY:
			if(direction==0) {
				return 9; // Convert Battery flag
			}
			break;
		case SUBMENU_FG_COLORS:
			// This will be where I will be adding to set the color
			if(direction) change_fg_colors(direction);
			break;
		case SUBMENU_BG_COLORS:
			// This will be where I will be adding to set the color
			if(direction) change_bg_colors(direction);
			break;
		case SUBMENU_RETURN_MAIN_MENU:
			if(direction==0) return -1; // finish
			break;
	}

	return 0; // continue
}
