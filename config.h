/* additional include stuff */
#include "layouts.c"
#include "fibonacci.c"
#include "selfrestart.c"
#include <X11/XF86keysym.h>

#define STATUSBAR "dwmblocks"

/* common dwm appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 0;       	/* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int user_bh            = 23;	/* height of bar */
static const unsigned int gappx     = 18;	/* fullgaps */

/* fonts */
static const char *fonts[]  = { "GoMono Nerd Font:style=Medium:size=12", "JoyPixels:pixelsize=15:antialias=true:autohint=true"};

/* colouring */
static const char titlebar_bg[]  = "#112117";
static const char titlebar_fg[]  = "#FBFADA";
static const char wsbar_bg[] 	 = "#040D12";
static const char wsbar_fg[] 	 = "#EEEEEE";
static const char selws_bg[] 	 = "#FBFADA";
static const char selws_fg[] 	 = "#000000";
static const char border_focus[] = "#e9d8a6";
static const char *colors[][3]   = {
	/*               fg         bg         border   */
	[SchemeNorm] = { wsbar_fg, wsbar_bg, "#000000" },
	[SchemeSel]  = { selws_fg, selws_bg,  border_focus  },
	[SchemeTitle]  = { titlebar_fg, titlebar_bg,  "#000000"  },
};

/* systray */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;     /* 0 means no systray */

/* tags */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* mostly used programs */
static const char default_terminal[] = "alacritty";
static const char web_browser[]      = "firefox";
static const char file_manager[]     = "thunar";
static const char music_player[]     = "spotify";
static const char code_editor[]      = "codium";
static const char program_launcher[] = "dmenu_run -fn 'GoMono Nerd Font:style=Bold:size=13' -nf '#eae3d2' -sf '#000000' -sb '#bbe1fa'";
static const char screenlocker[]     = "slock";
static const char take_ss[]	     = "flameshot gui";

/* multimedia commands */
static const char playpause[]   = "playerctl play-pause; pkill -RTMIN+12 dwmblocks";
static const char audiomute[]   = "pactl set-sink-mute @DEFAULT_SINK@ toggle";
static const char lowervolume[] = "pactl set-sink-volume @DEFAULT_SINK@ -5%";
static const char raisevolume[] = "pactl set-sink-volume @DEFAULT_SINK@ +5%";
static const char medianext[]   = "playerctl next"; 
static const char mediaprev[]   = "playerctl previous";

/* keyboard layouts */ 

static const char flip_kbl[] = "setxkbmap -query | grep -q 'us' && setxkbmap -layout tr || setxkbmap -layout us; pkill -RTMIN+13 dwmblocks";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ "Alacritty",  NULL,  NULL,           0,         0,          1,           0,        -1}
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "| []=",      tile },    /* first entry is default */
	{ "| ><>",      NULL },    /* no layout function means floating behavior */
	{ "| M",        monocle },
	{ "| #",        grid },
	{ "| [@]",		  spiral }
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


static Key keys[] = {
	/* modifier                     key                         function        argument */
	{ MODKEY,                       XK_d,                       spawn,          SHCMD(program_launcher) },
	{ MODKEY,                       XK_Return,                  spawn,          SHCMD(default_terminal) },
	{ MODKEY,			XK_F1,                      spawn,          SHCMD(file_manager) },
	{ MODKEY, 			XK_F2,                      spawn,          SHCMD(web_browser) },
	{ 0,                            XF86XK_Tools,               spawn,          SHCMD(music_player) },
	{ 0,                            XK_Print,                   spawn,          SHCMD(take_ss) },
	{ MODKEY,                       XK_F4,                      spawn,          SHCMD(code_editor) },
	{ MODKEY,                       XK_l,                       spawn,          SHCMD(screenlocker) },
	{ MODKEY,                       XK_q,                       killclient,     {0} },
	{ MODKEY|ControlMask,           XK_space,                   layoutscroll,   {.i = +1 } },
	{ MODKEY,                       XK_w,                       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_w,                       tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Tab,                     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Right,                   setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Left,                    setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_space,                   togglefloating, {0} },
	{ 0,                            XF86XK_AudioPlay,           spawn,          SHCMD(playpause)},
	{ 0,                            XF86XK_AudioLowerVolume,    spawn,          SHCMD(lowervolume) },
	{ 0,                            XF86XK_AudioRaiseVolume,    spawn,          SHCMD(raisevolume) },
	{ 0,                            XF86XK_AudioMute,           spawn,          SHCMD(audiomute) },
	{ 0,                            XF86XK_AudioPrev,           spawn,          SHCMD(mediaprev) },
	{ 0,                            XF86XK_AudioNext,           spawn,          SHCMD(medianext) },
	{ MODKEY,                       XK_space,                   spawn,          SHCMD(flip_kbl) },
	{ MODKEY,                       XK_s,                       togglesticky,   {0} },
        { MODKEY|ShiftMask,             XK_q,                       quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,                       self_restart,   {0} },
	TAGKEYS(                        XK_1,                       0)
	TAGKEYS(                        XK_2,                       1)
	TAGKEYS(                        XK_3,                       2)
	TAGKEYS(                        XK_4,                       3)
	TAGKEYS(                        XK_5,                       4)
	TAGKEYS(                        XK_6,                       5)
	TAGKEYS(                        XK_7,                       6)
	};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
     	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} }
};

/* disabled or unused variables but required for compilation */

static char dmenumon[2]       = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run" };

static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
