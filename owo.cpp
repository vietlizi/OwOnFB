#include <iostream>
#include <string>
#include <curl/curl.h>

const std::string ACCESS_TOKEN = "YOUR_ACCESS_TOKEN";  // Not showing mine, obviously.
const std::string POST_ID = "POST_ID_HERE";            // Not showing mine, obviously.
const std::string COMMENT_MESSAGE = "owo";

// Callback function to receive response from curl
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Initialize curl
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        std::string postUrl = "https://graph.facebook.com/v13.0/" + POST_ID + "/comments";
        std::string postData = "access_token=" + ACCESS_TOKEN + "&message=" + COMMENT_MESSAGE;

        // Set curl options
        curl_easy_setopt(curl, CURLOPT_URL, postUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postData.length());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Send the POST request.
        res = curl_easy_perform(curl);

        // Check for errors, why not.
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "owo successfully!" << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    // Cleanup curl
    curl_global_cleanup();

    return 0;
}
