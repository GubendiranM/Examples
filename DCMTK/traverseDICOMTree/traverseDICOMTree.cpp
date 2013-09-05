// STL includes
#include <iostream>

//DCMTK includes
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"

//---------------------------------------------------------------------
void visitNode(DcmObject* dicomobject)
  {
  DcmTag tag = dicomobject->getTag();
  std::cout<<tag;
   
  //int VM = dicomobject->getVM();
  //std::cout<<" "<<VM; 

  // VR stands for Value Representation
  DcmVR VR = dicomobject->getVR();
  OFString VRName = VR.getVRName();
  std::cout<<" "<<VRName;
     
  OFString tagName = tag.getTagName();
  std::cout<<" "<<tagName<<std::endl; 
  }

//---------------------------------------------------------------------
void traverseDICOMTree (DcmItem *dataset)
{
  DcmStack stack;
  dataset->nextObject( stack, OFTrue);

for (; stack.top();dataset->nextObject(stack, OFFalse))
{
    


  DcmObject *dicomobject = stack.top();
    
	//std::cout<<dicomobject;
    visitNode(dicomobject);
    DcmTag tag = dicomobject->getTag();
    DcmElement *dcmElem = dynamic_cast<DcmElement *> (dicomobject);
    if ( ! dicomobject->isLeaf() && dcmElem)
    {
      
      DcmSequenceOfItems* newNode = dynamic_cast<DcmSequenceOfItems*> (dcmElem);
      DcmObject *dO = newNode->nextInContainer( NULL);
      for( ; dO; dO = newNode->nextInContainer( dO))
      {
        DcmElement *dcmElem2 = dynamic_cast<DcmElement *> (dO);
        DcmTag tag2 = dO->getTag();
        if( tag2.getXTag() == DCM_Item)
          {
          traverseDICOMTree( dynamic_cast<DcmItem*> (dO));
          }
        
      }

      
     
    }
}
}
//---------------------------------------------------------------------

int main()
{
  DcmFileFormat fileformat;
  
  OFCondition status = fileformat.loadFile("test.dcm");
  DcmDataset* dataset = fileformat.getDataset();
  
  
  std::cout<<" TAG        "<< "VR "<<"TagName"<<std::endl;
  traverseDICOMTree(dataset);
  
  return 0;
}