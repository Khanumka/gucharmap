/*
 * Copyright (c) 2007 Christian Persch
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

#ifndef GUCHARMAP_CHARTABLE_PRIVATE_H
#define GUCHARMAP_CHARTABLE_PRIVATE_H

G_BEGIN_DECLS

struct _GucharmapChartable
{
  GtkDrawingArea parent_instance;

  /* scrollable implementation */
  GtkAdjustment *vadjustment;
  gulong vadjustment_changed_handler_id;

  /* Font */
  PangoFontDescription *font_desc;
  int drag_font_size;

  int bare_minimal_column_width;
  int bare_minimal_row_height;

  /* rows and columns on a page */
  gint rows, cols;

  GdkPixmap *pixmap;

  PangoLayout *pango_layout;

  gint page_first_cell;
  gint active_cell;
  gint old_page_first_cell;
  gint old_active_cell;

  GtkWidget *zoom_window;
  GtkWidget *zoom_image;

  /* for dragging (#114534) */
  gdouble click_x, click_y; 

  GtkTargetList *target_list;

  GucharmapCodepointList *codepoint_list;
  int last_cell; /* from gucharmap_codepoint_list_get_last_index */
  gboolean codepoint_list_changed;

  /* Settings */
  guint snap_pow2_enabled : 1;
  guint zoom_mode_enabled : 1;
};

struct _GucharmapChartableClass
{
  GtkDrawingAreaClass parent_class;

  void    (* set_scroll_adjustments) (GucharmapChartable *chartable,
                                      GtkAdjustment      *hadjustment,
                                      GtkAdjustment      *vadjustment);
  gboolean (* move_cursor)           (GucharmapChartable *chartable,
                                      GtkMovementStep     step,
                                      gint                count);
  void (* activate) (GucharmapChartable *chartable);

  void (* set_active_char) (GucharmapChartable *chartable, guint ch);
  void (* gucharmap_chartable_emit_status_message) (GucharmapChartable *chartable, const gchar *message);
};

gint _gucharmap_chartable_cell_column	(GucharmapChartable *chartable,
					 guint cell);
gint _gucharmap_chartable_column_width	(GucharmapChartable *chartable,
					 gint col);
gint _gucharmap_chartable_x_offset	(GucharmapChartable *chartable,
					 gint col);
gint _gucharmap_chartable_row_height	(GucharmapChartable *chartable,
		 			 gint row);
gint _gucharmap_chartable_y_offset	(GucharmapChartable *chartable,
					 gint row);
void _gucharmap_chartable_redraw	(GucharmapChartable *chartable,
					 gboolean move_zoom);

G_END_DECLS

#endif  /* #ifndef GUCHARMAP_CHARTABLE_PRIVATE_H */