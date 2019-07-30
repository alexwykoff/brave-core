/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/playlists/browser/playlists_service.h"

#include <string>

#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/task/post_task.h"
#include "brave/common/extensions/api/brave_playlists.h"
#include "brave/components/playlists/browser/playlists_controller.h"
#include "chrome/browser/profiles/profile.h"
#include "extensions/browser/event_router.h"

namespace {

const base::FilePath::StringType kBaseDirName(FILE_PATH_LITERAL("playlists"));

extensions::EventRouter* GetEventRouter(Profile* profile) {
  return extensions::EventRouter::Get(profile);
}

std::string ConvertPlaylistsChangeType(PlaylistsChangeParams::ChangeType type) {
  switch (type) {
    case PlaylistsChangeParams::ChangeType::CHANGE_TYPE_ADD:
      return "add";
    case PlaylistsChangeParams::ChangeType::CHANGE_TYPE_DELETE:
      return "delete";
    case PlaylistsChangeParams::ChangeType::CHANGE_TYPE_ABORT:
      return "abort";
    case PlaylistsChangeParams::ChangeType::CHANGE_TYPE_READY:
      return "ready";
    default:
      NOTREACHED();
      return "unknown";
  }
}

bool EnsurePlaylistsBaseDirectoryExists(const base::FilePath& path) {
  if (base::DirectoryExists(path))
    return true;
  return base::CreateDirectory(path);
}

}  // namespace

PlaylistsService::PlaylistsService(Profile* profile)
    : controller_(new PlaylistsController),
      observer_(this),
      base_dir_(profile->GetPath().Append(kBaseDirName)),
      profile_(profile),
      weak_factory_(this) {
  observer_.Add(controller_.get());

  base::PostTaskAndReplyWithResult(
    file_task_runner().get(),
    FROM_HERE,
    base::BindOnce(&EnsurePlaylistsBaseDirectoryExists, base_dir_),
    base::BindOnce(&PlaylistsService::OnBaseDirectoryReady,
                   weak_factory_.GetWeakPtr()));
}

PlaylistsService::~PlaylistsService() {
}

void PlaylistsService::OnBaseDirectoryReady(bool ready) {
  // If we can't create directory in profile dir, give up.
  if (!ready)
    return;

  controller_->Init(base_dir_);
}

void PlaylistsService::OnPlaylistsInitialized() {
  auto event = std::make_unique<extensions::Event>(
      extensions::events::BRAVE_PLAYLISTS_ON_INITIALIZED,
      extensions::api::brave_playlists::OnInitialized::kEventName,
      nullptr,
      profile_);

  GetEventRouter(profile_)->BroadcastEvent(std::move(event));
}

void PlaylistsService::OnPlaylistsChanged(
    const PlaylistsChangeParams& params) {
  auto event = std::make_unique<extensions::Event>(
      extensions::events::BRAVE_PLAYLISTS_ON_PLAYLISTS_CHANGED,
      extensions::api::brave_playlists::OnPlaylistsChanged::kEventName,
      extensions::api::brave_playlists::OnPlaylistsChanged::Create(
          ConvertPlaylistsChangeType(params.type), params.playlist_id),
      profile_);

  GetEventRouter(profile_)->BroadcastEvent(std::move(event));
}

scoped_refptr<base::SequencedTaskRunner>
PlaylistsService::file_task_runner() {
  if (!file_task_runner_) {
    file_task_runner_ = base::CreateSequencedTaskRunnerWithTraits(
                            { base::MayBlock(),
                              base::TaskPriority::BEST_EFFORT,
                              base::TaskShutdownBehavior::SKIP_ON_SHUTDOWN });
  }
  return file_task_runner_;
}
