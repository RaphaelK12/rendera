/*
Copyright (c) 2014 Joe Davisson.

This file is part of Rendera.

Rendera is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Rendera is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Rendera; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
*/

#ifndef RENDERA_H
#define RENDERA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <png.h>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Tooltip.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/fl_ask.H>

#include "common.h"

#define MIN(x, y)          (((x) < (y)) ? (x) : (y))
#define MAX(x, y)          (((x) > (y)) ? (x) : (y))
#define MID(a, b, c)       (MAX(a, MIN(b, c)))
#define SWAP(a, b)         { int c = (a); (a) = (b); (b) = c; }
#define SIGN(a)            (((a) > 0) ? 1 : -1)
#define ABS(a)             (((a) > 0) ? (a) : -(a))

#endif

