###########################################################################################
##		Created using Monkey Studio v1.8.3.3
##
##	Author    : You Name <your@email.org>
##	Project   : xMessGui
##	FileName  : xMessGui.pro
##	Date      : 2009-05-31T17:21:20
##	License   : GPL
##	Comment   : Creating using Monkey Studio IDE
##	Home Page   : http://www.mydomain.org
##
##	This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##	WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################

XUPProjectSettings {
	EDITOR	= QMake
	QT_VERSION	= Qt System (4.5.0)
	EXECUTE_DEBUG	= xMessGui_debug
	EXECUTE_RELEASE	= xMessGui
}

TEMPLATE	= app
LANGUAGE	= C++/Qt4
TARGET	= $$quote(xMessGui)
CONFIG	+= debug_and_release
BUILD_PATH	= ./build

CONFIG(debug, debug|release) {
	#Debug
	CONFIG	+= console
	unix:TARGET	= $$join(TARGET,,,_debug)
	else:TARGET	= $$join(TARGET,,,d)
	unix:OBJECTS_DIR	= $${BUILD_PATH}/debug/.obj/unix
	win32:OBJECTS_DIR	= $${BUILD_PATH}/debug/.obj/win32
	mac:OBJECTS_DIR	= $${BUILD_PATH}/debug/.obj/mac
	UI_DIR	= $${BUILD_PATH}/debug/.ui
	MOC_DIR	= $${BUILD_PATH}/debug/.moc
	RCC_DIR	= $${BUILD_PATH}/debug/.rcc
} else {
	#Release
	unix:OBJECTS_DIR	= $${BUILD_PATH}/release/.obj/unix
	win32:OBJECTS_DIR	= $${BUILD_PATH}/release/.obj/win32
	mac:OBJECTS_DIR	= $${BUILD_PATH}/release/.obj/mac
	UI_DIR	= $${BUILD_PATH}/release/.ui
	MOC_DIR	= $${BUILD_PATH}/release/.moc
	RCC_DIR	= $${BUILD_PATH}/release/.rcc
}

SOURCES	= src/main.cpp \
	src/UIMain.cpp \
	src/ProcessQuery.cpp \
	src/MachineModel.cpp \
	src/MachineItem.cpp \
	src/MachineFilterModel.cpp \
	src/Settings.cpp \
	src/UISettings.cpp \
	src/RomModel.cpp \
	src/SearchEdit.cpp \
	src/Utils.cpp \
	src/MachineInfos.cpp \
	src/RomFilterModel.cpp \
	src/UIAbout.cpp

FORMS	= src/UIMain.ui \
	src/UISettings.ui \
	src/UIAbout.ui
HEADERS	= src/UIMain.h \
	src/ProcessQuery.h \
	src/MachineModel.h \
	src/MachineItem.h \
	src/MachineFilterModel.h \
	src/Settings.h \
	src/UISettings.h \
	src/RomModel.h \
	src/SearchEdit.h \
	src/Utils.h \
	src/MachineInfos.h \
	src/RomFilterModel.h \
	src/main.h \
	src/UIAbout.h
QT	= core gui xml
INCLUDEPATH	= . \
	src
RESOURCES	= src/resources/resources.qrc