/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes
  
   Distributed under the GPL
   see the file COPYING for details
   or visit http://www.gnu.org/copyleft/gpl.html
  
   $Id$
  
   definition of global variables and functions
  
   Written by Moritz Bunkus <moritz@bunkus.org>.
 */


#ifndef __MKVINFO_H
#define __MKVINFO_H

#include "os.h"

#include <string>

#include "config.h"

#ifdef HAVE_WXWINDOWS
#include <wx/wx.h>
#include <wx/dnd.h>
#include <wx/treectrl.h>
#endif

#define NAME "MKVInfo"

using namespace std;

void parse_args(int argc, char **argv, char *&file_name);
int console_main(int argc, char **argv);
bool process_file(const string &file_name);
void setup();
void cleanup();

extern bool use_gui;

#ifdef HAVE_WXWINDOWS

#include "wxcommon.h"

class mi_app: public wxApp {
public:
  virtual bool OnInit();
};

class mi_dndfile: public wxFileDropTarget {
public:
  virtual bool OnDropFiles(wxCoord x, wxCoord y,
                           const wxArrayString &filenames);
};

class mi_frame: public wxFrame {
private:
  //For Drag-n-Drop
  mi_dndfile *dnd_load;
  wxMenu *menu_options, *menu_file;
  bool show_all_elements, expand_important_elements;
  bool file_open;
  int last_percent;
  int64_t num_elements, elements_saved;
  wxString current_file, last_dir;
  
  wxTreeCtrl *tree;
  wxTreeItemId item_ids[10];

public:
  mi_frame(const wxString &title, const wxPoint &pos, const wxSize &size,
           long style = wxDEFAULT_FRAME_STYLE);

  void open_file(wxString file_name);
  void show_progress(int percent, wxString msg);
  void show_error(wxString msg);
  void add_item(int level, wxString text);

protected:
  void on_file_open(wxCommandEvent &event);
  void on_file_savetext(wxCommandEvent &event);
  void on_file_quit(wxCommandEvent &event);
  void on_options_showall(wxCommandEvent &event);
  void on_options_expandimportant(wxCommandEvent &event);
  void on_help_about(wxCommandEvent &event);
  void on_right_click(wxTreeEvent &event);

  void expand_elements();
  void expand_all_elements(wxTreeItemId &root, bool expand = true);

  void save_elements(wxTreeItemId &root, int level, FILE *f);

private:
  DECLARE_EVENT_TABLE()
};

extern mi_frame *frame;

DECLARE_APP(mi_app);

#endif // HAVE_WXWINDOWS

#endif // __MKVINFO_H
