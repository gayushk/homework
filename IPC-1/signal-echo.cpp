#include <iostream>
#include <signal.h>
#include <pwd.h>

void sig_hand(int sig, siginfo_t* info, void* cont) {
	pid_t pid = info->si_pid;
	uid_t uid = info->si_uid;
	auto* pw = getpwuid(uid);
	const char* user = pw ? pw->pw_name : "unknown";
	
	ucontext_t* uc = (ucontext_t*) cont;
       	unsigned long eip = uc->uc_mcontext.gregs[REG_RIP];
	unsigned long eax = uc->uc_mcontext.gregs[REG_RAX];
	unsigned long ebx = uc->uc_mcontext.gregs[REG_RBX];
	
	std::cout << "Received a SIGUSR1 signal from process [" << pid << "]execute by [" << uid << "] ([" << user << "])." << std::endl;
	std::cout << "State of the context: EIP = [" << eip << "], EAX = [" << eax << "], EBX = [" << ebx << "]." << std::endl;
	std::cout << std::endl;
}

int main() {
	struct sigaction sa {};
	sa.sa_sigaction = sig_hand;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, nullptr);
	raise(SIGUSR1);
	while(true) {
		sleep(10);
	}
	return 0;
}
