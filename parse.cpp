#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

const char* ws = " \t\n\r\f\v";

// trim from end of string (right)
inline std::string& rtrim(std::string& s, const char* t = ws)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from beginning of string (left)
inline std::string& ltrim(std::string& s, const char* t = ws)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from both ends of string (right then left)
inline std::string& trim(std::string& s, const char* t = ws)
{
    return ltrim(rtrim(s, t), t);
}

int throw_error(size_t error_num) {
  std::map<std::string, std::string> errors;
  std::string error_code = std::to_string(error_num);
  errors["400"] = "Bad Request";
  errors["401"] = "Unauthorized";
  errors["402"] = "Payment Required";
  errors["403"] = "Forbidden";
  errors["404"] = "Not Found";
  errors["405"] = "Method Not Allowed";
  errors["406"] = "Not Acceptable";
  errors["407"] = "Proxy Authentication Required";
  errors["408"] = "Request Timeout";
  errors["409"] = "Conflict";
  errors["410"] = "Gone";
  errors["411"] = "Length Required";
  errors["412"] = "Precondition Failed";
  errors["413"] = "Payload Too Large";
  errors["414"] = "URI Too Long";
  errors["415"] = "Unsupported Media Type";
  errors["416"] = "Range Not Satisfiable";
  errors["417"] = "Expectation Failed";
  errors["418"] = "I'm a teapot";
  errors["421"] = "Misdirected Request";
  errors["422"] = "Unprocessable Entity (WebDAV)";
  errors["423"] = "Locked (WebDAV)";
  errors["424"] = "Failed Dependency (WebDAV)";
  errors["425"] = "Too Early";
  errors["426"] = "Upgrade Required";
  errors["428"] = "Precondition Required";
  errors["429"] = "Too Many Requests";
  errors["431"] = "Request Header Fields Too Large";
  errors["451"] = "Unavailable For Legal Reasons";


  if (errors.find(error_code) != errors.end())
    std::cout << errors[error_code] << std::endl;
  exit(1);
}

std::map<std::string, std::string> parse_request_line(const char *s){ 
  std::map<std::string, std::string> request;
  const char *head = s;
  const char *tail = s;
  size_t len = strlen(s);
  const char *msg_end = s + len;

  //RFC 7230 3.1.1
  if (len > 8000)
	  throw_error(400);

  // Find request type
  while (tail != msg_end && *tail != ' ') ++tail;
  request["Type"] = std::string(head, tail);

  //RFC 7230 3.1.1
  if (tail - head > 8)
	  throw_error(501);

  
  // Find path
  while (tail != msg_end && *tail == ' ') ++tail;
  head = tail;
  while (tail != msg_end && *tail != ' ') ++tail;
  request["Path"] = std::string(head, tail);

  //RFC 7230 3.1.1
  if (tail - head > 20)
	  throw_error(414);
  
  // Find HTTP version
  while (tail != msg_end && *tail == ' ') ++tail;
  head = tail;
  while (tail != msg_end && *tail != '\r') ++tail;
  request["Version"] = std::string(head, tail);

  return (request);

}

std::map<std::string, std::string> parse_headers(const char *s){ 
  std::map<std::string, std::string> headers;
  std::string header;
  std::string::size_type index;

  std::istringstream resp(s);
  while (std::getline(resp, header) && header != "\r") {
    index = header.find(':', 0);
    if(index != std::string::npos) {
	  std::string key = header.substr(0, index);
	  std::string value = header.substr(index + 1);
	  // RFC 7230, 3.2.4 
	  if (key.find(' ') != std::string::npos)
		  throw_error(400);
      headers.insert(std::make_pair(
        trim(key, ws), 
        trim(value, ws)
      ));
    }
  }

  //RFC 7230 5.4
  if ( headers.find("Host") == headers.end() ) 
	  throw_error(400);

  return (headers);
}


//TODO: implement check for obs fold (RFC 7230, 3.2.4)
//https://stackoverflow.com/questions/31237198/is-it-possible-to-include-multiple-crlfs-in-a-http-header-field/31324422

int main(int argc, char* argv[]) {
  //Random request message here
  const char *s = 
	        "GET / HTTP/1.1\r\n"
			"Host: index/8080"
            "Connection: keep-alive\r\n"
            "Upgrade-Insecure-Requests: 1\r\n"
            "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
            "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_3) AppleWebKit/604.5.6 (KHTML, like Gecko) Version/11.0.3 Safari/604.5.6\r\n"
            "Accept-Language: en-us\r\n"
            "DNT: 1\r\n"
            "Accept-Encoding: gzip, deflate\r\n"
            "\r\n"
            "Usually GET requests don\'t have a body\r\n"
            "But I don\'t care in this case :)";

  
  //TODO: Parse body of the request
  std::map<std::string, std::string> request = parse_request_line(s);
  std::map<std::string, std::string> headers = parse_headers(s);


  //Printing here, causes warnings(C++11). Just for testing purposes.
  for(auto& kv: request) {
    std::cout << "KEY: `" << kv.first << "`, VALUE: `" << kv.second << '`' << std::endl;
  }

  for(auto& kv: headers) {
    std::cout << "KEY: `" << kv.first << "`, VALUE: `" << kv.second << '`' << std::endl;
  }
  return(0);


}
