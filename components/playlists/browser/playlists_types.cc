/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/playlists/browser/playlists_types.h"

MediaFileInfo::MediaFileInfo(
    const std::string& url,
    const std::string& title)
    : media_file_url(url),
      media_file_title(title) {}
MediaFileInfo::~MediaFileInfo() {}

CreatePlaylistParams::CreatePlaylistParams() {}
CreatePlaylistParams::~CreatePlaylistParams() {}
CreatePlaylistParams::CreatePlaylistParams(const CreatePlaylistParams& rhs) {
  playlist_thumbnail_url = rhs.playlist_thumbnail_url;
  playlist_name = rhs.playlist_name;
  media_files = rhs.media_files;
}

PlaylistInfo::PlaylistInfo() {}
PlaylistInfo::~PlaylistInfo() {}
PlaylistInfo::PlaylistInfo(const PlaylistInfo& rhs) {
  id = rhs.id;
  playlist_name = rhs.playlist_name;
  thumbnail_path = rhs.thumbnail_path;
  titles = rhs.titles;
  ready = rhs.ready;
}
