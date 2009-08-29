
#include "../CppE4X/E4X.h"

using namespace E4X;

void test_read_write_file()
{
	E4XDocument doc;
	if( doc.loadFile("sample.xml"))
	{
		std::cout<< doc["#xml"]["@encoding"].toString()<< std::endl;
		E4XDocumentRef pDoc = doc.copy();
		E4XCellRef pCellExec = pDoc["exec"].getCell().copy();

		doc["exec"]["@hehe"] = std::string("hexhe");

		doc["exec"]["@attrib"]="hehe";
		
		pCellExec/"item"/1/"@hello" = "exec_value";

		E4XIterator it = doc["exec"]["item"]["minipic"];
		std::cout<< it[0].toString() << std::endl;

		try
		{
			doc["exec"]["item"][17]["minipic"] = std::string("minipic_new");
		}
		catch( E4XException& e)
		{
			std::cout << e.Error() << std::endl;
		}

		std::cout << doc["exec"].toXmlString() << std::endl;

		E4XIterator itnew( doc["exec"]);

		itnew["heihei"]["hoho"]["@haha"]= true;
		
		itnew/"heihei"/"hoho"/"heihei" = "heihei!!";

		std::cout << (itnew/"heihei"/"hoho"/"heihei").toXmlString() << std::endl;

		E4XIterator itremove( doc["exec"]["item"]);
		std::cout << itremove.toXmlString() << std::endl;

		while( itremove.hasNext())
		{
			itremove.next();
			itremove.remove();
		}

		itremove.getCell().appendChild( &pCellExec);

		doc.saveFile( "output.xml");

		std::cout << doc.toXmlString() << std::endl;

		pDoc.destroy();
	}
}


void test_create_new_file()
{
	E4XDocument doc;
	doc["root"]["item"]["@type"]="attribute";
	doc["root"]["item"][1]["@type"]="attribute_1";
	E4XIterator it( doc);
	std::cout << it.toXmlString() << std::endl;
}

void test_parse()
{
	E4XElement element;
	element.parseAnsi("<hehe xx=\"heihei\'ha测试中文字符串h&amp;a\'hoho\"   ></hehe>");
	
	E4XElement e("<element data=\"element_data\" ><abc  value=\"letter中英文混合\"  /></element>");

	E4XElement in("<invoke name=\"PlayMovie\" returntype=\"xml\"><arguments /></invoke>");

	std::cout << element.toAnsiXmlString() << std::endl;

	std::cout << e.toXmlString() << std::endl;

	std::cout << in["arguments"].toXmlString() << std::endl;
	std::cout << in["@name"].toXmlString() << std::endl;
	std::cout << in.toXmlString() << std::endl;
}


int main(int /*argc*/, char* /*argv*/[])
{

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
	int __tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG | _CRTDBG_LEAK_CHECK_DF);

	__tmpFlag |= _CRTDBG_LEAK_CHECK_DF;

	_CrtSetDbgFlag( __tmpFlag );

	//_CrtSetBreakAlloc(647); 

#endif
	test_parse();
	test_create_new_file();
	test_read_write_file();

	return 0;
}

