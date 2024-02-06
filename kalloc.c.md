运行程序：	make qemu

## 系统调用

### fork()

​	生成一个新的进程， 新进程复制父进程的文件描述符和栈信息， 子进程复制的文件描述符和父进程的文件共享同一个偏移量



### dup()

​	复制文件描述符， 共享同一个偏移量



### mknod()

​	创建一个引用设备的特殊文件， 与设备相关联的是主设备号和副设备号， 他们可以唯一的标识内核设备





## 用户级系统调用

### cd

```c
while(getcmd(buf, sizeof(buf)) >= 0){
    if(buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' '){
      // Chdir must be called by the parent, not the child.
      buf[strlen(buf)-1] = 0;  // chop \n
      if(chdir(buf+3) < 0)
        fprintf(2, "cannot cd %s\n", buf+3);
      continue;
    }
    if(fork1() == 0)
      runcmd(parsecmd(buf));
    wait(0);
  }
  exit(0);
}
```



## 命令行指令

### pstree	

> 展示当前运行的进程，以子树的形式

简单实现：

```c
#include "stdio.h"
#include "stdlib.h"
#include "dirent.h"

int arr[20000] = {0};

void printPid(char* pid){
	if(!arr[atoi(pid)])	return;
	arr[atoi(pid)]=0;
	printf("+-----|\n");
	printf("\t|--(%s)  ", pid);
	char pid_file[256];
	sprintf(pid_file, "/proc/%s/task", pid);


	// 读取名字
	char pid_name[256];
	sprintf(pid_name, "/proc/%s/status", pid);
	FILE* fp = fopen(pid_name, "r");
	// char *fgets( char *buf, int n, FILE *fp );
	char tmp[128];
	fgets(tmp, 7, fp);
	char buf[128];
	fgets(buf, 30, fp);
	printf("  %s  ", buf);

	// printf("%s\n", pid_file);
	
	// // Open Son`s dir
	DIR *dir = opendir(pid_file);
	if(dir==NULL)	printf("Opendir Error...\n");
	struct dirent *entry;

	entry = readdir(dir);
	entry = readdir(dir);
	entry = readdir(dir);
	int flag = 1;
    
    // 读取目录
	while((entry = readdir(dir)) != NULL){
		if(flag){
			printf("\t|-------------------------------|\n");
			flag = 0;
		}
		// printf("arr[atoi(entry->d_name)] is %d", arr[atoi(entry->d_name)]);
		// if(arr[atoi(entry->d_name) ]){
		// 	printf("son: ");
		// 	arr[atoi(entry->d_name)] = 0;
		// 	printPid(entry->d_name);

		// }
		// printf("\n");

		printf("\t\t\t\t");
		// 子pid
		printf("\t|--%s  ", entry->d_name);

		// 子pid的名字
		// 读取名字
		sprintf(pid_name, "/proc/%s/status", pid);
		fp = fopen(pid_name, "r");
		// char *fgets( char *buf, int n, FILE *fp );
		fgets(tmp, 7, fp);
		fgets(buf, 100, fp);
		printf("  %s  ", buf);
		

		
		// printf("%s  ", entry->d_name);
	}
	close(fp);
	// printf("\t|-------------------------------|\n");
	// printf("father\n");

}

int Pstree(int pid, int num_sort, int version){
	const char *dir_path = "/proc";
	DIR *dir = opendir(dir_path);

	if(dir == NULL)
		printf("Proc is Error...\n");

	struct dirent *entry;
	while((entry = readdir(dir)) != NULL){
		if(entry->d_name[0]>='0' && entry->d_name[0]<='9')
			arr[atoi(entry->d_name)] = 1;
	}

	for(int i = 1; i < 2000; i++){
		char c_pid[100];
		sprintf(c_pid, "%d", i);
		printPid(c_pid);
	}


	close(dir);
}	

int main(int argc, char* argv[]){
	
	int pid = 0;
	int num_sort = 0;
	int version = 0;

	Pstree(1,1,1);

	

	return 0;
}

