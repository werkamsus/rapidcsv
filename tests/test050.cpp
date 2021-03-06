// test050.cpp - read column header / label by index

#include <rapidcsv.h>
#include "unittest.h"

int main()
{
  int rv = 0;

  std::string csv =
    "-,A,B,C\n"
    "1,3,9,81\n"
    "2,4,16,256\n"
    ;

  std::string path = unittest::TempPath();
  unittest::WriteFile(path, csv);

  try
  {
    rapidcsv::Document doc(path);
    unittest::ExpectEqual(std::string, doc.GetColumnLabel(0), "A");
    unittest::ExpectEqual(std::string, doc.GetColumnLabel(1), "B");
    unittest::ExpectEqual(std::string, doc.GetColumnLabel(2), "C");
    ExpectException(doc.GetColumnLabel(3), std::out_of_range);
    
    rapidcsv::Document doc2(path, rapidcsv::LabelParams(-1, -1));
    ExpectException(doc2.GetColumnLabel(0), std::out_of_range);

    rapidcsv::Document doc3(path, rapidcsv::LabelParams(0, -1));
    unittest::ExpectEqual(std::string, doc3.GetColumnLabel(0), "-");
    unittest::ExpectEqual(std::string, doc3.GetColumnLabel(1), "A");
    unittest::ExpectEqual(std::string, doc3.GetColumnLabel(2), "B");
    unittest::ExpectEqual(std::string, doc3.GetColumnLabel(3), "C");
    ExpectException(doc3.GetColumnLabel(4), std::out_of_range);
  }
  catch(const std::exception& ex)
  {
    std::cout << ex.what() << std::endl;
    rv = 1;
  }

  unittest::DeleteFile(path);

  return rv;
}

