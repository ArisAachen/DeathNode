#include <linux/bpf.h>
#include <linux/ptrace.h>
#include <linux/version.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_core_read.h>

// 定义tracepoint参数结构体
struct sys_enter_execve_args {
    unsigned long long unused;
    long syscall_nr;            // 系统调用号
    const char *filename;       // 文件名
    const char *const *argv;    // 参数列表
    const char *const *envp;    // 环境变量列表
};

SEC("tracepoint/syscalls/sys_enter_execve")
int bpf_prog(struct sys_enter_execve_args *ctx) {
    char filename[256];
    bpf_probe_read_user_str(filename, sizeof(filename), ctx->filename);
    bpf_trace_printk(filename, sizeof(filename));
    return 0;
}

char _license[] SEC("license") = "GPL";