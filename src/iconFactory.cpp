// TODO implementation

#include "iconFactory.h"

Icon IconFactory::blueBlock() {
    //return Icon{ { Cell(BLUE, "□") } };
	return Icon{ { Cell(BLUE, " ") } };
}

Icon IconFactory::redPlayer() {
    //return Icon{ { Cell(RED, "■") } };
	return Icon{ { Cell(RED, " ") } };
}

Icon IconFactory::Player() {
	return Icon{ { Cell(BLUE, "PP") } };
}

Icon IconFactory::BOMBPlayer() {
	return Icon{ { Cell(BLACK, " BB ") } };
}

Icon IconFactory::APPLEPlayer() {
	return Icon{ { Cell(RED, " AA ") } };
}
