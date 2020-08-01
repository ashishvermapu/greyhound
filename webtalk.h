/* 
 * File:   webtalk.h
 * Author: ashish
 *
 * Created on 4 July, 2011, 7:11 AM
 */

#ifndef _WEBTALK_H
#define	_WEBTALK_H

#include <curl/curl.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>

using namespace std;

// callback function writes data to a std::ostream
static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
    	if(userp)
	{
            cout<<" .";
            fflush(stdout);
		std::ostream& os = *static_cast<std::ostream*>(userp);
		std::streamsize len = size * nmemb;
		if(os.write(static_cast<char*>(buf), len))
			return len;
	}

	return 0;
}

/**
 * timeout is in seconds
 **/
CURLcode curl_read(const std::string& url, std::ostream& os, long timeout = 30)
{
	CURLcode code(CURLE_FAILED_INIT);
	CURL* curl = curl_easy_init();
        cout<<"\n\t Downloading";
        fflush(stdout);

	if(curl)
	{
		if(CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FILE, &os))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))
		&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str())))
		{
			code = curl_easy_perform(curl);
		}
		curl_easy_cleanup(curl);
	}
	return code;
}

void webtalk(char url[500])
{
	curl_global_init(CURL_GLOBAL_ALL);
        //CURLOPT_NOPROGRESS = 0;

	std::ofstream ofs("test.txt");

        cout<<"\n\t Opening file test.txt to write webpage.";
        fflush(stdout);

        if(CURLE_OK == curl_read(url, ofs))
	{
            cout<<"\n\t WebPage Sucessfully Written to File 'test.txt'";
            fflush(stdout);
            // Web page successfully written to file
	}

	curl_global_cleanup();
}

#endif	/* _WEBTALK_H */

