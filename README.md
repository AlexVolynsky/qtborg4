Synopsis
The qtborg is a simple wrapper for borgbackup tool (borg is a command-line program that does data backups)
This product has the same goals as Borg, but it allows you to make backups more easily using a GUI (graphical user interface).
It's means that qtborg supports a GUI that remembers the options for each backup session. It configures data backup sessions, in tabs.
The qtborg software can to run few (simultaneously) of backup sessions.
For each session, the user needs to create a separate tab (previously assigning a specific name for each tab/session)

Installation
BorgBackup is required.
See the installation manual (https://borgbackup.readthedocs.io/en/stable/installation.html) or,
if you have already downloaded Borg, docs/installation.rst to get started with Borg.

API Reference
At the moment this version is only for Linux - https://github.com/AlexVolynsky/qtborg4
It was successfully tested on Ubuntu/32bit.
It's support the C++>=11, Qt5

Contributors
You only need to download the files (https://github.com/AlexVolynsky/qtborg4) :
    generaltab.cpp
    generaltab.h
    loggingcategories.cpp
    loggingcategories.h
    main.cpp
    mainwindow.cpp
    mainwindow.h
    qtborg4.pro
Add them to a separate project, and build to create an executable with the participation of Qt5 or the older version.

License
Completely free software
