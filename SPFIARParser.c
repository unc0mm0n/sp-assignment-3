#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SPFIARParser.h"

#define SPLIT_TOKEN ("\n\t\r ")

bool spParserIsInt(const char* str) {
    if (str == NULL) {
        return 0;
    }
    char *p_c = (char *)str;
    bool has_digits = 0; 

    if (*p_c == '-') { // We only accept p_c at the start.
        p_c++;
    }

    while (*p_c != '\0' && *p_c != '\n') { // Make sure all characters are digits
        if (*p_c < '0' || *p_c > '9') {
            return 0;
        }

        p_c++;
        has_digits++;
    }
    return (has_digits > 0); // We want to verify at least one character is a digit.
}

SPCommand spParserPraseLine(const char* str) {
    SPCommand cmd;
    char* token;
    char strCpy[SP_MAX_LINE_LENGTH];
    strcpy(strCpy, str);
    SP_COMMAND cmd_type;

    if (*str == '\n') {
        cmd_type = SP_INVALID_LINE;    
    } else {
        token = strtok(strCpy,SPLIT_TOKEN);
        cmd_type = spParserGetCommand(token);
    }

    cmd.cmd = cmd_type;
    cmd.validArg = 0;

    if (cmd_type == SP_ADD_DISC) {
        token = strtok(NULL, SPLIT_TOKEN);
        if (token == NULL) {
            cmd.cmd = SP_INVALID_LINE;
            return cmd;
        }
        if (spParserIsInt(token)) {
            cmd.validArg = 1;
            cmd.arg = atoi(token);
        }
    }

    if (strtok(NULL, SPLIT_TOKEN) != NULL) {
        cmd.cmd = SP_INVALID_LINE;
        cmd.validArg = 0;
    }

    return cmd;
}

/*
SPCommand* spParserPraseLine(char* str) {
    SPCommand* cmd = (SPCommand *)malloc(sizeof(SPCommand));
    char* token;
    SP_COMMAND cmd_type;

    if (*str == '\n') {
        cmd_type = SP_INVALID_LINE;    
    } else {
        token = strtok(str,SPLIT_TOKEN);
        cmd_type = spParserGetCommand(token);
    }

    cmd->cmd = cmd_type;
    cmd->validArg = 0;

    if (cmd_type == SP_ADD_DISC) {
        token = strtok(NULL, SPLIT_TOKEN);
        if (token == NULL) {
            cmd->cmd = SP_INVALID_LINE;
            return cmd;
        }
        if (spParserIsInt(token)) {
            cmd->validArg = 1;
            cmd->arg = atoi(token);
        }
    }

    if (strtok(NULL, SPLIT_TOKEN) != NULL) {
        cmd->cmd = SP_INVALID_LINE;
        cmd->validArg = 0;
    }

    return cmd;
}*/

SP_COMMAND spParserGetCommand(const char* str) {
    if (strcmp(str, SP_UNDO_MOVE_COMMAND) == 0) {
        return SP_UNDO_MOVE;
    } else if (strcmp(str, SP_SUGGEST_MOVE_COMMAND) ==  0){
        return SP_SUGGEST_MOVE;
    } else if (strcmp(str, SP_ADD_DISC_COMMAND) == 0) {
        return SP_ADD_DISC;
    } else if (strcmp(str, SP_QUIT_COMMAND) == 0) {
        return SP_QUIT;
    } else if (strcmp(str, SP_RESTART_COMMAND) == 0) {
        return SP_RESTART;
    } else {
        return SP_INVALID_LINE;
    }
}
