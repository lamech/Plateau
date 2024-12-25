#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = glBars

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	DistrhoPluginGLBars.cpp

FILES_UI  = \
	DistrhoUIGLBars.cpp

# --------------------------------------------------------------
# Do some magic

SKIP_NATIVE_AUDIO_FALLBACK = true
USE_FILE_BROWSER = false
include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Extra flags

LINK_FLAGS += -lpthread

# --------------------------------------------------------------
# Enable all possible plugin types

TARGETS = vst3

all: $(TARGETS)

# --------------------------------------------------------------
