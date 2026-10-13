#include "Paths.h"
#include <wx/dir.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/app.h>

namespace {
	const wxString RES = wxT("res");
	wxString temporary; // set by useTemporaryDir()

	/** Data directory of versions <= 2.0.4: the executable's folder. */
	void migrateLegacyData() {
		wxString legacy = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath();
		if (!wxDir::Exists(legacy + wxFileName::GetPathSeparator() + RES)) return;
		if (wxDir::Exists(Paths::dataDir() + wxFileName::GetPathSeparator() + RES)) return;
		Paths::copyTree(legacy + wxFileName::GetPathSeparator() + RES,
				Paths::dataDir() + wxFileName::GetPathSeparator() + RES);
	}
}

wxString Paths::dataDir() {
	if (!temporary.empty()) return temporary;
	return wxStandardPaths::Get().GetUserDataDir();
}

void Paths::useTemporaryDir() {
	temporary = wxFileName::GetTempDir() + wxFileName::GetPathSeparator()
			+ wxString::Format(wxT("MiniPlaner-%ld"), wxGetProcessId());
}

void Paths::removeTemporaryDir() {
	if (temporary.empty()) return;
	wxSetWorkingDirectory(wxFileName::GetTempDir());
	wxFileName::Rmdir(temporary, wxPATH_RMDIR_RECURSIVE);
}

void Paths::copyTree(const wxString& from, const wxString& to) {
	wxFileName::Mkdir(to, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
	wxDir dir(from);
	wxString name;
	for (bool ok = dir.GetFirst(&name); ok; ok = dir.GetNext(&name)) {
		wxString src = wxFileName(from, name).GetFullPath();
		wxString dst = wxFileName(to, name).GetFullPath();
		if (wxDir::Exists(src)) copyTree(src, dst);
		else wxCopyFile(src, dst, false);
	}
}

void Paths::init() {
	wxTheApp->SetAppName(wxT("MiniPlaner"));
#if defined(__UNIX__) && !defined(__WXOSX__)
	wxStandardPaths::Get().SetFileLayout(wxStandardPaths::FileLayout_XDG); // ~/.local/share/MiniPlaner
	// Relocatable install (e.g. AppImage): resources live in <exe dir>/../share/MiniPlaner.
	wxStandardPaths::Get().SetInstallPrefix(
			wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath() + wxT("/.."));
#endif
	wxFileName::Mkdir(Paths::dataDir(), wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
	migrateLegacyData();
	wxSetWorkingDirectory(Paths::dataDir());
}

wxString Paths::outputDir() {
	wxString dir = wxFileName(wxStandardPaths::Get().GetDocumentsDir(), wxT("MiniPlaner")).GetFullPath()
			+ wxFileName::GetPathSeparator() + wxT("output");
	wxFileName::Mkdir(dir, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
	return dir;
}
