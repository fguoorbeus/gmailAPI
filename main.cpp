/*
 * test.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: fguo
 */
#include <concurrency/ThreadManager.h>
#include <concurrency/PosixThreadFactory.h>

#include <protocol/TBinaryProtocol.h>
#include <server/TNonblockingServer.h>
#include <server/TSimpleServer.h>
#include <server/TThreadPoolServer.h>
#include <server/TThreadedServer.h>
#include <transport/TBufferTransports.h>
#include <transport/TServerSocket.h>
#include <transport/TTransportUtils.h>

#include "thrift/GmailService.h"
#include "thrift/gmail_Impl.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using boost::shared_ptr;

using namespace ::gmail_master_server;
using namespace gmail_master;

using namespace std;

int main(int argc, char **argv) {
	/*
	 std::string request=constructAuthString("fguo@orbe.us","ya29.LgAFJkuRGBuQMh8AAACTfaHiYdghWuzbNdivVYl21xSn-BgaVLzJSwECnB8C3g");
	 printf("the request is %s\n",request.c_str());
	 ChilkatSample(request);
	 const std::string s = "ADP GmbH\nAnalyse Design & Programmierung\nGesellschaft mit beschränkter Haftung" ;

	 std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
	 std::string decoded = base64_decode(encoded);

	 //std::cout << "encoded: " << encoded << std::endl;
	 //std::cout << "decoded: " << decoded << std::endl;
	 printf("done\n");
	 */

	boost::shared_ptr<GmailServiceHandler> handler(new GmailServiceHandler());
	boost::shared_ptr<TProcessor> processor(new GmailServiceProcessor(handler));
	boost::shared_ptr<TProtocolFactory> protocolFactory(
			new TBinaryProtocolFactory());

	boost::shared_ptr<ThreadManager> threadManager =
			ThreadManager::newSimpleThreadManager(128); // Max 128 concurrent image download each node.
	boost::shared_ptr<PosixThreadFactory> threadFactory = boost::shared_ptr<
			PosixThreadFactory>(new PosixThreadFactory());
	threadManager->threadFactory(threadFactory);
	threadManager->start();
	TNonblockingServer server(processor, protocolFactory, 28999,
			threadManager);
	server.serve();
	return 0;
}
