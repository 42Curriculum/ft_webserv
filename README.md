# Webserver
## IMPORTANT : This server uses system() for POST, PUT and DELETE requests, and therefore is NOT SECURE.

In this project we learn a little bit of networking and socket programming. The goal is to implement a sever that is able to take various kind of requests.

This project was done for learning purposes only, and in a bit of a rush so beware.

There is not much to this readme, so here are some notes and logs from the project

```
There is still a lot to do...
Most of the parsing could use with some more error checking.
I have yet to test if the error pages are handled correctly, but for that I need to create default erro pages first
Tomorrow if I don't spend my time doing math, I will look at CGI and create the erro pages (this second bit shouldmt take long, although I don't have internet to find examples)
I might also work on limiting body size, although as of now I am not quite sure what that means.
Need to talk to the group about the default parameters and update them on my progress and define a course of action since internet will be down for 3 more days.
Time is running out


---------------------------------------------------------------------------

THoughts about error pages :
	Since we need default error pages anyways, I migth as well just have an int,str map with
the error and its default value and change it if needed when parsing. It seems like the best solutio but I have to think about it more.
Need to talk about all the other default values. Can't wait to be done and work on my own things
~~Impossible to find one decent example of error page, everything is stupid feelsgood pages with too much embelisshment. Also impossible to inspect
standard error page from my phone. I will delegate this task to someone that has access to a computer.
I guess now I need to work on CGI and body_size

--------------------------------------------------------------------------

I now understand everything about webserver. Plan is as follows :

Today :
	-Improve the parsing, it is incomplete at best. <- fakew news, request parsing is fine. COnfig parsing can be improved still
	-Inplement the methods : []GET []POST []HEAD []PUT []DELETE []CONNECT []OPTIONS []TRACE
Tomorrow :
	- Work on return message ;
	- Implement CGI
	- Rest of the stuff under the config part part of the pdf

Please discard the above. Started working on response as I realized that implementing the methods implies implementing response;

FOr the error pages, I'm debating whether I should make a map of every single error and their path
and replace the ones specified in the config file or make a map with only what is specified.
-----------------------------------------------------------------------------
Decided to go with the first option. I am done for my part, however,I am using system for post, put and delete request... which is less than secure
Need to add scurity warning to readme. Might fix it later, but most likely not, I have other things to do.
```

### Warning For 42 Students

This is not kept up to date and I cannot guarantee that it will work on your future machines. You are welcome to use and learn from this as you want, but do not implement code that you do not understand.

