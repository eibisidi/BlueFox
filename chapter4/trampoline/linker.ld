SECTIONS
{
	. = 0x400000,
	.text 
	: 
	{ *(.text) ;
	. = 0x10000000;
	 *(.textfar)
	}

}