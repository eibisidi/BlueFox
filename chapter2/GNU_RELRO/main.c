#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <elf.h>

extern Elf64_Dyn  _DYNAMIC[];
extern Elf64_Addr _GLOBAL_OFFSET_TABLE_[];

Elf64_Addr	*got_ptr;
Elf64_Addr	*got_plt_ptr;
Elf64_Addr	*got_end_ptr;

//search .dynamic section for .got and .got.plt load address
void search_dynamic()
{
	Elf64_Dyn *dyn;
	Elf64_Xword pltrelsz;
	Elf64_Addr pltgot = 0;
	uint8_t bind_now = 0;

	for (dyn = _DYNAMIC; dyn->d_tag != DT_NULL; ++dyn)
	{
		if (dyn->d_tag == DT_PLTGOT)
			pltgot = dyn->d_un.d_ptr;

		if (dyn->d_tag == DT_FLAGS_1) {
			if (dyn->d_un.d_val & DF_1_NOW)
				bind_now = 1;
		}

		if (dyn->d_tag == DT_PLTRELSZ)
			pltrelsz  = dyn->d_un.d_val;
	}

	if (bind_now)
	{//no lazy bind allowed
		got_ptr = (Elf64_Addr*)(pltgot);
		got_plt_ptr = NULL;
	}
	else
	{
		got_ptr = _GLOBAL_OFFSET_TABLE_;
		got_plt_ptr = (Elf64_Addr*)(pltgot);
	}
	got_end_ptr = (Elf64_Addr*)((Elf64_Addr)got_ptr + pltrelsz);
}

int main()
{
	int i;
	Elf64_Addr *cur;
	Elf64_Addr dynamic;
	Elf64_Addr *printf_at_got, *printf_at_got_plt;

	search_dynamic();
	printf(".got section loaded at 0x%p\n", got_ptr);
	printf(".got.plt section loaded at 0x%p\n", got_plt_ptr);

	printf("printf() @%p\n", printf);
	printf("puts()	 @%p\n", puts);

	//search in .got and .got.plt to locate the printf() jump slot
	printf_at_got = printf_at_got_plt = NULL;

	if (!got_plt_ptr) {
		for (cur = got_ptr; cur != got_end_ptr; ++cur) {
			if (*cur == (Elf64_Addr)printf) {
				printf_at_got = cur;
				break;
			}
		}
	} else {
		for (cur = got_ptr; cur != got_plt_ptr; ++cur) {
			if (*cur == (Elf64_Addr)printf) {
				printf_at_got = cur;
				break;
			}
		}
		for (cur = got_plt_ptr; cur != got_end_ptr; ++cur) {
			if (*cur == (Elf64_Addr)printf) {
				printf_at_got_plt = cur;
				break;
			}
		}
	}

	if (!printf_at_got){
		printf("printf() is not in .got section!\n");
		return -1;
	}

	printf(".got	 jump slot @0x%p\n", printf_at_got);
	printf(".got.plt jump slot @0x%p\n", printf_at_got_plt);

	if (printf_at_got_plt) {
		//change .got.plt entry, call printf() will call puts() instead
		printf("going to change .got.plt entry\n");
		*printf_at_got_plt = (Elf64_Addr)puts;
		printf("after changing .got.plt entry, printf() is now @%p\n", printf);
		//revert change
		*printf_at_got_plt = (Elf64_Addr)printf;
	}

	//change .got entry
	printf("going to change .got entry\n");
	*printf_at_got = (Elf64_Addr)puts;
	printf("after changing .got entry, printf() is now @%p\n", printf);

	pause();
	return 0;
}

