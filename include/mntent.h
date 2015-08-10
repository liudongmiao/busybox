#ifndef _MNTENT_H_
#define _MNTENT_H_

#include <stdio.h>

struct mntent
{
	char* mnt_fsname;
	char* mnt_dir;
	char* mnt_type;
	char* mnt_opts;
	int mnt_freq;
	int mnt_passno;
};

#ifdef __ANDROID__
#define setmntent	fopen
#define endmntent	fclose
#define addmntent(fp, mnt) (NULL)
#define hasmntopt(mnt, opt) (NULL)
struct mntent *getmntent(FILE *fp);
struct mntent *getmntent_r(FILE *fp, struct mntent *mntbuf,
			   char *buf, int buflen);
#else
extern FILE *setmntent(const char *filename, const char *type);
extern int endmntent(FILE *fp);
extern int addmntent(FILE *fp, const struct mntent *mnt);
extern char *hasmntopt(const struct mntent *mnt, const char *opt);
extern struct mntent *getmntent(FILE *fp);
extern struct mntent *getmntent_r(FILE *fp, struct mntent *mntbuf,
			   char *buf, int buflen);
#endif

#endif
