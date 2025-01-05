#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#
# Modified by REIS0
# Modified by lamech

# --------------------------------------------------------------
# Project name, used for binaries

NAME = Plateau

# --------------------------------------------------------------
# Files to build

FILES_DSP = PlateauPlugin.cpp

FILES_UI = PlateauUI.cpp \
widgets/StaticImageBase.cpp \

# --------------------------------------------------------------
# Do some magic

UI_TYPE = cairo
include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# VST3 target

TARGETS += vst3

# --------------------------------------------------------------
# AU target

ifeq ($(MACOS),true)
TARGETS += au
endif

check:
	@echo "Building targets: $(TARGETS)"

all: check $(TARGETS)

art: # Converts the artwork to a header file
	python ../../dpf/utils/png2rgba.py PlateauArtwork artwork

apply: # Copies the VST3 file to the specified directory
	cp ../../bin/Plateau.vst3/Contents/x86_64-win/Plateau.vst3 "C:\Program Files\Common Files\VST3"

install-au: # Install AU
	sudo rm -rf /Library/Audio/Plug-Ins/Components/Plateau.component && sudo cp -R ../../bin/Plateau.component /Library/Audio/Plug-Ins/Components
