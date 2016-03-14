#include "HalfEdgeRepresent.h"

using std::ifstream;

int main(void)
{
	ifstream is("in.obj", std::ios::in);
	if (is.fail())
		exit(-1);

	HalfEdgeRepresent heds(is);

	return 0;
}