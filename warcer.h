// warcer.h: Headerdatei.
/*
 * =====================================================================================
 *
 *       Filename:  warcer.h
 *
 *    Description:  header file for warcer.cpp  
 *
 *        Version:  0.1
 *        Created:  19.05.2014 08:05:00
 *       Revision:  none
 *       Compiler:  clang++
 *
 *         Author:  Steffen Fritz, fritz@dla-marbach.de
 *   Organization:  DLA Marbach 
 *
 * =====================================================================================
 */

#include<iostream>
#include<fstream>
#include<string>
#include<boost/regex.hpp>
#include<boost/filesystem.hpp>
#include<boost/algorithm/string.hpp>
#include<boost/lexical_cast.hpp>

using namespace std;

void write_file(string & file_name, string & input_line);

boost::regex warc_type_response ("\\bWARC-Type: response(.*)");
boost::regex warc_content_type ("\\bContent-Type(.*)");
boost::regex warc_html_content ("\\bContent-Type: text/html");
boost::regex warc_target_uri ("\\bWARC-Target-URI: http(.*)");
boost::regex warc_version ("\\bWARC/(.*)");
boost::regex crlf_lineend ("(.*)\\r");

unsigned short counter = 0;
unsigned short index_n = 0;

string line;
string url_to_write;
string built_path;
string file_path;

char temp_sfx;

vector<string> url_strs;
vector<string> path_file_strs;
vector<string> full_path;

bool response_block = false;
bool html_content = false;
