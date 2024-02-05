// SPDX-License-Identifier: BSD-3-Clause

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "cmd.h"
#include "utils.h"

#define READ		0
#define WRITE		1

/**
 * Internal change-directory command.
 */
static bool shell_cd(word_t *dir) {
    char *dir_s = NULL;

    if (dir == NULL) {
        dir_s = getenv("HOME");
        if (dir_s == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
            return true;
        }
    } else {
        dir_s = get_word(dir);
        if (dir_s == NULL) {
            perror("get_word() error");
            return true;
        }
    }

    if (strcmp(dir_s, "-") == 0) {
        char *prev_dir = getenv("OLDPWD");
        if (prev_dir == NULL) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return true;
        }
        dir_s = prev_dir;
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        if (setenv("OLDPWD", cwd, 1) == -1) {
            perror("setenv() error");
        }
    } else {
        perror("getcwd() error");
    }

    if (chdir(dir_s) == -1) {
        perror("cd");
        return true;
    }

    return false;
}

/**
 * Internal exit/quit command.
 */
static int shell_exit(void)
{
	/* TODO: Execute exit/quit. */
	exit(0);
}

/**
 * Parse a simple command (internal, environment variable assignment,
 * external command).
 */
static int parse_simple(simple_command_t *s, int level, command_t *father) {
    /* TODO: Sanity checks. */
    if (s == NULL)
        return -1;

    /* TODO: If builtin command, execute the command. */
    int builtin_result = handle_builtin_commands(s);
    if (builtin_result != -1)
        return builtin_result;

    /* TODO: If variable assignment, execute the assignment and return the exit status. */
    int assignment_result = handle_variable_assignment(s);
    if (assignment_result != -1)
        return assignment_result;

    /* TODO: If external command, fork new process, perform redirections in child,
             load executable in child, wait for child, and return exit status. */
    return execute_external_command(s);
}

static int handle_builtin_commands(simple_command_t *s) {
    if (strcmp(s->verb->string, "exit") == 0 || strcmp(s->verb->string, "quit") == 0)
        return shell_exit();

    /* cd file redirects */
    if (strcmp(s->verb->string, "cd") == 0) {
        if (s->out != NULL) {
            int fd = open(get_word(s->out), O_WRONLY | O_CREAT | (s->io_flags == 1 ? O_APPEND : O_TRUNC), 0644);

            if (fd == -1) {
                perror("open() error");
                return -1;
            }

            if (close(fd) == -1) {
                perror("close() error");
                return -1;
            }
        }

        return shell_cd(s->params);
    }

    return -1;  // Not a builtin command
}

static int handle_variable_assignment(simple_command_t *s) {
    if (s->verb->next_part != NULL) {
        const char *var = s->verb->string;

        if (strcmp(s->verb->next_part->string, "=") == 0) {
            char *value = get_word(s->verb->next_part->next_part);

            if (var == NULL || value == NULL) {
                perror("get_word() error");
                return -1;
            }

            int ret = setenv(var, value, 1);

            if (ret == -1) {
                perror("setenv() error");
                return -1;
            }

            return 0;
        }

        /* Not an environment variable assignment. */
        perror("Invalid command");
        return -1;
    }

    return -1;  // Not a variable assignment
}

