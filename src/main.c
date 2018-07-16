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
// Inkluderer bibliotek som er n�dvendige for at programmet skal kunne kj�re
// 
#include "qmgetmailaddr.h"

/*
 * 
 * Hoved funksjonen som kj�res aller f�rst i programmet,
 * denne tar seg ogs� av � initialisere alle variabler og innstillinger
 * som programmet trenger for � f� gjort jobben sin.
 * 
 */
int main (int argc, char *argv[])
{
   //
   // Deklarerer variabler for bruk i funksjonen
   // 
   int    i;
   int    display;
   
   //
   // Feils�ker at brukeren for qmail eksisterer slik at vi kan hente ut
   // sti til hvor assign fila for brukere er.
   //
   p = getpwnam(QMAILU);   
   if (!p)
   {
      // Vi kunne ikke hente informasjon om brukeren, gi en feilmelding og avslutt deretter programmet
      fprintf(stderr, "qmgetmailaddr failed: Could'nt locate the qmail user (%s)....\n", QMAILU);
      exit( EXIT_FAILURE );
   }
   else
   {
      //
      // Vi klarte � hente ut informasjon om qmailbrukeren, da m� vi klargj�re stien til brukerfilen. Og, �pne
      // filen slik at dette er klargjort til funksjoner som evt. skal benytte seg av denne.
      // 
      strcpy(assignpath, p->pw_dir);
      strcat(assignpath, "/users/assign");
      assign_fp = fopen(assignpath, "r");
      if (!assign_fp)
      {
	 //
	 // Vi klarte ikke � �pne filen med brukerdata, avslutt og gi en feilmelding
	 //
	 fprintf(stderr, "qmgetmailaddr failed: Could'nt open the file %s for read access (Permission denied?)...\n", assignpath);
	 exit( EXIT_FAILURE );
      }
   }   	

   //
   // Sjekker argumenter som er blitt sendt til programmet.
   //
   if ((argc-1) == 0)
   {
      //
      // Ingen argumenter er blitt sendt til programmet, setter da igang � hente ut ALLE e-postadresser.
      //
      getdomainpath("");      
   }
   else
   {
      display = 0;
      
      //
      // Det ble sendt argumenter til programmet, da m� vi til � parse litt... :)
      //
      for (i = 1; i <= (argc-1); i++)
      {
	 if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0)
	 {
	    display = display+1;
	 }
	 else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--domain") == 0)
	 {
	    display = display+2;
	    i++;
	    if (argv[i])
	    {		 
	       if (strcmp(argv[i], "-e") != 0 && strcmp(argv[i], "--exclude") != 0 &&
		   strcmp(argv[i], "-a") != 0 && strcmp(argv[i], "--all") != 0 &&
		   strcmp(argv[i], "-d") != 0 && strcmp(argv[i], "--domain") != 0 &&
		   strcmp(argv[i], "-h") != 0 && strcmp(argv[i], "--help") != 0 &&
		   strcmp(argv[i], "") != 0)
	       {
		  strcpy(domene, argv[i]);
	       }
	    }	    
	    else
	    {
	       fprintf(stderr, "qmgetmailaddr failed: Missing domain...\n\n");
	       printusage();
	       exit( EXIT_FAILURE );
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
	       exit( EXIT_FAILURE );
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
	       exit( EXIT_FAILURE );
	    }	    	    
	 }	 
	 else
	 {
	    printusage();
	    exit( EXIT_SUCCESS );
	 }
      }
      
      if (display == 1)
      {
	 getdomainpath("");
      }
      else if (display == 2)
      {
	 getdomainpath(domene);
      }
      else if (display == 3)
      {
	 fprintf(stderr, "qmgetmailaddr failed: You cannot run -a and -d at the same time...\n\n");
	 printusage();
	 exit( EXIT_FAILURE );
      }
      else
      {
	 if (!excluden)
	 {	      
	    printusage();
	    exit( EXIT_SUCCESS );
	 }
	 else
	   getdomainpath("");
      }
   }   	
   
   //
   // Rydde opp litt etter oss...
   //
   fclose(assign_fp);

   return EXIT_SUCCESS;
}