```









## 文件

实质：	每一个文件底部都有自己的inode（索引结点）	每个链接都由一个条目组成， 包括文件名和inode引用。 inode保存有关文件的元数据（包括类型、长度、文件内容在磁盘上的位置， 以及指向文件的链接数）

### 文件重定向

**实质：**	先将0号文件描述符关闭， 再调用open打开目标文件， 将0号文件描述符分配给该文件， 				实现文件的重定向



​	`2>&1`	实现将报错消息显示在文件中	（告诉shell， 2号是一号的副本）

​	









## sh.c

```c
// Shell.
// 一个单纯的shell文件  属于用户不属于内核

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

// Parsed command representation
#define EXEC  1
#define REDIR 2
#define PIPE  3
#define LIST  4
#define BACK  5

#define MAXARGS 10

struct cmd {
  int type;
};

struct execcmd {
  int type;
  char *argv[MAXARGS];
  char *eargv[MAXARGS];
};

struct redircmd {
  int type;
  struct cmd *cmd;
  char *file;
  char *efile;
  int mode;
  int fd;
};

struct pipecmd {
  int type;
  struct cmd *left;
  struct cmd *right;
};

struct listcmd {
  int type;
  struct cmd *left;
  struct cmd *right;
};

struct backcmd {
  int type;
  struct cmd *cmd;
};

int fork1(void);  // Fork but panics on failure.
void panic(char*);
struct cmd *parsecmd(char*);

// Execute cmd.  Never returns.
__attribute__((noreturn))
void
runcmd(struct cmd *cmd)
{
  int p[2];
  struct backcmd *bcmd;
  struct execcmd *ecmd;
  struct listcmd *lcmd;
  struct pipecmd *pcmd;
  struct redircmd *rcmd;

  if(cmd == 0)
    exit(1);

  switch(cmd->type){
  default:
    panic("runcmd");

  case EXEC:
    ecmd = (struct execcmd*)cmd;
    if(ecmd->argv[0] == 0)
      exit(1);
    exec(ecmd->argv[0], ecmd->argv);
    fprintf(2, "exec %s failed\n", ecmd->argv[0]);
    break;

  case REDIR:	// 重定向
    rcmd = (struct redircmd*)cmd;
          // IO重定向： 先将0号文件描述符关闭， 然后打开文件，此时分配的为0号描述符， 						即改变了读取的位置
    close(rcmd->fd);
    if(open(rcmd->file, rcmd->mode) < 0){
      fprintf(2, "open %s failed\n", rcmd->file);
      exit(1);
    }
    runcmd(rcmd->cmd);
    break;

  case LIST:
    lcmd = (struct listcmd*)cmd;
    if(fork1() == 0)
      runcmd(lcmd->left);
    wait(0);
    runcmd(lcmd->right);
    break;

   //	通过
  case PIPE:
          
    pcmd = (struct pipecmd*)cmd;
    if(pipe(p) < 0)
      panic("pipe");
          //	左端调用fork和runcmd
    if(fork1() == 0){
      close(1);
      dup(p[1]);
      close(p[0]);
      close(p[1]);
      runcmd(pcmd->left);
    }
          //	左端调用fork和runcmd
    if(fork1() == 0){
      close(0);
      dup(p[0]);
      close(p[0]);
      close(p[1]);
      runcmd(pcmd->right);
    }
    close(p[0]);
    close(p[1]);
    wait(0);
    wait(0);
    break;

  case BACK:
    bcmd = (struct backcmd*)cmd;
    if(fork1() == 0)
      runcmd(bcmd->cmd);
    break;
  }
  exit(0);
}

int
getcmd(char *buf, int nbuf)
{
  fprintf(2, "$ ");
  memset(buf, 0, nbuf);
  gets(buf, nbuf);
  if(buf[0] == 0) // EOF
    return -1;
  return 0;
}

int
main(void)
{
  static char buf[100];
  int fd;

  // Ensure that three file descriptors are open.
  while((fd = open("console", O_RDWR)) >= 0){
    if(fd >= 3){
      close(fd);
      break;
    }
  }

  // Read and run input commands.
  while(getcmd(buf, sizeof(buf)) >= 0){
    if(buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' '){
      // Chdir must be called by the parent, not the child.
      buf[strlen(buf)-1] = 0;  // chop \n
      if(chdir(buf+3) < 0)
        fprintf(2, "cannot cd %s\n", buf+3);
      continue;
    }
    if(fork1() == 0)
      runcmd(parsecmd(buf));
    wait(0);
  }
  exit(0);
}

