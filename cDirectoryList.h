#ifndef __CDIRECTORYLIST_H
#define __CDIRECTORYLIST_H

// USED TO GET A DIRECTORY LISTING.
#include <windows.h>
#include <io.h>
#include <string.h>

struct cDirectoryList_Internal
{
	struct __finddata64_t c_oFileInfo;
	struct cDirectoryList_Internal *c_oNext;
};
class cDirectoryList
{
private:
	void AddItem(const struct __finddata64_t *oFileInfo);
	struct cDirectoryList_Internal *c_oListing;
	struct cDirectoryList_Internal *c_oCurrent;
public:
	cDirectoryList(void);
	~cDirectoryList(void);	
	void GetListing(const char *sFileSpec);	 // SHOULD END IN *.*
	static void CopyAFileIfDifferent(const char *sRemoteFile,const char *sLocalFile,const struct __finddata64_t *oRemoteFileInfo,const struct __finddata64_t *oLocalFileInfo);
	// THE FOLLOWING FUNCTIONS ARE USED TO LOOP THROUGH THE LIST.
	void Clear();
	void MoveFirst();
	void MoveNext();
	bool EOF();
	const struct __finddata64_t *Current();
	bool IsDirectory();
	const char *FileName();
};

#endif