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

#include "rendera.h"

extern Dialog *dialog;

static void close_callback(Fl_Widget *widget, void *)
{
  if((Fl::event() == FL_KEYDOWN || Fl::event() == FL_SHORTCUT)
    && Fl::event_key() == FL_Escape)
    return;
  else
    widget->hide();
}

static void quit()
{
  fl_message_title("Quit");
  if(fl_choice("Are You Sure?", "No", "Yes", NULL) == 1)
    exit(0);
}

Fl_Menu_Item menuitems[] =
{
  { "&File", 0, 0, 0, FL_SUBMENU },
    { "&New...", 0, (Fl_Callback *)show_new_image, 0 },
    { "&Load...", 0, (Fl_Callback *)load, 0 },
    { "&Save...", 0, (Fl_Callback *)save, 0, FL_MENU_DIVIDER },
    { "&Quit", 0, (Fl_Callback *)quit, 0 },
    { 0 },
  { "&Edit", 0, 0, 0, FL_SUBMENU },
    { "&Undo", 0, 0, 0 },
    { "&Redo", 0, 0, 0, FL_MENU_DIVIDER },
    { "Clear To Black", 0, 0, 0 },
    { "Clear To White", 0, 0, 0 },
    { "Clear To Color", 0, 0, 0, FL_MENU_DIVIDER },
    { "&Scale Image...", 0, 0, 0 },
    { 0 },
  { "&Palette", 0, 0, 0, FL_SUBMENU },
    { "&Create From Image...", 0, (Fl_Callback *)show_create_palette, 0, FL_MENU_DIVIDER },
    { "&Load...", 0, 0, 0 },
    { "&Save...", 0, 0, 0 },
    { 0 },
  { "&Effects", 0, 0, 0, FL_SUBMENU },
    { "Normalize", 0, 0, 0 },
    { "Equalize", 0, 0, 0 },
    { "Equalize Saturation", 0, 0, 0 },
    { "Saturate", 0, 0, 0 },
    { "Rotate Hue...", 0, 0, 0 },
    { "Invert", 0, 0, 0 },
    { "Restore...", 0, 0, 0 },
    { "Remove Dust...", 0, 0, 0 },
    { "Colorize", 0, 0, 0 },
    { 0 },
  { "&Help", 0, 0, 0, FL_SUBMENU },
    { "&About", 0, (Fl_Callback *)show_about, 0 },
    { 0 },
  { 0 }
};

