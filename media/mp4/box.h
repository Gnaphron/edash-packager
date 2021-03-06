// Copyright 2014 Google Inc. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef MEDIA_MP4_BOX_H_
#define MEDIA_MP4_BOX_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "media/mp4/fourccs.h"

namespace media {

class BufferWriter;

namespace mp4 {

class BoxBuffer;
class BoxReader;

/// Defines the base ISO BMFF box objects as defined in ISO 14496-12:2012
/// ISO BMFF section 4.2. All ISO BMFF compatible boxes inherit from either
/// Box or FullBox.
struct Box {
 public:
  Box();
  virtual ~Box();
  /// Parse the mp4 box.
  /// @param reader points to a BoxReader object which parses the box.
  bool Parse(BoxReader* reader);
  /// Write the box to buffer.
  /// This function calls ComputeSize internally to compute box size.
  /// @param writer points to a BufferWriter object which wraps the buffer for
  ///        writing.
  void Write(BufferWriter* writer);
  /// Compute the size of this box.
  /// The calculated size will be saved in |atom_size| for later consumption.
  virtual uint32 ComputeSize() = 0;
  virtual FourCC BoxType() const = 0;

 protected:
  friend class BoxBuffer;
  /// Read/write the mp4 box from/to BoxBuffer.
  virtual bool ReadWrite(BoxBuffer* buffer);

  /// We don't support 64-bit atom sizes. 32-bit should be large enough for our
  /// current needs.
  uint32 atom_size;
};

/// Defines FullBox, the other base ISO BMFF box objects as defined in
/// ISO 14496-12:2012 ISO BMFF section 4.2. All ISO BMFF compatible boxes
/// inherit from either Box or FullBox.
struct FullBox : Box {
 public:
  FullBox();
  virtual ~FullBox();

  uint8 version;
  uint32 flags;

 protected:
  virtual bool ReadWrite(BoxBuffer* buffer) OVERRIDE;
};

}  // namespace mp4
}  // namespace media

#endif  // MEDIA_MP4_BOX_H_