void
panic(char *s)
{
  fprintf(2, "%s\n", s);
  exit(1);
}

int
fork1(void)
{
  int pid;

  pid = fork();
  if(pid == -1)
    panic("fork");
  return pid;
}

//PAGEBREAK!
// Constructors

struct cmd*
execcmd(void)
{
  struct execcmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = EXEC;
  return (struct cmd*)cmd;
}

struct cmd*
redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd)
{
  struct redircmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = REDIR;
  cmd->cmd = subcmd;
  cmd->file = file;
  cmd->efile = efile;
  cmd->mode = mode;
  cmd->fd = fd;
  return (struct cmd*)cmd;
}

struct cmd*
pipecmd(struct cmd *left, struct cmd *right)
{
  struct pipecmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = PIPE;
  cmd->left = left;
  cmd->right = right;
  return (struct cmd*)cmd;
}

struct cmd*
listcmd(struct cmd *left, struct cmd *right)
{
  struct listcmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = LIST;
  cmd->left = left;
  cmd->right = right;
  return (struct cmd*)cmd;
}

struct cmd*
backcmd(struct cmd *subcmd)
{
  struct backcmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = BACK;
  cmd->cmd = subcmd;
  return (struct cmd*)cmd;
}
//PAGEBREAK!
// Parsing

char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>&;()";

int
gettoken(char **ps, char *es, char **q, char **eq)
{
  char *s;
  int ret;

  s = *ps;
  while(s < es && strchr(whitespace, *s))
    s++;
  if(q)
    *q = s;
  ret = *s;
  switch(*s){
  case 0:
    break;
  case '|':
  case '(':
  case ')':
  case ';':
  case '&':
  case '<':
    s++;
    break;
  case '>':
    s++;
    if(*s == '>'){
      ret = '+';
      s++;
    }
    break;
  default:
    ret = 'a';
    while(s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
      s++;
    break;
  }
  if(eq)
    *eq = s;

  while(s < es && strchr(whitespace, *s))
    s++;
  *ps = s;
  return ret;
}

int
peek(char **ps, char *es, char *toks)
{
  char *s;

  s = *ps;
  while(s < es && strchr(whitespace, *s))
    s++;
  *ps = s;
  return *s && strchr(toks, *s);
}

struct cmd *parseline(char**, char*);
struct cmd *parsepipe(char**, char*);
struct cmd *parseexec(char**, char*);
struct cmd *nulterminate(struct cmd*);

struct cmd*
parsecmd(char *s)
{
  char *es;
  struct cmd *cmd;

  es = s + strlen(s);
  cmd = parseline(&s, es);
  peek(&s, es, "");
  if(s != es){
    fprintf(2, "leftovers: %s\n", s);
    panic("syntax");
  }
  nulterminate(cmd);
  return cmd;
}

struct cmd*
parseline(char **ps, char *es)
{
  struct cmd *cmd;

  cmd = parsepipe(ps, es);
  while(peek(ps, es, "&")){
    gettoken(ps, es, 0, 0);
    cmd = backcmd(cmd);
  }
  if(peek(ps, es, ";")){
    gettoken(ps, es, 0, 0);
    cmd = listcmd(cmd, parseline(ps, es));
  }
  return cmd;
}

struct cmd*
parsepipe(char **ps, char *es)
{
  struct cmd *cmd;

  cmd = parseexec(ps, es);
  if(peek(ps, es, "|")){
    gettoken(ps, es, 0, 0);
    cmd = pipecmd(cmd, parsepipe(ps, es));
  }
  return cmd;
}

struct cmd*
parseredirs(struct cmd *cmd, char **ps, char *es)
{
  int tok;
  char *q, *eq;

  while(peek(ps, es, "<>")){
    tok = gettoken(ps, es, 0, 0);
    if(gettoken(ps, es, &q, &eq) != 'a')
      panic("missing file for redirection");
    switch(tok){
    case '<':
      cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
      break;
    case '>':
      cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREATE|O_TRUNC, 1);
      break;
    case '+':  // >>
      cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREATE, 1);
      break;
    }
  }
  return cmd;
}

