// Author: Niklas Meinzer <meinzer.niklas@gmail.com>
// This code is open-source under the terms of the GPLv3 (see LICENSE file)

#ifndef JUKEBERRY_JUKEBERRY_H
#define JUKEBERRY_JUKEBERRY_H

#include <string>
#include <vector>

#include "./RaspiLCD.h"
#include "./Library.h"
#include "./Player.h"

using std::string;
using std::vector;

// This is the main class of the JukeBerry Project. It holds an instance of
// classes like RaspiLCD and Library and manages them.
class JukeBerry {
 public:
  // Constructor with the basepath of the library
  JukeBerry(const string& path);

  // this method starts the JukeBerry
  void start();

 private:
  // this method is called once per iteration and handles all the logic
  void update();
  // this method is called once per iteration and handles the drawing on the
  // RaspiLCD
  void draw();

  RaspiLCD _display;
  Library _library;
  Player _player;

  vector<string> _currentFiles;

  size_t _selectedFile;


};

#endif  // JUKEBERRY_JUKEBERRY_H
