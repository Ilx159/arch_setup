/* See LICENSE file for copyright and license details. */

/* Gruvbox colors */
static const char col_bg[]       = "#282828";
static const char col_fg[]       = "#ebdbb2";
static const char col_border[]   = "#fabd2f";

/* Appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=10";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg, col_bg, col_bg },
	[SchemeSel]  = { col_bg, col_border, col_border },
};

/* Tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,       NULL,       NULL,       0,            0,           -1 },
};

/* Layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */
static const int refreshrate    = 60;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* Key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* Helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]       = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]        = { "kitty", NULL };
static const char *browsercmd[]     = { "firefox", NULL };
static const char *filemgrcmd[]     = { "nemo", NULL };
static const char *lockcmd[]        = { "slick", NULL };
static const char *volupcmd[]       = { "pamixer", "-i", "5", NULL };
static const char *voldowncmd[]     = { "pamixer", "-d", "5", NULL };
static const char *volmutecmd[]     = { "pamixer", "-t", NULL };
static const char *brightupcmd[]    = { "brightnessctl", "set", "10%+", NULL };
static const char *brightdowncmd[]  = { "brightnessctl", "set", "10%-", NULL };
static const char *screenshotcmd[]  = { "/bin/sh", "-c", "maim -s | xclip -selection clipboard -t image/png", NULL };

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_q,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_m,      quit,           {0} },
	{ MODKEY,                       XK_e,      spawn,          {.v = filemgrcmd } },
	{ MODKEY,                       XK_v,      togglefloating, {0} },
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, /* floating */
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[2]} }, /* monocle */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY,                       XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_i,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ 0,                            XK_Print,  spawn,          {.v = screenshotcmd } },

	/* Volume / Brightness */
	{ 0, XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
	{ 0, XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
	{ 0, XF86XK_AudioMute,        spawn, {.v = volmutecmd } },
	{ 0, XF86XK_MonBrightnessUp,  spawn, {.v = brightupcmd } },
	{ 0, XF86XK_MonBrightnessDown,spawn, {.v = brightdowncmd } },

	/* Workspaces 1–10 */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
};

/* Button definitions */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
