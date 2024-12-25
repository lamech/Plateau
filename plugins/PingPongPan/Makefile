#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = PingPongPan

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	DistrhoPluginPingPongPan.cpp

FILES_UI  = \
	DistrhoArtworkPingPongPan.cpp \
	DistrhoUIPingPongPan.cpp

# --------------------------------------------------------------
# Do some magic

UI_TYPE = generic
SKIP_NATIVE_AUDIO_FALLBACK = true
USE_FILE_BROWSER = false
include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

TARGETS = vst3

ifeq ($(HAVE_CAIRO_OR_OPENGL)$(HAVE_LIBLO),truetrue)
TARGETS += dssi
endif

all: $(TARGETS)

# --------------------------------------------------------------