Gui::Gui()
{
  int x1, y1;

  // window
  window = new Fl_Double_Window(800, 600, "Rendera");
  window->callback(close_callback);
  
  //group_main = new Fl_Group(0, 0, window->w(), window->h());

  menubar = new Fl_Menu_Bar(0, 0, window->w(), 24);
  menubar->menu(menuitems);

  // top_left
  top_left = new Fl_Group(0, menubar->h(), 112, 40);
  top_left->box(FL_UP_BOX);
  logo = new Widget(top_left, 8, 8, 96, 24, "", "data/logo.png", 0, 0);
  top_left->resizable(0);
  top_left->end();

  // top right
  top_right = new Fl_Group(top_left->w(), menubar->h(), window->w() - top_left->w(), 40);
  top_right->box(FL_UP_BOX);
  x1 = 8;
  zoom_fit = new ToggleButton(top_right, x1, 8, 24, 24, "Fit In Window", "data/zoom_fit.png");
  zoom_fit->callback((Fl_Callback *)check_zoom_fit, &zoom_fit->var);
  x1 += 24 + 8;
  zoom_one = new Button(top_right, x1, 8, 24, 24, "Actual Size", "data/zoom_one.png");
  zoom_one->callback((Fl_Callback *)check_zoom_one, &zoom_one->var);
  x1 += 24 + 8;
  zoom_in = new Button(top_right, x1, 8, 24, 24, "Zoom In", "data/zoom_in.png");
  zoom_in->callback((Fl_Callback *)check_zoom_in, &zoom_in->var);
  x1 += 24 + 8;
  zoom_out = new Button(top_right, x1, 8, 24, 24, "Zoom Out", "data/zoom_out.png");
  zoom_out->callback((Fl_Callback *)check_zoom_out, &zoom_out->var);
  x1 += 24 + 8;
  zoom = new Field(top_right, x1, 8, 56, 24, "");
  zoom->deactivate();
  x1 += 56 + 6;
  new Separator(top_right, x1, 2, 2, 36, "");
  x1 += 8;
  grid = new ToggleButton(top_right, x1, 8, 24, 24, "Show Grid", "data/grid.png");
  grid->callback((Fl_Callback *)check_grid, &grid->var);
  x1 += 24 + 48 + 8;
  gridx = new Field(top_right, x1, 8, 32, 24, "Grid X:");
  gridx->callback((Fl_Callback *)check_gridx, &gridx->var);
  gridx->value("8");
  x1 += 32 + 48 + 8;
  gridy = new Field(top_right, x1, 8, 32, 24, "Grid Y:");
  gridy->callback((Fl_Callback *)check_gridy, &gridy->var);
  gridy->value("8");
  top_right->resizable(0);
  top_right->end();

  // bottom
  bottom = new Fl_Group(224, window->h() - 40, window->w() - 224 - 112, 40);
  bottom->box(FL_UP_BOX);
  x1 = 8;
  wrap = new ToggleButton(bottom, x1, 8, 24, 24, "Wrap Edges", "data/wrap.png");
  wrap->callback((Fl_Callback *)check_wrap, &wrap->var);
  x1 += 24 + 6;
  new Separator(bottom, x1, 2, 2, 36, "");
  x1 += 8;
  clone = new ToggleButton(bottom, x1, 8, 24, 24, "Clone Enable", "data/clone.png");
  clone->callback((Fl_Callback *)check_clone, &clone->var);
  x1 += 24 + 8;
  mirror = new Widget(bottom, x1, 8, 96, 24, "Clone Mirroring", "data/mirror.png", 24, 24);
  mirror->callback((Fl_Callback *)check_mirror, &mirror->var);
  x1 += 96 + 6;
  new Separator(bottom, x1, 2, 2, 36, "");
  x1 += 8;
  origin = new Widget(bottom, x1, 8, 48, 24, "Origin", "data/origin.png", 24, 24);
  origin->callback((Fl_Callback *)check_origin, &origin->var);
  x1 += 48 + 8;
  constrain = new Widget(bottom, x1, 8, 48, 24, "Keep Square", "data/constrain.png", 24, 24);
  constrain->callback((Fl_Callback *)check_constrain, &constrain->var);
  bottom->resizable(0);
  bottom->end();

  // tools
  tools = new Fl_Group(0, top_right->h() + menubar->h(), 112, window->h() - (menubar->h() + top_right->h()));
  tools->label("Tools");
  tools->labelsize(12);
  tools->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TOP);
  tools->box(FL_UP_BOX);
  y1 = 20;
  tool = new Widget(tools, 8, y1, 96, 144, "Tools", "data/tools.png", 96, 24);
  tool->callback((Fl_Callback *)check_tool, &tool->var);
  y1 += 96 + 8;
  tools->resizable(0);
  tools->end();

  // paint
  paint = new Fl_Group(112, top_right->h() + menubar->h(), 112, window->h() - top_right->h() - menubar->h());
  paint->label("Paint");
  paint->labelsize(12);
  paint->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TOP);
  paint->box(FL_UP_BOX);
  y1 = 20;
  paint_brush = new Widget(paint, 8, y1, 96, 96, "Brush Preview", 0, 0);
  paint_brush->bitmap->clear(makecol(255, 255, 255));
  paint_brush->bitmap->setpixel_solid(48, 48, makecol(0, 0, 0), 0);
  y1 += 96 + 8;
  paint_size = new Widget(paint, 8, y1, 96, 24, "Size", "data/size.png", 6, 24);
  paint_size->callback((Fl_Callback *)check_paint_size, &paint_size->var);
  y1 += 24 + 8;
  paint_stroke = new Widget(paint, 8, y1, 96, 48, "Stroke", "data/stroke.png", 24, 24);
  paint_stroke->callback((Fl_Callback *)check_paint_stroke, &paint_stroke->var);
  y1 += 48 + 8;
  paint_shape = new Widget(paint, 8, y1, 96, 24, "Shape", "data/shape.png", 24, 24);
  // use same callback as size here
  paint_shape->callback((Fl_Callback *)check_paint_size, &paint_size->var);
  paint->resizable(0);
  paint->end();

  // airbrush
  airbrush = new Fl_Group(112, top_right->h() + menubar->h(), 112, window->h() - top_right->h() - menubar->h());
  airbrush->label("Airbrush");
  airbrush->labelsize(12);
  airbrush->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TOP);
  airbrush->box(FL_UP_BOX);
  y1 = 20;
  airbrush_brush = new Widget(airbrush, 8, y1, 96, 96, "Brush Preview", 0, 0);
  airbrush_brush->bitmap->clear(makecol(255, 255, 255));
  airbrush_brush->bitmap->setpixel_solid(48, 48, makecol(0, 0, 0), 0);
  y1 += 96 + 8;
  airbrush_size = new Widget(airbrush, 8, y1, 96, 24, "Size", "data/size.png", 6, 24);
  airbrush_size->callback((Fl_Callback *)check_airbrush_size, &airbrush_size->var);
  y1 += 24 + 8;
  airbrush_stroke = new Widget(airbrush, 8, y1, 96, 48, "Stroke", "data/stroke.png", 24, 24);
  airbrush_stroke->callback((Fl_Callback *)check_airbrush_stroke, &airbrush_stroke->var);
  y1 += 48 + 8;
  airbrush_shape = new Widget(airbrush, 8, y1, 96, 24, "Shape", "data/shape.png", 24, 24);
  // use same callback as size here
  airbrush_shape->callback((Fl_Callback *)check_airbrush_size, &airbrush_size->var);
  y1 += 24 + 8;
  airbrush_edge = new Widget(airbrush, 8, y1, 96, 24, "Soft Edge", "data/soft_edge.png", 12, 24);
  airbrush_edge->callback((Fl_Callback *)check_airbrush_edge, &airbrush_edge->var);
  y1 += 24 + 8;
  airbrush_smooth = new Widget(airbrush, 8, y1, 96, 48, "Coarse/Fine", "data/smooth.png", 48, 48);
  y1 += 48 + 8;
  airbrush_smooth->callback((Fl_Callback *)check_airbrush_smooth, &airbrush_smooth->var);
  airbrush->resizable(0);
  airbrush->end();

  // pixelart
  pixelart = new Fl_Group(112, top_right->h() + menubar->h(), 112, window->h() - top_right->h() - menubar->h());
  pixelart->label("Pixel Art");
  pixelart->labelsize(12);
  pixelart->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TOP);
  pixelart->box(FL_UP_BOX);
  y1 = 20;
  pixelart_brush = new Widget(pixelart, 8, y1, 96, 96, "Brush Shape", "data/tiny.png", 16, 16);
  pixelart_brush->callback((Fl_Callback *)check_pixelart_brush, &pixelart_brush->var);
  y1 += 96 + 8;
  pixelart_stroke = new Widget(pixelart, 8, y1, 96, 48, "Stroke", "data/stroke.png", 24, 24);
  pixelart_stroke->callback((Fl_Callback *)check_pixelart_stroke, &pixelart_stroke->var);
  y1 += 48 + 8;
  pixelart->resizable(0);
  pixelart->end();

  // crop
  crop = new Fl_Group(112, top_right->h() + menubar->h(), 112, window->h() - top_right->h() - menubar->h());
  crop->label("Crop");
  crop->labelsize(12);
  crop->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TOP);
  crop->box(FL_UP_BOX);
  y1 = 20;
  crop_x = new Field(crop, 24, y1, 72, 24, "X:");
  crop_x->deactivate();
  y1 += 24 + 6;
  crop_y = new Field(crop, 24, y1, 72, 24, "Y:");
  crop_y->deactivate();
  y1 += 24 + 6;
  crop_w = new Field(crop, 24, y1, 72, 24, "W:");
  crop_w->deactivate();
  y1 += 24 + 6;
  crop_h = new Field(crop, 24, y1, 72, 24, "H:");
  crop_h->deactivate();
  y1 += 24 + 6;
  crop->resizable(0);
  crop->end();

  // getcolor
  getcolor = new Fl_Group(112, top_right->h() + menubar->h(), 112, window->h() - top_right->h() - menubar->h());
  getcolor->label("Get Color");
  getcolor->labelsize(12);
  getcolor->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TOP);
  getcolor->box(FL_UP_BOX);
  getcolor->resizable(0);
  getcolor->end();

  // offset
  offset = new Fl_Group(112, top_right->h() + menubar->h(), 112, window->h() - top_right->h() - menubar->h());
  offset->label("Offset");
  offset->labelsize(12);
  offset->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TOP);
  offset->box(FL_UP_BOX);
  offset->resizable(0);
  offset->end();

  // right
  right = new Fl_Group(window->w() - 112, top_right->h() + menubar->h(), 112, window->h() - top_right->h() - menubar->h());
  right->label("Colors");
  right->labelsize(12);
  right->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_TOP);
  right->box(FL_UP_BOX);
  y1 = 20;
  palette = new Widget(right, 8, y1, 96, 96, "Color Palette", 6, 6);
  palette->callback((Fl_Callback *)check_palette, &palette->var);
  y1 += 96 + 8;
  plus = new Button(right, 8, y1, 44, 16, "Insert Color", "data/plus.png");
  plus->callback((Fl_Callback *)check_plus, &plus->var);
  minus = new Button(right, 8 + 44 + 8, y1, 44, 16, "Delete Color", "data/minus.png");
  minus->callback((Fl_Callback *)check_minus, &minus->var);
  y1 += 16 + 8;
  hue = new Widget(right, 8, y1, 96, 96, "Hue", 1, 1);
  hue->callback((Fl_Callback *)check_color, &hue->var);
  y1 += 96 + 8;
  color = new Widget(right, 8, y1, 96, 48, "Color", 0, 0);
  y1 += 48 + 8;
  sat = new Widget(right, 8, y1, 96, 24, "Saturation", 1, 24);
  sat->callback((Fl_Callback *)check_color, &sat->var);
  y1 += 24 + 8;
  val = new Widget(right, 8, y1, 96, 24, "Value", 1, 24);
  val->callback((Fl_Callback *)check_color, &val->var);
  y1 += 24 + 8;
  trans = new Widget(right, 8, y1, 96, 24, "Transparency", "data/transparency.png", 1, 24);
  trans->callback((Fl_Callback *)check_color, &trans->var);
  y1 += 24 + 8;
  blend = new Widget(right, 8, y1, 96, 24, "Blending Mode", "data/blend.png", 24, 24);
  blend->callback((Fl_Callback *)check_color, &blend->var);
  y1 += 24 + 8;
  right->resizable(0);
  right->end();

  // middle
  middle = new Fl_Group(224, top_right->h() + menubar->h(), window->w() - 224 - 112, window->h() - (menubar->h() + top_right->h() + bottom->h()));
  middle->box(FL_FLAT_BOX);
  view = new View(middle, 0, 0, middle->w(), middle->h(), "View");
  middle->resizable(view);
  middle->end();

  // container for top panels
  group_top = new Fl_Group(0, menubar->h(), window->w() - top_left->w(), 40);
  group_top->add(top_left);
  group_top->add(top_right);
  group_top->resizable(top_right);
  group_top->end();

  // container for left panels
  group_left = new Fl_Group(0, top_right->h() + menubar->h(), 224, window->h() - (menubar->h() + top_right->h() + bottom->h()));
  group_left->add(tools);
  group_left->add(paint);
  group_left->add(airbrush);
//  group_left->resizable(tools);
//  group_left->resizable(options);
  group_left->end();

  //group_main->resizable(view);
  //group_main->end();

  paint->show();
  airbrush->hide();

  window->size_range(640, 480, 0, 0, 0, 0, 0);
  window->resizable(view);
  window->end();
  window->show();
  Fl_Tooltip::enable(1);
  Fl_Tooltip::color(fl_rgb_color(192, 224, 248));
  Fl_Tooltip::textcolor(FL_BLACK);

}

Gui::~Gui()
{
}

