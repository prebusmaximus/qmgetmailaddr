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
#include <mysql/mysql.h>

//
// Setting defines for the program
//
#define DELIM ":" /* Delimiter for the assign file */
#define MYSQL_DELIM "|" /* Delimiter for the mysql config file */
#define QMAILU "qmaild" /* Qmail user */
#define VPOPMAILU "vpopmail" /* Vpopmail user */
#define VERSION "0.5b" /* Program version */

//
// Declaring functions
//
int displayaddr (char path[], char domain[]);
int getdomainpath (char[]);
int checkvpopmailmysql (void);
int fileexists (const char* filename);
error_t parse_opt (int key, char *arg, struct argp_state *state);

//
// Declaring global variables for use in entire program.
//
struct passwd *p;
struct passwd *v;
char assignpath[256];
char assignpathvpopmail[256];
char exportfn[256];
FILE *assign_fp;
struct arguments arguments;
MYSQL *mysql_conn;
MYSQL_RES *mysql_res;
MYSQL_ROW mysql_row;

struct mysql_cInfo {
    char *server;
    char *username;
    char *password;
    char *database;
};

struct arguments {
    char *args[1];
    int all, domain, exclude, output, mysql;
    char *domain_name;
    char *exclude_name;
    char *output_file;
    char *vpopmysql_file;
};

#endif /* qmgetmailaddr.h */