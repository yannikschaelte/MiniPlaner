#include "UserData.h"
#include <wx/datetime.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/file.h>
#include "DemoData.h"
#include "Paths.h"
#include "file/DataFileHandler.h"

bool UserData::isFirstRun() {
	return !wxDir::Exists(DataFileHandler::RES);
}

void UserData::clearAll(bool backup) {
	if (!wxDir::Exists(DataFileHandler::RES)) return;
	if (backup) {
		wxString dir = Paths::dataDir() + wxT("/res.backup-") + wxDateTime::Now().Format(wxT("%Y%m%d-%H%M%S"));
		wxRenameFile(DataFileHandler::RES, dir);
	} else {
		wxFileName::Rmdir(DataFileHandler::RES, wxPATH_RMDIR_RECURSIVE);
	}
}

void UserData::loadDemo(bool backup) {
	clearAll(backup);
	for (unsigned i = 0; i < DEMO_FILE_COUNT; i++) {
		wxFileName file(DataFileHandler::RES + wxT("/") + wxString::FromUTF8(DEMO_FILES[i].path));
		file.Mkdir(wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
		wxFile out(file.GetFullPath(), wxFile::write);
		out.Write(DEMO_FILES[i].data, DEMO_FILES[i].size);
	}
}
