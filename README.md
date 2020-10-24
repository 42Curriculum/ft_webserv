# Webserver
## IMPORTANT : This server uses system() for POST, PUT and DELETE requests, and therefore is NOT SECURE.

## Introduction	
The Hypertext Transfer Protocol (HTTP) is an application protocol for distributed, collaborative, hypermedia information systems.	
HTTP is the foundation of data communication for the World Wide Web, where hypertext documents include hyperlinks to other resources that the user can easily access, for example by a mouse click or by tapping the screen in a web browser.	
HTTP was developed to facilitate hypertext and the World Wide Web.	
The primary function of a web server is to store, process, and deliver web pages to clients.	
The communication between client and server takes place using the Hypertext Transfer Protocol (HTTP).	

Pages delivered are most frequently HTML documents, which may include images, style sheets, and scripts in addition to the text content.	

Multiple web servers may be used for a high traffic website.	

A user agent, commonly a web browser or web crawler, initiates communication by making a request for a specific resource using HTTP and the server responds with the content of that resource or an error message if unable to do so. The resource is typically a real file on the server's secondary storage, but this is not necessarily the case and depends on how the webserver is implemented.	

While the primary function is to serve content, full implementation of HTTP also includes ways of receiving content from clients. This feature is used for submitting web forms, including uploading of files.	

## Instructions	
Make sure you have the needed [dependencies](#dependencies) before proceeding.	
For instructions and/or greater detail refer to the project [pdf][pdf]	
## Mandatory part	
It must be conditionally compliant with the rfc 7230 to 7235 (http 1.1) but you need to implement only the following headers	
- [x] Accept-Charsets	
- [x] Accept-Language	
- [x] Allow	
- [x] Autho4rization	
- [x] Content-Language	
- [x] Content-Length	
- [x] Content-Location	
- [x] Content-Type	
- [x] Date	
- [x] Host	
- [x] Last-Modified	
- [x] Location	
- [x] Referer	
- [x] Retry-After	
- [x] Server	
- [x] Transfer-Encoding	
- [x] User-Agent	
- [x] WWW-Authenticate	

We will consider that nginx is HTTP 1.1 compliant and may be used to compare headers and answer behaviors	
- [x] It must be non-blocking and use only 1 select for all the IO between the client and the server (listens includes). [kosehy]	
- [x] Select should check read and write at the same time.	
- [X] Your server should never block and client should be bounce properly if necessary	
- [x] You should never do a read operation or a write operation without going through select	
- [x] Checking the value of errno is strictly forbidden after a read or a write operation	
- [x] A request to your server should never hang forever	
- [x] Your server should have default error pages if none are provided	
- [x] Your program should not leak and should never crash, even when out of memory if all the initialization is done	
- [x] You can't use fork for something else than CGI (like php or perl or ruby etc...)	
- [x] You can include and use everything in "iostream" "string" "vector" "list" "queue" "stack" "map" "algorithm"	
- [x] Your program should have a config file in argument or use a default path	
- [x] You can only use fcntl as flow: fcntl(fd, F_SETFL, O_NONBLOCK); Any other flags is forbidden	

In the config file, you shoul be able to :	
- [x] choose the port and host of each "server"	
- [x] setup the server_names or not	
- [x] The first server for a host:port will be the default for this host:port (meaning it will answer to all request that doesn't belong to the other server)	
- [x] setup default error pages	
- [x] limit client body size	

## Bonus part	

## Dependencies	
* A C language compiler most codmmon would be GCC or Clang.	
* These were written to run on Unix based systems, it would likely work on a windows machine too but is currently untested.

### Warning For 42 Students

This is not kept up to date and I cannot guarantee that it will work on your future machines. You are welcome to use and learn from this as you want, but do not implement code that you do not understand.

