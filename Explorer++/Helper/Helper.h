#ifndef HELPER_INCLUDED
#define HELPER_INCLUDED

#include <windows.h>
#include <winioctl.h>
#include <list>

using namespace std;

#define MAX_STRING_LENGTH	512

/* SummaryInformation stream constants. */
#define PROPERTY_ID_TITLE		0x02
#define PROPERTY_ID_SUBJECT		0x03
#define PROPERTY_ID_AUTHOR		0x04
#define PROPERTY_ID_KEYWORDS	0x05
#define PROPERTY_ID_COMMENT		0x06

/* DocumentSummaryInformation stream. */
#define PROPERTY_ID_CATEGORY	0x02

#define EXE_INVALID				0x4

/* ShellHelper definitions. */
#define DEFAULT_ICON_FOLDER		0
#define DEFAULT_ICON_FILE		1

/* CP_ACP is defined for ANSI, but there is no
corresponding definition for Unicode. Therefore,
add a definition here. */
#define CP_UNICODE	1200

typedef struct
{
	TCHAR szFullFileName[MAX_PATH];
} MergedFile_t;

typedef struct
{
	WORD wLanguage;
	WORD wCodePage;
} LANGANDCODEPAGE;

typedef struct
{
	TCHAR szFileName[MAX_PATH];
} PastedFile_t;

typedef enum
{
	GROUP_ADMINISTRATORS,
	GROUP_POWERUSERS,
	GROUP_USERS,
	GROUP_USERSRESTRICTED
} GroupType_t;

/* Listview helper functions. */
int				ListView_SelectAllItems(HWND hListView);
int				ListView_InvertSelection(HWND hListView);
void			ListView_HandleInsertionMark(HWND hListView,int iItemFocus,POINT *ppt);
BOOL			ListView_SelectItem(HWND hListView,int nItem,BOOL bSelect);
BOOL			ListView_FocusItem(HWND hListView,int nItem,BOOL bFocus);
int				ListView_DeselectAllItems(HWND hListView);
DWORD			ListView_SetGridlines(HWND hListView,BOOL bEnableGridlines);
void			ListView_SetAutoArrange(HWND hListView,BOOL bAutoArrange);
HRESULT			ListView_SetBackgroundImage(HWND hListView,UINT Image);
void			ListView_SwapItems(HWND hListView,int iItem1,int iItem2);
void			ListView_SwapItemsNolParam(HWND hListView,int iItem1,int iItem2);
void			ListView_ActivateOneClickSelect(HWND hListView,BOOL bActivate);
int				InsertItemIntoListView(HWND hListView,TCHAR *Text,int IconNumber,void *StoredData);

/* Tab control helper functions. */
void			TabCtrl_SwapItems(HWND hTabCtrl,int iItem1,int iItem2);
void			TabCtrl_SetItemText(HWND,int,TCHAR *);

/* Drive information. */
BOOL			GetDriveGeometryEx(TCHAR *lpszDrive,DISK_GEOMETRY_EX *pDiskGeometry,DWORD dwSize);
BOOL			GetDriveLayoutEx(TCHAR *lpszDrive,DRIVE_LAYOUT_INFORMATION_EX **pDriveLayout,DWORD BufSize);
BOOL			GetDrivePerformanceInfo(TCHAR *lpszDrive,DISK_PERFORMANCE *pDiskPerformance);
BOOL			GetFileSystemInfo(TCHAR *lpszDrive,FILESYSTEM_STATISTICS *pStatistics,DWORD BufSize);
BOOL			GetNtfsVolumeInfo(TCHAR *lpszDrive,NTFS_VOLUME_DATA_BUFFER *pNtfsVolumeInfo,DWORD BufSize);
TCHAR *			GetPartitionName(LARGE_INTEGER StartingOffset);
LARGE_INTEGER	GetDriveLength(TCHAR *lpszDrive);
BOOL			GetFileAllocationInfo(TCHAR *lpszFileName,STARTING_VCN_INPUT_BUFFER *pStartingVcn,RETRIEVAL_POINTERS_BUFFER *pRetrievalPointers,DWORD BufSize);
LONG			GetSectorSize(TCHAR *Drive);
LONG			GetClusterSize(TCHAR *Drive);
int				GetNumberOfUsedPartitions(DRIVE_LAYOUT_INFORMATION_EX *pDriveLayout);
LONG			GetFileSectorSize(TCHAR *FileName);
TCHAR			GetDriveNameFromMask(ULONG unitmask);

