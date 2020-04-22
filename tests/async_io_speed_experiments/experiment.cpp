//
// Created by kekor on 22.04.2020.
//

#include <string>
#include <sstream>
#include <sys/types.h>
#include <aio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <bits/sigaction.h>
#include <cassert>
#include <thread>


#define FILES_AMOUNT    10
#define SIZE_TO_READ    64

std::string base = "../tests/cache/files/file";

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

void thread_handler(union sigval val) {
    std::cout << "Thread_handler!" << std::endl;
    return;
}

void test_signals_with_list() {
    struct sigaction sig_struct{};
    memset(&sig_struct, 0, sizeof(struct sigaction));

    sig_struct.sa_flags |= SA_SIGINFO;
    sig_struct.sa_sigaction = handler;

    sigaction(SIGUSR1, &sig_struct, NULL);

    std::vector<int> files(10, 0);
    char num = '0';
    for (int i = 0; i < files.size(); ++i) {
        files[i] = open((base + num++).c_str(), O_RDONLY);
        assert(files[i] > 0);
    }



    int file = files[0];
    char *buffer = new char[SIZE_TO_READ];


    sigevent aio_sigevent{};
    memset(&aio_sigevent, 0, sizeof(sigevent));
    aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    aio_sigevent.sigev_signo = SIGUSR1;
    aio_sigevent.sigev_value.sival_int = file;

    aiocb cb{};
    memset(&cb, 0, sizeof(aiocb));
    cb.aio_nbytes = SIZE_TO_READ;
    cb.aio_fildes = file;
    cb.aio_offset = 0;
    cb.aio_buf = buffer;
    cb.aio_sigevent = aio_sigevent;



    if (aio_read(&cb) == -1) {
        std::cout << "Unable to create request!" << std::endl;
        close(file);
    }

    while (aio_error(&cb) == EINPROGRESS) {
        std::cout << "Working..." << std::endl;
    }

    int numBytes = aio_return(&cb);
    std::cout << buffer << std::endl;

    if (numBytes != -1)
        std::cout << "Success!" << std::endl;
    else
        std::cout << "Error!" << std::endl;

    delete[] buffer;
    close(file);
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

    std::vector<int> files(10, 0);
    char num = '0';
    for (int i = 0; i < files.size(); ++i) {
        files[i] = open((base + num++).c_str(), O_RDONLY);
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

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "aaaaaaaaaaaaa" << std::endl;


//    if (numBytes != -1)
//        std::cout << "Success!" << std::endl;
//    else
//        std::cout << "Error!" << std::endl;
//
//    delete[] buffer;
//    close(file);
}


void test_threads() {
    int file = open("../tests/cache/files/file1", O_RDONLY);
    char *buffer = new char[SIZE_TO_READ];


    sigevent aio_sigevent{};
    memset(&aio_sigevent, 0, sizeof(sigevent));
    aio_sigevent.sigev_notify = SIGEV_THREAD;
    aio_sigevent.sigev_notify_function = thread_handler;
    aio_sigevent.sigev_value.sival_ptr = (void*)buffer;

    aiocb cb{};
    memset(&cb, 0, sizeof(aiocb));
    cb.aio_nbytes = SIZE_TO_READ;
    cb.aio_fildes = file;
    cb.aio_offset = 0;
    cb.aio_buf = buffer;
    cb.aio_sigevent = aio_sigevent;



    if (aio_read(&cb) == -1) {
        std::cout << "Unable to create request!" << std::endl;
        close(file);
    }

    while (aio_error(&cb) == EINPROGRESS) {
        std::cout << "Working..." << std::endl;
    }

    int numBytes = aio_return(&cb);
    std::cout << buffer << std::endl;

    if (numBytes != -1)
        std::cout << "Success!" << std::endl;
    else
        std::cout << "Error!" << std::endl;

    delete[] buffer;
    close(file);
}



int main() {
    test_signals();
    std::thread workerThr(test_signals);
    workerThr.detach();
    std::this_thread::sleep_for(std::chrono::seconds(20));
    std::cout << "aaaaaaaaaaaaa" << std::endl;
//    std::cout << "END" << std::endl;
//    test_threads();
    return (0);
}