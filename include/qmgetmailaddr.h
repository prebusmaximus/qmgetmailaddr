/*
 * qmgetmailaddr - Provide list of email users on a system based on qmail mta.
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

#ifndef QMGETMAILADDR_H
#define QMGETMAILADDR_H

//
// Includes libraries need to run the program
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>
#include <sys/types.h>
#include <pwd.h>
#include <ctype.h>

//
// Setting defines for the program
//
#define DELIM ":" /* Delilmiter for the assign file */
#define QMAILU "qmaild" /* Qmail user */
#define VPOPMAILU "vpopmail" /* Vpopmail user */
#define VERSION "0.5b" /* Program version */

//
// Declaring functions
//
void printusage(void);
int displayaddr(char[], char[]);
int getdomainpath(char[]);
int checkvpopmailmysql (void);
int fileexists(const char*);
static error_t parse_opt (int, char, struct argp_state);

//
// Declaring global variables for use in entire program.
//
struct passwd *p;
struct passwd *v;
char assignpath[256];
char assignpathvpopmail[256];
char exportfn[256];
FILE *assign_fp;

//
// Declaring argp options
//
const char *argp_program_version = "qmgetmailaddr 0.5b";
const char *argp_program_bug_address = "preben.tonnessen@gmail.com";
static char doc[] = "Tiny program to provide list of email users on a system based on the qmail mta with vpopmail installed as management for virtual domains.";
static char args_doc[] = "ARG";

//
// Program options we accept.
//
static struct argp_option options[] = {
    {"all", 'a',        0,              0, "Displays all mailadresses on the system" },
    {"domain", 'd',     "DOMAIN",       0, "Displays all mailadresses for specified domain" },
    {"exclude", 'e',    "ACCOUNT",      0, "Exclude display of accounts with this name" },
    {"mysql", 'm',      "CONFIG_FILE",  0, "Use mysql to fetch information"},
    {"output", 'o',     "FILE",         0, "Output results to file specified" },
    { 0 }
};

struct arguments {
    char *args[1];
    int all, domain, exclude, output, mysql;
    char *domain_name;
    char *excluden;
    char *output_file;
    char *vpopmysql_file;
};

//
// Our ARGP parser
//
static struct argp argp = { options, parse_opt, args_doc, doc };

/*  Description of options for arguments of the program.
    fprintf(stderr, "qmgetmailaddr, version %s\n\n", VERSION);
    fprintf(stderr, "Usage: getmailaddr [-ah] [-d domain.tld] [-e excludename]\n\n");
    fprintf(stderr, "\t--help, -h\t - Displays this screen\n");
    fprintf(stderr, "\t--all, -a\t - Displays all mailadresses on the system\n");
    fprintf(stderr, "\t--domain, -d\t - Displays all mailadresses for specified domain\n");
    fprintf(stderr, "\t--exclude, -e\t - Exclude display of accounts with this name\n\n");
    fprintf(stderr, "\t--all is assumed if no arguments is given...\n");
    fprintf(stderr, "\t--all and --domain cannot be combined in search...\n\n");
    fprintf(stderr, "Copyright (C) 2006-2018 Preben Holm Tønnessen\n\n");
*/

#endif /* qmgetmailaddr.h */