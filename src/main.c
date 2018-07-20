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
int main(int argc, char *argv[])
{
	//
	// Main declaration
	//
	int i;
	int display;
	int usemysql = 1;

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
		fprintf(stderr, "qmgetmailaddr failed: Userdatabase for vpopmail users MySQL server not able to fetch users...\n");
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
		display = 0;

		//
		// Arguments where sendt to the program, lets do some parsing.
		//
		for (i = 1; i <= (argc - 1); i++)
		{
			if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0)
			{
				display = display + 1;
			}
			else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--domain") == 0)
			{
				display = display + 2;
				i++;
				if (argv[i])
				{
					if (strcmp(argv[i], "-e") != 0 && strcmp(argv[i], "--exclude") != 0 &&
						strcmp(argv[i], "-a") != 0 && strcmp(argv[i], "--all") != 0 &&
						strcmp(argv[i], "-d") != 0 && strcmp(argv[i], "--domain") != 0 &&
						strcmp(argv[i], "-h") != 0 && strcmp(argv[i], "--help") != 0 &&
						strcmp(argv[i], "") != 0)
					{
						strcpy(domain, argv[i]);
					}
				}
				else
				{
					fprintf(stderr, "qmgetmailaddr failed: Missing domain...\n\n");
					printusage();
					exit(EXIT_FAILURE);
				}
			}
			else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--exclude") == 0)
			{
				i++;
				if (argv[i])
				{
					if (strcmp(argv[i], "-e") != 0 && strcmp(argv[i], "--exclude") != 0 &&
						strcmp(argv[i], "-a") != 0 && strcmp(argv[i], "--all") != 0 &&
						strcmp(argv[i], "-d") != 0 && strcmp(argv[i], "--domain") != 0 &&
						strcmp(argv[i], "-h") != 0 && strcmp(argv[i], "--help") != 0 &&
						strcmp(argv[i], "") != 0)
					{
						strcpy(excluden, argv[i]);
					}
				}
				else
				{
					fprintf(stderr, "qmgetmailaddr failed: Missing name to exclude... (Ex. postmaster)\n\n");
					printusage();
					exit(EXIT_FAILURE);
				}
			}
			else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--outputfile") == 0)
			{
				i++;
				if (argv[i])
				{
					if (strcmp(argv[i], "-e") != 0 && strcmp(argv[i], "--exclude") != 0 &&
						strcmp(argv[i], "-a") != 0 && strcmp(argv[i], "--all") != 0 &&
						strcmp(argv[i], "-o") != 0 && strcmp(argv[i], "--outputfile") != 0 &&
						strcmp(argv[i], "-d") != 0 && strcmp(argv[i], "--domain") != 0 &&
						strcmp(argv[i], "-h") != 0 && strcmp(argv[i], "--help") != 0 &&
						strcmp(argv[i], "") != 0)
					{
						strcpy(exportfn, argv[i]);
					}
				}
				else
				{
					fprintf(stderr, "qmgetmailaddr failed: Missing filename for export...\n\n");
					printusage();
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				printusage();
				exit(EXIT_SUCCESS);
			}
		}

		if (display == 1)
		{
			getdomainpath("");
		}
		else if (display == 2)
		{
			getdomainpath(domain);
		}
		else if (display == 3)
		{
			fprintf(stderr, "qmgetmailaddr failed: You cannot run -a and -d at the same time...\n\n");
			printusage();
			exit(EXIT_FAILURE);
		}
		else
		{
			if (!excluden)
			{
				printusage();
				exit(EXIT_SUCCESS);
			}
			else
				getdomainpath("");
		}
	}

	//
	// Do some cleaning :-)
	//
	fclose(assign_fp);

	return EXIT_SUCCESS;
}
