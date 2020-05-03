//
// Created by kekor on 22.04.2020.
//

#include <string>
#include <sstream>
#include <sys/types.h>
#include <aio.h>
#include <linux/aio_abi.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <bits/sigaction.h>
#include <cassert>
#include <thread>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include "syscalls.h"


#define FILES_AMOUNT    100
#define SIZE_TO_READ    64
#define ITERATIONS    10

#define EVENTS_AMOUNT   1024

int fileSize(int fd) {
    struct stat stat_buf;
    int rc = fstat(fd, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

std::string base = "../tests/cache/files/file";
std::string baseScript = "./tests/cache/files/file";

struct Value {
    int fd;
    size_t length;
    char* buffer;
};

void handler(int signal, siginfo_t *info, void *ptr) {
    struct Value* value = (struct Value*) info->si_value.sival_ptr;
    std::cout << "Handler!" << "[" << value->fd << "]" << std::endl;
    std::string data(value->buffer, value->length);
    std::cout << data << std::endl;
    return;
}


void test_signals() {
    struct sigaction sig_struct{};
    memset(&sig_struct, 0, sizeof(struct sigaction));

    sig_struct.sa_flags |= SA_SIGINFO;
    sig_struct.sa_sigaction = handler;
    sigset_t   set;
    sigemptyset(&set);
    sigaddset(&set, SIGRTMIN);
    sig_struct.sa_mask = set;
    sigaction(SIGRTMIN, &sig_struct, NULL);

    std::vector<int> files(FILES_AMOUNT, 0);
    int num = 0;
    for (int i = 0; i < files.size(); ++i) {
        files[i] = open((base + std::to_string(num++)).c_str(), O_RDONLY | O_DIRECT);
        assert(files[i] > 0);
    }

    struct Value values[FILES_AMOUNT];
    aiocb cb[FILES_AMOUNT];
    sigevent aio_sigevent[FILES_AMOUNT];
    for (int i = 0; i < files.size(); ++i) {
        int file = files[i];
        char *buffer = new char[SIZE_TO_READ];

        values[i] = {file, SIZE_TO_READ, buffer};

        memset(&aio_sigevent, 0, sizeof(sigevent));
        aio_sigevent[i].sigev_notify = SIGEV_SIGNAL;
        aio_sigevent[i].sigev_signo = SIGRTMIN;
        aio_sigevent[i].sigev_value.sival_ptr = (void*)&values[i];

        memset(&cb[i], 0, sizeof(aiocb));
        cb[i].aio_nbytes = SIZE_TO_READ;
        cb[i].aio_fildes = file;
        cb[i].aio_offset = 0;
        cb[i].aio_buf = buffer;
        cb[i].aio_sigevent = aio_sigevent[i];

        if (aio_read(&cb[i]) == -1) {
            std::cout << "Unable to create request!" << std::endl;
            close(file);
        }
    }

    for(;;);
}   // GNU - create thread for each file.

void test_linux_api() {
//    int fd = open("../tests/cache/files/file1", O_RDONLY | O_DIRECT);
//
//    struct iocb **list_of_iocb = new struct iocb*[1];
//    struct iocb cb[1];
//    memset(cb, 0, 1 * sizeof(iocb));
//
//    size_t size = fileSize(fd);
//    char *buf = static_cast<char*>(aligned_alloc(512, 512*4));
//
//    cb[0].aio_data = reinterpret_cast<__u64>(buf);
//    cb[0].aio_lio_opcode = IOCB_CMD_PREAD;
//    cb[0].aio_fildes = static_cast<__u32>(fd);
//    cb[0].aio_buf = reinterpret_cast<__u64>(buf);
//    cb[0].aio_nbytes = size;
//
//    list_of_iocb[0] = &cb[0];
//
//    aio_context_t ctx = 0;
//    auto err = io_setup(1, &ctx);
//    if (err < 0) {
//        PFATAL("io_setup()");
//    }
//
//    err = io_submit(ctx, 1, list_of_iocb);
//    if (err < 0) {
//        PFATAL("io_submit()");
//    }
//
//    struct io_event *events = new struct io_event[1];
//
//
//    auto amount = io_getevents(ctx, 1, 1, events, NULL);
//    assert(events[0].res>0);
//    if (amount < 0) {
//        PFATAL("io_getevents()");
//    }
//
//    std::cout << reinterpret_cast<char*>(events[0].data) << std::endl;


    int fd = open("../tests/cache/files/file1", O_RDONLY | O_DIRECT);
    struct iocb **list_of_iocb = new struct iocb*[1];
    struct iocb cb[1];
    memset(cb, 0, 1 * sizeof(iocb));
    //size_t size = fileSize(fd);
    size_t size = 512;
    char *buf = static_cast<char*>(aligned_alloc(512, 512*4));

    cb[0].aio_data = reinterpret_cast<__u64>(buf);
    cb[0].aio_lio_opcode = IOCB_CMD_PREAD;
    cb[0].aio_fildes = static_cast<__u32>(fd);
    cb[0].aio_buf = reinterpret_cast<__u64>(buf);
    cb[0].aio_nbytes = size;

    list_of_iocb[0] = &cb[0];

    aio_context_t ctx1 = 0;
    auto err = io_setup(10, &ctx1);
    if (err < 0) {
        return ;
    }

    auto e = errno;
    err = io_submit(ctx1, 10, list_of_iocb);
    if (err < 0) {
        auto e2 = errno;
        return ;
    }

    struct io_event *events = new struct io_event[1];
    auto amount = io_getevents(ctx1, 1, 1, events, NULL);
    assert(events[0].res > 0);
    if (amount < 0) {
        return;
    }


//    std::vector<int> fd(FILES_AMOUNT, 0);
//    int num = 0;
//    for (int i = 0; i < FILES_AMOUNT; ++i) {
//        fd[i] = open((base + std::to_string(num++)).c_str(), O_RDONLY | O_DIRECT);
//        if (num > 99) {
//            num = 0;
//        }
//        assert(fd[i] > 0);
//    }
//
//
//    struct iocb **list_of_iocb = new struct iocb*[FILES_AMOUNT];
//    struct iocb **list_of_iocb2 = new struct iocb*[FILES_AMOUNT];
//    struct iocb cb[FILES_AMOUNT];
//    memset(cb, 0, FILES_AMOUNT * sizeof(iocb));
//
//    for (int i = 0; i < FILES_AMOUNT; ++i) {
//        size_t size = fileSize(fd[i]);
////        void *buf = new char[4096];
//        char *buf = static_cast<char*>(aligned_alloc(512, 512*4));
//
//
//        cb[i].aio_data = reinterpret_cast<__u64>(buf);
//        cb[i].aio_lio_opcode = IOCB_CMD_PREAD;
//        cb[i].aio_fildes = static_cast<__u32>(fd[i]);
//        cb[i].aio_buf = reinterpret_cast<__u64>(buf);
//        cb[i].aio_nbytes = size;
//
//        list_of_iocb[i] = &cb[i];
//        list_of_iocb2[i] = &cb[i];
//    }
//
//    aio_context_t ctx = 0;
//    auto err = io_setup(FILES_AMOUNT, &ctx);
//    if (err < 0) {
//        PFATAL("io_setup()");
//    }
//
//    err = io_submit(ctx, FILES_AMOUNT, list_of_iocb);
//    if (err < 0) {
//        PFATAL("io_submit()");
//    }
//
//
//
//    struct io_event *events = new struct io_event[FILES_AMOUNT];
//
//    size_t counter = 0;
//
//    while(counter < FILES_AMOUNT) {
//        auto amount = io_getevents(ctx, 1, 1, events, NULL);
//        if (amount < 0) {
//            PFATAL("io_getevents()");
//        }
//
//        counter += amount;
//        std::cout << reinterpret_cast<char*>(events[0].data) << std::endl;
//    }


    //io_destroy(ctx);

//    for (int i = 0; i < FILES_AMOUNT; ++i) {
//        close(fd[i]);
//    }
}

void test_sync_read() {
    std::vector<int> fd(FILES_AMOUNT, 0);
    int num = 0;
    for (int i = 0; i < FILES_AMOUNT; ++i) {
        fd[i] = open((base + std::to_string(num++)).c_str(), O_RDONLY | O_DIRECT );
        if (num > 99) {
            num = 0;
        }
        assert(fd[i] > 0);
    }

    for (int i = 0; i < FILES_AMOUNT; ++i) {
        size_t size = fileSize(fd[i]);
        char *buf = new char[size];
        read(fd[i], buf, size);
    }

    for (int i = 0; i < FILES_AMOUNT; ++i) {
        close(fd[i]);
    }
}



int main() {
    int nanosecondsCounter = 0;

    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    for (int i = 0; i < ITERATIONS; ++i) {
        start = std::chrono::steady_clock::now();
        test_linux_api();
        end = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        nanosecondsCounter += elapsed.count();
    }

    double average = (double)nanosecondsCounter / ITERATIONS;
    std::cout << "Average time: " << average << std::endl;

    return (0);
}