/*-
 * Copyright (c) 2011 FUKAUMI Naoki.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

static void
printmac(char *buf)
{

    printf("%c%c:%c%c:%c%c:%c%c:%c%c:%c%c",
      *buf, *(buf + 1), *(buf + 2), *(buf + 3), *(buf + 4), *(buf + 5),
      *(buf + 6), *(buf + 7), *(buf + 8), *(buf + 9), *(buf + 10), *(buf + 11));
}

static void
usage(void)
{

    fprintf(stderr, "usage: tccgetserial [-b|-w]\n");
    exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
    int boff, bt, ch, fd, wifi, woff;
    char buf[33];

    bt = wifi = 0;
    while ((ch = getopt(argc, argv, "bw")) != -1) {
        switch (ch) {
        case 'b':
            bt = 1;
            break;
        case 'w':
            wifi = 1;
            break;
        default:
            usage();
        }
    }
    argc -= optind;
    argv += optind;

    if (bt & wifi)
        usage();

    if ((fd = open("/dev/block/ndda", O_RDONLY)) == -1)
        err(EXIT_FAILURE, "/dev/block/ndda");
    if (ioctl(fd, 0xf008, buf) == -1) {
        close(fd);
        err(EXIT_FAILURE, "ioctl(0xf008)");
    }
    close(fd);

    boff = woff = 0;
    if (buf[0] == 'F') {
        if (buf[1] == '1')
            woff = 4;
        else if (buf[1] == '2') {
            boff = 4;
            woff = 16;
        }
    }

    if (bt && boff != 0)
        printmac(&buf[boff]);
    else if (wifi && woff != 0)
        printmac(&buf[woff]);
    else if ((bt|wifi) == 0) {
        buf[32] = '\0';
        printf("serial number: %s\n", buf);
        printf("   bt address: ");
        if (boff != 0)
            printmac(&buf[boff]);
        else
            printf("N/A");
        printf("\n wlan address: ");
        if (woff != 0)
            printmac(&buf[woff]);
        else
            printf("N/A");
        printf("\n");
    } else
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
