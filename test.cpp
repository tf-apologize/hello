#incude "test.h"

int main(int argc, const char *argv[])
{
	
	Test("*TAS", "sc2001tas");
	Test("*TAS","sc2001-C-2000tas");
	Test("*TAS","sc2001TAS");
	Test("*TAS","TAS2001");
	Test("*TAS","sTAS2001");
	Test("*TAS","nr2002TAS");

	/*std::cout << std::endl;

	Test("TAS*", "sc2001");
	Test("TAS*", "sc2001-C-2000");
	Test("TAS*", "sc2001TAS");
	Test("TAS*", "TAS2001");
	Test("TAS*", "sTAS2001");
	Test("TAS*", "nr2002TAS");

	std::cout << std::endl;

	Test("**?TAS*", "sc2001");
	Test("**?TAS*", "sc2001-C-2000");
	Test("**?TAS*", "sc2001TAS");
	Test("**?TAS*", "TAS2001");
	Test("**?TAS*", "sTAS2001");
	Test("[a-z][a-z][9-1][\s]*TAS", "nr2\s002TAS");*/
	return 0;
}
