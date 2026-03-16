/*
 * Tiku Operating System
 * http://tiku-os.org
 *
 * Authors: Ambuj Varshney <ambuj@tiku-os.org>
 *
 * tiku_cli.h - Interactive command-line interface (public types and API)
 *
 * The CLI is transport-agnostic: all I/O flows through the pluggable
 * backend in tiku_cli_io.h (UART today, network / LLM channel later).
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

#ifndef TIKU_CLI_H_
#define TIKU_CLI_H_

/*---------------------------------------------------------------------------*/
/* INCLUDES                                                                  */
/*---------------------------------------------------------------------------*/

#include "tiku.h"
#include "tiku_cli_io.h"       /* CLI_PRINTF, I/O backend API */
#include <stdint.h>

/*---------------------------------------------------------------------------*/
/* CONFIGURATION                                                             */
/*---------------------------------------------------------------------------*/

/** Maximum characters in a single input line */
#define TIKU_CLI_LINE_SIZE  64

/** Maximum number of space-separated arguments per command */
#define TIKU_CLI_MAX_ARGS   8

/** I/O poll interval (ticks). TIKU_CLOCK_SECOND/20 ~ 50 ms */
#define TIKU_CLI_POLL_TICKS (TIKU_CLOCK_SECOND / 20)

/*---------------------------------------------------------------------------*/
/* TYPES                                                                     */
/*---------------------------------------------------------------------------*/

/**
 * @brief Command handler function signature
 *
 * @param argc  Number of arguments (including the command name)
 * @param argv  Argument strings (argv[0] is the command name)
 */
typedef void (*tiku_cli_handler_t)(uint8_t argc, const char *argv[]);

/**
 * @brief Command table entry
 *
 * A sentinel entry with name == NULL marks the end of the table.
 */
typedef struct {
    const char *name;               /**< Command name (typed by user) */
    const char *help;               /**< One-line description */
    tiku_cli_handler_t handler;     /**< Handler function */
} tiku_cli_cmd_t;

/*---------------------------------------------------------------------------*/
/* PUBLIC API                                                                */
/*---------------------------------------------------------------------------*/

/**
 * @brief Return the NULL-terminated command table.
 *
 * Useful for commands (like "help") that need to enumerate all
 * registered commands.
 */
const tiku_cli_cmd_t *tiku_cli_get_commands(void);

/** The CLI process (defined in tiku_cli.c) */
extern struct tiku_process tiku_cli_process;

#endif /* TIKU_CLI_H_ */
