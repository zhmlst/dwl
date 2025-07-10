/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;
static const int bypass_surface_visibility = 1;
static const int follow                    = 1;
static const unsigned int borderpx         = 1;
static const int smartborders              = 1;
static const int showbar                   = 1;
static const int topbar                    = 1;
static const char *fonts[]                 = {"monospace:size=12"};
static const float rootcolor[]             = COLOR(0x333332ff);
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f};
static const char  kblayout_file[]         = "/tmp/dwl-keymap";
static const char *kblayout_cmd[]          = {"pkill", "-RTMIN+1", "sigbar", NULL};
static char *tags[]                        = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
	[SchemeNorm] = { 0xd1d1d1ff, 0x333332ff, 0x333332ff },
	[SchemeSel]  = { 0x333332ff, 0xd1d1d1ff, 0xd1d1d1ff },
	[SchemeUrg]  = { 0,          0,          0x900000ff },
};

/* logging */
static int log_level = WLR_ERROR;

static const Rule rules[] = {
	/* app_id             title       tags mask     isfloating   monitor */
	{ "firefox",          NULL,       0,            0,           -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "TTT",      bstack },
	{ "[D]",      deck },
	{ "><>",      NULL },
};

/* monitors */
static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	{ "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	.options = "grp:caps_toggle",
    .layout = "us,ru",
};

static const int repeat_rate = 50;
static const int repeat_delay = 250;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 0;
static const int natural_scrolling = 1;
static const int disable_while_typing = 0;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* Scroll sensitivity */
static const double scroll_factor = 0.5f;

/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, KEY,            tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,KEY,toggletag,  {.ui = 1 << TAG} }

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define WMENUFLAGS "-f", "monospace 12", "-N", "333332", "-n", "d1d1d1", "-M", "d1d1d1", "-m", "333332", "-S", "d1d1d1", "-s", "333332"

static const Layout *tilebstack[] = { &layouts[0], &layouts[1], NULL };
static const Layout *floatingtile[] = { &layouts[3], &layouts[0], NULL };

/* commands */
static const char *terminal[] = { "foot", NULL };
static const char *colorpick[] = { LIBDIR "colorpick", NULL };
static const char *browser[]  = { "firefox", NULL };
static const char *blueman[]  = { "blueman-manager", NULL };
static const char *explore[]  = { "nemo", NULL };
static const char *runmenu[]  = { "wmenu-run", WMENUFLAGS, NULL };
static const char *screenshot[] = { LIBDIR "screenshot", NULL };
static const char *clientshot[] = { LIBDIR "screenshot", "-c", NULL };
static const char *regionshot[] = { LIBDIR "screenshot", "-r", NULL };
static const char *connectionmenu[] = { LIBDIR "connectionmenu", WMENUFLAGS, NULL };

#include "keys.h"
static const Key keys[] = {
	/* modifier                  key          function          argument */
	{ MODKEY,                    Key_q,       killclient,       {0} },
	{ MODKEY,                    Key_w,       spawn,            {.v = runmenu} },
	{ MODKEY,                    Key_e,       spawn,            {.v = browser} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_e,       spawn,            {.v = explore} },
	{ MODKEY,                    Key_r,       cyclelayouts,     {.v = tilebstack} },
	{ MODKEY,                    Key_c,       spawn,            {.v = colorpick} },

	{ MODKEY,                    Key_d,       setlayout,        {.v = &layouts[2]} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_f,       setlayout,        {.v = &layouts[3]} },
	{ MODKEY,                    Key_f,       togglefloating,   {0} },
	{ MODKEY,                    Key_b,       spawn,            {.v = blueman} },
	{ MODKEY,                    Key_n,       spawn,            {.v = connectionmenu} },
	{ MODKEY,                    Key_m,       spawn,            {.v = terminal} },
	{ MODKEY,                    Key_space,   togglefullscreen, {0} },

	{ MODKEY,                    Key_h,       setmfact,         {.f = -0.05f} },
	{ MODKEY,                    Key_j,       focusstack,       {.i = +1} },
	{ MODKEY,                    Key_k,       focusstack,       {.i = -1} },
	{ MODKEY,                    Key_l,       setmfact,         {.f = +0.05f} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_h,       incnmaster,       {.i = +1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_j,       movestack,        {.i = +1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_k,       movestack,        {.i = -1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_l,       incnmaster,       {.i = -1} },

	{ 0,                   Key_XF86AudioMute, spawn,            SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle && pkill -RTMIN+2 sigbar") },
	{ 0,            Key_XF86AudioLowerVolume, spawn,            SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%- && pkill -RTMIN+2 sigbar") },
	{ 0,            Key_XF86AudioRaiseVolume, spawn,            SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+ -l 1.0 && pkill -RTMIN+2 sigbar") },
	{ 0,           Key_XF86MonBrightnessDown, spawn,            SHCMD("brightnessctl set 5%-") },
	{ 0,             Key_XF86MonBrightnessUp, spawn,            SHCMD("brightnessctl set 5%+") },
	{ 0,                         Key_Print,   spawninfo,        {.v = screenshot} },
	{ MODKEY,                    Key_Print,   spawninfo,        {.v = clientshot} },
	{ WLR_MODIFIER_SHIFT,        Key_Print,   spawninfo,        {.v = regionshot} },

	{ MODKEY,                    Key_0,       view,             {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_0,       tag,              {.ui = ~0} },
	TAGKEYS(                     Key_1,                         0),
	TAGKEYS(                     Key_2,                         1),
	TAGKEYS(                     Key_3,                         2),
	TAGKEYS(                     Key_4,                         3),
	TAGKEYS(                     Key_5,                         4),
	TAGKEYS(                     Key_6,                         5),
	TAGKEYS(                     Key_7,                         6),
	TAGKEYS(                     Key_8,                         7),
	TAGKEYS(                     Key_9,                         8),
	{ MODKEY,                    Key_comma,   focusmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    Key_period,  focusmon,         {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_comma,   tagmon,           {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_period,  tagmon,           {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_q,       quit,             {0} },

    #define CHVT(KEY,n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT, KEY, chvt, {.ui = (n)} }
	CHVT(Key_F1, 1), CHVT(Key_F2,  2),  CHVT(Key_F3,  3),  CHVT(Key_F4,  4),
	CHVT(Key_F5, 5), CHVT(Key_F6,  6),  CHVT(Key_F7,  7),  CHVT(Key_F8,  8),
	CHVT(Key_F9, 9), CHVT(Key_F10, 10), CHVT(Key_F11, 11), CHVT(Key_F12, 12),
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   cyclelayouts,     {.v = floatingtile} },
	{ ClkTitle,    0,      BTN_RIGHT,  killclient,       {0} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,       {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating,   {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,       {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,             {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,       {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,              {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,        {0} },
};
