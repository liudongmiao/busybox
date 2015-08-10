#include <stdio.h>
#include <string.h>
#include "mntent.h"

#ifdef __ANDROID__
#pragma message("octal escapes is not supported")

extern int atoi(const char *str);

struct mntent *getmntent_r(FILE *fp, struct mntent *mntbuf,
			   char *buf, int buflen)
{
	char *tmp;

	if (!fgets(buf, buflen, fp)) {
		return NULL;
	}

	if (*buf == '#') {
		return NULL;
	}

	if (!(mntbuf->mnt_fsname = strtok(buf, " \t\n"))) {
		return NULL;
	}

	if (!(mntbuf->mnt_dir = strtok(NULL, " \t\n"))) {
		return NULL;
	};

	if (!(mntbuf->mnt_type = strtok(NULL, " \t\n"))) {
		return NULL;
	};

	if (!(mntbuf->mnt_opts = strtok(NULL, " \t\n"))) {
		return NULL;
	};

	tmp = strtok(NULL, " \t\n");
	mntbuf->mnt_freq = tmp ? atoi(tmp) : 0;

	tmp = strtok(NULL, " \t\n");
	mntbuf->mnt_passno = tmp ? atoi(tmp) : 0;

	return mntbuf;
}

struct mntent *getmntent(FILE *fp)
{
	static char buf[4096];
	static struct mntent mntbuf;
	return getmntent_r(fp, &mntbuf, buf, 4096);
}
#endif
