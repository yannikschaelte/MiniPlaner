#ifndef PATHS_H
#define PATHS_H

#include <wx/string.h>

/** Locations of user data, exports and the bundled manual. */
namespace Paths {
	/**
	 * Switch to the per-user data directory (created if missing), so that the
	 * relative `res/` paths used by the file handlers resolve there. Data of
	 * older versions stored next to the executable is copied over once.
	 */
	void init();
	/** Default folder for exports (<Documents>/MiniPlaner/output), created if missing. */
	wxString outputDir();
	/** Use a fresh temporary data directory instead of the per-user one (call before init()). */
	void useTemporaryDir();
	/** Delete the directory created by useTemporaryDir(), if any. */
	void removeTemporaryDir();
	/** The per-user data directory. */
	wxString dataDir();
	/** Copy a directory tree; existing files are kept. */
	void copyTree(const wxString& from, const wxString& to);
}

#endif /* PATHS_H */
