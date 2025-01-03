#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#
# Modified by REIS0


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

all: $(TARGETS)

art: # Converts the artwork to a header file
	python png2rgba.py PlateauArtwork artwork

apply: # Copies the VST3 file to the specified directory
	cp ../../bin/Plateau.vst3/Contents/x86_64-win/Plateau.vst3 "C:\Program Files\Common Files\VST3"