#include ".\cdirectorylist.h"



cDirectoryList::cDirectoryList(void)
{
	// CONSTRUCTOR.
	c_oListing = NULL;
	c_oCurrent = NULL;
}

cDirectoryList::~cDirectoryList(void)
{
	// DESTRUCTOR.
	Clear();
}

void cDirectoryList::Clear()
{
	// CLEARS THE LISTING.
	struct cDirectoryList_Internal *oTemp;
	while (c_oListing != NULL)
	{
		oTemp = c_oListing;
		c_oListing = c_oListing->c_oNext;
		delete oTemp;
	}
	c_oCurrent = NULL;
	return;
}
void cDirectoryList::MoveFirst()
{
	c_oCurrent = c_oListing;
	return;
}
void cDirectoryList::MoveNext()
{
	if (c_oCurrent != NULL)
	{
		c_oCurrent = c_oCurrent->c_oNext;
	}
	return;
}
bool cDirectoryList::EOF()
{
	return c_oCurrent == NULL;
}
const struct __finddata64_t *cDirectoryList::Current()
{
	return c_oCurrent == NULL ? NULL : &c_oCurrent->c_oFileInfo;
}
void cDirectoryList::GetListing(const char *sFileSpec)
{		
	struct __finddata64_t oFileInfo;
	intptr_t oHandle;
	bool bContinue;

	Clear();

	oHandle = _findfirst64(sFileSpec,&oFileInfo);
	bContinue = (oHandle != -1);
	while (bContinue)
	{
		AddItem(&oFileInfo);
		bContinue = (_findnext64(oHandle,&oFileInfo)!= -1);		
	}
	_findclose(oHandle);
	return;
}
void cDirectoryList::AddItem(const struct __finddata64_t *oFileInfo)
{
	// ADDS AN ITEM.
	struct cDirectoryList_Internal *oNew;

	if (strcmp(oFileInfo->name,".")==0)
	{
		return;
	}
	if (strcmp(oFileInfo->name,"..")==0)
	{
		return;
	}
	oNew = new cDirectoryList_Internal;
	memcpy(&(oNew->c_oFileInfo),oFileInfo,sizeof(*oFileInfo));	
	if (c_oCurrent == NULL)
	{
		oNew->c_oNext = c_oListing;
		c_oListing = oNew;
	} else
	{
		oNew->c_oNext = c_oCurrent->c_oNext;
		c_oCurrent->c_oNext = oNew;
		c_oCurrent = oNew;
	}
	return;
}
bool cDirectoryList::IsDirectory()
{
	// RETURNS true IF THE CURRENT ENTRY IS A DIRECTORY.
	return c_oCurrent == NULL ? false : ((c_oCurrent->c_oFileInfo.attrib & 16)!=0);
}
const char *cDirectoryList::FileName()
{
	// RETURN THE FILE NAME.
	return c_oCurrent == NULL ? NULL : c_oCurrent->c_oFileInfo.name;
}
void cDirectoryList::CopyAFileIfDifferent(const char *sRemoteFile,const char *sLocalFile,const struct __finddata64_t *oRemoteFileInfo,const struct __finddata64_t *oLocalFileInfo)
{
	// COPY A FILE IF IT'S DIFFERENT.	
	bool bCopy;

	do
	{
		bCopy = true;
		if ((oRemoteFileInfo == NULL) || (oLocalFileInfo == NULL))
		{
			// DON'T TRY TO COMPARE. JUST COPY.
			break;
		}

		if (oRemoteFileInfo->size != oLocalFileInfo->size)
		{
			// SIZE IS DIFFERENT. COPY.
			break;
		}
		if (oRemoteFileInfo->time_write != oLocalFileInfo->time_write)
		{
			// LAST MODIFIED DATE/TIME IS DIFFERENT. COPY.
			break;
		}
		// DON'T COPY.
		bCopy = false;
	} while (false);
	if (bCopy)
	{
		CopyFile(sRemoteFile,sLocalFile,false);		
	}
	return;
}
