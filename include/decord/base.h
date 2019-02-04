/*!
 *  Copyright (c) 2019 by Contributors
 * \file base.h
 * \brief configuration of DECORD and basic data structure.
 */
#ifndef DECORD_BASE_H_
#define DECORD_BASE_H_

#include <cstdint>
#include <string>
#include <ostream>

#include <dlpack/dlpack.h>

/*! \brief DECORD version */
#define DECORD_VERSION "0.0.1"

namespace decord {

// common data types
static const DLDataType kUInt8 = { kDLUInt, 8U, 1U };
static const DLDataType kUInt16 = { kDLUInt, 16U, 1U };
static const DLDataType kFloat16 = { kDLFloat, 16U, 1U };
static const DLDataType kFloat32 = { kDLFloat, 32U, 1U };

/*! \brief check if current date type equals another one */
inline bool operator== (const DLDataType &d1, const DLDataType &d2) {
  return (d1.bits == d2.bits && d1.code == d2.code && d1.lanes == d2.lanes);
}

static const DLContext kCPU = {kDLCPU, 0};

/*! \brief Type of Decoder support */
enum DecoderType {
  kFFMPEG = 0U,
  kNVDEC = 1U,
};  // enum DecoderType

/*! Decoder type */
struct Decoder {
  
  /*! \brief Decoder type. */
  DecoderType dec_type;

  /*! \brief default constructor */
  Decoder() : dec_type(kFFMPEG) {}
  /*! \brief constructor */
  Decoder(DecoderType type) : dec_type(type) {}
  /*! \brief default FFMPEG Decoder */
  inline static Decoder FFMPEG() { return Decoder(kFFMPEG); };
  /*! \brief NVDEC Decoder */
  inline static Decoder NVDEC() { return Decoder(kNVDEC); };

  /*!
   * \brief check if current decoder equals another one
   * \param b another decoder to compare
   * \return whether decoders are same
   */
  inline bool operator==(const Decoder &b) const {
    return dec_type == b.dec_type;
  }

  /*!
   * \brief Type to stream conversion.
   * \param os OStream
   * \param dec Decoder instance
   * \return Same OStream as input
   */ 
  friend std::ostream& operator<< (std::ostream& os, const Decoder& dec) {
    if (dec.dec_type == kFFMPEG) {
      os << " [FFMPEG] ";
    } else if (dec.dec_type == kNVDEC) {
      os << " [NVDEC] ";
    } else {
      os << " [Unknown]";
    }
    return os;
  }
}; // struct Decoder

};  // namespace decord
#endif  // DECORD_BASE_H_
