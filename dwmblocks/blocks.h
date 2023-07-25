//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"", "sb-loadavg", 60, 0},
	{"|🌡", "echo $(sensors | grep 'Package id 0' | awk '{ print $4}' | cut -c 2-3)°C", 60, 0},
	{"|", "sb-network", 1, 0},
	{"|", "sb-memory", 60, 0},
	{"|", "echo 🌍 $(setxkbmap -query | grep layout | awk '{print $2}')",0 , 13},
	{"|", "sb-datetime",	30,		0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = "\0";
static unsigned int delimLen = 5;