struct cmd*
parseblock(char **ps, char *es)
{
  struct cmd *cmd;

  if(!peek(ps, es, "("))
    panic("parseblock");
  gettoken(ps, es, 0, 0);
  cmd = parseline(ps, es);
  if(!peek(ps, es, ")"))
    panic("syntax - missing )");
  gettoken(ps, es, 0, 0);
  cmd = parseredirs(cmd, ps, es);
  return cmd;
}

struct cmd*
parseexec(char **ps, char *es)
{
  char *q, *eq;
  int tok, argc;
  struct execcmd *cmd;
  struct cmd *ret;

  if(peek(ps, es, "("))
    return parseblock(ps, es);

  ret = execcmd();
  cmd = (struct execcmd*)ret;

  argc = 0;
  ret = parseredirs(ret, ps, es);
  while(!peek(ps, es, "|)&;")){
    if((tok=gettoken(ps, es, &q, &eq)) == 0)
      break;
    if(tok != 'a')
      panic("syntax");
    cmd->argv[argc] = q;
    cmd->eargv[argc] = eq;
    argc++;
    if(argc >= MAXARGS)
      panic("too many args");
    ret = parseredirs(ret, ps, es);
  }
  cmd->argv[argc] = 0;
  cmd->eargv[argc] = 0;
  return ret;
}

// NUL-terminate all the counted strings.
struct cmd*
nulterminate(struct cmd *cmd)
{
  int i;
  struct backcmd *bcmd;
  struct execcmd *ecmd;
  struct listcmd *lcmd;
  struct pipecmd *pcmd;
  struct redircmd *rcmd;

  if(cmd == 0)
    return 0;

  switch(cmd->type){
  case EXEC:
    ecmd = (struct execcmd*)cmd;
    for(i=0; ecmd->argv[i]; i++)
      *ecmd->eargv[i] = 0;
    break;

  case REDIR:
    rcmd = (struct redircmd*)cmd;
    nulterminate(rcmd->cmd);
    *rcmd->efile = 0;
    break;

  case PIPE:
    pcmd = (struct pipecmd*)cmd;
    nulterminate(pcmd->left);
    nulterminate(pcmd->right);
    break;

  case LIST:
    lcmd = (struct listcmd*)cmd;
    nulterminate(lcmd->left);
    nulterminate(lcmd->right);
    break;

  case BACK:
    bcmd = (struct backcmd*)cmd;
    nulterminate(bcmd->cmd);
    break;
  }
  return cmd;
}
```



## kalloc.c

### kalloc()

> kmem.freelist 是一个可用的页表空间链表	将其的头节点作为分配的内存返回

```c
// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *
kalloc(void)
{
  struct run *r;

  acquire(&kmem.lock);
  r = kmem.freelist;
  if(r)
    kmem.freelist = r->next;
  release(&kmem.lock);

  if(r)
    memset((char*)r, 5, PGSIZE); // fill with junk
  return (void*)r;
}
```



## proc.h

`struck proc`

```c
struct proc {
  struct spinlock lock;

  // p->lock must be held when using these:
  enum procstate state;        // Process state
  struct proc *parent;         // Parent process
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  int xstate;                  // Exit status to be returned to parent's wait
  int pid;                     // Process ID

