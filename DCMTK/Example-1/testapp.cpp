#include <iostream>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"

using namespace std;


int main()
{
	
	DcmFileFormat fileformat;

OFCondition status = fileformat.loadFile("test.dcm");
fileformat.print;
if (status.good())
{
   OFString patientsName;
   
   if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientsName).good())
   {
      cout << "Patient's Name: " << patientsName << endl;
   } else
     cerr << "Error: cannot access Patient's Name!" << endl;
} else
cerr << "Error: cannot read DICOM file (" << status.text() << ")" << endl;

return 0;
}