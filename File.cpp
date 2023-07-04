#include "File.h"

std::string File::getFileName()
{
    return FILE_NAME;
}

int File::getLastId()
{
    return lastId;
}

void File::checkRootNode()
{
    xmlDoc.LoadFile(getFileName().c_str());
    tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();

    if (pRoot == nullptr)
    {
        tinyxml2::XMLNode* pRoot = xmlDoc.NewElement("Root");
        xmlDoc.InsertFirstChild(pRoot);
    }
}