/* Idl helpers. */
void			DecodePath(TCHAR *szInitialPath,TCHAR *szCurrentDirectory,TCHAR *szParsingPath,size_t cchDest);
HRESULT			GetIdlFromParsingName(TCHAR *szParsingName,LPITEMIDLIST *pidl);
HRESULT			GetDisplayName(TCHAR *szParsingPath,TCHAR *szDisplayName,DWORD uFlags);
HRESULT			GetDisplayName(LPITEMIDLIST pidlDirectory,TCHAR *szDisplayName,DWORD uFlags);
BOOL			CheckIdl(LPITEMIDLIST pidl);
BOOL			IsIdlDirectory(LPITEMIDLIST pidl);
void			GetVirtualFolderParsingPath(UINT uFolderCSIDL,TCHAR *szParsingPath);
HRESULT			GetVirtualParentPath(LPITEMIDLIST pidlDirectory,LPITEMIDLIST *pidlParent);
BOOL			IsNamespaceRoot(LPCITEMIDLIST pidl);
HRESULT			GetItemInfoTip(TCHAR *szItemPath,TCHAR *szInfoTip,int cchMax);
HRESULT			GetItemInfoTip(LPITEMIDLIST pidlComplete,TCHAR *szInfoTip,int cchMax);
HRESULT			GetCsidlFolderName(UINT csidl,TCHAR *szFolderName,DWORD uParsingFlags);
BOOL			MyExpandEnvironmentStrings(TCHAR *szSrc,TCHAR *szExpandedPath,DWORD nSize);

/* Drag and drop helpers. */
DWORD			DetermineCurrentDragEffect(DWORD grfKeyState,DWORD dwCurrentEffect,BOOL bDataAccept,BOOL bOnSameDrive);

/* File helpers. */
int				CreateFileTimeString(FILETIME *FileTime,TCHAR *Buffer,int MaxCharacters,BOOL bFriendlyDate);
void			PasteFilesFromClipboard(HWND hwnd,TCHAR *Directory,BOOL bPasteLinks,void (*PasteFilesCallback)(void *,list<PastedFile_t> *),void *pData);
int				PasteLinksToClipboardFiles(TCHAR *szDestination);
HRESULT			CreateLinkToFile(TCHAR *PathToFile,TCHAR *PathToLink,TCHAR *LinkDescription);
int				CopyFilesToFolder(HWND hOwner,TCHAR *FileNameList,BOOL bMove);
BOOL			GetRealFileSize(TCHAR *FileName,PLARGE_INTEGER lpRealFileSize);
HRESULT			ResolveLink(HWND hwnd,DWORD fFlags,TCHAR *LinkFile,TCHAR *LinkPath,int nBufferSize);
BOOL			CompareFileTypes(TCHAR *pszFile1,TCHAR *pszFile2);
BOOL			SetFileSparse(TCHAR *szFileName);
void			DeleteFileSecurely(TCHAR *szFileName);
DWORD			BuildFileAttributeString(TCHAR *lpszFileName,TCHAR *Buffer,DWORD BufSize);
int				PasteHardLinks(TCHAR *szDestination);
size_t			GetFileOwner(TCHAR *szFile,TCHAR *szOwner,DWORD BufSize);
DWORD			GetNumFileHardLinks(TCHAR *lpszFileName);
int				ReadFileProperty(TCHAR *lpszFileName,DWORD dwPropertyId,TCHAR *lpszPropertyBuf,DWORD dwBufLen);
int				SetFileProperty(TCHAR *lpszFileName,DWORD dwPropertyType,TCHAR *szNewValue);
HRESULT			GetItemAttributes(TCHAR *szItemParsingPath,SFGAOF *pItemAttributes);
HRESULT			GetItemAttributes(LPITEMIDLIST pidl,SFGAOF *pItemAttributes);
void			SplitFile(HWND hProgressBar,TCHAR *szFullFileName,TCHAR *szOutputDirectory,UINT uSplitSize);
void			MergeFiles(list<MergedFile_t> *MergedFileNameList,TCHAR *szOutputFileName);
BOOL			ExecuteFileAction(HWND hwnd,TCHAR *szVerb,TCHAR *szStartDirectory,LPCITEMIDLIST pidl);
BOOL			GetVersionInfoString(TCHAR *szFileName,TCHAR *szVersionInfo,TCHAR *szBuffer,UINT cbBufLen);
BOOL			ReadImageProperty(TCHAR *lpszImage,UINT PropertyId,void *pPropBuffer,DWORD dwBufLen);
BOOL			IsImage(TCHAR *FileName);
WORD			GetFileLanguage(TCHAR *szFullFileName);
BOOL			GetFileProductVersion(TCHAR *szFullFileName,DWORD *pdwProductVersionLS,DWORD *pdwProductVersionMS);

/* Ownership and access. */
BOOL			GetProcessOwner(TCHAR *szOwner,DWORD BufSize);
BOOL			CheckGroupMembership(GroupType_t GroupType);

/* Menu helpers. */
BOOL			lCheckMenuItem(HMENU hMenu,UINT ItemID,BOOL bCheck);
BOOL			lEnableMenuItem(HMENU hMenu,UINT ItemID,BOOL bEnable);