  // these are private to the process, so p->lock need not be held.
  uint64 kstack;               // Virtual address of kernel stack
  uint64 sz;                   // Size of process memory (bytes)
  pagetable_t pagetable;       // User page table
  uint tracemask;
  pagetable_t kpagetable;      // Kernel pagetable
  struct trapframe *trapframe; // data page for trampoline.S
    // 用于上下文切换，如进程和进程/线程间切换	（保证了并行）
  struct context context;      // swtch() here to run process
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)

 
};
```



## proc.c	

### proc_pagetable()

> 创建一个线程内的空页表

```C
// Create a user page table for a given process,
// with no user memory, but with trampoline pages.
pagetable_t
proc_pagetable(struct proc *p)
{
  pagetable_t pagetable;

  // An empty page table.
  pagetable = uvmcreate();
  if(pagetable == 0)
    return 0;

  // map the trampoline code (for system call return)
  // at the highest user virtual address.
  // only the supervisor uses it, on the way
  // to/from user space, so not PTE_U.
    // 将TRAMPOLINE 映射到虚拟地址的最高位
  if(mappages(pagetable, TRAMPOLINE, PGSIZE,
              (uint64)trampoline, PTE_R | PTE_X) < 0){
    uvmfree(pagetable, 0);
    return 0;
  }
  // map the trapframe just below TRAMPOLINE, for trampoline.S.
    //// 将TRAPFRAME 映射到虚拟地址的第二位
  if(mappages(pagetable, TRAPFRAME, PGSIZE,
              (uint64)(p->trapframe), PTE_R | PTE_W) < 0){
    uvmunmap(pagetable, TRAMPOLINE, 1, 0);
    uvmfree(pagetable, 0);
    return 0;
  }

  return pagetable;
}
```



### allocproc()

```C
static struct proc*
allocproc(void)
{
  struct proc *p;

  for(p = proc; p < &proc[NPROC]; p++) {
    acquire(&p->lock);
    if(p->state == UNUSED) {	//查找一个空闲的进程
      goto found;
    } else {
      release(&p->lock);
    }
  }
  return 0;

found:
  p->pid = allocpid();

  // Allocate a trapframe page.
  if((p->trapframe = (struct trapframe *)kalloc()) == 0){
    release(&p->lock);
    return 0;
  }

  // An empty user page table.
  p->pagetable = proc_pagetable(p);
  if(p->pagetable == 0){
    freeproc(p);
    release(&p->lock);
    return 0;
  }

  // Alloc a new page table for user
  // 为进程分配一个专属页表
  p->kpagetable = ukvminit();
  if(p->kpagetable == 0){
    freeproc(p);
    release(&p->lock);
    return 0;
  }
	// 为进程分配一个内核所用的堆栈列表
  uint64 va = KSTACK((int) (p - proc));
  pte_t pa = kvmpa(va);
  memset((void *)pa, 0, PGSIZE); // 初始化kernel stack
    // 将堆栈地址映射到页表上
  ukvmmap(p->kpagetable, va, (uint64)pa, PGSIZE, PTE_R | PTE_W);
  
  p->kstack = va;

  // Set up new context to start executing at forkret,
  // which returns to user space.
  memset(&p->context, 0, sizeof(p->context));
  p->context.ra = (uint64)forkret;	//内核执行forkret函数,转移控制权
  p->context.sp = p->kstack + PGSIZE;

  return p;
}
```



### scheduler()

```c
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  
  c->proc = 0;
  for(;;){
    // Avoid deadlock by ensuring that devices can interrupt.
    intr_on();
    
    int found = 0;
    for(p = proc; p < &proc[NPROC]; p++) {
      acquire(&p->lock);
      if(p->state == RUNNABLE) {
        // Switch to chosen process.  It is the process's job
        // to release its lock and then reacquire it
        // before jumping back to us.
        p->state = RUNNING;
        c->proc = p;

        // 切换新进程的内核页表		(RISCV 的规定)
        w_satp(MAKE_SATP(p->kpagetable));
        sfence_vma();

        swtch(&c->context, &p->context);

        // Process is done running for now.
        // It should have changed its p->state before coming back.
        kvminithart();
        c->proc = 0;

        found = 1;
      }
      release(&p->lock);
    }
```





## vm.c

### ukvminit()

> 对内核态页表的初始化

```c
// 内核态页表
pagetable_t ukvminit() {

  // 得到一个空页表
  pagetable_t kpagetable = (pagetable_t) kalloc();	
  memset(kpagetable, 0, PGSIZE);
	
  ukvmmap(kpagetable, UART0, UART0, PGSIZE, PTE_R | PTE_W);

  ukvmmap(kpagetable, VIRTIO0, VIRTIO0, PGSIZE, PTE_R | PTE_W);

  ukvmmap(kpagetable, CLINT, CLINT, 0x10000, PTE_R | PTE_W);

  ukvmmap(kpagetable, PLIC, PLIC, 0x400000, PTE_R | PTE_W);

  ukvmmap(kpagetable, KERNBASE, KERNBASE, (uint64)etext-KERNBASE, PTE_R | PTE_X);

  ukvmmap(kpagetable, (uint64)etext, (uint64)etext, PHYSTOP-(uint64)etext, PTE_R | PTE_W);

  ukvmmap(kpagetable, TRAMPOLINE, (uint64)trampoline, PGSIZE, PTE_R | PTE_X);

  return kpagetable;
}
```



### walk()

> 返回最后一页页表地址， 用于修改查询	
>
> 查表由MMU 执行

```c
// Return the address of the PTE in page table pagetable
// that corresponds to virtual address va.  If alloc!=0,
// create any required page-table pages.
//
// The risc-v Sv39 scheme has three levels of page-table
// pages. A page-table page contains 512 64-bit PTEs.
// A 64-bit virtual address is split into five fields:
//   39..63 -- must be zero.
//   30..38 -- 9 bits of level-2 index.
//   21..29 -- 9 bits of level-1 index.
//   12..20 -- 9 bits of level-0 index.
//    0..11 -- 12 bits of byte offset within the page.
pte_t *
walk(pagetable_t pagetable, uint64 va, int alloc)
{
  if(va >= MAXVA)
    panic("walk");
	// 页表的分级查询，由高到低
  for(int level = 2; level > 0; level--) {
    pte_t *pte = &pagetable[PX(level, va)];
    if(*pte & PTE_V) {	//验证地址是否有效
      pagetable = (pagetable_t)PTE2PA(*pte);
    } else {
      if(!alloc || (pagetable = (pde_t*)kalloc()) == 0)
        return 0;
      memset(pagetable, 0, PGSIZE);
        // 将地址设置为有效， 有效位设为1
      *pte = PA2PTE(pagetable) | PTE_V;
    }
  }
  return &pagetable[PX(0, va)];
}
```



### mappages()

```c
int
mappages(pagetable_t pagetable, uint64 va, uint64 size, uint64 pa, int perm)
{
  uint64 a, last;
  pte_t *pte;

  a = PGROUNDDOWN(va);	//调到页表首
  last = PGROUNDDOWN(va + size - 1);
  for(;;){
    if((pte = walk(pagetable, a, 1)) == 0)
      return -1;
    if(*pte & PTE_V)
      panic("remap");
    *pte = PA2PTE(pa) | perm | PTE_V;
    if(a == last)
      break;
    a += PGSIZE;
    pa += PGSIZE;
  }
  return 0;
}
```



### walkaddr()

>  适用于用户态， 将虚拟地址转换为物理地址

```c
// Look up a virtual address, return the physical address,
// or 0 if not mapped.
// Can only be used to look up user pages.
uint64
walkaddr(pagetable_t pagetable, uint64 va)
{
  pte_t *pte;
  uint64 pa;
	
    // 判断是否越界
  if(va >= MAXVA)
    return 0;
	// 通过walk查询到最后一页的地址
  pte = walk(pagetable, va, 0);
  if(pte == 0)
    return 0;
  if((*pte & PTE_V) == 0)
    return 0;
  if((*pte & PTE_U) == 0)
    return 0;
    // 通过宏转换为实际物理地址
  pa = PTE2PA(*pte);
  return pa;
}
```



### ukvmmap()

> 对内核态页表的映射

```c
// 内核态页表
void
ukvmmap(pagetable_t kpagetable, uint64 va, uint64 pa, uint64 sz, int perm)
{
  if(mappages(kpagetable, va, sz, pa, perm) != 0)
    panic("ukvmmap");
}
```



## memlayout.h

```c
// MAXVA代表的是虚拟地址的最高地址，表示将蹦床页面分配到最高的一页，保证能找到
#define TRAMPOLINE (MAXVA - PGSIZE)

// TRAMPOLINE 用于处理异常、中断和系统调用，决定控制权
#define TRAPFRAME (TRAMPOLINE - PGSIZE)
```





# Lab

### No.1

sleep.c

```c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char*argv[]){
    if(argc != 2){
        fprintf(2, "Not Enough...\n");
        exit(1);   
    }
    sleep(atoi(argv[1])*10);
    exit(0);
}
```



pingpong.c

```c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    int p[2];
    pipe(p);
    int pid = fork();
    if(pid==0){
        char buf[10];
        read(p[0], buf, sizeof(buf));
        close(p[0]);
        printf("%d : received ", getpid());
        printf(buf);
        printf("\n");

        write(p[1], "pong", 5);

    }
    else{
        char buf[10];
        write(p[1], "ping", 5);
        close(p[1]);
        wait(0);
        read(p[0], buf, sizeof(buf));
        printf("%d : received ", getpid());
        printf(buf);
        printf("\n");
    }
    // wait(0);
    exit(0);
}
```





find.c

```c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
find(char* path, const char* target){
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: argument error... %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0 ){
        fprintf(2, "cannot fstat  %s error...\n", path);
        close(fd);
        return;
    }

     // 判断目录长度                    // 为何可以不加括号
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
        printf("ls: path too long\n");
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        // 目录中文件的个数
        if(de.inum == 0)    continue;

        // 将整个儿目录拷贝到p 中
        memmove(p, de.name, DIRSIZ);    //添加路径名称
        p[DIRSIZ] = 0;                  // 字符串结束标志

        if(stat(buf, &st) < 0){
            printf("find: cannot stat %s\n", buf);
            continue;
        }

        // 判断题目要求
        if(st.type==T_DIR && strcmp(p, ".") != 0 && strcmp(p, "..")!=0){
            find(p, target);
        }
        else if(strcmp(p, target) == 0){
            printf("%s ", buf);
        }
                // }
                // if((strcmp(fmtname(buf), target)) == 0){
                //     printf("same !!!\n");
                //     printf("%s  ", fmtname(buf));
                // }
            
    }    
    close(fd);           
}

