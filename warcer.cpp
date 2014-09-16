// warcer.cpp: Hauptprojektdatei.
/*
 * =====================================================================================
 *
 *       Filename:  warc.cpp
 *
 *    Description:  extracts content from warc archives  
 *
 *        Version:  0.1
 *        Created:  07.05.2014 14:28:32
 *       Revision:  none
 *       Compiler:  clang++
 *
 *         Author:  Steffen Fritz, fritz@dla-marbach.de
 *   Organization:  DLA Marbach 
 *
 * =====================================================================================
 */

#ifdef _WIN32
    #include "StdAfx.h"
#endif

#include "warcer.h"

using namespace std;

void write_file(string & file_name) {
    
    ofstream output_file (file_name, ios::out | ios::binary | ios::app);
    output_file.close();    
}


string rm_trailing_lf(string & in_string) {
    
    if (boost::regex_match(in_string, crlf_lineend)) {
        in_string.pop_back();
    }
    return in_string;
}


int main(int argc, char* argv[]) {
    
    if (argc != 2){
        cout << "Fehler: Programm erwartet als Agument eine warc-Datei.\n";
        return 1;
     }

    ifstream infile(argv[1], ios::binary);
    
    if (infile.is_open()){
        cout << "Info: Starte Aufbau der Seite. Dies kann einige Zeit dauern.\n";
        // read lines 
        while (getline(infile, line)){
            rm_trailing_lf(line);
            // decide if we are in a response block
            if (boost::regex_match(line, warc_type_response)){
                response_block = true;
            }
            // decide if we found a target-uri inside a response block
            if (boost::regex_match(line, warc_target_uri) && (response_block)){
                // Tokenize line
                boost::split(path_file_strs, line, boost::is_any_of("/"));
                //build path from vector path_file_strs, remove trailing \r       
                for (unsigned int i=2; i < path_file_strs.size()-1; i++) {
                    built_path.append(path_file_strs[i]);
                    built_path.append("/");
                }
                    // create directory
                    boost::filesystem::path dir(built_path);
	            boost::filesystem::create_directories(dir);

                    // construct file_path
                    file_path = built_path + path_file_strs.back();
                    
                    // check file name. if none, guess its index.html
                    temp_sfx = file_path[file_path.size() - 1];
                    if (temp_sfx == '/') {
                        cout << "Info: Leerer Dateiname. Verwende index.html." + boost::lexical_cast<std::string>(index_n) << "\n";
                        cout << "      Datei eventuell manuell in index.html umbenennen. \n";
                        file_path = file_path + "index.html." + boost::lexical_cast<std::string>(index_n);    
                        index_n += 1;
                    }
                    write_file(file_path);
                    built_path.clear();
            }
           
            // identify text/html content
            if (boost::regex_match(line, warc_html_content)) {
                html_content = true;
            }

            // count empty lines after response block, i.e. identify content start 
            if ( !file_path.empty() && response_block && line.size() == 0) {
                if (counter < 2) {
                    counter = counter + 1;
                }
            }
            // break condition at new warc block. reset.
            if (boost::regex_match(line, warc_version)) {
                response_block = false;
                html_content = false;
                counter = 0;
                file_path.clear();
            }
           
            // write line to file. dont double empty lines 
            if (!file_path.empty() && response_block && counter == 2){
                ofstream output_file (file_path, ios::out | ios::binary | ios::app);
                if (!line.empty() || (line.empty() && html_content)) {
        		output_file << line << "\n";
	        	output_file.close();
                }
                else{
                    output_file << line;
                    output_file.close();
                }
            }
                
        };
    infile.close();
    
    return 0;
    }

    else {
        cout << "Fehler: Konnte auf warc-Datei nicht zugreifen.\n";

        return 1;
    };
}
