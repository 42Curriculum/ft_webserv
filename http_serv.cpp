/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_serv.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 15:40:51 by jjosephi          #+#    #+#             */
/*   Updated: 2020/06/01 23:07:39 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


#define PORT 80
int main(int argc, char const *argv[])
{
    int desc_ready, close_conn, end_server = 0;
    int client[30];
    int i, check_socket, rc, len, on, *listen_sd, max_sd, new_sd, size;
    int max_client = 30;
    char buffer[1025];
    struct sockaddr_in *address;
    struct timeval time_out;
	std::vector<Data> servers;
    std::string ss;

	servers = init();
    // set of socket descriptors
    fd_set master_set, working_set;
    
    // Only this line has been changed. Everything is same.
    char hello[] = {"HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!"};
    size = servers.size();
	listen_sd = (int *)malloc(sizeof(int) * size);
	address = (sockaddr_in *)malloc(sizeof(sockaddr_in) * size);
	
    /**************************************************************************/
    /* initialise all client arrays to 0                                      */
    /**************************************************************************/
    for (i = 0; i < max_client; ++i)
    {
        client[i] = 0;
    }
	
	std::cout << "Initialized" << std::endl;
    /**************************************************************************/
    /* Create an AF_INET stream socket to receive incoming connections on     */
    /**************************************************************************/
	for (int n = 0; n < size; n++)
	{
		listen_sd[n] = socket(AF_INET, SOCK_STREAM, 0);
		if (listen_sd[n] == 0)
		{
			perror("socket() failed");
			exit(EXIT_FAILURE);
		}
	}

	std::cout << "AF_INET" << std::endl;
    /**************************************************************************/
    /* Allow socket descriptor to be reuseable                                */
    /**************************************************************************/
	for (int n = 0; n < size; n++)
	{
		rc = setsockopt(listen_sd[n], SOL_SOCKET, SO_REUSEADDR,
                    (char *)&on, sizeof(on));
		if (rc < 0)
		{
			perror("set_socketopt() failed");
			close(listen_sd[n]);
			exit(-1);
		}
	}
	std::cout << "REusable" << std::endl;
    /**************************************************************************/
    /* Set socket to be nonblocking. All of the sockets for the incoming      */
    /* connections will also be nonblocking since they will inherit that      */
    /* state from the listening socket.                                       */
    /**************************************************************************/
	for (int n = 0; n < size; n++)
	{
		rc = ioctl(listen_sd[n], FIONBIO, (char *)&on);
		if (rc < 0)
		{
			perror("ioctl() failed");
			close(listen_sd[n]);
			exit(-1);
		}
	}
	std::cout << "Nonblocking" << std::endl;
    /**************************************************************************/
    /* Bind the socket                                                        */
    /**************************************************************************/
	for (int n = 0; n < size; n++)
	{
		address[n].sin_family = AF_INET;
		address[n].sin_addr.s_addr = INADDR_ANY;
		address[n].sin_port = htons(servers[n].get_port());
		rc = bind(listen_sd[n], (struct sockaddr *)&address[n], sizeof(address[n]));
		if (rc < 0)
		{
			perror("bind() failed");
			close(listen_sd[n]);
			exit(EXIT_FAILURE);
		}
	}
	std::cout << "Bind" << std::endl;
    /**************************************************************************/
    /* Set the listen back log                                                */
    /**************************************************************************/
		
	for (int n = 0; n < size; n++)
	{
		rc = listen(listen_sd[n], 32);
		if (rc < 0)
		{
			perror("listen() failed");
			close(listen_sd[n]);
			exit(EXIT_FAILURE);
		}
	}
	std::cout << "Backlog" << std::endl;
    /**************************************************************************/
    /* Initialize the master fd_set                                           */
    /**************************************************************************/
    FD_ZERO(&master_set);
    max_sd = listen_sd[size - 1];
	for (int n = 0; n < size; n++)
	{
		FD_SET(listen_sd[n], &master_set);
	}

	std::cout << "master_fd" << std::endl;
    /**************************************************************************/
    /* Initialize the time_out to 3 minutes. If no activity after 3 minutes,  */
    /* this program will end                                                  */
    /**************************************************************************/
    time_out.tv_sec = 3 * 60;
    time_out.tv_usec = 0;

    /**************************************************************************/
    /* Loop waiting for incoming connects or for incoming data on any of the  */
    /* connected sockets.                                                     */
    /**************************************************************************/
    do
    {
        /**********************************************************************/
        /* Copy the master fd_set over to the working fd_set.                 */
        /**********************************************************************/
        memcpy(&working_set, &master_set, sizeof(master_set));

        /**********************************************************************/
        /* Call select() and wait 3 minutes for it to complete.               */
        /**********************************************************************/
        std::cout << "Waiting on select()..." << std::endl;
        rc = select(max_sd + 1, &working_set, NULL, NULL, &time_out);

        /**********************************************************************/
        /* Check to see if the select call failed.                            */
        /**********************************************************************/
        if (rc < 0)
        {
            perror(" select() failed");
            break;
        }

        /**********************************************************************/
        /* Check to see if the 3 minute time out expired.                     */
        /**********************************************************************/
        if (rc == 0)
        {
            std::cout << " select() timed out. End program." << std::endl;
            break;
        }

        /**********************************************************************/
        /* One or more descriptors are are readable. Need to determine        */
        /* which ones they are.                                               */
        /**********************************************************************/
        desc_ready = rc;
        for (i = 0; i <= max_sd && desc_ready > 0; ++i)
        {
            // Check to see if this descriptor is ready
            if (FD_ISSET(i, &working_set))
            {
                // A Descriptor was found that was readable - one less has to be
                // lokked for. This is being done so that we can stop looking at
                // the working set once we have found all of the descriptors
                // that were ready.
                desc_ready -= 1;
                // Check to see if this is the listening socket
				for (int n = 0; n < size; n++)
				{
					if (i == listen_sd[n])
					{
						std::cout << " Listening socket is readable" << std::endl;
						// Accept all incoming connections that are qeueued up on the
						// listenning socket before we loop back and call 
						// select again.
						do
						{
							// Accept each incoming conneciton. If accept fails with
							// EWOULDBLOCK, then we have accepted all of them. Any
							// other failure on accept will cause us to end the
							// server.
							new_sd = accept(listen_sd[n], NULL, NULL);
							if (new_sd < 0)
							{
								if (errno != EWOULDBLOCK)
								{
									perror(" accept() failed");
									end_server = 1;
								}
								break;
							}
							// Add the new incoming connections to the
							// master read set
							std::cout << " New incoming connection - ";
							std::cout << std::to_string(new_sd) << std::endl;
							FD_SET(new_sd, &master_set);
							if (new_sd > max_sd)
								max_sd = new_sd;
							// Loop back up and accept another incoming connection
						} while (new_sd != -1);
					}
					// This is not the listening socket, therefore an existing
					// connection must be readable
					else
					{
						std::cout << " Descriptor " << std::to_string(i);
						std::cout << " is readable" << std::endl;
						close_conn = 0;
						// Receive all incoming data on this socket before we loop
						// back and call select again.
						do
						{
							// Receive data on this connection until the recv
							// fails with EWOULDBLOCK. If any other failure
							// occurs, we will close the connection.
							rc = recv(i, buffer, sizeof(buffer), 0);
							if (rc < 0)
							{
								if (errno != EWOULDBLOCK)
								{
									perror(" recv() failed");
									close_conn = 1;
								}
								break;
							}

							// CHeck to see if the connection has been closed
							// by the client
							if (rc == 0)
							{
								std::cout << " Connection closed" << std::endl;
								close_conn = 1;
								break;
							}

							// Data was received
							len = rc;
							std::cout << " " << std::to_string(len);
							std::cout << " bytes received" << std::endl;

							// Echo the data back to the client
							rc = send(i, buffer, len, 0);
							if (rc < 0)
							{
								perror(" send() failed");
								close_conn = 1;
								break;
							}
						} while (1);

						// If the close_conn flag was turned on, we need to clean up
						// this active connection. This clean up process includes
						// removing the descriptor from the master set and
						// determining the new maximum descriptor value based on
						// the bits that are still turned on in the master set.
						if (close_conn)
						{
							close(i);
							FD_CLR(i, &master_set);
							if (i == max_sd)
							{
								while (FD_ISSET(max_sd, &master_set) == 0)
									max_sd -= 1;
							}
						}
					} // End of existing connection is readable
				}
            } // End of if (FD_ISSET(i, &working_set))
        } // End of loop through selectable descriptors
    } while (end_server == 0);
}