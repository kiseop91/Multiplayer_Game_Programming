#include "MemoryStream.h"
#include "kiseop.h"
int main()
{

	kiseop seop(29, 'k');
	seop.init();

	OutputMemoryStream outStream;
	seop.Write(outStream);

	char* Buffer = static_cast<char*>(malloc(1470));
	memcpy(Buffer, outStream.GetBufferPtr(), outStream.GetLength()); //ī��(����������� ����)
	InputMemoryStream inStream(Buffer, 1470);

	kiseop seop2;
	seop2.Read(inStream);
	seop2.print();

	return  0;
}