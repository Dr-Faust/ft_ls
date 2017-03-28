#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/print_includes/ft_printf.h"
# include <stat.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>

/*
** -a [LS_A]	to display hidden files, current and previous folders;
** -l [LS_L]	to get more details;
** -R [LS_RR]	recursively list subdirectories encountered;
** -r [LS_R]	Reverse the order of the sort to get reverse lexicographical
**				order or the oldest entries first (or largest files last, if
**				combined with sort by size;
** -t [LS_T]	to display by time modified;
** -d [LS_D]	to display current folder only;
** -g [LS_G]	o display the group name in the long (-l) format output;
** -1 [LS_1]	to display result on one column;
** -S [LS_SS]	to display files sorted by size;
** -s [LS_S]	to display the number of file system blocks actually used by
**				each file, in units of 512 bytes, where partial units are
**				rounded up to the next integer value;
*/

# define LS_A	1
# define LS_L	2
# define LS_RR	4
# define LS_R	8
# define LS_T	16
# define LS_D	32
# define LS_G	64
# define LS_1	128
# define LS_SS	256
# define LS_S	512

enum	{ERRNO, USAGE, MALL_ERR};

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

/*
**				mode	- [XSI] Mode of file;
**				nlink	- [XSI] Number of hard links;
**				uid		- [XSI] User ID of the file;
**				gid		- [XSI] Group ID of the file;
**				rdev	- [XSI] Device ID;
**				size	- [XSI] file size, in bytes;
**				time	- [XSI] Last data modification time;
**				ntime	- last data modification nsec;
**				blocks	- [XSI] blocks allocated for file;
*/

typedef struct			s_file
{
	mode_t				mode;
	nlink_t				nlink;
	uid_t				uid;
	gid_t				gid;
	dev_t				rdev;
	off_t				size;
	time_t				time;
	long				ntime;
	blkcnt_t			blocks;
	char				*name;
	char				full_path[PATH_MAX];
	t_list				list;
	struct s_file		*next;
}						t_file;

int						ft_error(char *str, int error);
int						ft_add_file(path[PATH_MAX], char *name, t_file **file);
int						ft_display(t_file *file, int flags, int flag, int argc);


#endif
