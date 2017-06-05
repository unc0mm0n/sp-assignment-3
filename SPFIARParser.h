#ifndef SPFIARPARSER_H_
#define SPFIARPARSER_H_
#include <stdbool.h>

//specify the maximum line length
#define SP_MAX_LINE_LENGTH 1024
#define SP_UNDO_MOVE_COMMAND ("undo_move")
#define SP_SUGGEST_MOVE_COMMAND ("suggest_move")
#define SP_ADD_DISC_COMMAND ("add_disc")
#define SP_QUIT_COMMAND ("quit")
#define SP_RESTART_COMMAND ("restart")

//a type used to represent a command
typedef enum {
	SP_UNDO_MOVE,
	SP_ADD_DISC,
	SP_SUGGEST_MOVE,
	SP_QUIT,
	SP_RESTART,
	SP_INVALID_LINE,
} SP_COMMAND;

//a new type that is used to encapsulate a parsed line
typedef struct command_t {
	SP_COMMAND cmd;
	bool validArg; //is set to true if the line contains a valid argument
	int arg;
} SPCommand;

/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool spParserIsInt(const char* str);

/**
 * Parses a specified line. If the line is a command which has an integer
 * argument then the argument is parsed and is saved in the field arg and the
 * field validArg is set to true. In any other case then 'validArg' is set to
 * false and the value 'arg' is undefined
 *
 * @return
 * A parsed line such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   validArg - is set to true if the command is add_disc and the integer argument
 *              is valid
 *   arg      - the integer argument in case validArg is set to true
 */
SPCommand spParserPraseLine(const char* str);

/**
 * Parse a string and return the corresponsing SP_COMMAND value.
 * Return SP_INVALID_LINE if no value found.
 *  
 * @param str string to parse
 * 
 * @return SP_COMMAND corresponsing SP_COMMAND value.
 */
SP_COMMAND spParserGetCommand(const char* str);

#endif
