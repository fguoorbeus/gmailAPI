/*
 * gmail_Impl.h
 *
 *  Created on: Jun 18, 2014
 *      Author: fguo
 */

#ifndef GMAIL_IMPL_H_
#define GMAIL_IMPL_H_

#include "GmailService.h"
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <string>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;
using namespace std;
using namespace ::gmail_master_server;

namespace gmail_master {
class GmailServiceHandler: virtual public GmailServiceIf {
public:
	GmailServiceHandler();
	~GmailServiceHandler();
	void analyze(const GmailRequest& req);
private:
	string ConstructAuthString(const string& email, const string& access_token);
};
}

#endif /* GMAIL_IMPL_H_ */
