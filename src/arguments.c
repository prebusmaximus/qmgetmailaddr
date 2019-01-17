/*
* qmgetmailaddr - Provide list of email users on a system based on qmail mta.
*
* Copyright (C) 2006-2019 Preben Holm Tønnessen
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
#ifndef QMGETMAILADDR_H
#include "qmgetmailaddr.h"
#endif

error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    //
    // Retrieve input arguments from argp_parse, which we know is a pointer
    // to our arguments structure
    //
    struct arguments *arguments = state->input;

    switch (key)
    {
        case 'a':
            arguments->all = 1;
            break;

        case 'd':
            arguments->domain_name = arg;
            printf("ARG1 = %s\n", arg);            
            break;

        case 'e':
            arguments->exclude = 1;
            arguments->exclude_name = arg;
            break;

        case 'o':
            arguments->output_file = arg;
            break;

        case 'm':
            arguments->mysql = 1;
            arguments->vpopmysql_file = arg;
            break;

        case ARGP_KEY_ARG:
            if (state->arg_num >= 1) argp_usage(state);
            arguments->args[state->arg_num] = arg;            
            break;

        case ARGP_KEY_END:
            if (state->arg_num < 1) argp_usage (state);
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}