// Copyright 2014 Google Inc. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd
//
// MpdNotifier is responsible for notifying the MpdBuilder class to generate an
// MPD file.

#ifndef MPD_BASE_MPD_NOTIFIER_H_
#define MPD_BASE_MPD_NOTIFIER_H_

#include "base/basictypes.h"
#include "mpd/base/media_info.pb.h"

namespace dash_packager {

class ContentProtectionElement;
class MediaInfo;

/// Interface for publish/subscribe publisher class which notifies MpdBuilder
/// of media-related events.
class MpdNotifier {
 public:
  MpdNotifier() {};
  virtual ~MpdNotifier() {};

  /// Initializes the notifier. For example, if this notifier uses a network for
  /// notification, then this would set up the connection with the remote host.
  /// @return true on success, false otherwise.
  virtual bool Init() = 0;

  /// Notifies the MpdBuilder that there is a new container along with
  /// @a media_info. Live may have multiple files (segments) but those should be
  /// notified via NotifyNewSegment().
  /// @param media_info is the MediaInfo that will be passed to MpdBuilder.
  /// @param[out] container_id is the numeric ID of the container, possibly for
  ///             NotifyNewSegment() and AddContentProtectionElement(). Only
  ///             populated on success.
  /// @return true on success, false otherwise.
  virtual bool NotifyNewContainer(const MediaInfo& media_info,
                                  uint32* container_id) = 0;

  /// Notifies MpdBuilder that there is a new segment ready. Used only for live
  /// profile.
  /// @param container_id Container ID obtained from calling
  ///        NotifyNewContainer().
  /// @param start_time is the start time of the new segment, in units of the
  ///        stream's time scale.
  /// @param duration is the duration of the new segment, in units of the
  ///        stream's time scale..
  /// @return true on success, false otherwise.
  virtual bool NotifyNewSegment(uint32 container_id,
                                uint64 start_time,
                                uint64 duration) = 0;

  /// Adds content protection information to the MPD.
  /// @param container_id is the nummeric container ID obtained from calling
  ///        NotifyNewContainer().
  /// @param content_protection_element New ContentProtection element
  ///        specification.
  /// @return true on success, false otherwise.
  virtual bool AddContentProtectionElement(
      uint32 container_id,
      const ContentProtectionElement& content_protection_element) = 0;
};

}  // namespace dash_packager

#endif  // MPD_BASE_MPD_NOTIFIER_H_
