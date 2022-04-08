![dwm icon](dwm.png "icon")
# My build of dwm
Forked in Mar 18, 2022. No patch from upstream has been added since then.

It's a rich-featured (i.e., bloated) build of dynamic window manager with a
dozen or so patches added, aimed to work with
[dwmblocks-aysnc](https://github.com/UtkarshVerma/dwmblocks-async). Details
below.

## Requirements
In order to build dwm you need the Xlib header files. And this build doesn't
need [libxft-bgra](https://github.com/uditkarode/libxft-bgra) patch,
temporarily (Hence no color emoji in the panel).


## Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):
```
make clean install
```

And don't forget to `rm config.h` if needed.

## Running dwm
Add the following line to your .xinitrc to start dwm using startx:
```
exec dwm
```
In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:
```
DISPLAY=foo.bar:1 exec dwm
```
(This will start dwm on display :1 of the host foo.bar.)

## Features
See more in man page (which is still working on, and check out my
[config.def.h](config.def.h) may help).

* [fancybar](https://dwm.suckless.org/patches/fancybar/), [hide vacant
  tags](https://dwm.suckless.org/patches/hide_vacant_tags/),
  [status2d](https://dwm.suckless.org/patches/status2d/) combined together make
  my panel look great (At least I think it is great).
* Floating window always appear in the
  [center](https://dwm.suckless.org/patches/alwayscenter/) (if no direct pos is
  set), and can be moved and resized without mouse due to
  [move-resize](https://dwm.suckless.org/patches/moveresize/) patch.
* Multiple [scratchpad](https://dwm.suckless.org/patches/namedscratchpads/)
  windows can be created and accessible with differnt keybindings or
  [fsignals](https://dwm.suckless.org/patches/fsignal/).
* Clients in stack or master can be
  [moved](https://dwm.suckless.org/patches/inplacerotate/) up or down.
* `autostart.sh` will run when dwm
  [starts](https://dwm.suckless.org/patches/autostart/) (totally useless if you
  don't do WM hopping).
* New layouts and [gaps](https://dwm.suckless.org/patches/vanitygaps/) allowed
  across all layouts.
* [Clickable statusbar](https://dwm.suckless.org/patches/statuscmd/) with
  UtkarshVerma's build of
  [dwmblocks](https://github.com/UtkarshVerma/dwmblocks-async).
* [Sticky client](https://dwm.suckless.org/patches/sticky/): similar to `tag`
  function build in suckless dwm, but with ability to toggle off. And a cute
  [indicator](https://dwm.suckless.org/patches/stickyindicator/) will also be
  shown in the bar.
* [No border](https://dwm.suckless.org/patches/noborder/) will be shown if
  there is only one tiled window visible.

## See also
1. My [dotfiles](https://github.com/yuandi42/dotfiles)
1. My build of [dmenu](https://github.com/yuandi42/dmenu-yuandi42)
