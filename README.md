# cDirectoryList
C++ class to get the directory listing in Windows, store, and traverse the list.
I wrote this a long time ago, but thought I'd include it as a sample of my work.
# Public methods:
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