int main(int argc, char* argv[]){
    if(argc<3){
        fprintf(1, "argument num error...\n");
    }
    else{
        find(argv[1], argv[2]);
    }
    exit(0);
}
```





# System_syy



## pstree	

> 查询当前活动的进程 

```c
#include "stdio.h"
#include "stdlib.h"
#include "dirent.h"

int arr[20001] = {0};

void printPid(char* pid){
	if(!arr[atoi(pid)])	return;
	arr[atoi(pid)]=0;
	printf("+-----|\n");
	printf("\t|--(%s)  ", pid);
	char pid_file[256];
	sprintf(pid_file, "/proc/%s/task", pid);


	// 读取名字
	char pid_name[256];
	sprintf(pid_name, "/proc/%s/status", pid);
	FILE* fp = fopen(pid_name, "r");
	// char *fgets( char *buf, int n, FILE *fp );
	char tmp[128];
	fgets(tmp, 7, fp);
	char buf[128];
	fgets(buf, 30, fp);
	printf("  %s  ", buf);

	// printf("%s\n", pid_file);
	
	// // Open Son`s dir
	DIR *dir = opendir(pid_file);
	if(dir==NULL)	printf("Opendir Error...\n");
	struct dirent *entry;

	entry = readdir(dir);
	entry = readdir(dir);
	entry = readdir(dir);
	int flag = 1;
	while((entry = readdir(dir)) != NULL){
		if(flag){
			printf("\t|-------------------------------|\n");
			flag = 0;
		}
		// printf("arr[atoi(entry->d_name)] is %d", arr[atoi(entry->d_name)]);
		// if(arr[atoi(entry->d_name) ]){
		// 	printf("son: ");
		// 	arr[atoi(entry->d_name)] = 0;
		// 	printPid(entry->d_name);

		// }
		// printf("\n");

		printf("\t\t\t\t");
		// 子pid
		printf("\t|--%s  ", entry->d_name);

		// 子pid的名字
		// 读取名字
		sprintf(pid_name, "/proc/%s/status", pid);
		fp = fopen(pid_name, "r");
		// char *fgets( char *buf, int n, FILE *fp );
		fgets(tmp, 7, fp);
		fgets(buf, 100, fp);
		printf("  %s  ", buf);
		

		
		// printf("%s  ", entry->d_name);
	}
	close(fp);
	// printf("\t|-------------------------------|\n");
	// printf("father\n");

}

int Pstree(int pid, int num_sort, int version){
	const char *dir_path = "/proc";
	DIR *dir = opendir(dir_path);

	if(dir == NULL)
		printf("Proc is Error...\n");

	struct dirent *entry;
	while((entry = readdir(dir)) != NULL){
		if(entry->d_name[0]>='0' && entry->d_name[0]<='9')
			arr[atoi(entry->d_name)] = 1;
	}

	for(int i = 1; i < 2000; i++){
		char c_pid[100];
		sprintf(c_pid, "%d", i);
		printPid(c_pid);
	}


	close(dir);
}	

int main(int argc, char* argv[]){
	
	int pid = 0;
	int num_sort = 0;
	int version = 0;

	Pstree(1,1,1);

	

	return 0;
}

```

