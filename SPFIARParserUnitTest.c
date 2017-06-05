#include "unit_test_util.h"
#include "SPFIARParser.h"

static bool spParserCheckIsInt() {

    ASSERT_FALSE(spParserIsInt(""));
    ASSERT_FALSE(spParserIsInt(" "));

	ASSERT_TRUE(spParserIsInt("1"));
	ASSERT_TRUE(spParserIsInt("11"));
	ASSERT_TRUE(spParserIsInt("111"));
	ASSERT_TRUE(spParserIsInt("-1"));
	ASSERT_TRUE(spParserIsInt("-11"));
	ASSERT_TRUE(spParserIsInt("-111"));
	ASSERT_TRUE(spParserIsInt("01"));
	ASSERT_TRUE(spParserIsInt("011"));
	ASSERT_TRUE(spParserIsInt("0111"));
	ASSERT_TRUE(spParserIsInt("-01"));
	ASSERT_TRUE(spParserIsInt("-011"));
	ASSERT_TRUE(spParserIsInt("-0111"));

    ASSERT_FALSE(spParserIsInt("a"));
    ASSERT_FALSE(spParserIsInt("a1"));
    ASSERT_FALSE(spParserIsInt("1a"));
    ASSERT_FALSE(spParserIsInt("a1a"));
    ASSERT_FALSE(spParserIsInt("1a1"));

    ASSERT_FALSE(spParserIsInt("1-1"));
    ASSERT_FALSE(spParserIsInt("-"));
    ASSERT_FALSE(spParserIsInt("--1"));
    ASSERT_FALSE(spParserIsInt("3--1"));
    ASSERT_FALSE(spParserIsInt("-a"));
    ASSERT_FALSE(spParserIsInt("a-"));

    ASSERT_FALSE(spParserIsInt(NULL));

	return true;
}
static bool spParserCheckParseLine() {
	SPCommand cmd;
    char cmd_str[] = "add_disc 17";
	cmd = spParserPraseLine(cmd_str);
	ASSERT_TRUE(cmd.cmd == SP_ADD_DISC && cmd.validArg && cmd.arg == 17);

    char cmd_str2[] = "add_disc	17\n";
	cmd = spParserPraseLine(cmd_str2);
	ASSERT_TRUE(cmd.cmd == SP_ADD_DISC && cmd.validArg && cmd.arg == 17);

    char cmd_str3[] = "	add_disc 17\n";
	cmd = spParserPraseLine(cmd_str3);
	ASSERT_TRUE(cmd.cmd == SP_ADD_DISC && cmd.validArg && cmd.arg == 17);

    char cmd_str4[] = "aDd_disc 17";
	cmd = spParserPraseLine(cmd_str4);
	ASSERT_TRUE(cmd.cmd == SP_INVALID_LINE && !cmd.validArg);

    char cmd_str5[] = "undo_move";
	cmd = spParserPraseLine(cmd_str5);
	ASSERT_TRUE(cmd.cmd == SP_UNDO_MOVE && !cmd.validArg);

    char cmd_str6[] = "suggest_move";
	cmd = spParserPraseLine(cmd_str6);
	ASSERT_TRUE(cmd.cmd == SP_SUGGEST_MOVE && !cmd.validArg);

    char cmd_str_quit[] = "quit";
	cmd = spParserPraseLine(cmd_str_quit);
	ASSERT_TRUE(cmd.cmd == SP_QUIT && !cmd.validArg);

    char cmd_str_restart[] = "restart";
	cmd = spParserPraseLine(cmd_str_restart);
	ASSERT_TRUE(cmd.cmd == SP_RESTART && !cmd.validArg);

    char cmd_str7[] = "add_disc";
	cmd = spParserPraseLine(cmd_str7);
	ASSERT_TRUE(cmd.cmd == SP_INVALID_LINE && !cmd.validArg);

    char cmd_str8[] = "suggest_move 17";
	cmd = spParserPraseLine(cmd_str8);
	ASSERT_TRUE(cmd.cmd == SP_INVALID_LINE && !cmd.validArg);

    char cmd_str9[] = "add_disc a";
	cmd = spParserPraseLine(cmd_str9);
    ASSERT_TRUE(cmd.cmd == SP_ADD_DISC && !cmd.validArg); 

	return true;
}

static bool spParserCheckGetCommand() {
    SP_COMMAND cmd;
    cmd = spParserGetCommand("undo_move");
    ASSERT_TRUE(cmd == SP_UNDO_MOVE);
    cmd = spParserGetCommand("suggest_move");
    ASSERT_TRUE(cmd == SP_SUGGEST_MOVE);
    cmd = spParserGetCommand("add_disc");
    ASSERT_TRUE(cmd == SP_ADD_DISC);
    cmd = spParserGetCommand("quit");
    ASSERT_TRUE(cmd == SP_QUIT);
    cmd = spParserGetCommand("restart");
    ASSERT_TRUE(cmd == SP_RESTART);

    cmd = spParserGetCommand("add_disc 3");
    ASSERT_TRUE(cmd == SP_INVALID_LINE);
    cmd = spParserGetCommand("a");
    ASSERT_TRUE(cmd == SP_INVALID_LINE);
    cmd = spParserGetCommand("");
    ASSERT_TRUE(cmd == SP_INVALID_LINE);
    cmd = spParserGetCommand(" ");
    ASSERT_TRUE(cmd == SP_INVALID_LINE);
    cmd = spParserGetCommand(" add_disc");
    ASSERT_TRUE(cmd == SP_INVALID_LINE);
    cmd = spParserGetCommand("add disc");
    ASSERT_TRUE(cmd == SP_INVALID_LINE);
    return true;

}

int main() {
	RUN_TEST(spParserCheckIsInt);
    RUN_TEST(spParserCheckGetCommand);
	RUN_TEST(spParserCheckParseLine);
	return 0;
}
