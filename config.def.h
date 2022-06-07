/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka Nerd Font:size=12", };
static const char dmenufont[]       = "monospace:size=12";
static const char col_bg[]          = "#1d2021";
static const char col_fg[]          = "#a89984";
static const char col_g1[]          = "#98971a";
static const char *colors[][3]      = {
	/*               fg      bg      border   */
	[SchemeNorm] = { col_fg, col_bg, col_bg },
	[SchemeSel]  = { col_bg, col_g1, col_g1 },
};
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance        title             tags mask     isfloating   monitor    scratch key */
	{ "stalonetray", "stalonetray", "stalonetray",     0,            1,           -1,        0 },
	{ "wemeetapp"  , "wemeetap",      NULL,            0,            1,           -1,        0 },
	{ "icalingua",    NULL,           NULL,            0,            1,           -1,        0 },
	{ "Sxiv",        "sxiv",        "sxiv",            0,            1,           -1,        0 },
	{ "mpv",          NULL,           NULL,            0,            1,           -1,        0 },
	{ "Pinentry-gtk-2",NULL,          NULL,            0,            1,           -1,        0 },
	{  "tabbed",     "scratchpad",    NULL,            0,            1,           -1,       's'},
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "shiftview.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL }; /* just an example. */

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "scratchpad", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
    { MODKEY,                       XK_equal, scratchpad_show, {0} },
    { MODKEY|ShiftMask,             XK_equal, scratchpad_hide, {0} },
    { MODKEY,                       XK_minus,scratchpad_remove,{0} },
    { MODKEY|ALTKEY,                XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      inplacerotate,  {.i = +1} },
    { MODKEY|ShiftMask,             XK_k,      inplacerotate,  {.i = -1} },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_a,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_s,      togglesticky,   {0} },
    { MODKEY,                       XK_e,      zoom,           {0} },
    { MODKEY,                       XK_g,      togglegaps,     {0} },
    { MODKEY|ShiftMask,             XK_g,      defaultgaps,    {0} },
    { MODKEY|ALTKEY,                XK_g,      incrgaps,       {.i = +1 } },
    { MODKEY|ALTKEY|ShiftMask,      XK_g,      incrgaps,       {.i = -1 } },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[4]} },
    { MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[5]} },
    { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[6]} },
    { MODKEY,                       XK_w,      togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_c,      movecenter,     {0} },
    { MODKEY,                       XK_i,      moveresize,     {.v = "0x 25y 0w 0h" } },
    { MODKEY,                       XK_o,      moveresize,     {.v = "0x -25y 0w 0h" } },
    { MODKEY,                       XK_p,      moveresize,     {.v = "25x 0y 0w 0h" } },
    { MODKEY,                       XK_u,      moveresize,     {.v = "-25x 0y 0w 0h" } },
    { MODKEY|ShiftMask,             XK_i,      moveresize,     {.v = "0x 0y 0w 25h" } },
    { MODKEY|ShiftMask,             XK_o,      moveresize,     {.v = "0x 0y 0w -25h" } },
    { MODKEY|ShiftMask,             XK_p,      moveresize,     {.v = "0x 0y 25w 0h" } },
    { MODKEY|ShiftMask,             XK_u,      moveresize,     {.v = "0x 0y -25w 0h" } },
    { MODKEY|ALTKEY,                XK_o,      moveresizeedge, {.v = "t"} },
    { MODKEY|ALTKEY,                XK_i,      moveresizeedge, {.v = "b"} },
    { MODKEY|ALTKEY,                XK_u,      moveresizeedge, {.v = "l"} },
    { MODKEY|ALTKEY,                XK_p,      moveresizeedge, {.v = "r"} },
    { MODKEY|ALTKEY|ShiftMask,      XK_o,      moveresizeedge, {.v = "T"} },
    { MODKEY|ALTKEY|ShiftMask,      XK_i,      moveresizeedge, {.v = "B"} },
    { MODKEY|ALTKEY|ShiftMask,      XK_u,      moveresizeedge, {.v = "L"} },
    { MODKEY|ALTKEY|ShiftMask,      XK_p,      moveresizeedge, {.v = "R"} },
    { MODKEY,                       XK_semicolon,   shiftview, { .i = -1 } },
    { MODKEY,                       XK_apostrophe,  shiftview, { .i = +1 } },
    { MODKEY|ShiftMask,             XK_semicolon,    shifttag, { .i = -1 } },
    { MODKEY|ShiftMask,             XK_apostrophe,   shifttag, { .i = +1 } },
    { MODKEY,                       XK_bracketleft,  focusmon, {.i = -1 } },
    { MODKEY,                       XK_bracketright, focusmon, {.i = +1 } },
    { MODKEY|ShiftMask,             XK_bracketleft,  tagmon,   {.i = -1 } },
    { MODKEY|ShiftMask,             XK_bracketright, tagmon,   {.i = +1 } },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ControlMask,           XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
    { ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
    { ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
    { ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
    { ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            0,              Button4,        shiftview,      {.i = -1} },
    { ClkTagBar,            0,              Button5,        shiftview,      {.i = +1} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
	/* signum       function        argument  */
	{ 1,            togglescratch,  {.v = scratchpadcmd} },
};
