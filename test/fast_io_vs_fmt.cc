#include <fast_io.h>
#include <fast_io_device.h>
#include <fmt/os.h>
#include <chrono>
#include <functional>
#include <string_view>

fast_io::obuf_file fast_io_out("a.txt");

auto fmt_out = fmt::output_file("b.txt");

void run_fast_io() {
    const int RECORDS = 10000;
    auto      t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < RECORDS; ++i) {
        fast_io::io::print(
                fast_io_out, "Simple log message with one parameters, ", i);
    }
    auto t1 = std::chrono::high_resolution_clock::now();

    double span =
            std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t0)
                    .count();
    fmt::print(
            "fast_io, front latency: {:.1f} ns/msg average\n",
            (span / RECORDS) * 1e9);
}

void run_fmt() {
    const int RECORDS = 10000;
    auto      t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < RECORDS; ++i) {
        fmt_out.print("Simple log message with one parameters, {}", i);
    }
    auto t1 = std::chrono::high_resolution_clock::now();

    double span =
            std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t0)
                    .count();
    fmt::print(
            "fmt, front latency: {:.1f} ns/msg average\n",
            (span / RECORDS) * 1e9);
}

int main() {
    run_fmt();
    run_fast_io();
    
}
