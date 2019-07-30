/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_PLAYLISTS_BROWSER_PLAYLISTS_CONTROLLER_H_
#define BRAVE_COMPONENTS_PLAYLISTS_BROWSER_PLAYLISTS_CONTROLLER_H_

#include <string>

#include "base/macros.h"
#include "base/observer_list.h"
#include "brave/components/playlists/browser/playlists_types.h"

namespace base {
class FilePath;
}  // namespace base

class PlaylistsControllerObserver;
class PlaylistsDatabase;
class PlaylistsDownloadManager;

class PlaylistsController {
 public:
  PlaylistsController();
  virtual ~PlaylistsController();

  bool initialized() const { return initialized_; }

  void Init(const base::FilePath& base_dir);

  void CreatePlaylist(const CreatePlaylistParams& params);
  std::vector<PlaylistInfo> GetAllPlaylists();
  PlaylistInfo GetPlaylist(const std::string& id);
  void DeletePlaylist(const std::string& id);
  void DeleteAllPlaylists();

  void AddObserver(PlaylistsControllerObserver* observer);
  void RemoveObserver(PlaylistsControllerObserver* observer);

 private:
  base::ObserverList<PlaylistsControllerObserver> observers_;
  std::unique_ptr<PlaylistsDatabase> db_;
  std::unique_ptr<PlaylistsDownloadManager> download_manager_;
  bool initialized_ = false;

  DISALLOW_COPY_AND_ASSIGN(PlaylistsController);
};

#endif  // BRAVE_COMPONENTS_PLAYLISTS_BROWSER_PLAYLISTS_CONTROLLER_H_
