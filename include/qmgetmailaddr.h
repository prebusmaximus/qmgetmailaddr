/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) <year> <name of author
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
// Inkluderer bibliotek som er n�dvendige for at programmet skal kunne kj�re
// 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <ctype.h>

//
// Setter opp definerte variabler
// 
#define  DELIM     ":"
#define  QMAILU    "qmaild"
#define  VERSION   "0.3 beta"

//
// Deklarerer funksjoner
// 
void printusage (void);
int  displayaddr (char[], char[]);
int  getdomainpath (char[]);

//
// Deklarerer globale variabler
//
struct   passwd   *p;
char     domene[63];
char     assignpath[256];
char     excluden[256];
char     exportfn[256];
FILE     *assign_fp;

