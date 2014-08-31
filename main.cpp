#include "SuDokuUnit.h"

int main() 
{
	SuDokuUnit unit3( { 2, 2, 6, 1, 3, 9, 5, 8, 0 } );
	unit3.Print();
	unit3.Solve();
	unit3.Print();

}

