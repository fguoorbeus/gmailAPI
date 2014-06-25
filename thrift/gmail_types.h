/**
 * Autogenerated by Thrift Compiler (0.8.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef gmail_TYPES_H
#define gmail_TYPES_H

#include <Thrift.h>
#include <TApplicationException.h>
#include <protocol/TProtocol.h>
#include <transport/TTransport.h>



namespace gmail_master_server {

typedef struct _GmailRequest__isset {
  _GmailRequest__isset() : email(false), access_token(false) {}
  bool email;
  bool access_token;
} _GmailRequest__isset;

class GmailRequest {
 public:

  static const char* ascii_fingerprint; // = "07A9615F837F7D0A952B595DD3020972";
  static const uint8_t binary_fingerprint[16]; // = {0x07,0xA9,0x61,0x5F,0x83,0x7F,0x7D,0x0A,0x95,0x2B,0x59,0x5D,0xD3,0x02,0x09,0x72};

  GmailRequest() : email(""), access_token("") {
  }

  virtual ~GmailRequest() throw() {}

  std::string email;
  std::string access_token;

  _GmailRequest__isset __isset;

  void __set_email(const std::string& val) {
    email = val;
  }

  void __set_access_token(const std::string& val) {
    access_token = val;
  }

  bool operator == (const GmailRequest & rhs) const
  {
    if (!(email == rhs.email))
      return false;
    if (!(access_token == rhs.access_token))
      return false;
    return true;
  }
  bool operator != (const GmailRequest &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const GmailRequest & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

} // namespace

#endif
