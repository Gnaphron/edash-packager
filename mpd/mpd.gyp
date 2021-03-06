# Copyright 2014 Google Inc. All rights reserved.
#
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file or at
# https://developers.google.com/open-source/licenses/bsd
#
# GYP file for any MPD generation targets.

{
  'variables': {
    # Compile as chromium code to enable warnings and warnings-as-errors.
    'chromium_code': 1,
  },
  'target_defaults': {
    'include_dirs': [
      '..',
    ],
  },
  'targets': [
    {
      'target_name': 'media_info_proto',

      'type': 'static_library',
      'sources': [
        'base/media_info.proto',
      ],
      'variables': {
        'proto_in_dir': 'base',
        'proto_out_dir': 'mpd/base',
      },
      'includes': ['../build/protoc.gypi'],
      'dependencies': [
        # This target needs to depend on 'protobuf_full_do_not_use' to generate
        # non-LITE (full) protobuf. We need full protobuf to serialize and
        # deserialize human readable protobuf messages.
        '../third_party/protobuf/protobuf.gyp:protobuf_full_do_not_use',
      ],
    },
    {
      'target_name': 'mpd_builder',
      'type': 'static_library',
      'sources': [
        'base/content_protection_element.cc',
        'base/content_protection_element.h',
        'base/mpd_builder.cc',
        'base/mpd_builder.h',
        'base/mpd_utils.cc',
        'base/mpd_utils.h',
        'base/xml/scoped_xml_ptr.h',
        'base/xml/xml_node.cc',
        'base/xml/xml_node.h',
      ],
      'dependencies': [
        '../base/base.gyp:base',
        '../third_party/libxml/libxml.gyp:libxml',
        'media_info_proto',
      ],
      'export_dependent_settings': [
        '../third_party/libxml/libxml.gyp:libxml',
        'media_info_proto',
      ],
    },
    {
      'target_name': 'mpd_unittest',
      'type': '<(gtest_target_type)',
      'sources': [
        'base/mpd_builder_unittest.cc',
        'base/xml/xml_node_unittest.cc',
        'test/mpd_builder_test_helper.cc',
        'test/mpd_builder_test_helper.h',
        'util/mpd_writer_unittest.cc',
      ],
      'dependencies': [
        '../base/base.gyp:base',
        '../media/file/file.gyp:file',
        '../media/test/media_test.gyp:run_all_unittests',
        '../testing/gtest.gyp:gtest',
        'mpd_builder',
        'mpd_util',
      ],
    },
    {
      'target_name': 'mpd_util',
      'type': '<(component)',
      'sources': [
        'util/mpd_writer.cc',
        'util/mpd_writer.h',
      ],
      'dependencies': [
        '../media/file/file.gyp:file',
        'mpd_builder',
      ],
    },
  ],
}
