/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slct_loop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 14:16:51 by jjosephi          #+#    #+#             */
/*   Updated: 2020/06/03 14:16:51 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void slct_loop(t_loop_data* data)
{
	int desc_ready, close_conn, end_server = 0, rc, len;
	int selected;
	int max_fd;
	char buffer[1025];
	std::vector<int> accepted;
	/**************************************************************************/
    /* Loop waiting for incoming connects or for incoming data on any of the  */
    /* connected sockets.                                                     */
    /**************************************************************************/
    while (end_server == 0)
    {
        /**********************************************************************/
        /* Copy the master fd_set over to the working fd_set.                 */
        /**********************************************************************/
		//FD_ZERO(&data->working_set);
        memcpy(&data->working_set, &data->master_set, sizeof(data->master_set));

        /**********************************************************************/
        /* Call select() and wait 3 minutes for it to complete.               */
        /**********************************************************************/
        std::cout << "Waiting on select()..."  << std::to_string(data->listen_sd->operator[](1) + 1) << std::endl;
        rc = select(data->listen_sd->operator[](data->size - 1) + 1, &data->working_set, NULL, NULL, &data->time_out);

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
		std::cout << "Loop" << std::endl;
        for (int i = 0; i <= data->size && desc_ready > 0; ++i)
        {
            // Check to see if this descriptor is ready
            if (FD_ISSET(data->listen_sd->operator[](i), &data->working_set))
            {
                // A Descriptor was found that was readable - one less has to be
                // lokked for. This is being done so that we can stop looking at
                // the working set once we have found all of the descriptors
                // that were ready.
                desc_ready -= 1;
                // Check to see if this is the listening socket
				// for (int n = 0; n < size; n++)
				// {
				// 	if (i == data->listen_sd->operator[](n))
				// 	{
				// 		std::cout << " Listening socket is readable" << std::endl;
				// 		// accepted all incoming connections that are qeueued up on the
				// 		// listenning socket before we loop back and call 
				// 		// select again.
						// do
						// {
							// accepted each incoming conneciton. If accepted fails with
							// EWOULDBLOCK, then we have accepteded all of them. Any
							// other failure on accepted will cause us to end the
						// server.
				int tmp = 0;
				for (int n = 0;(tmp = accept(data->listen_sd->operator[](n), NULL, NULL)) > 0; n++)
				{
					std::cout << "Accepted fd... "  << std::to_string(tmp) << std::endl;
					accepted.push_back(tmp);
					if (accepted.operator[](n) < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror(" accepted() failed");
							end_server = 1;
						}
						break;
					}
								// Add the new incoming connections to the
								// master read set
					std::cout << " New incoming connection - ";
					std::cout << std::to_string(accepted.operator[](n)) << std::endl;
					FD_SET(accepted.operator[](n), &data->working_set);
								// Loop back up and accepted another incoming connection
						// 	} while (accepted.operator[](n) != -1);
						// }
						// // This is not the listening socket, therefore an existing
						// // connection must be readable
						// else
						// {
						// 	std::cout << " Descriptor " << std::to_string(i);
					std::cout << " is readable" << std::endl;
					close_conn = 0;
							// Receive all incoming data on this socket before we loop
							// back and call select again.
						// Receive data on this connection until the recv
						// fails with EWOULDBLOCK. If any other failure
						// occurs, we will close the connection.
					rc = recv(accepted.operator[](n), buffer, sizeof(buffer), MSG_DONTWAIT);
					std::cout << "Accepted..."  << std::string(buffer) << std::endl;
					if (rc < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror(" recv() failed");
							close_conn = 1;
						}
						break;
					}
					// Check to see if the connection has been closed
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
					rc = send(accepted.operator[](n), buffer, len, 0);
					if (rc < 0)
					{
						perror(" send() failed");
						close_conn = 1;
						break;
					}
					std::cout << "Reply" << std::endl;
					memset(buffer, 0, sizeof(buffer));
				}
				
				std::cout << "Success" << std::endl;

				// If the close_conn flag was turned on, we need to clean up
				// this active connection. This clean up process includes
				// removing the descriptor from the master set and
				// determining the new maximum descriptor value based on
				// the bits that are still turned on in the master set.
				if (close_conn)
				{
					//close(i);
					FD_CLR(i, &data->working_set);
					// if (i == data->size)
					// {
					// 	while (FD_ISSET(data->size, &data->working_set) == 0)
					// 		data->size -= 1;
					// }
				}
				// } // End of existing connection is readable
			}
        } // End of if (FD_ISSET(i, &working_set))
    } // End of loop through selectable descriptors
}