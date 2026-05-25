#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MESSAGE_BUFFER_SIZE 32
#define TOP_BANNER_LINES 9

#define RESET   "\033[0m"
#define WHITE   "\033[37m"
#define BLACK   "\033[30m"
#define GREY    "\033[90m"
#define RED     "\033[1;31m" // BOLD

char* top_banner[] = {
	RED "\n                 .          .-+.        " RESET,
	RED "               +#´           `+++.      " RESET,
	RED "             +++´      .-##.  .++++     " RESET,
	RED "            ++++.  .++++" BLACK "++" RED "#+++++++++    " RESET,
	RED "            ++++++++++" BLACK "+ " RED "++++#++.-++++    " RESET,
	RED "            ++++++++++++++´" WHITE "++" RED "`+." WHITE "++" RED "+.    " RESET,
	RED "            `#+++++++++++´" WHITE "++" RED "." BLACK "@" RED "`+" BLACK "@" WHITE "+" RED ".#    " RESET,
	RED "              `#+++++++++." WHITE "++" BLACK "@@" RED "#" BLACK "@@" WHITE  "+" RED "+-.   " RESET,
	RED "                `+++++++++." WHITE "++" RED ".##++++++."  RESET "/"
};

char* bottom_banner =
	RED "                 #+++++++++#-#+++++++ " GREY ".- \n" RESET
	RED "                 `+++++" BLACK "++++" RED "++++´" BLACK "+++#+" GREY ".+ .+- \n" RESET
	RED "                  `#++++##." BLACK "+++++" RED "+#´" GREY "   -. - ´ . \n" RESET
	RED "                    `#+++++++###´  .#" GREY "_---. .+´ \n" RESET
	RED "                     -++++++++#.  +++# \n" RESET
	RED "                    .++++++++++++++++´ \n" RESET
	RED "                    ++++#+#++++++++´ \n" RESET
	RED "                    ++++++++++++" BLACK "#" RED "+´ \n" RESET
	BLACK "                    `++++++" RED "++++++" BLACK "#. \n" RESET
	RED "                    -+++" GREY "--" BLACK "#++++#" RED "+## \n" RESET
	RED "                   .++" GREY "--" RED "+++++++++#´ \n" RESET
	RED "                  .+"GREY "--" RED "++++++++++#´ \n" RESET
	RED "                .++++#++++++#+-`#..______ \n" RESET
	RED "        ..-#+++++´  ``.+-" WHITE "++++" RED "++" WHITE "///" RED "++####" WHITE ".#-. \n" RESET
	RED "    .+++++#´´´        ++" WHITE "@" RED "+" WHITE "///" RED "-+####" WHITE ".---/#### \n" RESET
	RED "   ++-´.             .##++###+###+" WHITE "/.-######´ \n" RESET
	RED "   ++++.+++-.        " WHITE "####----- -#/#+##´´ \n" RESET
	RED "    +++++++++++#-.      " WHITE "` \n" RESET
	RED "      ````````````` \n\n" RESET
;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("%s: <message to say>\n", argv[0]);
		return 0;
	}

	int bytes = 0;

	for (int i = 1; i < argc; i++)
		bytes += strlen(argv[i]) + 1;

	char* message = malloc(bytes + 1);
	if (!message)
		return 1;

	message[0] = '\0';

	for (int i = 1; i < argc; i++) {
		strcat(message, argv[i]);
		if (i != argc - 1)
			strcat(message, " ");
	}

	int msg_len = strlen(message);
	int message_lines = (msg_len + LINE_MESSAGE_BUFFER_SIZE - 1) / LINE_MESSAGE_BUFFER_SIZE;
	int bubble_width = msg_len < LINE_MESSAGE_BUFFER_SIZE ? msg_len : LINE_MESSAGE_BUFFER_SIZE;

	int bubble_total_lines = message_lines + 2;
	int bubble_start = TOP_BANNER_LINES - bubble_total_lines;

	int current_pos = 0;

	for (int line = 0; line < TOP_BANNER_LINES; line++) {

		printf("%s", top_banner[line]);

		if (line < bubble_start) {
			printf("\n");
			continue;
		}

		int bubble_line = line - bubble_start;

		if (bubble_line == 0) {
			printf(" ");
			for (int i = 0; i < bubble_width + 2; i++)
				printf("-");
			printf("\n");
			continue;
		}

		if (bubble_line == bubble_total_lines - 1) {
			printf(" ");
			for (int i = 0; i < bubble_width + 2; i++)
				printf("-");
			printf("\n");
			continue;
		}

		char buffer[LINE_MESSAGE_BUFFER_SIZE + 1];

		int remaining = msg_len - current_pos;
		int copy_len = remaining > LINE_MESSAGE_BUFFER_SIZE ? LINE_MESSAGE_BUFFER_SIZE : remaining;

		strncpy(buffer, message + current_pos, copy_len);
		buffer[copy_len] = '\0';

		current_pos += copy_len;

		if (message_lines == 1) {
			printf("< %-*s >\n", bubble_width, buffer);
			continue;
		}

		if (bubble_line == 1) {
			printf("/ %-*s \\\n", bubble_width, buffer);
			continue;
		}

		if (bubble_line == bubble_total_lines - 2) {
			printf("\\ %-*s /\n", bubble_width, buffer);
			continue;
		}

		printf("| %-*s |\n", bubble_width, buffer);
	}

	printf("%s", bottom_banner);

	free(message);

	return 0;
}
