// Copyright 2013
// Author: Niklas Meinzer <meinzer.niklas@gmail.com>
// This code is open-source under the terms of the GPLv3 (see LICENSE file)

#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "./Library.h"

using namespace boost::filesystem;

using std::vector;
using std::string;
using std::cout;

// _____________________________________________________________________________
Library::Library(const string& basePath){
  path baseDir = absolute(basePath);
  try {
    if (exists(baseDir)) {
      if (!is_directory(baseDir)) {
        cout << baseDir << " is not directory!\n";
      }
      _basepath = basePath;
    }
    else
      cout << baseDir << " does not exist\n";

    // cd into the root
    _currentDirFiles.push_back(basePath);
    cd(0);
  }

  catch (const filesystem_error& ex)
  {
    cout << ex.what() << '\n';
  }

  _currentPath = baseDir;
};


// _____________________________________________________________________________
const vector<string>& Library::getFileList() const {
  return _currentDirFiles;
}

// _____________________________________________________________________________
void Library::cd(int i) {
  
  if (i >= static_cast<int>(_currentDirFiles.size())) return;

  // if i >= 0 switch into deeper directory
  if (i >= 0) {
    // create a path object for the new directory
    path newDir(_currentDirFiles[i]);

    // return if it is not a directory
    if (!is_directory(newDir)) return;

    // push current path to parents
    _parents.push_back(_currentPath);

    // actually cd into newDir
    cd(newDir);
  } else { // if i < 0 switch into parent directory
    path parent = _parents.back();

    std::cout << "cahnging into " << parent.native() << std::endl;

    // pop the last element unless this is the base
    if (_parents.size() > 1) _parents.pop_back();

    // actually cd into parent
    cd(parent);
  }
}

// _____________________________________________________________________________
void Library::cd(const path& p) {
  
  // return if it is not a directory
  if (!is_directory(p)) return;

  // reset current path
  _currentPath = p;

  // update file list
  _currentDirFiles.clear();

  for(directory_iterator it(_currentPath); it != directory_iterator(); ++it) {
    _currentDirFiles.push_back((*it).path().native());
  }
}
