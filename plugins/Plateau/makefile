#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#
# Modified by REIS0

VST3 ?= true

# --------------------------------------------------------------
# Project name, used for binaries

NAME = Plateau

# --------------------------------------------------------------
# Files to build

FILES_DSP = PlateauPlugin.cpp

FILES_UI = PlateauUI.cpp

# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# VST3 target

ifeq ($(VST3), true)
TARGETS += vst3
endif

all: $(TARGETS)

art: # Converts the artwork to a header file
	py png2rgba.py PlateauArtwork artwork/