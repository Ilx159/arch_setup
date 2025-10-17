/* Gruvbox colors */
static const char col_bg[]       = "#282828";
static const char col_fg[]       = "#ebdbb2";
static const char col_border[]   = "#fabd2f";

/* Appearance */
static const unsigned int borderpx  = 2;
static const unsigned int snap      = 32;
static const int showbar            = 1;
static const int topbar             = 1;
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=10";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg, col_bg, col_bg },
	[SchemeSel]  = { col_bg, col_border, col_border },
};

/* Commands */
static const char *termcmd[]     = { "kitty", NULL };
static const char *browsercmd[]  = { "firefox", NULL };
static const char *filemgrcmd[]  = { "nemo", NULL };
static const char *dmenucmd[]    = { "rofi", "-show", "drun", NULL };
static const char *lockcmd[]     = { "slick", NULL };
static const char *volupcmd[]    = { "pamixer", "-i", "5", NULL };
static const char *voldowncmd[]  = { "pamixer", "-d", "5", NULL };
static const char *volmutecmd[]  = { "pamixer", "-t", NULL };
static const char *brightupcmd[] = { "brightnessctl", "set", "10%+", NULL };
static const char *brightdowncmd[] = { "brightnessctl", "set", "10%-", NULL };
static const char *screenshotcmd[]  = { "maim", "-s", "|", "xclip", "-selection", "clipboard", "-t", "image/png", NULL };

/* Key definitions */
#define MODKEY Mod4Mask

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_q,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_m,      quit,           {0} },
	{ MODKEY,                       XK_e,      spawn,          {.v = filemgrcmd } },
	{ MODKEY,                       XK_v,      togglefloating, {0} },
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_l,      spawn,          {.v = lockcmd } },
	{ 0,                            XK_Print,  spawn,          {.v = screenshotcmd } },

	/* Volume / Brightness */
	{ 0, XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
	{ 0, XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
	{ 0, XF86XK_AudioMute,        spawn, {.v = volmutecmd } },
	{ 0, XF86XK_MonBrightnessUp,  spawn, {.v = brightupcmd } },
	{ 0, XF86XK_MonBrightnessDown,spawn, {.v = brightdowncmd } },

	/* Workspaces 1–10 */
	{ MODKEY,                       XK_1,      view,           {.ui = 1 << 0} },
	{ MODKEY,                       XK_2,      view,           {.ui = 1 << 1} },
	{ MODKEY,                       XK_3,      view,           {.ui = 1 << 2} },
	{ MODKEY,                       XK_4,      view,           {.ui = 1 << 3} },
	{ MODKEY,                       XK_5,      view,           {.ui = 1 << 4} },
	{ MODKEY,                       XK_6,      view,           {.ui = 1 << 5} },
	{ MODKEY,                       XK_7,      view,           {.ui = 1 << 6} },
	{ MODKEY,                       XK_8,      view,           {.ui = 1 << 7} },
	{ MODKEY,                       XK_9,      view,           {.ui = 1 << 8} },
	{ MODKEY,                       XK_0,      view,           {.ui = 1 << 9} },
	{ MODKEY|ShiftMask,             XK_1,      tag,            {.ui = 1 << 0} },
	{ MODKEY|ShiftMask,             XK_2,      tag,            {.ui = 1 << 1} },
	{ MODKEY|ShiftMask,             XK_3,      tag,            {.ui = 1 << 2} },
	{ MODKEY|ShiftMask,             XK_4,      tag,            {.ui = 1 << 3} },
	{ MODKEY|ShiftMask,             XK_5,      tag,            {.ui = 1 << 4} },
	{ MODKEY|ShiftMask,             XK_6,      tag,            {.ui = 1 << 5} },
	{ MODKEY|ShiftMask,             XK_7,      tag,            {.ui = 1 << 6} },
	{ MODKEY|ShiftMask,             XK_8,      tag,            {.ui = 1 << 7} },
	{ MODKEY|ShiftMask,             XK_9,      tag,            {.ui = 1 << 8} },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = 1 << 9} },
};

/* Button definitions */
static const Button buttons[] = {
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

