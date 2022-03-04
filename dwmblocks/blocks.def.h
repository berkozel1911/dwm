//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"  ", "cat /proc/loadavg | awk '{ print $1\", \"$2\", \"$3 }'", 60, 0},
	{"  ", "free --giga -h | awk 'NR==2 { print $3\"/\"$2 }'", 60, 0},
	{"  ", "cat /sys/class/power_supply/BAT1/capacity", 600, 0},
	{"  ", "date '+%d/%m/%y - %a %H:%M'",					50,		0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
