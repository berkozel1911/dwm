/* additional include stuff */
#include "layouts.c"
#include <X11/XF86keysym.h>

#define STATUSBAR "dwmblocks"

/* common dwm appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 0;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 22;	    /* height of bar */
static const unsigned int gappx     = 18;		/* fullgaps */

/* fonts */
static const char *fonts[]          = { "FontAwesome:style=Regular:size=10", "SFMono:style=Bold:size=10"};
static const char dmenufont[]       =   "SFMono:style=Bold:size=10";

/* colouring */
static const char titlebar_bg[]  = "#293241";
static const char titlebar_fg[]  = "#e9d8a6";
static const char wsbar_bg[] 	 = "#001219";
static const char wsbar_fg[] 	 = "#e0fbfc";
static const char selws_bg[] 	 = "#e0fbfc";
static const char selws_fg[] 	 = "#001219";
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
static const char *tags[] = { "www", "dev", "doc", "sys", "chat", "gfx", "misc" };

/* mostly used programs */
static const char default_terminal[] = "alacritty";
static const char web_browser[]      = "brave-browser";
static const char file_manager[]     = "pcmanfm";
static const char *music_player[]    = {default_terminal, "-e", "/usr/bin/cmus"};
static const char *newsboat[]	     = {default_terminal, "-e", "/usr/bin/newsboat"};
static const char *calculator[]	     = {default_terminal, "-e", "qalc"};
static const char *calendar[]	     = {default_terminal, "-e", "calcurse"};
static const char code_editor[]      = "codium";
static const char program_launcher[] = "dmenu_run -fn 'SFMono:style=Bold:size=11' -nf '#e0fbfc' -sf '#001219' -sb '#e0fbfc'";
static const char screenlocker[]     = "slock";
static const char screenshot_tool[]  = "flameshot gui";

/* multimedia commands */
static const char playpause[]   = "playerctl play-pause";
static const char audiomute[]   = "pactl set-sink-mute @DEFAULT_SINK@ toggle";
static const char lowervolume[] = "pactl set-sink-volume @DEFAULT_SINK@ -5%";
static const char raisevolume[] = "pactl set-sink-volume @DEFAULT_SINK@ +5%";
static const char medianext[]   = "playerctl next";
static const char mediaprev[]   = "playerctl previous";

/* keyboard layouts */ 
static const char flip_kbl[] = "setxkbmap -query | grep -q 'us' && setxkbmap tr || setxkbmap us";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "M",        monocle },
	{ "+",        grid },
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
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          SHCMD(program_launcher) },
	{ MODKEY,             		XK_Return, spawn,          SHCMD(default_terminal) },
	{ MODKEY,			XK_F1,	   spawn,	   SHCMD(file_manager) },
	{ MODKEY, 			XK_F2,	   spawn, 	   SHCMD(web_browser) },
	{ MODKEY, 			XF86XK_AudioPlay,          spawn, {.v = music_player} },
	{ MODKEY, 			XK_F3,     spawn, 	   {.v = newsboat} },
	{ MODKEY, 			XK_F4,	   spawn, 	   SHCMD(code_editor) },
	{ 0, 				XF86XK_Calculator,         spawn, {.v = calculator} },
	{ MODKEY,			XK_F5,	   spawn,	   {.v = calendar} },
	{ MODKEY, 			XK_l,	   spawn, 	   SHCMD(screenlocker) },
	{ MODKEY,			XK_q, 	   killclient, 	   {0} },
	{ MODKEY|ControlMask,           XK_space,  layoutscroll,   {.i = +1 } },
	{ MODKEY,			XK_w,	   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_w,	   tagmon,	   {.i = +1 } },
	{ MODKEY,			XK_Tab,	   focusstack,     {.i = +1 } },
	{ MODKEY, 			XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY, 			XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,		XK_space,  togglefloating, {0} },
	{ 0, 				XF86XK_AudioPlay,          spawn, SHCMD(playpause)},
	{ 0,				XF86XK_AudioLowerVolume,   spawn, SHCMD(lowervolume) },
	{ 0,				XF86XK_AudioRaiseVolume,   spawn, SHCMD(raisevolume) },
	{ 0,				XF86XK_AudioMute,   	   spawn, SHCMD(audiomute) },
	{ 0,				XK_Print,  spawn,	   SHCMD(screenshot_tool) },
	{ MODKEY, 			XK_F11,	   spawn,	   SHCMD(mediaprev) },
	{ MODKEY,			XK_F12,    spawn, 	   SHCMD(medianext) },
	{ MODKEY,		XK_space,		 spawn,			 SHCMD(flip_kbl) },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run" };

static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
