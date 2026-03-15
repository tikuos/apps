/*
 * Tiku Operating System
 * http://tiku-os.org
 *
 * Authors: Ambuj Varshney <ambuj@tiku-os.org>
 *
 * tiku_cli_cmd_ps.c - "ps" command implementation
 *
 * Walks the process linked list and prints each active process
 * with its name and running status.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*---------------------------------------------------------------------------*/
/* INCLUDES                                                                  */
/*---------------------------------------------------------------------------*/

#include "tiku_cli_cmd_ps.h"
#include <apps/cli/tiku_cli.h>             /* CLI_PRINTF via tiku_cli_io.h */
#include <kernel/process/tiku_process.h>

/*---------------------------------------------------------------------------*/
/* COMMAND IMPLEMENTATION                                                    */
/*---------------------------------------------------------------------------*/

void
tiku_cli_cmd_ps(uint8_t argc, const char *argv[])
{
    struct tiku_process *p;
    uint8_t count = 0;

    (void)argc;
    (void)argv;

    CLI_PRINTF("PID  NAME             STATE\n");
    CLI_PRINTF("---  ---------------  -------\n");

    for (p = tiku_process_list_head; p != NULL; p = p->next) {
        count++;
        CLI_PRINTF("%3u  %s", count,
                    p->name ? p->name : "(null)");
        CLI_PRINTF("  %s\n",
                    p->is_running ? "running" : "stopped");
    }

    CLI_PRINTF("---\n");
    CLI_PRINTF("%u process(es) active\n", count);
    CLI_PRINTF("Event queue: %u/%u\n",
                tiku_process_queue_length(), TIKU_QUEUE_SIZE);
}
