/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL
   see the file COPYING for details
   or visit http://www.gnu.org/copyleft/gpl.html

   PGS packetizer

   Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#include "common/common_pch.h"

#include <matroska/KaxContentEncoding.h>

#include "common/compression.h"
#include "common/matroska.h"
#include "output/p_pgs.h"

using namespace libmatroska;

pgs_packetizer_c::pgs_packetizer_c(generic_reader_c *p_reader,
                                   track_info_c &p_ti)
  : generic_packetizer_c(p_reader, p_ti)
{
  set_track_type(track_subtitle);
  set_default_compression_method(COMPRESSION_ZLIB);
}

pgs_packetizer_c::~pgs_packetizer_c() {
}

void
pgs_packetizer_c::set_headers() {
  set_codec_id(MKV_S_HDMV_PGS);

  generic_packetizer_c::set_headers();

  m_track_entry->EnableLacing(false);
}

int
pgs_packetizer_c::process(packet_cptr packet) {
  add_packet(packet);

  return FILE_STATUS_MOREDATA;
}

connection_result_e
pgs_packetizer_c::can_connect_to(generic_packetizer_c *src,
                                 std::string &error_message) {
  return dynamic_cast<pgs_packetizer_c *>(src) == NULL ? CAN_CONNECT_NO_FORMAT : CAN_CONNECT_YES;
}