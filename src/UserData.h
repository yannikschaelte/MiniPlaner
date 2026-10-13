#ifndef USERDATA_H
#define USERDATA_H

/** Operations on the user's data in the data directory (see Paths). */
namespace UserData {
	/** True if the data folder does not exist yet, i.e. the app is started for the first time. */
	bool isFirstRun();
	/** Replace all data by the demo data embedded in the executable. */
	void loadDemo(bool backup = true);
	/** Remove all data; with `backup` it is moved to a timestamped folder next to it instead. */
	void clearAll(bool backup = true);
}

#endif /* USERDATA_H */
