#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;

// Function to run speedtest-cli command and return the download and upload speeds
pair<double, double> run_speedtest(string ip_address) {
    // Construct the speedtest-cli command with IP address argument
    string command = "speedtest-cli --simple --source " + ip_address;
    
    // Open a pipe to the command and read the output
    FILE* pipe = popen(command.c_str(), "r");
    char buffer[128];
    string output = "";
    while (fgets(buffer, 128, pipe) != NULL) {
        output += buffer;
    }
    pclose(pipe);
    
    // Parse the download and upload speeds from the output
    double download_speed = 0.0;
    double upload_speed = 0.0;
    size_t pos = output.find("Download: ");
    if (pos != string::npos) {
        download_speed = stod(output.substr(pos + 10));
    }
    pos = output.find("Upload: ");
    if (pos != string::npos) {
        upload_speed = stod(output.substr(pos + 8));
    }
    
    return make_pair(download_speed, upload_speed);
}

int main() {
    // List of IP addresses to test
    vector<string> ip_addresses = {"192.168.1.1", "192.168.1.2", "192.168.1.3"};
    
    // Open a file to write the speed test results
    ofstream results_file("speedtest_results.csv");
    results_file << "IP Address,Download Speed,Upload Speed" << endl;
    
    // Loop through each IP address and run the speed test
    for (string ip_address : ip_addresses) {
        pair<double, double> speeds = run_speedtest(ip_address);
        results_file << ip_address << "," << speeds.first << "," << speeds.second << endl;
    }
    
    results_file.close();
    
    return 0;
}