static int execute_external_command(simple_command_t *s) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork() error");
        return -1;
    }

    if (pid == 0) {
        /* Child process. */

        // ... Redirections handling ...

        /* Execute command. */
        int size;
        char **argv = get_argv(s, &size);

        if (argv == NULL) {
            perror("get_argv() error");
            return -1;
        }

        int ret = execvp(argv[0], argv);

        if (ret == -1) { /* Command not found. */
            fprintf(stderr, "Execution failed for '%s'\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    /* Parent process. */
    int status;

    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid() error");
        return -1;
    }

    return status; /* TODO: Replace with actual exit status. */
}

/**
 * Process two commands in parallel, by creating two children.
 */
static bool run_in_parallel(command_t *cmd1, command_t *cmd2, int level, command_t *father) {
    /* TODO: Execute cmd1 and cmd2 simultaneously. */
    pid_t pid1 = fork();

    if (pid1 == -1) {
        perror("fork() error");
        return true;
    }

    if (pid1 == 0) {
        /* Child process. */
        int ret = run_command_in_child(cmd1, level + 1, father);
        exit(ret);
    }

    pid_t pid2 = fork();

    if (pid2 == -1) {
        perror("fork() error");
        return true;
    }

    if (pid2 == 0) {
        /* Child process. */
        int ret = run_command_in_child(cmd2, level + 1, father);
        exit(ret);
    }

    /* Parent process. */

    /* Wait for children. */
    int status;

    if (waitpid(pid1, &status, 0) == -1) {
        perror("waitpid() error");
        return true;
    }

    if (waitpid(pid2, &status, 0) == -1) {
        perror("waitpid() error");
        return true;
    }

    return status; /* TODO: Replace with actual exit status. */
}

static bool run_command_in_child(command_t *cmd, int level, command_t *father) {
    int ret = parse_command(cmd, level + 1, father);

    if (ret == -1) {
        perror("parse_command() error");
        return true;
    }

    return false;
}

/**
 * Run commands by creating an anonymous pipe (cmd1 | cmd2).
 */
static bool run_on_pipe(command_t *cmd1, command_t *cmd2, int level,
		command_t *father)
{
	/* TODO: Redirect the output of cmd1 to the input of cmd2. */
	int pipefd[2];

	if (pipe(pipefd) == -1) {
		perror("pipe() error");
		return true;
	}

	pid_t pid1 = fork();

	if (pid1 == -1) {
		perror("fork() error");
		return true;
	}

	if (pid1 == 0) {
		/* Child process. */

		/* Close read end of pipe. */
		if (close(pipefd[READ]) == -1) {
			perror("close() error");
			return true;
		}

		/* Redirect stdout to write end of pipe. */
		if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1) {
			perror("dup2() error");
			return true;
		}

		int ret = parse_command(cmd1, level, father);

		if (ret == -1) {
			perror("parse_command() error");
			return true;
		}

		exit(ret);
	}

	pid_t pid2 = fork();

	if (pid2 == -1) {
		perror("fork() error");
		return true;
	}

	if (pid2 == 0) {
		/* Child process. */

		/* Close write end of pipe. */
		if (close(pipefd[WRITE]) == -1) {
			perror("close() error");
			return true;
		}

		/* Redirect stdin to read end of pipe. */
		if (dup2(pipefd[READ], STDIN_FILENO) == -1) {
			perror("dup2() error");
			return true;
		}

		int ret = parse_command(cmd2, level, father);

		if (ret == -1) {
			perror("parse_command() error");
			return true;
		}

		exit(ret);
	}

	/* Parent process. */

	/* Close read end of pipe. */
	if (close(pipefd[READ]) == -1) {
		perror("close() error");
		return true;
	}

	/* Close write end of pipe. */
	if (close(pipefd[WRITE]) == -1) {
		perror("close() error");
		return true;
	}

	/* Wait for children. */
	int status;

	if (waitpid(pid1, &status, 0) == -1) {
		perror("waitpid() error");
		return true;
	}

	if (waitpid(pid2, &status, 0) == -1) {
		perror("waitpid() error");
		return true;
	}

	return status; /* TODO: Replace with actual exit status. */
}

/**
 * Parse and execute a command.
 */
int parse_command(command_t *c, int level, command_t *father) {
    /* TODO: Implement sanity checks. */
    if (c == NULL)
        return -1;

    int ret;

    switch (c->op) {
    case OP_SEQUENTIAL:
        /* TODO: Execute the commands one after the other. */

        ret = parse_command(c->cmd1, level, father);
        if (ret == -1) {
            fprintf(stderr, "%s error", __func__);
            return -1;
        }

        ret = parse_command(c->cmd2, level, father);
        if (ret == -1) {
            fprintf(stderr, "%s error", __func__);
            return -1;
        }

        break;

    case OP_PARALLEL:
        /* TODO: Execute the commands simultaneously. */

        ret = run_in_parallel(c->cmd1, c->cmd2, level, father);
        if (ret == true) {
            perror("run_in_parallel() error");
            return -1;
        }

        break;

    case OP_CONDITIONAL_NZERO:
        /* TODO: Execute the second command only if the first one
         * returns non-zero.
         */

        ret = parse_command(c->cmd1, level, father);
        if (ret == -1) {
            fprintf(stderr, "%s error", __func__);
            return -1;
        }

        if (ret != 0) {
            ret = parse_command(c->cmd2, level, father);
            if (ret == -1) {
                fprintf(stderr, "%s error", __func__);
                return -1;
            }
        }

        break;

    case OP_CONDITIONAL_ZERO:
        /* TODO: Execute the second command only if the first one
         * returns zero.
         */

        ret = parse_command(c->cmd1, level, father);
        if (ret == -1) {
            fprintf(stderr, "%s error", __func__);
            return -1;
        }

        if (ret == 0) {
            ret = parse_command(c->cmd2, level, father);
            if (ret == -1) {
                fprintf(stderr, "%s error", __func__);
                return -1;
            }
        }

        break;

    case OP_PIPE:
        /* TODO: Redirect the output of the first command to the
         * input of the second.
         */

        ret = run_on_pipe(c->cmd1, c->cmd2, level, father);
        if (ret == true) {
            perror("run_on_pipe() error");
            return -1;
        }

        break;

    default:
        return SHELL_EXIT;
    }

    return ret; /* TODO: Replace with the actual exit code of the command. */
}