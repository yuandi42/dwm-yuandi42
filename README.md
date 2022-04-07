# My build of dwm
Forked in Mar 18, 2022. No patch from upstream has been added since then.

It's a rich-featured (i.e., bloated) build of dynamic window manager with ten
or more patch added, aimed to work with
[dwmblocks-aysnc](https://github.com/UtkarshVerma/dwmblocks-async). Details
below.

## Requirements
In order to build dwm you need the Xlib header files. And this build doesn't
need [libxft-bgra](https://github.com/uditkarode/libxft-bgra) patch,
temporarily.


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
TODO, and check out my [config.def.h](config.def.h) may help.

## See also
1. My [dotfiles](https://github.com/yuandi42/dotfiles)
1. My build of [dmenu](https://github.com/yuandi42/dmenu-yuandi42)
