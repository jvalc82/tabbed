/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]        = "monospace:size=12";
static const char* normbgcolor  = "#000000";
static const char* normfgcolor  = "#3fffa3";
static const char* selbgcolor   = "#000000";
static const char* selfgcolor   = "#ff3f9b";
static const char* urgbgcolor   = "#ff3f9b";
static const char* urgfgcolor   = "#000000";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "...";
static const int  tabwidth      = 200;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;
static const Bool focusnewtab   = True;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = 1;
static Bool npisrelative  = True;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

#define MODKEY ControlMask
#define L_ALTK Mod1Mask
#define R_ALTK Mod3Mask

static Key keys[] = {
	/* modifier             key        function     argument */
	{ MODKEY|ShiftMask,     XK_Return, focusonce,   { .i = focusnewtab } },
	{ MODKEY|ShiftMask,     XK_Return, spawn,       { 0 } },

	{ MODKEY|ShiftMask,     XK_l,      rotate,      { .i = +1 } },
	{ MODKEY|ShiftMask,     XK_h,      rotate,      { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_j,      movetab,     { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_k,      movetab,     { .i = +1 } },
	{ MODKEY,               XK_Tab,    rotate,      { .i = 0 } },

	{ MODKEY,               XK_grave,  spawn,       SETPROP("_TABBED_SELECT_TAB") },
	{ L_ALTK,               XK_1,      move,        { .i = 0 } },
	{ R_ALTK,               XK_1,      move,        { .i = 0 } },
	{ L_ALTK,               XK_2,      move,        { .i = 1 } },
	{ R_ALTK,               XK_2,      move,        { .i = 1 } },
	{ L_ALTK,               XK_3,      move,        { .i = 2 } },
	{ R_ALTK,               XK_3,      move,        { .i = 2 } },
	{ L_ALTK,               XK_4,      move,        { .i = 3 } },
	{ R_ALTK,               XK_4,      move,        { .i = 3 } },
	{ L_ALTK,               XK_5,      move,        { .i = 4 } },
	{ R_ALTK,               XK_5,      move,        { .i = 4 } },
	{ L_ALTK,               XK_6,      move,        { .i = 5 } },
	{ R_ALTK,               XK_6,      move,        { .i = 5 } },
	{ L_ALTK,               XK_7,      move,        { .i = 6 } },
	{ R_ALTK,               XK_7,      move,        { .i = 6 } },
	{ L_ALTK,               XK_8,      move,        { .i = 7 } },
	{ R_ALTK,               XK_8,      move,        { .i = 7 } },
	{ L_ALTK,               XK_9,      move,        { .i = 8 } },
	{ R_ALTK,               XK_9,      move,        { .i = 8 } },
	{ L_ALTK,               XK_0,      move,        { .i = 9 } },
	{ R_ALTK,               XK_0,      move,        { .i = 9 } },

	{ MODKEY,               XK_q,      killclient,  { 0 } },

	{ MODKEY,               XK_u,      focusurgent, { 0 } },
	{ MODKEY|ShiftMask,     XK_u,      toggle,      { .v = (void*) &urgentswitch } },

	{ 0,                    XK_F11,    fullscreen,  { 0 } },
};
