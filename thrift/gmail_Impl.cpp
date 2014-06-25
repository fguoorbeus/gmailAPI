/*
 * gmail_Impl.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: fguo
 */

#include <base64.h>
#include <CkEmail.h>
#include <CkEmailBundle.h>
#include <CkImap.h>
#include <CkMessageSet.h>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

#include "gmail_Impl.h"
#include "timing.hpp"

using namespace std;

namespace gmail_master {

typedef struct {
	int thread_id;
	CkEmailBundle ** bundle;
	CkImap * imap;
	int * cursor;
	int msg_cnt;
	mutable mutex* mu;
} PoolThreadData;

void* PoolThread(void *threadarg) {
	PoolThreadData * thread_data = (PoolThreadData *) threadarg;
	//cout << "the thread size is " << size << endl;
	while (*(thread_data->cursor) < thread_data->msg_cnt - 1) {
		//	cout << thread_data->thread_id << ":try to get lock" << endl;
		{
			lock_guard < mutex > lock(*(thread_data->mu));
			if (*(thread_data->cursor) >= thread_data->msg_cnt - 1) {
				continue;
			}
			*(thread_data->cursor) += 1;
			//	cout << "cursor:" << *(thread_data->cursor) << endl;
		}
		CkEmail *email = (*(thread_data->bundle))->GetEmail(*(thread_data->cursor));
		int numAttach;
		numAttach = thread_data->imap->GetMailNumAttach(*email);
		if (numAttach > 0) {
			//printf("%s\n",email->ck_from());
			int uid = email->GetImapUid();
			CkEmail *photoemail[numAttach];
			for (int j = 0; j < numAttach; j++) {
				CkString filename;
				thread_data->imap->GetMailAttachFilename(*email, j, filename);
				if (filename.containsSubstringNoCase("jpg")) {
					photoemail[j] = thread_data->imap->FetchSingle(uid,
							true);
					thread_data->imap->FetchAttachment(*(photoemail[j]), j,
							"/home/fguo/workspace/gmailtest/");
					delete photoemail[j];
				}
			}
		}
		delete email;
		usleep(500);
	}
	pthread_exit((void*) threadarg);

}

GmailServiceHandler::GmailServiceHandler() {

}

GmailServiceHandler::~GmailServiceHandler() {

}

string GmailServiceHandler::ConstructAuthString(const string& email,
		const string& access_token) {
	// get the authenticaiton string
	std::stringstream newstream;
	newstream << "user=" << email << "\1auth=Bearer " << access_token << "\1\1";
	std::string newstring = newstream.str();
	std::string encoded_newstring = base64_encode(
			reinterpret_cast<const unsigned char*>(newstring.c_str()),
			newstring.length());
	std::string request = "XOAUTH2 " + encoded_newstring;
	request = "AUTHENTICATE " + request;
	return request;
}

void GmailServiceHandler::analyze(const GmailRequest& req) {
	Timing clock;

	CkImap imap;
	bool success;
	string request = ConstructAuthString(req.email, req.access_token);

	// Anything unlocks the component and begins a fully-functional 30-day trial.
	success = imap.UnlockComponent("Anything for 30-day trial");
	if (success != true) {
		printf("%s\n", imap.lastErrorText());
		return;
	}
	imap.put_KeepSessionLog(true);
	// Connect to an IMAP server.
	imap.put_Port(993);
	imap.put_Ssl(true);
	success = imap.Connect("imap.gmail.com");

	if (success == true) {
		printf("connect success\n");
	}

	//send Authenticate Command
	CkString response;
	success = imap.SendRawCommand(request.c_str(), response);
	if (success == true) {
		printf("Authentication success\n");
	} else {
		printf("Authenticaitn failed\n");
	}

	// Select an IMAP mailbox
	success = imap.SelectMailbox("Inbox");
	if (success != true) {
		printf("%s\n", imap.lastErrorText());
		return;
	} else {
		printf("selectMailbox success1111\n");
	}

	CkMessageSet *messageSet = 0;
	// We can choose to fetch UIDs or sequence numbers.
	bool fetchUids;
	fetchUids = true;
	// Get the message IDs of all the emails in the mailbox

	messageSet = imap.Search("ALL", fetchUids);
	if (messageSet == 0) {
		printf("%s\n", imap.lastErrorText());
		return;
	}

	// Fetch the emails into a bundle object:
	CkEmailBundle *bundle = 0;
	CkEmailBundle *bundle_headers = 0;
	bundle_headers = imap.FetchHeaders(*messageSet);
	if (bundle_headers == 0) {
		delete messageSet;
		printf("%s\n", imap.lastErrorText());
		return;
	}
	clock.print("Preprocessing");

	for (int k = 0; k < bundle_headers->get_MessageCount(); k++) {
		CkEmail *email = 0;
		email = bundle_headers->GetEmail(k);
		int numAttach;
		numAttach = imap.GetMailNumAttach(*email);
		if (numAttach > 0) {
			//printf("%s\n",email->ck_from());
			int uid = email->GetImapUid();
			for (int j = 0; j < numAttach; j++) {
				CkString filename;
				imap.GetMailAttachFilename(*email, j, filename);
				//printf(filename);
				//printf("\n");
				if (filename.containsSubstringNoCase("jpg")) {
					//printf("image find!");

					CkEmail *photoemail = imap.FetchSingle(uid, true);

					imap.FetchAttachment(*photoemail, j,
							"/home/fguo/workspace/gmailtest/");

					delete photoemail;
				}
			}
		}
	}
	clock.print("fetchheaders first");
	/*bundle = imap.FetchBundle(*messageSet);
	 if (bundle == 0) {
	 delete messageSet;
	 printf("%s\n", imap.lastErrorText());
	 return;
	 }
	 //loop over the headers bundle, find the eamils with attachments of photos, save their uid

	 // loop over the message_bundle, find the emails with attachemnts, then select image file from them and download it.
	 for (int i = 0; i < bundle->get_MessageCount(); i++) {
	 CkEmail *email = 0;
	 email = bundle->GetEmail(i);
	 int numAttach;
	 numAttach = imap.GetMailNumAttach(*email);
	 if (numAttach > 0) {
	 //printf("%s\n",email->ck_from());
	 for (int j = 0; j <= numAttach - 1; j++) {
	 CkString filename;
	 imap.GetMailAttachFilename(*email, j, filename);
	 //printf(filename);
	 //printf("\n");
	 if (filename.containsSubstringNoCase("jpg")) {
	 //printf("image find!");
	 imap.FetchAttachment(*email, j,
	 "/home/fguo/workspace/gmailtest/");
	 }
	 }
	 }

	 //printf("--\n");
	 delete email;
	 }

	 clock.print("traditionnal");*/

	std::mutex mu;
	vector<PoolThreadData> thread_data;
	int batch_size = 128;
	thread_data.resize(batch_size);
	pthread_t threads[batch_size];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int cursor = -1;
	int msg_cnt = bundle_headers->get_MessageCount();

	for (int i = 0; i < batch_size; ++i) {

		// Add more parameters if you want
		thread_data[i].thread_id = i;
		thread_data[i].bundle = &bundle_headers;
		thread_data[i].imap = &imap;
		thread_data[i].mu = &mu;
		thread_data[i].cursor = &cursor;
		thread_data[i].msg_cnt = msg_cnt;

		int rc = pthread_create(&threads[i], &attr, PoolThread,
				(void *) &thread_data[i]);
		if (rc) {
			cout << "ERROR; thread return code from pthread_create() is " << rc
					<< "\n";
		}
		usleep(20000); // in us
	}

	pthread_attr_destroy(&attr);
	for (int i = 0; i < batch_size; ++i) {
		// Extract a face with surrounding areas.
		void *status;
		int rc = pthread_join(threads[i], &status);
		if (rc) {
			cout << "ERROR; thread return code from pthread_join() is " << rc
					<< "\n";
		}
	}

	clock.print("In parall");

	// Disconnect from the IMAP server.
	imap.Disconnect();

	delete messageSet;
	delete bundle;
}
}
