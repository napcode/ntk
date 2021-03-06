//
// "$Id: howto-parse-args.cxx 8183 2011-01-04 17:31:56Z AlbrechtS $"
//
//     How to parse command line arguments - Duncan Gibson 2010-10-23
//     First posted in http://www.fltk.org/newsgroups.php?gfltk.general+v:31449
//
//     Shows how to decode additional command line arguments using Fl::args()
//     on top of the "standard" options used by the toolkit itself.
//
//     Note that this only handles "option separateValue" rather than the
//     usual *nix idiom of "option=value", and provides no validation nor
//     conversion of the paramter string into ints or floats.
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//
#include <stdio.h>
#include <string.h>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>

int helpFlag = 0;
char *optionString = 0;

/*
 * callback function passed to Fl::args() to parse individual argument.
 * If there is a match, 'i' must be incremented by 2 or 1 as appropriate.
 * If there is no match, Fl::args() will then call Fl::arg() as fallback
 * to try to match the "standard" FLTK parameters.
 * 
 * Returns 2 if argv[i] matches with required parameter in argv[i+1],
 * returns 1 if argv[i] matches on its own,
 * returns 0 if argv[i] does not match.
 */
int arg(int argc, char **argv, int &i)
{
  if (strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0) {
    helpFlag = 1;
    i += 1;
    return 1;
  }
  if (strcmp("-o", argv[i]) == 0 || strcmp("--option", argv[i]) == 0) {
    if (i < argc-1 && argv[i+1] != 0) {
      optionString = argv[i+1];
      i += 2;
      return 2;
    }
  }
  return 0;
}

int main(int argc, char** argv)
{
  int i = 1;
  if (Fl::args(argc, argv, i, arg) < argc)
    // note the concatenated strings to give a single format string!
    Fl::fatal("error: unknown option: %s\n"
              "usage: %s [options]\n"
              " -h | --help     : print extended help message\n"
              " -o | --option # : example option with parameter\n"
              " plus standard fltk options\n",
              argv[i], argv[0]);
  if (helpFlag)
    Fl::fatal("usage: %s [options]\n"
              " -h | --help     : print extended help message\n"
              " -o | --option # : example option with parameter\n"
              " plus standard fltk options:\n"
              "%s\n",
              argv[0], Fl::help);

  Fl_Window* mainWin = new Fl_Window(300, 200);
  Fl_Box* textBox = new Fl_Box(0, 0, 300, 200);
  if (optionString != 0)
    textBox->label(optionString);
  else
    textBox->label("re-run with [-o|--option] text");
  mainWin->show(argc, argv);
  return Fl::run();
}

//
// End of "$Id: howto-parse-args.cxx 8183 2011-01-04 17:31:56Z AlbrechtS $".
//
