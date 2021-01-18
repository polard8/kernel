

struct statusbar_d
{
	int size_in_chars;
	
	//string1 support
	char *string1;
	int string1_offset;
	
	//string2 support
	char *string2;
	int string2_offset;
};
struct statusbar_d STATUSBAR;




void statusInitializeStatusBar(void);
void update_statuts_bar( char *string1, char *string2 );



