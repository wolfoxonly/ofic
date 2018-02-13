
Debian
====================
This directory contains files used to package OFIChaind/OFIChain-qt
for Debian-based Linux systems. If you compile OFIChaind/OFIChain-qt yourself, there are some useful files here.

## OFIChain: URI support ##


OFIChain-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install OFIChain-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your OFIChain-qt binary to `/usr/bin`
and the `../../share/pixmaps/OFIChain128.png` to `/usr/share/pixmaps`

OFIChain-qt.protocol (KDE)

