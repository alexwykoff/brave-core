/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_PLAYLISTS_BROWSER_PLAYLISTS_DATABASE_H_
#define BRAVE_COMPONENTS_PLAYLISTS_BROWSER_PLAYLISTS_DATABASE_H_

#include "base/files/file_path.h"
#include "base/macros.h"

class PlaylistsDatabase {
 public:
  explicit PlaylistsDatabase(const base::FilePath& db_path);
  virtual ~PlaylistsDatabase();

 private:
  base::FilePath db_path_;

  DISALLOW_COPY_AND_ASSIGN(PlaylistsDatabase);
};


#endif  // BRAVE_COMPONENTS_PLAYLISTS_BROWSER_PLAYLISTS_DATABASE_H_
