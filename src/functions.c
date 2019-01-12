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

int getdomainpath(char domainarg[])
{
    //
    // Declaring variables
    //
    char domain[63];
    char domainpath[256];
    char *sep;
    char buffer[4096];
    int i;

    while (fgets(buffer, sizeof(buffer), assign_fp) != NULL)
    {
        sep = strtok(buffer, DELIM);
        i = 1;

        while ((sep = strtok(NULL, DELIM)) != NULL)
        {
            switch (i)
            {
            case 1:
                strcpy(domain, sep);
                break;

            case 4:
                strcpy(domainpath, sep);
                break;
            }
            i++;
        }

        if (strcmp(domainarg, "") != 0)
        {
            if (strcmp(domain, domain) == 0)
            {
                displayaddr(domainpath, domain);
            }
        }
        else
        {
            displayaddr(domainpath, domain);
        }
    }

    return EXIT_SUCCESS;
}

int displayaddr(char path[], char domain[])
{
    //
    // Declaring variables
    //
    FILE *fp;
    char buffer[4096];
    char fpath[256];
    char *sep;

    // Fix path in order to open vpopmail passwords file.
    strcpy(fpath, path);
    strcat(fpath, "/vpasswd");

    //
    // Open the vpopmail passwords file.
    //
    fp = fopen(fpath, "r");
    if (fp)
    {
        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            sep = strtok(buffer, DELIM);
            if (strcmp(sep, arguments.excluden) != 0)
                printf("%s@%s\n", sep, domain);
        }
        fclose(fp);
    }
    else
    {
        fprintf(stderr, "qmgetmailaddr failed: Could'nt open userdatabase (%s)\n", path);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

void printusage(void)
{
    fprintf(stderr, "qmgetmailaddr, version %s\n\n", VERSION);
    fprintf(stderr, "Usage: getmailaddr [-ah] [-d domain.tld] [-e excludename]\n\n");
    fprintf(stderr, "\t--help, -h\t - Displays this screen\n");
    fprintf(stderr, "\t--all, -a\t - Displays all mailadresses on the system\n");
    fprintf(stderr, "\t--domain, -d\t - Displays all mailadresses for specified domain\n");
    fprintf(stderr, "\t--exclude, -e\t - Exclude display of accounts with this name\n\n");
    fprintf(stderr, "\t--all is assumed if no arguments is given...\n");
    fprintf(stderr, "\t--all and --domain cannot be combined in search...\n\n");
    fprintf(stderr, "Copyright (C) 2006-2018 Preben Holm Tønnessen\n\n");
}

//
// Function to check for mysql support in vpopmail
//
int checkvpopmailmysql (void)
{
    //
    // Declare variables
    //
    char fpath[256];

    // Fix path to vpopmail.mysql config
    strcpy(fpath, v->pw_dir);
    strcat(fpath, "/etc/vpopmail.mysql");

    if (!fileexists(fpath))
        return 0;

    return 1;
}

//
// Function to check for file existence
//
int fileexists(const char* filename)
{
    FILE *file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return 1;
    }

    return 0;
}