/* Time helpers. */
BOOL			LocalSystemTimeToFileTime(LPSYSTEMTIME lpLocalTime,LPFILETIME lpFileTime);
BOOL			FileTimeToLocalSystemTime(LPFILETIME lpFileTime,LPSYSTEMTIME lpLocalTime);

/* File streams. */
int				DumpSummaryInformationStream(TCHAR *lpszInputFile,TCHAR *lpszOutputFile);
int				EnumFileStreams(TCHAR *lpszFileName);
void			ReadFileStreams(TCHAR *lpszFile);

/* Bitmap helper functions. */
HRESULT			GetBitmapDimensions(TCHAR *FileName,SIZE *BitmapSize);

/* String helpers. */
void			StringReplace(TCHAR *szString,TCHAR szCharToReplace,TCHAR szReplacement);

/* File slack. */
void			WriteFileSlack(TCHAR *szFileName,void *pData,int iDataSize);
int				ReadFileSlack(TCHAR *FileName,TCHAR *pszSlack,int iBufferLen);

/* Default icon indices. */
int				GetDefaultIcon(int iIconType);
int				GetDefaultFolderIconIndex(void);
int				GetDefaultFileIconIndex(void);

/* Infotips. */
HRESULT			GetFileInfoTip(HWND hwnd,LPCITEMIDLIST pidlDirectory,LPCITEMIDLIST pridl,TCHAR *szInfoTip,UINT cchMax);

/* User interaction. */
BOOL			CreateBrowseDialog(HWND hOwner,TCHAR *Title,TCHAR *PathBuffer,int BufferSize);
BOOL			CreateBrowseDialog(HWND hOwner,TCHAR *Title,LPITEMIDLIST *ppidl);
BOOL			GetFileNameFromUser(HWND hwnd,TCHAR *FullFileName,TCHAR *InitialDirectory);

/* Device related. */
BOOL			GetMonitorDeviceName(TCHAR *lpszMonitorName,DWORD BufSize);
TCHAR			*DecodePrinterStatus(DWORD dwStatus);
void			RetrieveAdapterInfo(void);

/* Process helpers. */
DWORD			GetCurrentProcessImageName(TCHAR *szImageName,DWORD nSize);

/* Computer information. */
void			GetCPUBrandString(char *pszCPUBrand,UINT cchBuf);

/* Media metadata. */
HRESULT			GetMediaMetadata(TCHAR *szFileName,LPCWSTR szAttribute,BYTE **pszOutput);

/* General helper functions. */
size_t			FormatSizeString(DWORD FileSizeLow,DWORD FileSizeHigh,TCHAR *FileSizeBuffer,int BufferSize,BOOL bShowSizeInBytes);
size_t			FormatSizeString(ULARGE_INTEGER lFileSize,TCHAR *pszFileSize,size_t cchBuf,BOOL bShowSizeInBytes);
size_t			FormatSizeString(ULARGE_INTEGER lFileSize,TCHAR *pszFileSize,size_t cchBuf,BOOL bShowSizeInBytes,BOOL bRound);
HINSTANCE		StartCommandPrompt(TCHAR *Directory);
BOOL			SetProcessTokenPrivilege(DWORD ProcessId,TCHAR *PrivilegeName,BOOL bEnablePrivilege);
void			ShowLastError(void);
int				WriteTextToRichEdit(HWND hRichEdit,TCHAR *fmt,...);
int				GetRectHeight(RECT *rc);
int				GetRectWidth(RECT *rc);
HANDLE			CopyTextToClipboard(TCHAR *szTextData);
void			CheckItem(HWND hwnd,BOOL bCheck);
BOOL			IsItemChecked(HWND hwnd);
BOOL			lShowWindow(HWND hwnd,BOOL bShowWindow);
void			EnumLoggedOnUsers(void);
TCHAR			*PrintComma(unsigned long nPrint);
TCHAR			*PrintCommaLargeNum(LARGE_INTEGER lPrint);
BOOL			CheckWildcardMatch(TCHAR *szWildcard,TCHAR *szString,BOOL bCaseSensitive);
void			ReplaceCharacters(TCHAR *str,char ch,char replacement);
TCHAR			*GetToken(TCHAR *ptr,TCHAR *Buffer,TCHAR *BufferLength);
HRESULT			DecodeFriendlyPath(TCHAR *szFriendlyPath,TCHAR *szParsingPath);
void			AddGripperStyle(UINT *fStyle,BOOL bAddGripper);
void			AddWindowStyle(HWND hwnd,UINT fStyle,BOOL bAdd);
void			ReplaceCharacterWithString(TCHAR *szBaseString,TCHAR *szOutput,UINT cchMax,TCHAR chToReplace,TCHAR *szReplacement);
void			CenterWindow(HWND hParent,HWND hChild);
TCHAR			*ReplaceSubString(TCHAR *szString,TCHAR *szSubString,TCHAR *szReplacement);
void			UpdateToolbarBandSizing(HWND hRebar,HWND hToolbar);

#endif