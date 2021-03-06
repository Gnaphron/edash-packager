// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_MP4_CENC_H_
#define MEDIA_MP4_CENC_H_

#include <vector>

#include "base/basictypes.h"
#include "media/base/decrypt_config.h"

namespace media {

class BufferReader;
class BufferWriter;

namespace mp4 {

class FrameCENCInfo {
 public:
  FrameCENCInfo();
  explicit FrameCENCInfo(const std::vector<uint8>& iv);
  ~FrameCENCInfo();

  bool Parse(uint8 iv_size, BufferReader* reader);
  void Write(BufferWriter* writer) const;
  size_t ComputeSize() const;
  size_t GetTotalSizeOfSubsamples() const;

  void AddSubsample(const SubsampleEntry& subsample) {
    subsamples_.push_back(subsample);
  }

  const std::vector<uint8>& iv() const { return iv_; }
  const std::vector<SubsampleEntry>& subsamples() const { return subsamples_; }

 private:
  std::vector<uint8> iv_;
  std::vector<SubsampleEntry> subsamples_;

  // Not using DISALLOW_COPY_AND_ASSIGN here intentionally to allow the compiler
  // generated copy constructor and assignment operator.
};

}  // namespace mp4
}  // namespace media

#endif  // MEDIA_MP4_CENC_H_
