#ifndef FIO_OS_SOLARIS_H
#define FIO_OS_SOLARIS_H

#include <sys/types.h>
#include <sys/fcntl.h>

#define FIO_HAVE_POSIXAIO
#define FIO_HAVE_SOLARISAIO
#define FIO_HAVE_FALLOCATE
#define FIO_HAVE_POSIXAIO_FSYNC

#define OS_MAP_ANON		(MAP_ANON)

typedef unsigned long os_cpu_mask_t;
typedef unsigned int os_random_state_t;

/*
 * FIXME
 */
static inline int blockdev_size(int fd, unsigned long long *bytes)
{
	return EINVAL;
}

static inline int blockdev_invalidate_cache(int fd)
{
	return EINVAL;
}

static inline unsigned long long os_phys_mem(void)
{
#if 0
	int mib[2] = { CTL_HW, HW_PHYSMEM };
	unsigned long long mem;
	size_t len = sizeof(mem);

	sysctl(mib, 2, &mem, &len, NULL, 0);
	return mem;
#else
	return 0;
#endif
}

static inline void os_random_seed(unsigned long seed, os_random_state_t *rs)
{
	srand(seed);
}

static inline long os_random_long(os_random_state_t *rs)
{
	long val;

	val = rand_r(rs);
	return val;
}

#define FIO_OS_DIRECTIO
extern int directio(int, int);
static inline int fio_set_odirect(int fd)
{
	if (directio(fd, DIRECTIO_ON) < 0)
		return errno;

	return 0;
}

#endif
