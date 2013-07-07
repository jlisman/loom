/*
Fuse filesystem implementation for use in loom (or else where).
Copyright (C) 2013 Commonwealth of Australia


This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

  gcc -Wall hello.c `pkg-config fuse --cflags --libs` -o hello
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define BUFFER_SIZE 10000000


struct loomfsData {
    //TODO: Needs to be generic talloc buffer
    uint8_t *buffer;
}

static void* loomfs_init(struct fuse_conn_info *conn)
{
    //TODO: Need to change this to the generic talloc type
    struct loomfsData *lfsD = malloc(sizeof(struct loomfsData));
    lfsD->buffer = malloc(BUFFER_SIZE);
    return lfsD;
}

static void loomfs_destroy(void *private)
{
    //TODO: Need to change this for generic talloc type
    struct loomfsData *lfsD = (struct loomfsData)private;
    free(lfsD->buffer);
    free(lfsD);
}


int get_hardlinks(const char *path)
{
    int numLinks = 1;
    //query for number of pcap files available and add to numLinks
    if(strcmp(path, "/")) {
        // count the configured captures and add it to numLinks
        // dummy below
        return numLinks + 1;
    }

    /*
    else {
        obtain count of "files directories" using specified filter. ie:
        if in srcaddr filter count would be the number of unique srcaddrs
    }
    */

    return numLinks;   
}


static int loomfs_getattr(const char *path, struct stat *stbuf)
{
    int res = 0;

    /*
    hard links = current dir + number of files
    created time = time of first packet
    modified time = last packet time
    access time = last packet time

    */

    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0555;
        stbuf->st_nlink = get_hardlinks(path);
    } else if (strcmp(path, hello_path) == 0) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(hello_str);
    } else
        res = -ENOENT;

    return res;
}

static int loomfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
             off_t offset, struct fuse_file_info *fi)
{
    (void) offset;
    (void) fi;

    if (strcmp(path, "/") != 0)
        return -ENOENT;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, hello_path + 1, NULL, 0);

    return 0;
}

static int loomfs_open(const char *path, struct fuse_file_info *fi)
{
    if (strcmp(path, hello_path) != 0)
        return -ENOENT;

    if ((fi->flags & 3) != O_RDONLY)
        return -EACCES;

    return 0;
}

static int loomfs_read(const char *path, char *buf, size_t size, off_t offset,
              struct fuse_file_info *fi)
{
    size_t len;
    (void) fi;
    if(strcmp(path, hello_path) != 0)
        return -ENOENT;

    len = strlen(hello_str);
    if (offset < len) {
        if (offset + size > len)
            size = len - offset;
        memcpy(buf, hello_str + offset, size);
    } else
        size = 0;

    return size;
}

static struct fuse_operations loomfs_oper = {
    .getattr    = loomfs_getattr,
    .readdir    = loomfs_readdir,
    .open       = loomfs_open,
    .read       = loomfs_read,
    .init       = loomfs_init,
    .destroy    = loomfs_destroy,
};

int main(int argc, char *argv[])
{
    return fuse_main(argc, argv, &loomfs_oper, NULL);
}
