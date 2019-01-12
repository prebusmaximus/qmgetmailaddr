/*
* qmgetmailaddr - Provice list of email users on a system based on qmail mta.
*
* Copyright (C) 2006-2018 Preben Holm Tønnessen
*
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the Free
* Software Foundation, either version 3 of the License, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along with
* this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//
// Includes libraries need to run the application
//
#include "qmgetmailaddr.h"

/*
* 
* Main function, first running in the application. The main function
* deals with initalizing all variables and settings need for the application.
* 
*/
int main(int argc, char **argv)
{
	//
	// Main declaration
	//
	int i;
	int display;
	int usemysql = 1;

	//
	// Declare default values for arguments
	//
	arguments.all = 0;
	arguments.domain = 0;
	arguments.exclude = 0;
	arguments.output = 0;
	arguments.mysql = 0;

	//
	// Calling function to parse arguments
	//
	arg_parse(&argp, argc, argv, 0, 0, &arguments);

	//
	// Checking for path and existence of the user VPOPMAIL, without VPOPMAIL program fails.
	//
	v = getpwnam(VPOPMAILU);
	if (!v)
	{
		// Could not fetch path for the VPOPMAIL user
		fprintf(stderr, "qmgetmailaddr failed: vpopmail user missing (%s)....\n", VPOPMAILU);
		exit(EXIT_FAILURE);
	}

	//
	// Check for existance of mysql configuration on vpopmail
	//
	if (checkvpopmailmysql())
	{
		usemysql = 0;
		fprintf(stderr, "qmgetmailaddr failed: Userdatabase for vpopmail users on MySQL server, not able to fetch users...\n");
		exit(EXIT_FAILURE);
	}

	//
	// Checking for path of the QMAIL user in order to get the correct path of the assign file from
	// qmail.
	//
	p = getpwnam(QMAILU);
	if (!p)
	{
		// Could not fetch folder location, reply with error and exit application.
		fprintf(stderr, "qmgetmailaddr failed: Could'nt locate the qmail user (%s)....\n", QMAILU);
		exit(EXIT_FAILURE);
	}
	else
	{
		//
		// Succesfully got the information on the qmail users, lets make the path correct for the userfile and open
		// the file for further functions and stuff...
		//
		strcpy(assignpath, p->pw_dir);
		strcat(assignpath, "/users/assign");
		assign_fp = fopen(assignpath, "r");
		if (!assign_fp)
		{
			//
			// Could not open file containing userdata, exit application and return error
			//
			fprintf(stderr, "qmgetmailaddr failed: Could'nt open the file %s for read access (Permission denied?)...\n", assignpath);
			exit(EXIT_FAILURE);
		}
	}

	//
	// Check command line arguments.
	//
	if ((argc - 1) == 0)
	{
		//
		// No arguments sent to application, starting procedure to fetch ALL e-mailaddresses on the system.
		//
		getdomainpath("");
	}
	else
	{
		if (arguments.domain == 1 && arguments.all == 1)
		{
			fprintf(stderr, "qmgetmailaddr failed: You cannot run -a and -d at the same time...\n\n");
			printusage();
			exit(EXIT_FAILURE);
		}
		else if (arguments.domain == 1 && arguments.all == 0)
		{
			getdomainpath(arguments.domain_name);
		}
		else if (arguments.domain == 0 && arguments.all == 1)
		{
			getdomainpath("");
		}
	}

	//
	// Do some cleaning :-)
	//
	fclose(assign_fp);

	return EXIT_SUCCESS;
}
