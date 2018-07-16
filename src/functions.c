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
// Inkluderer bibliotek som er nødvendige for at programmet skal kunne kjøre
// 
#include "qmgetmailaddr.h"

int getdomainpath (char domenearg[])
{
   // 
   // Variabler for bruk i funksjonen
   // 
   char domene[63];
   char domenesti[256];
   char *sep;
   char buffer[4096];
   int  i;
   
   while (fgets(buffer, sizeof(buffer), assign_fp) != NULL)
   {
      sep = strtok(buffer, DELIM);
      i   = 1;
      
      while ( (sep = strtok(NULL, DELIM)) != NULL)
      {
	 switch (i)
	 {
	  case 1:
	    strcpy(domene, sep);
	    break;
	    
	  case 4:
	    strcpy(domenesti, sep);
	    break;
	 }
	 i++;
      }
      
      if (strcmp(domenearg, "") != 0)
      {
	 if (strcmp(domene, domenearg) == 0)
	 {
	    displayaddr(domenesti, domene);	    
	 }	 
      }
      else
      {
	 displayaddr(domenesti, domene);
      }      	   
   }   	
   
   return EXIT_SUCCESS;
}

int displayaddr (char path[], char domene[])
{
   //
   // Variabler for bruk i funksjonen
   // 
   FILE *fp;
   char buffer[4096];
   char fpath[256];
   char *sep;
   
   // Ordne path, slik at vi kan åpne filen med brukernavnene i
   strcpy(fpath, path);
   strcat(fpath, "/vpasswd");
   
   //
   // Åpne filen med brukernavnene i
   //
   fp = fopen(fpath, "r");
   if (fp)
   {
      while (fgets(buffer, sizeof(buffer), fp) != NULL)
      {
	 sep = strtok(buffer, DELIM);
	 if (strcmp(sep, excluden) != 0)
	   printf("%s@%s\n", sep, domene);
      }
      fclose(fp);
   }
   else
   {
      fprintf(stderr, "qmgetmailaddr failed: Could'nt open userdatabase (%s)\n", path);
      exit( EXIT_FAILURE );
   }
   
   return EXIT_SUCCESS;
}

void printusage (void)
{
   fprintf(stderr, "qmgetmailaddr, version %s\n\n", VERSION);
   fprintf(stderr, "Usage: getmailaddr [-ah] [-d domain.tld] [-e excludename]\n\n");
   fprintf(stderr, "\t--help, -h\t - Displays this screen\n");
   fprintf(stderr, "\t--all, -a\t - Displays all mailadresses on the system\n");
   fprintf(stderr, "\t--domain, -d\t - Displays all mailadresses for specified domain\n");
   fprintf(stderr, "\t--exclude, -e\t - Exclude display of accounts with this name\n\n");
   fprintf(stderr, "\t--all is assumed if no arguments is given...\n");
   fprintf(stderr, "\t--all and --domain cannot be combined in search...\n\n");
   fprintf(stderr, "Copyright (C) 2005, IT PAYS AS, http://www.itpays.no\n\n");
}
