/**
 * @file exec.c
 * @brief TODO.
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "exec.h"


static void show_tag(
        const char * const tag)
{
    if(tag != NULL)
    {
        (void) fprintf(
                stdout,
                "on-tag '%s'\n",
                tag);
    }
}


static void do_command(
        const on_tag_data_s * const on_tag_data)
{
    if(on_tag_data->cmd != NULL)
    {
        if(on_tag_data->verbose != 0)
        {
            (void) fprintf(
                    stdout,
                    "exec command '%s'\n",
                    on_tag_data->cmd);
        }

        (void) system(on_tag_data->cmd);
    }
}


int exec_is_allowed(
        const char * const tag,
        const on_tag_data_s * const on_tag_data)
{
    int ret = EXEC_STATUS_DENIED;

    if((tag != NULL) && (on_tag_data != NULL))
    {
        if(on_tag_data->src_tag != NULL)
        {
            const int diff = strncmp(
                    tag,
                    on_tag_data->src_tag,
                    on_tag_data->tag_size);
            if(diff == 0)
            {
                ret = EXEC_STATUS_ALLOWED;
            }
        }
        else
        {
            ret = EXEC_STATUS_ALLOWED;
        }
    }

    return ret;
}


void exec_on_tag(
        const char * const tag,
        const on_tag_data_s * const on_tag_data)
{
    if((tag != NULL) && (on_tag_data != NULL))
    {
        if(on_tag_data->verbose != 0)
        {
            show_tag(tag);
        }

        const int status = exec_is_allowed(
                tag,
                on_tag_data);
        if(status == EXEC_STATUS_ALLOWED)
        {
            do_command(on_tag_data);
        }
    }
}
