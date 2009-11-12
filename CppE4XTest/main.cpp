
#include "../CppE4X/E4X.h"

using namespace E4X;


void test_read_write_file()
{
	std::cout << "---------------------" << __FUNCTION__ << std::endl;
	E4XDocument doc;
	if( doc.loadFile("sample.xml"))
	{
		E4XCellRef refImage = doc["rss"]["channel"];
		std::cout << "title: " << refImage["title"].toString() << std::endl;
		std::cout << "link: " << refImage["link"].toString() << std::endl;
		std::cout << "description: " << refImage["description"].toString() << std::endl;

		E4XCellRef channel = doc["rss"]["channel"][0].copy();
		E4XIterator items = doc["rss"]["channel"]["item"];
		while( items.hasNext())
		{
			E4XCellRef cell = items.next();
			cell["description"].remove();
			// or items.next()["description"].getCell().removeFromParent();
			std::cout << cell["title"].toString() << std::endl;
		}

		doc["rss"][0].appendChild( channel);

		doc.saveFile("sample_output.xml");
	}
	else
	{
		std::cout << "parser file error." << std::endl;
	}
}

void test_create_new_file()
{
	std::cout << "---------------------" << __FUNCTION__ << std::endl;
	E4XDocument doc;
	doc["root"]["item"]["@type"]="fist";
	doc["root"]["item"][1]["@type"]="second";
	for( int i = 0; i< 10; i++)
	{
		doc["root"]["item"][i%2]["data"][i/2] = i;
	}
	doc.saveFile( "create_test.xml");
}

void test_parse()
{
	std::cout << "---------------------" << __FUNCTION__ << std::endl;

	E4XElement element;
	if( element.parse("<invoke name=\"PlayMovie\" returntype=\"xml\"><arguments ><string>here is a string</string></arguments></invoke>"))
	{
		std::cout << element["@name"].toString() << std::endl;

		std::cout << element["arguments"].toXmlString() << std::endl;
		std::cout << element["arguments"]["string"].toString() << std::endl;

		E4X::E4XIterator it = element["arguments"][""];
		while( it.hasNext())
		{
			E4X::E4XCellRef cell = it.next();
			std::cout << cell.getName() << std::endl;
		}
	}
	else
	{
		std::cout << "parse 1 error" << std::endl;
	}



	E4XElement http;
	if( http.parseAnsi("<http_xml_request http=\"http://dy.gougou.com/top_movie?key=¹¦·ò&num=12&t=200\" />"))
	{
		std::cout << http["@http"].toString() << std::endl;
		std::cout << http.toAnsiXmlString() << std::endl;
	}
	else
	{
		std::cout << "parse 2 error" << std::endl;
	}

}


int main(int /*argc*/, char* /*argv*/[])
{

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
	int __tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG | _CRTDBG_LEAK_CHECK_DF);

	__tmpFlag |= _CRTDBG_LEAK_CHECK_DF;

	_CrtSetDbgFlag( __tmpFlag );

#endif
	test_parse();
	test_create_new_file();
	test_read_write_file();


	E4XDocument doc;
	doc["root"]["data"] = __int64( 12345678987621);
	__int64 data = doc["root"]["data"].toBigNumber();

	std::cout << doc.toXmlString() << std::endl;
	std::cout << data << std::endl;

	return 0;
}

